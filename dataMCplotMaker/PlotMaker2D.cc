#include "PlotMaker2D.h"
#include "PlotMakingTools.h"

void PlotMaker2D(TH2D* hist, std::string options_string){
  TH2F* blah = (TH2F*)hist->Clone();
  PlotMaker2D(blah, options_string); 
}

void PlotMaker2D(TH2F* hist, std::string options_string){

  //Turn "options" string into vector of strings, one parm each
  std::vector <std::string> Options = GetParms(options_string);  

  //Default values of user-adjustable parameters
  string outputName = "2Dplot.txt";
  bool doOverflow = true;
  string title = ""; 
  string Xaxis = "";
  string Yaxis = "";
  string sciNot = "";
  bool color = 0;
  bool text = 0; 

  //Loop over options and change default settings to user-defined settings
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("outputName") < Options[i].length()) outputName = getString(Options[i], "outputName");
    else if (Options[i].find("noOverflow") < Options[i].length()) doOverflow = false;
    else if (Options[i].find("setTitle") < Options[i].length()) title = getString(Options[i], "setTitle"); 
    else if (Options[i].find("Xaxis") < Options[i].length()) Xaxis = getString(Options[i], "Xaxis"); 
    else if (Options[i].find("Yaxis") < Options[i].length()) Yaxis = getString(Options[i], "Yaxis"); 
    else if (Options[i].find("sciNot") < Options[i].length()){ sciNot = getString(Options[i], "sciNot"); if (sciNot == "") cout << "Warning!  --sciNot requires an argument for the precision.  Ex: .2"; }
    else if (Options[i].find("color") < Options[i].length()) color = 1;
    else if (Options[i].find("text") < Options[i].length()) text = 1;
    else cout << "Warning: Option not recognized!  Option: " << Options[i] << endl;
  }

  //Fix right margin (too much space)
  if (!color) gStyle->SetPadRightMargin(0.04); 
  if ( color) gStyle->SetPadRightMargin(0.14); 

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

  //Set scientific notation if needed
  if (sciNot != "") gStyle->SetPaintTextFormat(Form("%sE", sciNot.c_str()));

  //Make it a contour plot

  //Draw it
  string opt = ""; 
  if (text) opt += "TEXTE";
  if (color) opt += "COLZ";
  hist->Draw(opt.c_str()); 

  //Save it
  canvas->Print(Form("%s.pdf", outputName.c_str())); 

  //Print Warning
  if (doOverflow) std::cout << "Warning!  PlotMaker2D does not handle your overflow (yet!)!!" << std::endl;

  delete canvas;

}
