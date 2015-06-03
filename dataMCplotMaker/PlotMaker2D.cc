#include "PlotMaker2D.h"
#include "PlotMakingTools.h"

void PlotMaker2D(TH2F* hist, std::string options_string){

  //Turn "options" string into vector of strings, one parm each
  std::vector <std::string> Options = GetParms(options_string);  

  //Default values of user-adjustable parameters
  string outputName = "2Dplot.txt";
  bool doOverflow = true;
  string title = ""; 
  string Xaxis = "";
  string Yaxis = "";

  //Loop over options and change default settings to user-defined settings
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("outputName") < Options[i].length()) outputName = getString(Options[i], "outputName");
    else if (Options[i].find("noOverflow") < Options[i].length()) doOverflow = false;
    else if (Options[i].find("setTitle") < Options[i].length()) title = getString(Options[i], "setTitle"); 
    else if (Options[i].find("Xaxis") < Options[i].length()) Xaxis = getString(Options[i], "Xaxis"); 
    else if (Options[i].find("Yaxis") < Options[i].length()) Yaxis = getString(Options[i], "Yaxis"); 
    else cout << "Warning: Option not recognized!  Option: " << Options[i] << endl;
  }

  //Fix right margin (too much space)
  gStyle->SetPadRightMargin(0.04); 

  //Declare canvas
  TCanvas *canvas = new TCanvas("canvas");

  //Turn off text box
  gStyle->SetOptStat(0);

  //Text marker size
  hist->SetMarkerSize(1.7);

  //Set precision
  gStyle->SetPaintTextFormat(".3f"); 

  //Set title
  if (title != "") hist->SetTitle(title.c_str()); 

  //Set axis titles;
  if (Xaxis != "") hist->GetXaxis()->SetTitle(Xaxis.c_str());
  if (Yaxis != "") hist->GetYaxis()->SetTitle(Yaxis.c_str());

  //Draw it
  hist->Draw("TEXTE"); 

  //Save it
  canvas->Print(Form("%s.pdf", outputName.c_str())); 

  //Print Warning
  if (doOverflow) std::cout << "Warning!  PlotMaker2D does not handle your overflow (yet!)!!" << std::endl;

  delete canvas;

}
