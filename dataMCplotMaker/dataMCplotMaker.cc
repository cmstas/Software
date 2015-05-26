#include "dataMCplotMaker.h"

//Comparison to put smallest histogram on bottom of stack
bool Integral(PlotInfo plot1, PlotInfo plot2){
  return plot1.Plot->Integral(0,plot1.Plot->GetNbinsX()) < plot2.Plot->Integral(0,plot2.Plot->GetNbinsX());
}

//Needed for freaking vertical lines
void DrawVerticalLine(Double_t x){
  TLine l;
  l.SetLineStyle(2);
  l.SetLineWidth(2);
  l.SetLineColor(kGray+2);
  Double_t lm = gPad->GetLeftMargin();
  Double_t rm = 1.-gPad->GetRightMargin();
  Double_t tm = 1.-gPad->GetTopMargin();
  Double_t bm = gPad->GetBottomMargin();
  Double_t xndc = (rm-lm)*((x-gPad->GetUxmin())/(gPad->GetUxmax()-gPad->GetUxmin()))+lm;
  l.DrawLineNDC(xndc,bm,xndc,tm);
}

//Function to determine maximum of each histogram, including error bars.  Side = 1 left, 2 right, 3 both, 4 = overflow
TH1F *null = new TH1F("", "", 1,0,1);
float AdjustedMaximum(int side, std::vector <TH1F*> Plots, TH1F* data = null, std::vector <TH1F*> Signals = std::vector<TH1F*>()){
  int lowerBound = 1;
  if (side == 2) lowerBound = 0.5*Plots[0]->GetNbinsX()+1;
  int upperBound = Plots[0]->GetNbinsX();
  if (side == 1) upperBound = 0.5*Plots[0]->GetNbinsX()+1;
  if (side == 2) upperBound--;
  if (side == 4) lowerBound = Plots[0]->GetNbinsX(); 
  if (side == 4) upperBound = Plots[0]->GetNbinsX()+1; 
  int nbins = Plots[0]->GetNbinsX(); 
  if (nbins < 6){
    lowerBound = 1;
    upperBound = nbins;
  }
  vector <float> heights;
  for (int i = lowerBound; i < upperBound; i++){
    float temp = 0;
    for (unsigned int j = 0; j < Plots.size(); j++) temp += Plots[j]->GetBinContent(i);
    heights.push_back(temp);
  }
  if (Signals.size() > 0 && Signals[0]->GetEntries() > 0){
    for (int i = 1; i < Signals[0]->GetNbinsX(); i++){
      float temp = 0;
      for (unsigned int j = 0; j < Signals.size(); j++){
        temp += Signals[j]->GetBinContent(i);
      }
      heights.push_back(temp);
    }
  }
  std::sort( heights.begin(), heights.end() );
  float bkgd_height = heights[heights.size()-1];
  heights.clear();
  for (int i = lowerBound; i < upperBound; i++){
    heights.push_back(data->GetBinContent(i)+data->GetBinError(i));
  }
  std::sort( heights.begin(), heights.end() );
  float data_height = heights[heights.size()-1];
  return max(data_height, bkgd_height);
}

