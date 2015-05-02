#include <iostream>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TRegexp.h"
#include "TSystem.h"

using namespace std;

int checkCMS3( TString samplePath = "" ) {

  if( samplePath == "" ) {
	cout << "Please provide a path to a CMS3 ntuple!" << endl;
	return 1;
  }

  int nProblems = 0;
  bool isMerged = false;
  bool isSUSY   = false;
  bool isScan   = false;

  TChain* chain = new TChain("Events");

  cout << endl;


  /////////////////////////////////////////////////////////////////////////////////
  // File counting

  // Make a chain, and count the number of files in the directory
  const unsigned int nMergedFiles = chain->Add( samplePath + "/merged_ntuple*.root");
  const unsigned int nUnmergedFiles = chain->Add( samplePath + "/ntuple*.root");

  // Check to see if these are merged or unmerged ntuples
  if(      nMergedFiles>0  && nUnmergedFiles==0 ) {
	isMerged = true;
	cout << "I found " << nMergedFiles << " merged ntuple files in this directory." << endl;
  }
  else if( nMergedFiles==0 && nUnmergedFiles>0  ) {
	isMerged = false;
	cout << "I found " << nUnmergedFiles << " unmerged ntuple files in this directory." << endl;
  }
  else if( nMergedFiles==0 && nUnmergedFiles==0 ) {
	cout << "Sorry, I couldn't find any CMS3 ntuples in this directory!" << endl;
	return 1;
  }
  else if( nMergedFiles>0  && nUnmergedFiles>0  ) {
	cout << "This doesn't make sense -- it looks like there are both merged and unmerged ntuples in this directory!" << endl;
	cout << "That shouldn't happen, so I'm exiting..." << endl;
	return 1;
  }
  else {
	cout << "Something went terribly wrong when I tried to count the files in this directory. Exiting!" << endl;
	return 1;
  }


  /////////////////////////////////////////////////////////////////////////////////
  // Set up a few branches, and read in some key values

  chain->SetMakeClass(1);
  
  vector<TString> cms3tag;
  vector<TString> dataset;
  vector<TString> sparm_names;
  vector<float>   sparm_values;
  
  TBranch* branch_CMS3tag;
  TBranch* branch_dataset = chain->GetBranch(chain->GetAlias("evt_dataset"));
  TBranch* branch_sparmnames;
  TBranch* branch_sparmvals;

  if( chain->GetAlias("evt_CMS3tag") != 0 ) branch_CMS3tag = chain->GetBranch(chain->GetAlias("evt_CMS3tag"));
  else branch_CMS3tag = chain->GetBranch(chain->GetAlias("evt_CMS2tag"));

  branch_CMS3tag->SetAddress(    &cms3tag      );
  branch_dataset->SetAddress(    &dataset      );

  branch_dataset->GetEntry(1);
  TString dataset_name = dataset.at(0);

  TRegexp massScan("[mM][a-zA-Z]+-[0-9]+to[0-9]+");
  if( dataset_name.Contains(massScan)) isScan = true;
  if( dataset_name.Contains("SMS") )   isSUSY = true;

  if( isSUSY && isMerged ) {
	branch_sparmnames = chain->GetBranch(chain->GetAlias("sparm_names"));
	branch_sparmvals  = chain->GetBranch(chain->GetAlias("sparm_values"));
	branch_sparmnames->SetAddress( &sparm_names  );
	branch_sparmvals->SetAddress(  &sparm_values );
	branch_sparmnames->GetEntry(1);
	branch_sparmvals->GetEntry(1);
  }
  
  /////////////////////////////////////////////////////////////////////////////////
  // Check CMS3 tag

  branch_CMS3tag->GetEntry(0);
  TString tagtext = cms3tag.at(0);

  printf("\nCMS3 tag: \033[96m%s \033[0m\n", tagtext.Data());

  
  /////////////////////////////////////////////////////////////////////////////////
  // Event counting

  cout << "\n================ Event counts ================================\n" << endl;

  // Read from nEvts branch
  Long64_t nEvts_branch = 0;
  if( isMerged ) {
	nEvts_branch = (Long64_t)chain->GetMaximum("evt_nEvts");
	cout << "Number in \"nEvts\" branch: " << nEvts_branch << endl;
  }

  // Count using chain->GetEntries()
  cout << "Total events in files:    ";
  const Long64_t nEvts_chain = chain->GetEntries();
  cout << nEvts_chain << endl;

  // Get event count from DAS
  cout << "Event count from DAS:     ";
  TString Evts_das = gSystem->GetFromPipe( "python das_client.py --query=\"dataset= "+dataset_name+" | grep dataset.nevents\" | tail -1" );
  const Long64_t nEvts_das = Evts_das.Atoll();
  cout << nEvts_das << endl;

  // Check to see if the numbers match up
  if( nEvts_chain==nEvts_das ) {
	if( !isMerged ) printf("           \033[92m Matched \033[0m\n");
	else if( isMerged && nEvts_chain==nEvts_branch ) printf("           \033[92m Matched \033[0m\n");
	else {
	  printf("          \033[91m  MISMATCH!  \033[0m\n");
	  nProblems++;
	}
  }
  else {
	printf("          \033[91m  MISMATCH!  \033[0m\n");
	nProblems++;
  }
  
  // Breakdown by filename
  cout << "\nNumber of events by file:" << endl;
  TObjArray *fileList = chain->GetListOfFiles();
  TIter fileIter(fileList);
  TFile *currentFile = 0;
  TRegexp shortname("[mergd_]*ntuple_[0-9]+.root");

  while(( currentFile = (TFile*)fileIter.Next() )) {
	TFile *file = new TFile( currentFile->GetTitle() );
	TTree *tree = (TTree*)file->Get("Events");
	TString filename = file->GetName();
	Long64_t nEvts_file = tree->GetEntries();
	printf( "%28s:  %8lld\n", filename(shortname).Data(), nEvts_file );
  }



  /////////////////////////////////////////////////////////////////////////////////
  // Check CMS3 post-processing variables (if this is a merged sample)

  cout << "\n\n============ Post-processing variables ============================" << endl;

  if( isMerged ) {
	// Check for branches with values set to zero
	cout << "\nChecking for events with important values set to zero:" << endl;
	Long64_t nZeros_xsec     = chain->GetEntries("evt_xsec_incl==0");
	cout << "Cross-section: ";
	if( nZeros_xsec == 0 ) printf("\033[92mNone found\033[0m\n");
	else {
	  printf("\033[91m%lld events with zeros!\033[0m\n", nZeros_xsec);
	  nProblems++;
	}
	Long64_t nZeros_kfact    = chain->GetEntries("evt_kfactor==0");
	cout << "k factor:      ";
	if( nZeros_kfact == 0 ) printf("\033[92mNone found\033[0m\n");
	else {
	  printf("\033[91m%lld events with zeros!\033[0m\n", nZeros_kfact);
	  nProblems++;
	}
	Long64_t nZeros_filteff  = chain->GetEntries("evt_filt_eff==0");
	cout << "Filter eff:    ";
	if( nZeros_filteff == 0 ) printf("\033[92mNone found\033[0m\n");
	else {
	  printf("\033[91m%lld events with zeros!\033[0m\n", nZeros_filteff);
	  nProblems++;
	}
	Long64_t nZeros_scale1fb = chain->GetEntries("evt_scale1fb==0");
	cout << "scale1fb:      ";
	if( nZeros_scale1fb == 0 ) printf("\033[92mNone found\033[0m\n");
	else {
	  printf("\033[91m%lld events with zeros!\033[0m\n", nZeros_scale1fb);
	  nProblems++;
	}

	// Make sure the value of scale1fb is consistent with the other numbers
	cout << "\nChecking values for consistency:" << endl;
	cout << " Number of events = " << nEvts_chain << endl;
	double xsec = chain->GetMaximum("evt_xsec_incl");
	cout << "    Cross section = " << xsec << endl;
	double kfact = chain->GetMaximum("evt_kfactor");
	cout << "         k factor = " << kfact << endl;
	double filteff = chain->GetMaximum("evt_filt_eff");
	cout << "Filter efficiency = " << filteff << endl;
	double scale1fb = chain->GetMaximum("evt_scale1fb");
	cout << "         Scale1fb = " << scale1fb << endl;

	double test_scale1fb = 1000.*xsec*filteff*kfact / double(nEvts_chain);
	// cout << "test_scale1fb: " << test_scale1fb << ". Consistency: " << (test_scale1fb - scale1fb) / scale1fb << endl;
	if( ((test_scale1fb - scale1fb) / scale1fb) < 0.000001 ) printf("                \033[92m CONSISTENT \033[0m\n");
	else {
	  printf("                \033[91m INCONSISTENT! \033[0m\n");
	  nProblems++;
	}

  } // end "if( isMerged )"
  else cout << "\nThis is an unmerged sample. Skipping checks on postprocessing branches..." << endl;


  /////////////////////////////////////////////////////////////////////////////////
  // Sparm checks

  cout << "\n\n============ Sparm branches ============================" << endl;	

  if( isSUSY && isMerged ) {

	if( isScan ) {
	  cout << "\nThis file appears to have a range of sparm values.\nI'm not equipped to handle that; please check the values by eye:" << endl;
	  chain->Draw("sparm_values");
	}
	else {
	  cout << "\nFound these sparm values:" << endl;
	  int nSparmVals = sparm_values.size();
	  for( int i=0; i<nSparmVals; i++ )  printf("%10s = %7.1f\n", sparm_names.at(i).Data(), sparm_values.at(i) );
	}

  }
  else if( !isSUSY) cout << "\nThis doesn't appear to be a SUSY sample. Skipping checks on sparm branches..." << endl;
  else if( !isMerged ) cout << "\nThis SUSY sample isn't merged. Skipping checks on sparm branches..." << endl;



  /////////////////////////////////////////////////////////////////////////////////
  // Summary
  
  cout << "\n\n=============== RESULTS =========================" << endl;	
  cout << "\nProblems found:";
  if (nProblems==0) printf("\033[92m 0 \033[0m\n\n");
  else printf("\033[91m %d \033[0m\n\n", nProblems);
  return nProblems;
}


#ifndef __CINT__
int main()
{
  checkCMS3("");
  return 0;
}
#endif