//Set style -- this is completely ripped off from TDRStyle.cc
void SetTDRStyle(){

  tdrStyleAG = new TStyle("tdrStyleAGAG","Style for P-TDR");

  // For the canvas:
  tdrStyleAG->SetCanvasBorderMode(0);
  tdrStyleAG->SetCanvasColor(kWhite);
  tdrStyleAG->SetCanvasDefH(550); //Height of canvas
  tdrStyleAG->SetCanvasDefW(600); //Width of canvas
  tdrStyleAG->SetCanvasDefX(0);   //Position on screen
  tdrStyleAG->SetCanvasDefY(0);

  // For the Pad:
  tdrStyleAG->SetPadBorderMode(0);
  tdrStyleAG->SetPadColor(kWhite);
  tdrStyleAG->SetPadGridX(false);
  tdrStyleAG->SetPadGridY(false);
  tdrStyleAG->SetGridColor(0);
  tdrStyleAG->SetGridStyle(3);
  tdrStyleAG->SetGridWidth(1);

  // For the frame:
  tdrStyleAG->SetFrameBorderMode(0);
  tdrStyleAG->SetFrameBorderSize(1);
  tdrStyleAG->SetFrameFillColor(0);
  tdrStyleAG->SetFrameFillStyle(0);
  tdrStyleAG->SetFrameLineColor(1);
  tdrStyleAG->SetFrameLineStyle(1);
  tdrStyleAG->SetFrameLineWidth(1);

  //For the histo:
  tdrStyleAG->SetHistLineColor(1);
  tdrStyleAG->SetHistLineWidth(2);

  tdrStyleAG->SetEndErrorSize(2);
  tdrStyleAG->SetMarkerStyle(20);

  //For the fit/function:
  tdrStyleAG->SetOptFit(1);
  tdrStyleAG->SetFitFormat("5.4g");
  tdrStyleAG->SetFuncColor(2);
  tdrStyleAG->SetFuncStyle(1);
  tdrStyleAG->SetFuncWidth(1);

  //For the date:
  tdrStyleAG->SetOptDate(0);

  //For the statistics box:
  tdrStyleAG->SetOptFile(0);
  tdrStyleAG->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyleAG->SetOptFit(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyleAG->SetStatColor(kWhite);
  tdrStyleAG->SetStatFont(42);
  tdrStyleAG->SetStatFontSize(0.025);
  tdrStyleAG->SetStatTextColor(1);
  tdrStyleAG->SetStatFormat("6.4g");
  tdrStyleAG->SetStatBorderSize(1);
  tdrStyleAG->SetStatH(0.1);
  tdrStyleAG->SetStatW(0.15);

  //Margins:
  tdrStyleAG->SetPadTopMargin(0.10);
  tdrStyleAG->SetPadBottomMargin(0.15);
  tdrStyleAG->SetPadLeftMargin(0.15);
  tdrStyleAG->SetPadRightMargin(0.04);

  //For the Global title:
  tdrStyleAG->SetOptTitle(1);
  tdrStyleAG->SetTitleFont(42);
  tdrStyleAG->SetTitleColor(1);
  tdrStyleAG->SetTitleTextColor(1);
  tdrStyleAG->SetTitleFillColor(10);
  tdrStyleAG->SetTitleFontSize(0.05);
  tdrStyleAG->SetTitleX(0.5); // Set the position of the title box
  tdrStyleAG->SetTitleY(0.985); // Set the position of the title box
  tdrStyleAG->SetTitleAlign(23);
  tdrStyleAG->SetTitleStyle(0);
  tdrStyleAG->SetTitleBorderSize(0);
  tdrStyleAG->SetTitleFillColor(0);

  //For the axis titles:
  tdrStyleAG->SetTitleColor(1, "XYZ");
  tdrStyleAG->SetTitleFont(42, "XYZ");
  tdrStyleAG->SetTitleSize(0.035, "XYZ");
  tdrStyleAG->SetTitleOffset(1.20, "X");
  tdrStyleAG->SetTitleOffset(1.10, "Y"); 

  //For the axis labels:
  tdrStyleAG->SetLabelColor(1, "XYZ");
  tdrStyleAG->SetLabelFont(42, "XYZ");
  tdrStyleAG->SetLabelOffset(0.007, "XYZ");
  tdrStyleAG->SetLabelSize(0.035, "XYZ");

  //For the axis:
  tdrStyleAG->SetAxisColor(1, "XYZ");
  tdrStyleAG->SetStripDecimals(kTRUE);
  tdrStyleAG->SetTickLength(0.03, "XYZ");
  tdrStyleAG->SetNdivisions(510, "XYZ");
  tdrStyleAG->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyleAG->SetPadTickY(1);

  //Change for log plots:
  tdrStyleAG->SetOptLogx(0);
  tdrStyleAG->SetOptLogy(0);
  tdrStyleAG->SetOptLogz(0);

  //Postscript options:
  tdrStyleAG->SetPaperSize(20.,20.);
  tdrStyleAG->cd();
}

void dataMCplotMaker(TH1F* Data, std::vector <TH1F*> Backgrounds, std::vector <string> Titles, std::string titleIn, std::string title2In, std::string options_string, std::vector <TH1F*> Signals, std::vector <string> SignalTitles, std::vector <Color_t> color_input){

  char* title = (char *)alloca(titleIn.size() + 1);
  memcpy(title, titleIn.c_str(), titleIn.size() + 1);

  char* title2 = (char *)alloca(title2In.size() + 1);
  memcpy(title2, title2In.c_str(), title2In.size() + 1);

  bool noData = false;
  if (Data->GetEntries() == 0) noData = true;

  bool use_signals = true;
  if (Signals.size() == 0) use_signals = false;
  if (Signals.size() == 1 && Signals[0]->GetEntries() == 0) use_signals = false;

  //Turn "options" string into vector of strings, one parm each
  std::vector <std::string> Options = GetParms(options_string);  

  //Default values of all user-adjustable parameters
  bool linear = 0;
  bool nostack = 0;
  bool noFill = 0;
  bool normalize = 0;
  bool doOverflow = 1;
  bool showXaxisUnit = 1;
  std::string xAxisLabel = "M_{T}";
  std::string energy = "13";
  std::string lumi = "10.0";
  std::string yAxisLabel = "Entries";
  std::string yAxisUnit = "";
  std::string yAxisOverride = "";
  std::string xAxisUnit = "GeV";
  std::string xAxisOverride = "";
  std::string dataName = "data";
  std::string topYaxisTitle = "data/SM";
  std::string overrideHeader = "";
  std::string type = "CMS Preliminary ";
  std::string outputName = "data_MC_plot";
  bool preserveBackgroundOrder = 0;
  bool preserveSignalOrder = 0;
  bool showDivisionLabel = 1;
  float setMaximum = -1;
  float setMinimum = -1;
  float legendUp = 0;
  float legendRight = 0;
  float legendTextSize = 0.04;
  vector <float> vLines;
  vector <float> hLines;
  bool doHalf = 0;
  Int_t nDivisions = -1;
  bool noLegend = false;
  bool png = false;
  bool dots = false;
  std::string datacolor = "";

  //Loop over options and change default settings to user-defined settings
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("isLinear") < Options[i].length()) linear = 1; 
    else if (Options[i].find("preserveBackgroundOrder") < Options[i].length()) preserveBackgroundOrder = 1; 
    else if (Options[i].find("noStack") < Options[i].length()) nostack = 1; 
    else if (Options[i].find("noFill") < Options[i].length()) noFill = 1;
    else if (Options[i].find("normalize") < Options[i].length()) normalize = 1; 
    else if (Options[i].find("preserveSignalOrder") < Options[i].length()) preserveSignalOrder = 1; 
    else if (Options[i].find("png") < Options[i].length()) png = true;
    else if (Options[i].find("noDivisionLabel") < Options[i].length()) showDivisionLabel = 0; 
    else if (Options[i].find("noLegend") < Options[i].length()) noLegend = 1; 
    else if (Options[i].find("noOverflow") < Options[i].length()) doOverflow = 0; 
    else if (Options[i].find("noXaxisUnit") < Options[i].length()) showXaxisUnit = 0; 
    else if (Options[i].find("divHalf") < Options[i].length()) doHalf = 1; 
    else if (Options[i].find("energy") < Options[i].length()) energy = getString(Options[i], "energy");
    else if (Options[i].find("lumi") < Options[i].length()) lumi = getString(Options[i], "lumi");
    else if (Options[i].find("yAxisLabel") < Options[i].length()) yAxisLabel = getString(Options[i], "yAxisLabel");
    else if (Options[i].find("yAxisUnit") < Options[i].length()) yAxisUnit = getString(Options[i], "yAxisUnit");
    else if (Options[i].find("yAxisOverride") < Options[i].length()) yAxisOverride = getString(Options[i], "yAxisOverride");
    else if (Options[i].find("xAxisLabel") < Options[i].length()) xAxisLabel = getString(Options[i], "xAxisLabel");
    else if (Options[i].find("xAxisUnit") < Options[i].length()) xAxisUnit = getString(Options[i], "xAxisUnit");
    else if (Options[i].find("xAxisOverride") < Options[i].length()) xAxisOverride = getString(Options[i], "xAxisOverride");
    else if (Options[i].find("dataName") < Options[i].length()) dataName = getString(Options[i], "dataName");
    else if (Options[i].find("dataColor") < Options[i].length()) datacolor = getString(Options[i], "dataColor");
    else if (Options[i].find("topYaxisTitle") < Options[i].length()) topYaxisTitle = getString(Options[i], "topYaxisTitle");
    else if (Options[i].find("type") < Options[i].length()) type = getString(Options[i], "type");
    else if (Options[i].find("overrideHeader") < Options[i].length()) overrideHeader = getString(Options[i], "overrideHeader");
    else if (Options[i].find("outputName") < Options[i].length()) outputName = getString(Options[i], "outputName");
    else if (Options[i].find("vLine") < Options[i].length()) vLines.push_back(atof( getString(Options[i], "vLine").c_str() ));
    else if (Options[i].find("hLine") < Options[i].length()) hLines.push_back(atof( getString(Options[i], "hLine").c_str() ));
    else if (Options[i].find("setMaximum") < Options[i].length()) setMaximum = atof( getString(Options[i], "setMaximum").c_str() );
    else if (Options[i].find("legendUp") < Options[i].length()) legendUp = atof( getString(Options[i], "legendUp").c_str() );
    else if (Options[i].find("legendRight") < Options[i].length()) legendRight = atof( getString(Options[i], "legendRight").c_str() );
    else if (Options[i].find("legendTextSize") < Options[i].length()) legendTextSize = atof( getString(Options[i], "legendTextSize").c_str() );
    else if (Options[i].find("setMinimum") < Options[i].length()) setMinimum = atof( getString(Options[i], "setMinimum").c_str() );
    else if (Options[i].find("nDivisions") < Options[i].length()) nDivisions = atoi( getString(Options[i], "nDivisions").c_str() );
    else if (Options[i].find("drawDots") < Options[i].length()) dots = true; 
    else cout << "Warning: Option not recognized!  Option: " << Options[i] << endl;
  }

  //Decode data color
  Color_t dataColor = kBlack;
  if (datacolor != ""){
    std::transform(datacolor.begin(), datacolor.end(), datacolor.begin(), ::tolower); 
    if (datacolor == "kred" || datacolor == "red") dataColor = kRed;
    if (datacolor == "kblue" || datacolor == "blue") dataColor = kBlue;
    if (datacolor == "kgreen" || datacolor == "green") dataColor = kGreen;
    if (datacolor == "korange" || datacolor == "orange") dataColor = kOrange;
    if (datacolor == "kcyan" || datacolor == "cyan") dataColor = kCyan;
    if (datacolor == "kmagenta" || datacolor == "magenta") dataColor = kMagenta;
  }

  //Set Style
  SetTDRStyle();
  gStyle->SetOptStat(0);
  if (noData) gStyle->SetPadBottomMargin(.12);
  if (noData) gStyle->SetPadLeftMargin(.12);
  if (noData) gStyle->SetPadTopMargin(.07);

  //Make sure there is at least one background and enough titles
  if (Backgrounds.size() < 1){ 
    cout << "Error: Running with no backgrounds!" << endl;
    return;
  }
  if (Titles.size() != Backgrounds.size()) cout << "Warning! Wrong number of titles for your backgrounds!" << endl;
  while (Titles.size() < Backgrounds.size()){
    char* blank = new char[strlen("")+2];
    std::strcpy(blank, "");
    Titles.push_back(blank);
  }
  if (use_signals && SignalTitles.size() != Signals.size()) cout << "Warning! Wrong number of titles for your signals!" << endl;
  while (SignalTitles.size() < Signals.size()){
    char* blank = new char[strlen("")+2];
    std::strcpy(blank, "");
    SignalTitles.push_back(blank);
  }

  //Format Titles
  for (unsigned int i = 0; i < Titles.size(); i++){
    string title_temp = Titles[i];
    if (title_temp == "ttsl" || title_temp == "1ltop" || title_temp == "1lep" || title_temp == "singlelep" || title_temp == "singlelepton"){
       char* temp = new char[strlen("1 #font[12]{l} top")+2];
       std::strcpy(temp, "1 #font[12]{l} top");
       Titles[i] = temp;
    }
    if (title_temp == "ttdl" || title_temp == "2lep" || title_temp == "dilep" || title_temp == "dilepton"){
       char* temp = new char[strlen("t#bar{t}#rightarrow #font[12]{ll}")+2];
       std::strcpy(temp, "t#bar{t}#rightarrow #font[12]{ll}");
       Titles[i] = temp;
    }
    if (title_temp == "wjets"){
       char* temp = new char[strlen("W+jets")+2];
       std::strcpy(temp, "W+jets");
       Titles[i] = temp;
    }
  }

  //Do Overflow
  if (doOverflow == 1){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->SetBinContent(Backgrounds[i]->GetNbinsX(), Backgrounds[i]->GetBinContent(Backgrounds[i]->GetNbinsX())+Backgrounds[i]->GetBinContent(Backgrounds[i]->GetNbinsX()+1) );
    }
    for (unsigned int i = 0; i < Signals.size(); i++){
      Signals[i]->SetBinContent(Signals[i]->GetNbinsX(), Signals[i]->GetBinContent(Signals[i]->GetNbinsX())+Signals[i]->GetBinContent(Signals[i]->GetNbinsX()+1) );
    }
    if (!noData) Data->SetBinContent(Data->GetNbinsX(), Data->GetBinContent(Data->GetNbinsX())+Data->GetBinContent(Data->GetNbinsX()+1) );
  }

  std::vector <Color_t> Colors;

  //Set colors for histograms (this is my color scheme, probably needs changed for publishable plots)
  if (color_input.size() == 0 && use_signals == 0 && nostack == 0){ 
    Colors.push_back(kGreen+3);   
    Colors.push_back(kYellow-4); 
    Colors.push_back(kOrange+10);
    Colors.push_back(kCyan-4);
    Colors.push_back(kViolet+4);
  }
  if (color_input.size() == 0 && use_signals == 0 && nostack){ 
    Colors.push_back(kRed); 
    Colors.push_back(kBlue);
    Colors.push_back(kGreen+3);   
    Colors.push_back(kBlack);
    Colors.push_back(kViolet+4);
  }
  else if (color_input.size() == 0 && use_signals == 1){ 
    Colors.push_back(kGreen-3);
    Colors.push_back(kCyan);
    Colors.push_back(kOrange-4);
    Colors.push_back(kMagenta-8);
    Colors.push_back(kRed);
    Colors.push_back(kBlue);
    Colors.push_back(kGreen+3);
    Colors.push_back(kYellow-7);
  }
  else if (color_input.size() != 0){
    for (unsigned int i = 0; i < color_input.size(); i++){
      Colors.push_back(color_input[i]);
    }
  }

  //Sort Backgrounds, with Titles and Colors
  if (preserveBackgroundOrder == 0){
    std::vector<PlotInfo> myPlotInfo;
 
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      PlotInfo temp;
      temp.Plot = Backgrounds[i];
      temp.Title = Titles[i];
      if (color_input.size() > 0){
        temp.Color = color_input[i];
      }
      else{
        temp.Color = Colors[i];
      }
      myPlotInfo.push_back(temp);
    }

    std::sort(myPlotInfo.begin(), myPlotInfo.end(), Integral);
    Backgrounds.clear();
    Titles.clear();

    for (unsigned int i = 0; i < myPlotInfo.size(); i++){
      Backgrounds.push_back(myPlotInfo[i].Plot);
      Titles.push_back(myPlotInfo[i].Title);
      Colors[i] = myPlotInfo[i].Color;
    }
  }

  //Sort Signals, with Titles and Colors
  if (preserveSignalOrder == 0){
    std::vector<PlotInfo> myPlotInfo;
 
    for (unsigned int i = 0; i < Signals.size(); i++){
      PlotInfo temp;
      temp.Plot = Signals[i];
      temp.Title = SignalTitles[i];
      if (color_input.size() > 0){
        temp.Color = color_input[i+Backgrounds.size()];
      }
      else{
        temp.Color = Colors[i+Backgrounds.size()];
      }
      myPlotInfo.push_back(temp);
    }

    std::sort(myPlotInfo.begin(), myPlotInfo.end(), Integral);
    Signals.clear();
    SignalTitles.clear();

    for (unsigned int i = 0; i < myPlotInfo.size(); i++){
      Signals.push_back(myPlotInfo[i].Plot);
      SignalTitles.push_back(myPlotInfo[i].Title);
      if (color_input.size() > 0) Colors.push_back(myPlotInfo[i].Color);
      else Colors[Backgrounds.size()+i] = myPlotInfo[i].Color;  
    }
  }

  //Draw histogram with two pads
  TCanvas c0("c0", "c0");
  TPad* finPad[2];
  if (noData == false){
    c0.SetCanvasSize(600, 700);
    finPad[0] = new TPad("1", "1", 0.0, 0.0, 1.0, 0.84);
    if (!linear) finPad[0]->SetLogy();
    finPad[0]->SetTopMargin(0.05);
    finPad[0]->SetLeftMargin(0.12);
    finPad[0]->SetBottomMargin(0.11);
    finPad[1] = new TPad("2", "2", 0.0, 0.83, 1.0, 1.0);
    finPad[1]->SetLeftMargin(0.12);
    finPad[0]->Draw();
    finPad[1]->Draw();
    finPad[0]->cd();
  }
  if (noData == true){
    c0.SetCanvasSize(600, 550);
    finPad[0] = new TPad();
    finPad[1] = new TPad();
    if (!linear) c0.SetLogy();
  }

  //--------First pad: histogram------------
  //Stack of backgrounds
  THStack *stack = new THStack("stack", ""); 
  Data->SetMarkerStyle(20);
  Data->UseCurrentStyle();
  if(noFill == 0 && Signals.size() >= 5 && !nostack){
    vector <int> Style;
    Style.push_back(3003);
    Style.push_back(3004);
    Style.push_back(3005);
    Style.push_back(3006);
    Style.push_back(3007);
    Style.push_back(3013);
    Style.push_back(3001);
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->UseCurrentStyle();
      Backgrounds[i]->SetFillColor(kGray);
      Backgrounds[i]->SetLineColor(kGray);
      Backgrounds[i]->SetFillStyle(Style[i]);
      stack->Add(Backgrounds[i]);
    }
  } 
  if(noFill == 0 && (Signals.size() < 5 || nostack)){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->UseCurrentStyle();
      if (!nostack) Backgrounds[i]->SetFillColor(Colors[i]);
      if (dots) Backgrounds[i]->SetMarkerColor(Colors[i]);
      Backgrounds[i]->SetLineColor(Colors[i]);
      if (nostack && normalize) Backgrounds[i]->Scale(1.0/Backgrounds[i]->Integral());
      stack->Add(Backgrounds[i]);
    }
  } 
  else if(noFill == 1){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->UseCurrentStyle();
      Backgrounds[i]->SetFillColor(kWhite);
      Backgrounds[i]->SetLineColor(Colors[i]);
      if (nostack && normalize) Backgrounds[i]->Scale(1.0/Backgrounds[i]->Integral());
      stack->Add(Backgrounds[i]);
    }
}

  //Minimum and maximum
  float leftMax = AdjustedMaximum(1, Backgrounds, Data, Signals);
  float rightMax = AdjustedMaximum(2, Backgrounds, Data, Signals);
  float myMin = 0.1;
  if (setMinimum != -1) myMin = setMinimum;
  if (setMinimum == -1 && !linear && Backgrounds[0]->GetMinimum() > 0) myMin = min(0.1, 0.9*Backgrounds[0]->GetMinimum());
  else if (setMinimum == -1 && !linear && stack->GetMinimum() > 0) myMin = min(0.1, 0.5*stack->GetMinimum());
  else if (setMinimum == -1 && !linear) myMin = 0.1;
  if (setMinimum == -1 && linear) myMin = 0; 
  if (!nostack) stack->Draw("hist");
  if (nostack) stack->Draw("nostack");
  float myMax = stack->GetMaximum();
  if (setMaximum != -1) myMax = setMaximum; 
  else if (setMaximum == -1 && !linear){
    myMax = pow(AdjustedMaximum(3, Backgrounds, Data, Signals), 1.0/0.69)*pow(myMin, (0.69-1)/0.69); 
    if (leftMax > 5*rightMax) myMax = pow(AdjustedMaximum(3, Backgrounds, Data, Signals), 1.0/0.74)*pow(myMin, (0.74-1)/0.74);
    if (rightMax > leftMax)   myMax = myMax*10; 
  }
  else if (setMaximum == -1 && linear && noLegend)  myMax = (AdjustedMaximum(3, Backgrounds, Data, Signals))*(1.2) - (stack->GetMinimum())*(1.0/3.0);
  else if (setMaximum == -1 && linear){
    myMax = (AdjustedMaximum(3, Backgrounds, Data, Signals))*1.46 - (stack->GetMinimum())*(1.0/3.0);  
    if (rightMax < 0.7*leftMax){
      myMax = myMax*0.88;
      if (strcmp(title2, "") == 0) myMax = myMax*0.94; 
    }
    else if (rightMax > leftMax){ 
      if (Backgrounds.size() + Signals.size() >= 4) myMax = myMax*1.2;
    }
  }
  else if (!linear) myMax = myMax*20.0;
  else myMax = myMax*2;

  stack->SetMinimum(myMin);
  stack->SetMaximum(myMax);

  //Y-axis titles
  float bin_width = Backgrounds[0]->GetXaxis()->GetBinWidth(1);
  if (yAxisOverride != "" && yAxisOverride[0] != '\0') stack->GetYaxis()->SetTitle(Form("%s", yAxisOverride.c_str()));
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] != '\0') stack->GetYaxis()->SetTitle(Form("%s [%s] / %.0f %s  ", yAxisLabel.c_str(), yAxisUnit.c_str(), bin_width, xAxisUnit.c_str()));
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] == '\0' && bin_width >= 2) stack->GetYaxis()->SetTitle(Form("%s / %.0f %s  ", yAxisLabel.c_str(), bin_width, xAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] == '\0' && bin_width < 2) stack->GetYaxis()->SetTitle(Form("%s / %.2f %s  ", yAxisLabel.c_str(), bin_width, xAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && !showDivisionLabel && yAxisUnit[0] != '\0')stack->GetYaxis()->SetTitle(Form("%s [%s]  ", yAxisLabel.c_str(), yAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && !showDivisionLabel && yAxisUnit[0] == '\0')stack->GetYaxis()->SetTitle(Form("%s  ", yAxisLabel.c_str()));
  else cout << "nothing" << endl;

  //X-axis titles
  if (xAxisLabel == "HT" || xAxisLabel == "ht" || xAxisLabel == "Ht") xAxisLabel = "H_{T}"; 
  if (xAxisLabel == "MT" || xAxisLabel == "mt" || xAxisLabel == "Mt") xAxisLabel = "M_{T}"; 
  if (xAxisOverride[0] == '\0' && showXaxisUnit == 0) stack->GetXaxis()->SetTitle(Form("%s", xAxisLabel.c_str()));
  if (xAxisOverride[0] == '\0' && showXaxisUnit == 1) stack->GetXaxis()->SetTitle(Form("%s [%s]", xAxisLabel.c_str(), xAxisUnit.c_str()));
  if (xAxisOverride[0] != '\0') stack->GetXaxis()->SetTitle(Form("%s", xAxisOverride.c_str()));
  if (!noData) stack->GetYaxis()->SetTitleOffset(1.5);
  if (noData) stack->GetYaxis()->SetTitleOffset(1.4);
  if (noData && linear) stack->GetYaxis()->SetTitleOffset(1.6);

  //Draw
  if (!nostack && !dots) stack->Draw("hist");
  if (dots) stack->Draw("PE"); 
  if (nostack) stack->Draw("nostack");
  THStack *stack2 = new THStack("stack2", "stack2"); 
  Data->SetMarkerColor(dataColor);
  Data->SetLineColor(dataColor);
  stack2->Add(Data);
  stack2->Draw("PSAMEE");
  vector<int> markerStyle;
  markerStyle.push_back(20);
  markerStyle.push_back(21);
  markerStyle.push_back(22);
  markerStyle.push_back(23);
  markerStyle.push_back(29);
  markerStyle.push_back(33);
  markerStyle.push_back(34);
  for (unsigned int i = 0; i < Signals.size(); i++){
    Signals[i]->Draw("SAMEP");
    if (Colors.size() >= i + Backgrounds.size() + 1) Signals[i]->SetMarkerColor(Colors[i + Backgrounds.size()]);
    Signals[i]->SetLineColor(kBlack);
    Signals[i]->SetLineWidth(3);
    Signals[i]->SetMarkerStyle(markerStyle[i%7]);
  }

  //Legend
  TLegend *leg;
  if ((Backgrounds.size()+Signals.size() == 1 || Backgrounds.size()+Signals.size() == 2) && noData) leg = new TLegend(0.7+legendRight,0.79+legendUp,0.92+legendRight,0.87+legendUp); 
  else if ((Backgrounds.size()+Signals.size() == 1 || Backgrounds.size()+Signals.size() == 2) && !noData) leg = new TLegend(0.7+legendRight,0.69+legendUp,0.92+legendRight,0.77+legendUp); 
  else leg = new TLegend(0.7+legendRight,0.59+legendUp,0.92+legendRight,0.87+legendUp);
  leg->SetTextSize(legendTextSize);
  if (noData == false) leg->AddEntry(Data, dataName.c_str(), "lp");
  if (!dots) for (int i = Titles.size()-1; i > -1; i--) leg->AddEntry(Backgrounds[i], Titles[i].c_str(), "f");
  if (dots) for (int i = Titles.size()-1; i > -1; i--) leg->AddEntry(Backgrounds[i], Titles[i].c_str(), "LPE");
  if (use_signals) for (int i = SignalTitles.size()-1; i > -1; i--) leg->AddEntry(Signals[i], SignalTitles[i].c_str(), "P");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  if (!noLegend) leg->Draw();

  //Draw title & subtitle on plot 
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.035);
  if (noData == false){
    tex->DrawLatex(0.16,0.88,title);
    tex->DrawLatex(0.16,0.83,title2);
  }
  if (noData == true){
    tex->DrawLatex(0.16,0.78,title);
    tex->DrawLatex(0.16,0.73,title2);
  }

  //Draw vertical lines
  c0.Update();
  for (unsigned int i = 0; i < vLines.size(); i++) DrawVerticalLine(vLines[i]); 

  //Draw Horizontal lines
  for (unsigned int i = 0; i < hLines.size(); i++){
    TLine linecut;
    c0.Update();
    linecut.SetLineStyle(2);
    linecut.SetLineWidth(2);
    linecut.SetLineColor(kGray+2);
    linecut.DrawLine(0.0, hLines[i], Backgrounds.size() > 0 ? Backgrounds[0]->GetXaxis()->GetXmax() : Signals[0]->GetXaxis()->GetXmax(), hLines[i]);
  }

  //Draw header
  float type_y = .95;
  if (!noData) type_y = .96;
  tex->SetTextSize(0.028);
  if (overrideHeader[0] == '\0') tex->DrawLatex(0.79,type_y,Form("%s fb^{-1} (%s TeV)", lumi.c_str(), energy.c_str()));
  tex->SetTextSize(0.035);
  if (noData && overrideHeader[0] == '\0'){
    tex->DrawLatex(0.16,type_y-.08, "CMS");
    tex->DrawLatex(0.16,type_y-.11, "#it{Preliminary}"); 
  }
  if (!noData && overrideHeader[0] == '\0'){ 
    tex->DrawLatex(0.83,type_y-.08, "CMS");
    tex->DrawLatex(0.73,type_y-.13, "#it{Preliminary}"); 
  }
  if (overrideHeader[0] != '\0') tex->DrawLatex(0.17,type_y,Form("%s", overrideHeader.c_str()));
  if (!noData && stack->GetMaximum() > 80000 && linear) finPad[0]->SetPad(0.0, 0.0, 1.0, 0.84);

  //Set number of divisions on x-axis
  if (doHalf){
    Int_t sign = (stack->GetXaxis()->GetNdivisions() > 0) ? 1 : -1;
    Int_t orig = abs(stack->GetXaxis()->GetNdivisions());
    Int_t orig_high =orig-orig%100;
    Int_t orig_low = orig%100;
    Int_t new_ndiv = (orig_low%2==1) ? orig_high+orig_low/2 : orig_high + (orig_low-1)/2;
    stack->GetXaxis()->SetNdivisions(new_ndiv, (sign>0) ? kTRUE : kFALSE);
  }
  if (nDivisions != -1 && nDivisions > 0) stack->GetXaxis()->SetNdivisions(nDivisions, kTRUE);
  if (nDivisions != -1 && nDivisions < 0) stack->GetXaxis()->SetNdivisions(nDivisions, kFALSE);

  //-----------Second pad: data/MC yields---------------
  if (noData == false){
    finPad[1]->cd();
    TH1F* err_hist = (TH1F*)Backgrounds[0]->Clone(); 
    err_hist->SetTitle("");
    err_hist->Draw();
    err_hist->SetLineColor(kBlack);
    err_hist->SetMarkerColor(kBlack);
    err_hist->GetYaxis()->SetTitle("Data/MC");
    err_hist->GetYaxis()->SetTitleSize(0.08);
    err_hist->GetYaxis()->SetTitleOffset(1.8);
    for (int ib = 1; ib < err_hist->GetNbinsX()+1; ib++){
      float MC_value = 0;
      float MC_error_2 = 0;
      for (unsigned int i = 0; i < Backgrounds.size(); i++){
        MC_value += Backgrounds[i]->GetBinContent(ib);
        MC_error_2 += pow(Backgrounds[i]->GetBinError(ib), 2);
      }
      float data_value = Data->GetBinContent(ib);
      float value = (MC_value > 0 ? data_value/MC_value : 1000);
      err_hist->SetBinContent(ib, value);
      float MC_err = sqrt(MC_error_2);
      float data_err = Data->GetBinError(ib);
      err_hist->SetBinError(ib, value * sqrt( pow(MC_err/MC_value, 2) + pow(data_err/data_value, 2) ));
    }
    err_hist->SetMarkerStyle(20);
    err_hist->Draw("PE");
    TText *blah = new TText();
    blah->SetTextFont(42);
    blah->SetTextSize(0.17);
    blah->SetTextAngle(90);
    blah->DrawTextNDC(0.045,0.15,topYaxisTitle.c_str());
    TLine line;
    line.SetLineColor(kGray+2);
    line.SetLineWidth(2);
    int maxbin = err_hist->GetXaxis()->GetNbins();
    line.DrawLine(err_hist->GetXaxis()->GetBinLowEdge(1),1,err_hist->GetXaxis()->GetBinUpEdge(maxbin),1);
    err_hist->Draw("PESAME");
    err_hist->GetXaxis()->SetLabelSize(0);
    err_hist->GetYaxis()->SetLabelSize(0.2);
    err_hist->GetYaxis()->SetRangeUser(0., 2.);
    err_hist->GetYaxis()->SetNdivisions(505);
  }
  //--------------------------------

  //Print plot as pdf 
  if (png) c0.Print(Form("%s.png", outputName.c_str()));
  else c0.Print(Form("%s.pdf", outputName.c_str()));
}
