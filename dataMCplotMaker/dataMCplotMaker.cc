#include "dataMCplotMaker.h"
#include "TGraphAsymmErrors.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"

bool do_background_syst = true;
TStyle *tdrStyleAG = NULL;

//Comparison to put smallest histogram on bottom of stack
bool Integral(PlotInfo plot1, PlotInfo plot2){
  return plot1.Plot->Integral(0,plot1.Plot->GetNbinsX()) < plot2.Plot->Integral(0,plot2.Plot->GetNbinsX());
}

//Comparison between pair in order to make sort on index 
bool pairCompare(const std::pair<float, int> & a, const std::pair<float, int> & b) {
  return a.first > b.first;
}

//Function to determine maximum of each histogram, including error bars.  Side = 1 left, 2 right, 3 both, 4 = overflow
TH1F *null = new TH1F("", "", 1,0,1);
float AdjustedMaximum(int side, std::vector <std::pair<TH1F*, TH1F*> > Plots_in, TH1F* data = null, std::vector <TH1F*> Signals = std::vector<TH1F*>()){
  std::vector <TH1F*> Plots;
  std::vector <TH1F*> Plots_syst;
  for (unsigned int i = 0; i < Plots_in.size(); i++) Plots.push_back(Plots_in[i].first); 
  for (unsigned int i = 0; i < Plots_in.size(); i++) Plots_syst.push_back(Plots_in[i].second); 
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
  std::vector <float> heights;
  for (int i = lowerBound; i < upperBound; i++){
    float temp = 0;
    for (unsigned int j = 0; j < Plots.size(); j++) temp += Plots[j]->GetBinContent(i)+Plots_syst[j]->GetBinError(i);
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
  return std::max(data_height, bkgd_height);
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
  tdrStyleAG->SetHistLineColor(kBlack);
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
  tdrStyleAG->SetTitleSize(0.045, "XYZ");
  tdrStyleAG->SetTitleOffset(1.17, "X");
  tdrStyleAG->SetTitleOffset(1.15, "Y"); 

  //For the axis labels:
  tdrStyleAG->SetLabelColor(1, "XYZ");
  tdrStyleAG->SetLabelFont(42, "XYZ");
  tdrStyleAG->SetLabelOffset(0.007, "XYZ");
  tdrStyleAG->SetLabelSize(0.040, "XYZ");

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

void singlePlotMaker(TH1F* h1, std::string title, std::string options_string) {
    if(h1->GetEntries() < 1) {
        std::cout << "Plot with title " << title << " is empty. Not drawing." << std::endl; return;
    }
    TH1F* null = new TH1F("","",1,0,1);
    std::vector <TH1F*> Backgrounds;
    std::vector <std::string> Titles;
    Backgrounds.push_back(h1);
    Titles.push_back(title);
    dataMCplotMaker(null, Backgrounds, Titles, title, "", options_string);
}

void singleComparisonMaker(TH1F* h1, TH1F* h2, std::string title, std::string title2, std::string options_string) {
    if(h1->GetEntries() < 1) {
        std::cout << "Plot with title " << title << " is empty. Not drawing." << std::endl; return;
    }
    std::vector <TH1F*> Backgrounds;
    std::vector <std::string> Titles;
    Backgrounds.push_back(h2);
    Titles.push_back(title);
    dataMCplotMaker(h1, Backgrounds, Titles, title2, "", options_string);
}


///////////////////
///////////////////
// MAIN FUNCTION //
///////////////////
///////////////////

void dataMCplotMaker(TH1F* Data_in, std::vector <std::pair <TH1F*, TH1F*> > Backgrounds_pair_in, std::vector <std::string> Titles, std::string titleIn, std::string title2In, std::string options_string, std::vector <TH1F*> Signals_in, std::vector <std::string> SignalTitles, std::vector <Color_t> color_input, TH1F* overrideSyst) {

  //Copy inputs
  TH1F* Data = new TH1F(*Data_in); 
  Data->SetBinErrorOption( Data_in->GetBinErrorOption() );
  std::vector <TH1F*> Backgrounds; 
  std::vector <TH1F*> Background_systs; 
  std::vector <TH1F*> Signals; 
  std::vector <std::pair<TH1F*, TH1F*> > Backgrounds_pair; 
  for (unsigned int i = 0; i < Backgrounds_pair_in.size(); i++){
    TH1F* blah  = new TH1F(*Backgrounds_pair_in[i].first); 
    Backgrounds.push_back(blah);  
    TH1F* blah2 = new TH1F(*Backgrounds_pair_in[i].second);  
    Background_systs.push_back(blah2); 
    //TH1F* blah3 = 0; 
    //if (Backgrounds_pair_in[i].second->GetEntries() > 0){
      
    //}
    //else blah3 = new TH1F(*Backgrounds_pair_in[i].second);
    //std::pair<TH1F*, TH1F*> blah4 = std::make_pair(blah, Backgrounds_pair_in[i].second->GetEntries() > 0 ? blah2 : blah3); 
    std::pair<TH1F*, TH1F*> blah4 = std::make_pair(blah, blah2); 
    //Backgrounds_pair.push_back(blah4); 
    Backgrounds_pair.push_back(blah4); 
  }
  for (unsigned int i = 0; i < Signals_in.size(); i++){
    TH1F* blah = new TH1F(*Signals_in[i]); 
    Signals.push_back(blah);  
  }



  //Convert titles to fucking char*s 
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
  bool doCounts = 0;
  bool legendCounts = 0;
  bool showXaxisUnit = 1;
  bool noType = false;
  bool colorTitle = false;
  std::string xAxisLabel = "M_{T}";
  std::string energy = "13";
  std::string lumi = "10.0";
  std::string yAxisLabel = "Entries";
  std::string yAxisUnit = "";
  std::string yAxisOverride = "";
  std::string xAxisUnit = "GeV";
  std::string xAxisOverride = "";
  std::string xAxisBinLabels = "";
  std::string dataName = "data";
  std::string topYaxisTitle = "data/MC";
  std::string overrideHeader = "";
  std::string type = "";//Preliminary, Supplementary, etc
  std::string outputName = "data_MC_plot";
  bool preserveBackgroundOrder = 0;
  bool preserveSignalOrder = 0;
  bool showDivisionLabel = 1;
  bool xAxisVerticalBinLabels = 0;
  float setMaximum = -1;
  float setMaxMultiplier = -1;
  float setMinimum = -1;
  float legendUp = 0;
  float legendRight = 0;
  float legendTextSize = 0.035;
  std::vector <std::string> vLines;
  std::vector <std::string> hLines;
  std::string boxLines = "";
  std::string flagLocation = "";
  bool doHalf = 0;
  bool doPull = 0;
  Int_t nDivisions = -1;
  bool noLegend = false;
  bool png = false;
  bool dots = false;
  bool showPercentage = false;
  bool percentageInBox = false;
  bool errHistAtBottom = false;
  std::vector<int> percent;
  std::vector<float> counts;
  std::string datacolor = "";
  std::string ratiocolor = "";
  bool noOutput = false;
  bool noErrBars = false;
  bool noBlackLines = false;
  bool totalBlackLine = false;
  bool darkColorLines = false;
  bool histoErrors = false;
  bool legendBox = false;
  bool xAxisOverrideGiven = false;  
  std::string lumiUnit = "fb"; 
  bool sigError = false;
  bool blackSignals = false;
  bool outOfFrame = false;
  bool markerStyle2 = false;
  float legendWider_ = 0;
  float legendTaller_ = 0;
  float ratioUpperBound = 2.;
  bool largeLabels = false;
  float yTitleOffset_ = 0;
  bool compareMultiple = 0; 
  bool noLumi = 0; 
  int ratio = -1; 
  int ratioNumerBG = -1; 
  bool ratioOnly = 0; 
  bool ratioLine = 0; 
  int bkgd_width = 1; 
  bool dontShowZeroRatios = 1; 
  bool systInclStat = 0; 
  bool noRatioPlot = 0; 
  int systFillStyle = 3644; 
  bool systBlack = 0; 
  int lumiPrec = 1; 
  bool noTextBetweenPads = 0;
  bool poissonErrorsNoZeros = 0;
  bool noGrass = 0;
  bool makeTable = 0;
  bool makeJSON = 0;
  bool makeRootFile = 0;
  bool doWide = 0;
  bool noDataWidth = 0;

  //Loop over options and change default settings to user-defined settings
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("isLinear") < Options[i].length()) linear = 1; 
    else if (Options[i].find("preserveBackgroundOrder") < Options[i].length()) preserveBackgroundOrder = 1; 
    else if (Options[i].find("systFillStyle") < Options[i].length()) systFillStyle = atoi( getString(Options[i], "systFillStyle").c_str() );
    else if (Options[i].find("noBlackLines") < Options[i].length()) noBlackLines = 1; 
    else if (Options[i].find("totalBlackLine") < Options[i].length()) totalBlackLine = 1; 
    else if (Options[i].find("darkColorLines") < Options[i].length()) darkColorLines = 1; 
    else if (Options[i].find("noStack") < Options[i].length()) nostack = 1; 
    else if (Options[i].find("lumiUnit") < Options[i].length()) lumiUnit = getString(Options[i], "lumiUnit"); 
    else if (Options[i].find("lumiPrec") < Options[i].length()) lumiPrec = atoi( getString(Options[i], "lumiPrec").c_str() );
    else if (Options[i].find("noFill") < Options[i].length()) noFill = 1;
    else if (Options[i].find("normalize") < Options[i].length()) normalize = 1; 
    else if (Options[i].find("preserveSignalOrder") < Options[i].length()) preserveSignalOrder = 1; 
    else if (Options[i].find("legendBox") < Options[i].length()) legendBox = 1; 
    else if (Options[i].find("outputName") < Options[i].length()) outputName = getString(Options[i], "outputName");
    else if (Options[i].find("png") < Options[i].length()) png = true;
    else if (Options[i].find("noDivisionLabel") < Options[i].length()) showDivisionLabel = 0; 
    else if (Options[i].find("noLegend") < Options[i].length()) noLegend = 1; 
    else if (Options[i].find("noOverflow") < Options[i].length()) doOverflow = 0; 
    else if (Options[i].find("doCounts") < Options[i].length()) doCounts = 1; 
    else if (Options[i].find("legendCounts") < Options[i].length()) legendCounts = 1; 
    else if (Options[i].find("noType") < Options[i].length()) noType = 1; 
    else if (Options[i].find("colorTitle") < Options[i].length()) colorTitle = 1; 
    else if (Options[i].find("noXaxisUnit") < Options[i].length()) showXaxisUnit = 0; 
    else if (Options[i].find("divHalf") < Options[i].length()) doHalf = 1; 
    else if (Options[i].find("doPull") < Options[i].length()) doPull = 1; 
    else if (Options[i].find("energy") < Options[i].length()) energy = getString(Options[i], "energy");
    else if (Options[i].find("lumi") < Options[i].length()) lumi = getString(Options[i], "lumi");
    else if (Options[i].find("yAxisLabel") < Options[i].length()) yAxisLabel = getString(Options[i], "yAxisLabel");
    else if (Options[i].find("yAxisUnit") < Options[i].length()) yAxisUnit = getString(Options[i], "yAxisUnit");
    else if (Options[i].find("yAxisOverride") < Options[i].length()) yAxisOverride = getString(Options[i], "yAxisOverride");
    else if (Options[i].find("xAxisLabel") < Options[i].length()) xAxisLabel = getString(Options[i], "xAxisLabel");
    else if (Options[i].find("xAxisUnit") < Options[i].length()) xAxisUnit = getString(Options[i], "xAxisUnit");
    else if (Options[i].find("xAxisOverride") < Options[i].length()){ xAxisOverride = getString(Options[i], "xAxisOverride"); xAxisOverrideGiven = true; }
    else if (Options[i].find("xAxisBinLabels") < Options[i].length()) xAxisBinLabels = getString(Options[i], "xAxisBinLabels");
    else if (Options[i].find("xAxisVerticalBinLabels") < Options[i].length()) xAxisVerticalBinLabels = 1; 
    else if (Options[i].find("dataName") < Options[i].length()) dataName = getString(Options[i], "dataName");
    else if (Options[i].find("dataColor") < Options[i].length()) datacolor = getString(Options[i], "dataColor");
    else if (Options[i].find("ratioColor") < Options[i].length()) ratiocolor = getString(Options[i], "ratioColor");
    else if (Options[i].find("topYaxisTitle") < Options[i].length()) topYaxisTitle = getString(Options[i], "topYaxisTitle");
    else if (Options[i].find("type") < Options[i].length()) type = getString(Options[i], "type");
    else if (Options[i].find("overrideHeader") < Options[i].length()) overrideHeader = getString(Options[i], "overrideHeader");
    else if (Options[i].find("vLine") < Options[i].length()) vLines.push_back(getString(Options[i], "vLine").c_str());
    else if (Options[i].find("hLine") < Options[i].length()) hLines.push_back(getString(Options[i], "hLine").c_str());
    else if (Options[i].find("boxLines") < Options[i].length()) boxLines = getString(Options[i], "boxLines").c_str();
    else if (Options[i].find("flagLocation") < Options[i].length()) flagLocation = getString(Options[i], "flagLocation").c_str();
    else if (Options[i].find("setMaximum") < Options[i].length()) setMaximum = atof( getString(Options[i], "setMaximum").c_str() );
    else if (Options[i].find("setMaxMultiplier") < Options[i].length()) setMaxMultiplier = atof( getString(Options[i], "setMaxMultiplier").c_str() );
    else if (Options[i].find("legendUp") < Options[i].length()) legendUp = atof( getString(Options[i], "legendUp").c_str() );
    else if (Options[i].find("legendRight") < Options[i].length()) legendRight = atof( getString(Options[i], "legendRight").c_str() );
    else if (Options[i].find("legendTextSize") < Options[i].length()) legendTextSize = atof( getString(Options[i], "legendTextSize").c_str() );
    else if (Options[i].find("setMinimum") < Options[i].length()) setMinimum = atof( getString(Options[i], "setMinimum").c_str() );
    else if (Options[i].find("nDivisions") < Options[i].length()) nDivisions = atoi( getString(Options[i], "nDivisions").c_str() );
    else if (Options[i].find("drawDots") < Options[i].length()) dots = true; 
    else if (Options[i].find("showPercentage") < Options[i].length()) showPercentage = true; 
    else if (Options[i].find("percentageInBox") < Options[i].length()) percentageInBox = true; 
    else if (Options[i].find("errHistAtBottom") < Options[i].length()) errHistAtBottom = true; 
    else if (Options[i].find("noOutput") < Options[i].length()) noOutput = true; 
    else if (Options[i].find("noDataWidth") < Options[i].length()) noDataWidth = true; 
    else if (Options[i].find("noErrBars") < Options[i].length()) noErrBars = true; 
    else if (Options[i].find("histoErrors") < Options[i].length()) histoErrors = true; 
    else if (Options[i].find("sigError") < Options[i].length()) sigError = true; 
    else if (Options[i].find("blackSignals") < Options[i].length()) blackSignals = true; 
    else if (Options[i].find("outOfFrame") < Options[i].length()) outOfFrame = true; 
    else if (Options[i].find("markerStyle2") < Options[i].length()) markerStyle2 = true; 
    else if (Options[i].find("largeLabels") < Options[i].length()) largeLabels = true; 
    else if (Options[i].find("legendWider") < Options[i].length())  legendWider_ = atof( getString(Options[i], "legendWider").c_str() );
    else if (Options[i].find("legendTaller") < Options[i].length()) legendTaller_ = atof( getString(Options[i], "legendTaller").c_str() ); 
    else if (Options[i].find("ratioUpperBound") < Options[i].length()) ratioUpperBound = atof( getString(Options[i], "ratioUpperBound").c_str() ); 
    else if (Options[i].find("yTitleOffset") < Options[i].length()) yTitleOffset_ = atof( getString(Options[i], "yTitleOffset").c_str() ); 
    else if (Options[i].find("compareMultiple") < Options[i].length()) compareMultiple = true;
    else if (Options[i].find("ratioOnly") < Options[i].length()) ratioOnly = true;
    else if (Options[i].find("ratioLine") < Options[i].length()) ratioLine = true;
    else if (Options[i].find("ratioNumerBG") < Options[i].length()) ratioNumerBG = atoi( getString(Options[i], "ratioNumerBG").c_str() );
    else if (Options[i].find("ratio") < Options[i].length()) ratio = atoi( getString(Options[i], "ratio").c_str() );
    else if (Options[i].find("noLumi") < Options[i].length()) noLumi = true;
    else if (Options[i].find("bkgd_width") < Options[i].length()) bkgd_width = atoi( getString(Options[i], "bkgd_width").c_str() ); 
    else if (Options[i].find("showZeroRatios") < Options[i].length()) dontShowZeroRatios = false; 
    else if (Options[i].find("systInclStat") < Options[i].length()) systInclStat = true; 
    else if (Options[i].find("noRatioPlot") < Options[i].length()) noRatioPlot = true; 
    else if (Options[i].find("systBlack") < Options[i].length()) systBlack = true; 
    else if (Options[i].find("noTextBetweenPads") < Options[i].length()) noTextBetweenPads = true;
    else if (Options[i].find("poissonErrorsNoZeros") < Options[i].length()) poissonErrorsNoZeros = true;
    else if (Options[i].find("noGrass") < Options[i].length()) noGrass = true;
    else if (Options[i].find("makeTable") < Options[i].length()) makeTable = true;
    else if (Options[i].find("makeJSON") < Options[i].length()) makeJSON = true;
    else if (Options[i].find("makeRootFile") < Options[i].length()) makeRootFile = true;
    else if (Options[i].find("doWide") < Options[i].length()) doWide = true;
    else std::cout << "Warning: Option not recognized!  Option: " << Options[i] << std::endl;
  }

  //Print warnings
  if (normalize && !nostack) std::cout << "Warning! You set option to normalize, but not option --noStack.  This won't do much!" << std::endl;
  if (ratioLine && !noErrBars) std::cout << "Warning!  ratioLine won't do much without noErrBars!" << std::endl;

  //Try to guess if we should turn off division label
  if (xAxisUnit == "" || xAxisUnit.find("SR") < xAxisUnit.length() || !showXaxisUnit) showDivisionLabel = 0;

  //Decode data color
  Color_t dataColor = kBlack;
  Color_t ratioColor = kBlack;
  if (datacolor != ""){
    std::transform(datacolor.begin(), datacolor.end(), datacolor.begin(), ::tolower); 
    if (datacolor == "kred"     || datacolor == "red") dataColor = kRed;
    if (datacolor == "kblue"    || datacolor == "blue") dataColor = kBlue;
    if (datacolor == "kgreen"   || datacolor == "green") dataColor = kGreen;
    if (datacolor == "korange"  || datacolor == "orange") dataColor = kOrange;
    if (datacolor == "kcyan"    || datacolor == "cyan") dataColor = kCyan;
    if (datacolor == "kmagenta" || datacolor == "magenta") dataColor = kMagenta;
  }
  if (ratiocolor != ""){
    std::transform(ratiocolor.begin(), ratiocolor.end(), ratiocolor.begin(), ::tolower); 
    if (ratiocolor == "kred"     || ratiocolor == "red") ratioColor = kRed;
    if (ratiocolor == "kblue"    || ratiocolor == "blue") ratioColor = kBlue;
    if (ratiocolor == "kgreen"   || ratiocolor == "green") ratioColor = kGreen;
    if (ratiocolor == "korange"  || ratiocolor == "orange") ratioColor = kOrange;
    if (ratiocolor == "kcyan"    || ratiocolor == "cyan") ratioColor = kCyan;
    if (ratiocolor == "kmagenta" || ratiocolor == "magenta") ratioColor = kMagenta;
  }

  //Set Style
  SetTDRStyle();
  gStyle->SetOptStat(0);
  if (noData || noRatioPlot) gStyle->SetPadBottomMargin(.12);
  if (noData || noRatioPlot) gStyle->SetPadLeftMargin(.12);
  if (noData || noRatioPlot) gStyle->SetPadTopMargin(.07);


  //Make sure there is at least one background and enough titles
  if (Backgrounds.size() < 1){ 
    std::cout << "Error: Running with no backgrounds!" << std::endl;
    return;
  }
  if (Titles.size() != Backgrounds.size()) std::cout << "Warning! Wrong number of titles for your backgrounds!" << std::endl;
  while (Titles.size() < Backgrounds.size()){
    char* blank = new char[strlen("")+2];
    std::strcpy(blank, "");
    Titles.push_back(blank);
  }
  if (use_signals && SignalTitles.size() != Signals.size()) std::cout << "Warning! Wrong number of titles for your signals!" << std::endl;
  while (SignalTitles.size() < Signals.size()){
    char* blank = new char[strlen("")+2];
    std::strcpy(blank, "");
    SignalTitles.push_back(blank);
  }

  //Format Titles
  for (unsigned int i = 0; i < Titles.size(); i++){
    std::string title_temp = Titles[i];
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
    for (unsigned int i = 0; i < Background_systs.size(); i++){
      Background_systs[i]->SetBinContent(Background_systs[i]->GetNbinsX(), Background_systs[i]->GetBinContent(Background_systs[i]->GetNbinsX())+Background_systs[i]->GetBinContent(Background_systs[i]->GetNbinsX()+1) );
    }
    for (unsigned int i = 0; i < Signals.size(); i++){
      Signals[i]->SetBinContent(Signals[i]->GetNbinsX(), Signals[i]->GetBinContent(Signals[i]->GetNbinsX())+Signals[i]->GetBinContent(Signals[i]->GetNbinsX()+1) );
    }
    if (!noData) Data->SetBinContent(Data->GetNbinsX(), Data->GetBinContent(Data->GetNbinsX())+Data->GetBinContent(Data->GetNbinsX()+1) );
  }

  //Do Underflow
  if (doOverflow == 1){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->SetBinContent(1, Backgrounds[i]->GetBinContent(1)+Backgrounds[i]->GetBinContent(0) );
    }
    for (unsigned int i = 0; i < Background_systs.size(); i++){
      Background_systs[i]->SetBinContent(1, Background_systs[i]->GetBinContent(1)+Background_systs[i]->GetBinContent(0) );
    }
    for (unsigned int i = 0; i < Signals.size(); i++){
      Signals[i]->SetBinContent(1, Signals[i]->GetBinContent(1)+Signals[i]->GetBinContent(0) );
    }
    if (!noData) Data->SetBinContent(1, Data->GetBinContent(1)+Data->GetBinContent(0) );
  }

  std::vector <Color_t> Colors;
  std::vector <Color_t> Colors2;

  //Set colors for histograms
  //(a) Use colors assigned
  if (color_input.size() != 0){
    for (unsigned int i = 0; i < color_input.size(); i++){
      Colors.push_back(color_input[i]);
    }
  }
  //(b) If compareMultiple, then need to light + dark colors
  if (compareMultiple){
    Colors.push_back(kGray);     Colors2.push_back(kGray+3);
    Colors.push_back(kAzure+8);  Colors2.push_back(kAzure-2);
    Colors.push_back(kSpring-5); Colors2.push_back(kSpring-6);
    Colors.push_back(kRed-7);    Colors2.push_back(kRed);
    Colors.push_back(kMagenta);  Colors2.push_back(kViolet+3);
    Colors.push_back(kOrange-3); Colors2.push_back(kOrange+7);
  }
  //(c) If only 2 backgrounds, use this green + "Azure"
  if (color_input.size() == 0 && Backgrounds.size() == 2){
    if(Colors.size() > 0) Colors[0] = kAzure+7; else Colors.push_back(kAzure+7);
    if(Colors.size() > 1) Colors[1] = kSpring-5; else Colors.push_back(kSpring-5);
  }
  //(d) Otherwise, default scheme for no signals
  if (color_input.size() == 0 && use_signals == 0){
    Colors.push_back(kSpring-5);
    Colors.push_back(kAzure+7);
    if (!nostack) Colors.push_back(kRed-7);
    Colors.push_back(kOrange-2);
    if (!nostack) Colors.push_back(kCyan-7);
    Colors.push_back(kMagenta-7);
    if (!nostack) Colors.push_back(kTeal+6);
    Colors.push_back(kGray+2);
  }
  //(e) Otherwise, default scheme for signals
  if (color_input.size() == 0 && use_signals == 1){
    Colors.push_back(kSpring-5);
    Colors.push_back(kAzure+7);
    Colors.push_back(kCyan-7);
    Colors.push_back(kRed-7);
    Colors.push_back(kOrange-4);
    Colors.push_back(kMagenta-7);
    Colors.push_back(kTeal-5);
    Colors.push_back(kOrange+6);
  }

  if (color_input.size() > 0 && use_signals == 1){
    Colors.push_back(kRed);
  }

  //Black Signals
  if (blackSignals){
    for (unsigned int i = Backgrounds.size(); i < Colors.size(); i++) Colors[i] = kBlack; 
  }

  std::vector <int> Backgrounds_number; 

  //Sort Backgrounds, with Titles and Colors
  if (preserveBackgroundOrder == 0){
    std::vector<PlotInfo> myPlotInfo;
 
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      PlotInfo temp;
      temp.Plot = Backgrounds[i];
      temp.Title = Titles[i];
      temp.Number = i; 
      if (Signals.size() >= i+1)     temp.Signal      = Signals[i];
      if (Colors2.size() >= i+1) temp.SignalColor = Colors2[i];
      if (SignalTitles.size() >= i+1) temp.SignalTitle = SignalTitles[i];
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
      Backgrounds_number.push_back(myPlotInfo[i].Number); 
      Titles.push_back(myPlotInfo[i].Title);
      Colors[i] = myPlotInfo[i].Color;
      if (compareMultiple) Signals[i] = myPlotInfo[i].Signal;
      if (compareMultiple) Colors2[i] = myPlotInfo[i].SignalColor;
      if (compareMultiple) SignalTitles[i] = myPlotInfo[i].SignalTitle;
    }
  }

  //Sort Signals, with Titles and Colors
  if (!preserveSignalOrder && !compareMultiple){
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
  if ((noData == false && !noRatioPlot) || compareMultiple){
    if (!doWide) c0.SetCanvasSize(600, 700);
    else c0.SetCanvasSize(800, 700);
    if (errHistAtBottom == false){
        if (noTextBetweenPads) {
            finPad[0] = new TPad("p1", "p1", 0.0, 0.0, 1.0, 0.79);
            finPad[1] = new TPad("p2", "p2", 0.0, 0.78, 1.0, 0.99);
        } else {
            finPad[0] = new TPad("p1", "p1", 0.0, 0.0, 1.0, 0.84);
            finPad[1] = new TPad("p2", "p2", 0.0, 0.83, 1.0, 1.0);
        }
    }
    else{
      finPad[0] = new TPad("p1", "p1", 0.0, 0.16, 1.0, 1.0);
      finPad[1] = new TPad("p2", "p2", 0.0, 0.0, 1.0, 0.17);
    }
    if (!linear) finPad[0]->SetLogy();
    finPad[0]->SetTopMargin(0.05);
    if (noTextBetweenPads) finPad[0]->SetTopMargin(0.005);
    if (noTextBetweenPads) finPad[1]->SetTopMargin(0.20);
    finPad[0]->SetLeftMargin(0.12);
    finPad[0]->SetBottomMargin(0.11);
    finPad[1]->SetLeftMargin(0.12);
    finPad[1]->Draw();
    finPad[0]->Draw();
    finPad[0]->cd();
  }
  else {
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
  if (Data->GetNbinsX() > 150) Data->SetMarkerSize(0.5);
  else if (Data->GetNbinsX() > 100) Data->SetMarkerSize(0.6);
  else if (Data->GetNbinsX() > 60) Data->SetMarkerSize(0.8);

  if(!compareMultiple && noFill == 0 && Signals.size() >= 5 && !nostack){
    std::vector <int> Style;
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
  if(noFill == 0 && (Signals.size() < 5 || nostack || compareMultiple)){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->UseCurrentStyle();
      if (!nostack) Backgrounds[i]->SetFillColor(Colors[i]);
      Backgrounds[i]->SetMarkerColor(Colors[i]);
      if (noBlackLines || nostack) Backgrounds[i]->SetLineColor(Colors[i]);
      else if (darkColorLines) Backgrounds[i]->SetLineColor(TColor::GetColorDark(Colors[i]));
      else Backgrounds[i]->SetLineColor(kBlack);
      Backgrounds[i]->SetLineWidth(Backgrounds[i]->GetLineWidth()/1.5);
      if (nostack && normalize) Backgrounds[i]->Scale(1.0/Backgrounds[i]->Integral());
      stack->Add(Backgrounds[i]);

      if (totalBlackLine) Backgrounds[i]->SetLineWidth(0);
      if (noBlackLines || nostack) Backgrounds[i]->SetLineWidth(2);//would be good to have an option for this
      // if (noBlackLines || nostack) Backgrounds[i]->SetLineWidth(4);//would be good to have an option for this // FIXME
    }
  } 
  else if(noFill == 1){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->UseCurrentStyle();
      Backgrounds[i]->SetFillColor(kWhite);
      Backgrounds[i]->SetLineColor(Colors[i]);
      Backgrounds[i]->SetMarkerColor(Colors[i]);
      if (nostack && normalize) Backgrounds[i]->Scale(1.0/Backgrounds[i]->Integral());
      stack->Add(Backgrounds[i]);
    }
  }
  else {
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->SetMarkerColor(Colors[i]);
    }
  }

  if (totalBlackLine) {
      if (Backgrounds.size()) {
          Backgrounds[Backgrounds.size()-1]->SetLineWidth(2);
          Backgrounds[Backgrounds.size()-1]->SetLineColor(kBlack);
      }
  }

  //Try this
  if (!dots && !nostack) Backgrounds[0]->SetMarkerColor(0);
  if (dots){ Backgrounds[0]->SetMarkerColor(kAzure-3); Backgrounds[0]->SetLineColor(kAzure-3); }
  if (dots && Backgrounds.size() > 1){ Backgrounds[1]->SetMarkerColor(kRed-7); Backgrounds[1]->SetLineColor(kRed-7); }
  if (dots && Backgrounds.size() > 2){ Backgrounds[2]->SetMarkerColor(kTeal+4); Backgrounds[2]->SetLineColor(kTeal+4); }
  if (dots && Backgrounds.size() > 3){ Backgrounds[3]->SetMarkerColor(kOrange+7); Backgrounds[3]->SetLineColor(kOrange+7); }

  //Minimum and maximum
  float leftMax = AdjustedMaximum(1, Backgrounds_pair, Data, Signals);
  float rightMax = AdjustedMaximum(2, Backgrounds_pair, Data, Signals);
  float myMin = 0.1;
  if (setMinimum != -1) myMin = setMinimum;
  if (setMinimum == -1 && !linear && Backgrounds[0]->GetMinimum() > 0) myMin = std::min(0.1, 0.9*Backgrounds[0]->GetMinimum());
  else if (setMinimum == -1 && !linear && stack->GetMinimum() > 0) myMin = std::min(0.1, 0.5*stack->GetMinimum());
  else if (setMinimum == -1 && !linear) myMin = 0.1;
  if (setMinimum == -1 && linear) myMin = 0; 
  if (!nostack) stack->Draw("hist");
  if (nostack) stack->Draw("nostack");
  float myMax = stack->GetMaximum();
  if (setMaximum != -1) myMax = setMaximum; 
  else if (setMaximum == -1 && !linear){
    myMax = pow(AdjustedMaximum(3, Backgrounds_pair, Data, Signals), 1.0/0.69)*pow(myMin, (0.69-1)/0.69); 
    if (leftMax > 5*rightMax) myMax = pow(AdjustedMaximum(3, Backgrounds_pair, Data, Signals), 1.0/0.74)*pow(myMin, (0.74-1)/0.74);
    if (rightMax > leftMax)   myMax = myMax*10; 
  }
  else if (setMaximum == -1 && linear && noLegend)  myMax = (AdjustedMaximum(3, Backgrounds_pair, Data, Signals))*(1.2) - (stack->GetMinimum())*(1.0/3.0);
  else if (setMaximum == -1 && linear){
    myMax = (AdjustedMaximum(3, Backgrounds_pair, Data, Signals))*1.46 - (stack->GetMinimum())*(1.0/3.0);  
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

  if (setMaxMultiplier != -1) myMax *= setMaxMultiplier; 

  stack->SetMinimum(myMin);
  stack->SetMaximum(myMax);

  //If linear and large numbers, need extra space
  if (linear && myMax > 1000) finPad[0]->SetLeftMargin(0.15);
  if (linear && myMax > 1000) finPad[1]->SetLeftMargin(0.15);
  if (!linear) finPad[0]->SetLeftMargin(0.12); 

  //Y-axis titles
  float bin_width = Backgrounds[0]->GetXaxis()->GetBinWidth(1);
  if (yAxisOverride != "" && yAxisOverride[0] != '\0') stack->GetYaxis()->SetTitle(Form("%s", yAxisOverride.c_str()));
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] != '\0') stack->GetYaxis()->SetTitle(Form("%s (%s) / %.0f %s  ", yAxisLabel.c_str(), yAxisUnit.c_str(), bin_width, xAxisUnit.c_str()));
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] == '\0' && bin_width >= 2) stack->GetYaxis()->SetTitle(Form("%s / %.0f %s  ", yAxisLabel.c_str(), bin_width, xAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && showDivisionLabel && yAxisUnit[0] == '\0' && bin_width < 2) stack->GetYaxis()->SetTitle(Form("%s / %.2f %s  ", yAxisLabel.c_str(), bin_width, xAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && !showDivisionLabel && yAxisUnit[0] != '\0')stack->GetYaxis()->SetTitle(Form("%s (%s)  ", yAxisLabel.c_str(), yAxisUnit.c_str())); 
  else if (yAxisOverride[0] == '\0' && !showDivisionLabel && yAxisUnit[0] == '\0')stack->GetYaxis()->SetTitle(Form("%s  ", yAxisLabel.c_str()));
  else std::cout << "nothing" << std::endl;

  //X-axis titles
  if (xAxisLabel == "HT" || xAxisLabel == "ht" || xAxisLabel == "Ht") xAxisLabel = "H_{T}"; 
  if (xAxisLabel == "MT" || xAxisLabel == "mt" || xAxisLabel == "Mt") xAxisLabel = "M_{T}"; 
  if (xAxisOverride[0] == '\0' && showXaxisUnit == 0) stack->GetXaxis()->SetTitle(Form("%s", xAxisLabel.c_str()));
  if (xAxisOverride[0] == '\0' && showXaxisUnit == 1) stack->GetXaxis()->SetTitle(Form("%s (%s)", xAxisLabel.c_str(), xAxisUnit.c_str()));
  if (xAxisOverride[0] != '\0' || xAxisOverrideGiven) stack->GetXaxis()->SetTitle(Form("%s", xAxisOverride.c_str()));
  if (!noData && !noRatioPlot &&  linear) stack->GetYaxis()->SetTitleOffset(1.5+yTitleOffset_);
  if (!noData && !noRatioPlot && !linear) stack->GetYaxis()->SetTitleOffset(1.2+yTitleOffset_);
  if ((noData || noRatioPlot) && !linear) stack->GetYaxis()->SetTitleOffset(1.4+yTitleOffset_);
  if ((noData || noRatioPlot) &&  linear && myMax > 1000) stack->GetYaxis()->SetTitleOffset(2.1+yTitleOffset_);
  if ((noData || noRatioPlot) &&  linear && myMax < 1000) stack->GetYaxis()->SetTitleOffset(1.5+yTitleOffset_);

  //Title size
  if (largeLabels){
    stack->GetYaxis()->SetTitleSize(0.05);
    stack->GetXaxis()->SetTitleSize(0.05);
    stack->GetYaxis()->SetLabelSize(0.045);
    stack->GetXaxis()->SetLabelSize(0.045);
    stack->GetXaxis()->SetTitleOffset(stack->GetXaxis()->GetTitleOffset()-0.2); 
    stack->GetYaxis()->SetTitleOffset(stack->GetYaxis()->GetTitleOffset()-0.2); 
  }

  //X-axis string bin labels
  TString ts = ""+xAxisBinLabels;
  TObjArray *tx = ts.Tokenize(",");
  if (xAxisBinLabels[0] != '\0') {
      for (Int_t i = 0; i < tx->GetEntries(); i++) {
          stack->GetXaxis()->SetBinLabel(i+1, ((TObjString *)(tx->At(i)))->String());
      }
      if(xAxisVerticalBinLabels) stack->GetXaxis()->LabelsOption("v");
      // else stack->GetXaxis()->LabelsOption("u");
      else stack->GetXaxis()->LabelsOption();
  }

  //Show Percentage
  if(showPercentage || percentageInBox){
    std::vector<double> each;
    float total = 0;
    for(unsigned int i=0; i<Backgrounds.size(); i++){
      each.push_back(Backgrounds[i]->Integral());
      total += each.back();
    }
    for(unsigned int i=0; i<Backgrounds.size(); i++){
      each[i] = each[i]/total*100;
      percent.push_back((int) each[i]);
    }
    // Get the rounded percentage add up to 100
    int ptotal = 0;
    for(unsigned int i=0; i<percent.size(); i++)  ptotal += percent[i];
    if (ptotal > 0){ //need this in case the plots are empty!
      std::vector< std::pair<float,int> > roundings;
      for(unsigned int i=0; i< percent.size(); i++) roundings.push_back(std::make_pair((each[i]-percent[i]),i));
      std::sort(roundings.begin(), roundings.end(), pairCompare);
      for(int i=0; i< (100-ptotal); i++) percent[roundings[i].second] += 1;
    }
  }

  // Keep track of background counts
  for (unsigned int i=0; i<Backgrounds.size(); i++){
      counts.push_back(Backgrounds[i]->Integral());
  }

  if (Background_systs.size() == 0) gStyle->SetErrorX(0.001); //why the fuck is this even here?

  //Stupid dots thing
  if (dots && myMin == 0){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      for (int j = 1; j <= Backgrounds[i]->GetNbinsX(); j++){
        if (Backgrounds[i]->GetBinContent(j) == 0){
          Backgrounds[i]->SetBinContent(j, 0.0000001); 
		  std::cout << "Warning! One of your 'dots' is 0 and won't show up.  Setting it to 0.0000001" << std::endl;  
        }
      }
    }
  }

  //Try this
  if (!dots && !nostack) Backgrounds[0]->SetMarkerColor(0);
  if (dots){ Backgrounds[0]->SetMarkerColor(kAzure+7); Backgrounds[0]->SetLineColor(kAzure+7); }
  if (dots && Backgrounds.size() > 1){ Backgrounds[1]->SetMarkerColor(kRed-7); Backgrounds[1]->SetLineColor(kRed-7); }
  if (dots && Backgrounds.size() > 2){ Backgrounds[2]->SetMarkerColor(kGreen-3); Backgrounds[2]->SetLineColor(kGreen-3); }
  if (dots && Backgrounds.size() > 3){ Backgrounds[3]->SetMarkerColor(kOrange+7); Backgrounds[3]->SetLineColor(kOrange+7); }
  if (dots && Backgrounds.size() > 4){ Backgrounds[4]->SetMarkerColor(kMagenta-7); Backgrounds[4]->SetLineColor(kMagenta-7); }
  if (dots && Backgrounds.size() > 5){ Backgrounds[5]->SetMarkerColor(kOrange-4); Backgrounds[5]->SetLineColor(kOrange-4); }

  if (bkgd_width > 1){
    for (unsigned int i = 0; i < Backgrounds.size(); i++){
      Backgrounds[i]->SetLineWidth(bkgd_width); 
    }
  }

  //Draw
  if (!nostack && !dots && histoErrors) stack->Draw("histe");
  else if (!nostack && !dots && !histoErrors) stack->Draw("hist");
  else if (dots) stack->Draw("PEnostack"); 
  else if (nostack) stack->Draw("histnostack");
  Data->SetMarkerColor(dataColor);
  Data->SetLineColor(dataColor);
  if (!ratioOnly) {
    if(noErrBars) Data->Draw("PSAME");
    else Data->Draw("PSAME");
  }
  std::vector<int> markerStyle;
  markerStyle.push_back(20);
  markerStyle.push_back(21);
  markerStyle.push_back(22);
  markerStyle.push_back(23);
  markerStyle.push_back(29);
  markerStyle.push_back(33);
  markerStyle.push_back(34);
  std::vector <int> markerStyle2_;
  markerStyle2_.push_back(24);
  markerStyle2_.push_back(20);
  markerStyle2_.push_back(25);
  markerStyle2_.push_back(21);
  markerStyle2_.push_back(26);
  markerStyle2_.push_back(22);
  markerStyle2_.push_back(23);
  THStack signalsAG;
  for (unsigned int i = 0; i < Signals.size(); i++){
    if (!compareMultiple && !sigError) Signals[i]->Draw("SAMEHISTP");
    if (!compareMultiple &&  sigError) Signals[i]->Draw("SAMEPE");
    if (compareMultiple) Signals[i]->SetMarkerColor(Colors2[i]); 
    if (compareMultiple) signalsAG.Add(Signals[i]); 
    else if (Colors.size() >= i + Backgrounds.size() + 1) Signals[i]->SetMarkerColor(Colors[i + Backgrounds.size()]);

    bool hack = true;

    if (!hack) {
        Signals[i]->SetLineColor(kBlack);
        Signals[i]->SetLineWidth(3);
        if (!markerStyle2) Signals[i]->SetMarkerStyle(markerStyle[i%7]);
        if ( markerStyle2) Signals[i]->SetMarkerStyle(markerStyle2_[i%7]);
    } else {
        Signals[i]->SetLineColor(kRed);
        Signals[i]->SetLineWidth(4);
        Signals[i]->SetMarkerSize(4);
        Signals[i]->Draw("SAMEHISTLPE");
    }

  }
  if (compareMultiple) signalsAG.Draw("SAMEHISTP");

  //Draw syst errors
  TH1F *background_syst = 0;
  TH1F *background_sum = 0;
  if (Background_systs.size() > 0){
    background_syst = new TH1F(*Background_systs[0]); 
    if (!background_syst->GetSumw2N()) background_syst->Sumw2(); 
    background_syst->SetFillColor(kGray+2); 
    background_syst->SetFillStyle(systFillStyle); 
    if (systBlack) background_syst->SetFillColor(kBlack); //should have a better option for these?
  }
  if (Backgrounds.size() > 0){
    background_sum = new TH1F(*Backgrounds[0]); 
    if (!background_sum->GetSumw2N()) background_sum->Sumw2(); 
  }
  for (unsigned int iSyst = 0; iSyst < Background_systs.size(); iSyst++){
    if (iSyst == 0) continue;
    background_syst->Add(Background_systs[iSyst]); 
  }
  for (unsigned int iBack = 0; iBack < Backgrounds.size(); iBack++){
    if (iBack == 0) continue;
    background_sum->Add(Backgrounds[iBack]); 
  }
  //Now add stat error to systs
  if (systInclStat && Backgrounds[0]->GetNbinsX() > 0){
    for (int i = 1; i <= Backgrounds[0]->GetNbinsX(); i++){
      float err = background_syst->GetBinError(i); 
      float stat = background_sum->GetBinError(i); 
      background_syst->SetBinError(i, sqrt( pow(err, 2) + pow(stat, 2) ) ); 
    }
  }

    if(overrideSyst->GetEntries() > 0) {
        overrideSyst->SetMarkerSize(0); 
        overrideSyst->SetFillColor(kGray+2); 
        overrideSyst->SetFillStyle(systFillStyle); 
        overrideSyst->Draw("E2 SAME");
    }

  if (background_syst != 0 && do_background_syst == true) background_syst->Draw("E2 SAME");

  //Redraw the data on top of the shaded area
  if(noErrBars) Data->Draw("PSAME");
  else {
    if (poissonErrorsNoZeros && !noData) {
      //do this to avoid showing error bars for zero entries
      TGraphAsymmErrors * g = new TGraphAsymmErrors(Data);
      g->SetMarkerSize(0);
      g->SetLineWidth(Data->GetLineWidth());
      g->SetLineColor(Data->GetLineColor());
      const double alpha = 1 - 0.6827;
      for (int i = 0; i < g->GetN(); ++i) {
        int N = g->GetY()[i];
        if (noGrass) {
            if (N == 0) continue;
        }
        double L = (N==0) ? 0 : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
        // double U = (N==0) ? 0 : (ROOT::Math::gamma_quantile_c(alpha/2,N+1,1));
        // // poisson grass
        double U = (ROOT::Math::gamma_quantile_c(alpha/2,N+1,1));
        double xerr = Data->GetBinWidth(i)/2.;
        if (noDataWidth) xerr = 0.;
        g->SetPointError(i, xerr, xerr, N-L, U-N);
        // g->SetPointEYlow(i, N-L);
        // g->SetPointEYhigh(i, U-N);
        // std::cout << " i: " << i << " N: " << N << " U: " << U << " L: " << L << " N-L: " << N-L << " U-N: " << U-N << std::endl;
      }
      g->Draw("PZSAME");
      Data->Draw("PSAME");
    } else Data->Draw("PSAMEE");
  }

  if (makeTable) {
      bool hasSignal = Signals.size() > 0;
      // dump out a table with .txt
      // TODO: this is ugly. make more general and put in function. right now it only works for cases where we have 1 data and at least 1 background
      TString buff = "";
      std::vector<float> bkgTots(Backgrounds.size(), 0.0); // totals along columns, indexed by ib
      std::vector<float> bkgSqErrors(Backgrounds.size(), 0.0);
      float totData = 0;

      buff += "bin|xrange|";
      for (unsigned int ib = 0; ib < Backgrounds.size(); ib++){
          buff += Titles[ib];
          buff += "|";
      }
      buff += "total_bkg|data|data/bkg";
      if (hasSignal) buff += Form("|%s|s/b",SignalTitles.at(0).c_str());
      buff += "\n";
      for (int xbin=1; xbin <= Data->GetNbinsX(); xbin++) {

          float lowEdge = Data->GetXaxis()->GetBinLowEdge(xbin);
          float upEdge = Data->GetXaxis()->GetBinUpEdge(xbin);
          float dataContent = Data->GetBinContent(xbin);
          totData += dataContent;
          buff += Form("%i|[%.2f,%.2f]|",xbin,lowEdge,upEdge);
          
          float bkgTot = 0.0; // total along row
          float bkgSqError = 0.0;
          for (unsigned int ib = 0; ib < Backgrounds.size(); ib++){

              float binContent = Backgrounds[ib]->GetBinContent(xbin);
              float binError = Backgrounds[ib]->GetBinError(xbin);

              bkgTot += binContent;
              bkgSqError += binError*binError;

              bkgTots[ib] += binContent;
              bkgSqErrors[ib] += binError*binError;

              buff += Form("%.2f+-%.2f|", binContent, binError);
          }

          float r = dataContent/bkgTot;
          
          // Total columns, ratio
          buff += Form("%.2f+-%.2f|", bkgTot, sqrt(bkgSqError));
          buff += Form("%.0f|", dataContent);
          buff += Form("%.2f+-%.2f", r, r*sqrt( 1.0/dataContent + bkgSqError/(bkgTot*bkgTot) ));
          if (hasSignal) {
              buff += Form("|%.2f+-%.2f", Signals.at(0)->GetBinContent(xbin), Signals.at(0)->GetBinError(xbin));
              buff += Form("|%.2f", Signals.at(0)->GetBinContent(xbin)/bkgTot);
          }
          buff += "\n";

      }

      buff += "\n";

      // Totals: Last row
      float totalBkg = 0.;
      float totalBkgSqError = 0.;
      for(auto& num : bkgTots) totalBkg += num;
      for(auto& num : bkgSqErrors) totalBkgSqError += num;
      buff += " | |";
      for (unsigned int ib = 0; ib < Backgrounds.size(); ib++){
          buff += Form("%.2f+-%.2f", bkgTots[ib], sqrt(bkgSqErrors[ib]));
          buff += "|";
      }

      float r = 1.0*totData/totalBkg;
      buff += Form("%.2f+-%.2f|", totalBkg, sqrt(totalBkgSqError));
      buff += Form("%.0f|", 1.0*totData);
      buff += Form("%.2f+-%.2f", r, r*sqrt( 1.0/totData + totalBkgSqError/(totalBkg*totalBkg) ));
      if (hasSignal) {
          buff += Form("|%.2f", Signals[0]->Integral());
      }
      buff += "\n";

      TString tableFileName(outputName.c_str());
      std::ofstream tableFile;
      tableFile.open("tmp_table.txt");
      tableFile << buff.Data();
      tableFile.close();
      system(Form("cat tmp_table.txt | column -t -s'|' -x > %s.txt", tableFileName.Data()));

  }


  //Legend
  TLegend *leg;
  TString dataDrawOpt = "lep";
  if (noDataWidth) dataDrawOpt = "ep";
  if ((Backgrounds.size()+Signals.size() == 1 || Backgrounds.size()+Signals.size() == 2) && (noData || noRatioPlot || ratioOnly) && !compareMultiple) leg = new TLegend(0.7+legendRight,0.79+legendUp,0.92+legendRight+legendWider_,0.87+legendUp+legendTaller_); 
  else if ((Backgrounds.size()+Signals.size() == 1 || Backgrounds.size()+Signals.size() == 2) && !noData && !noRatioPlot && !ratioOnly) leg = new TLegend(0.7+legendRight,0.69+legendUp,0.92+legendRight+legendWider_,0.77+legendUp+legendTaller_); 
  else leg = new TLegend(0.7+legendRight,0.59+legendUp,0.92+legendRight+legendWider_,0.87+legendUp+legendTaller_);
  leg->SetTextSize(legendTextSize);
  leg->SetTextFont(42);
  if (!noData && !ratioOnly && !legendCounts) leg->AddEntry(Data, dataName.c_str(),dataDrawOpt);
  if (!noData && !ratioOnly && legendCounts) leg->AddEntry(Data, Form("%s [%i]",dataName.c_str(),(int)(Data->Integral())),dataDrawOpt);
  if (showPercentage) for (int i = Titles.size()-1; i > -1; i--) Titles[i] =  Form("%s [%i%%]", Titles[i].c_str(), percent[i]);
  if (legendCounts) for (int i = Titles.size()-1; i > -1; i--) Titles[i] =  Form("%s [%.2f]", Titles[i].c_str(), counts[i]);
  if (!dots && !nostack) for (int i = Titles.size()-1; i > -1; i--) leg->AddEntry(Backgrounds[i], Titles[i].c_str(), "f");
  // if (dots || nostack) for (int i = Titles.size()-1; i > -1; i--) leg->AddEntry(Backgrounds[i], Titles[i].c_str(), "L");
  if (dots || nostack) for (int i = Titles.size()-1; i > -1; i--) leg->AddEntry(Backgrounds[i], Titles[i].c_str(), "f"); // FIXME
  if (use_signals && !compareMultiple) for (int i = SignalTitles.size()-1; i > -1; i--) leg->AddEntry(Signals[i], SignalTitles[i].c_str(), "lep");
  leg->SetFillStyle(0);
  if ( legendBox) leg->SetBorderSize(1);
  if (!legendBox) leg->SetBorderSize(0);
  if (!noLegend) leg->Draw();

  if (percentageInBox){
    TLatex *pctTex = new TLatex();
    leg->SetMargin(leg->GetMargin()*1.25);
    float legHeight=abs(leg->GetY1()-leg->GetY2());
    float entryHeight=legHeight/leg->GetNRows();
    float legWidth=abs(leg->GetX2()-leg->GetX1());
    float halfFillWidth = legWidth*leg->GetMargin()/2;
    int nRows = leg->GetNRows();

    float yRowOffset = 0.65 - nRows*0.05; // painstakingly-determined empirical formula
    float xPctFudge = 0.01, yPctFudge = 0.01;
    if (Titles.size() < 5) yPctFudge = 0.005; // damn, this works nicely
    if (Titles.size() > 6) yPctFudge = -0.001;
    if (Titles.size() > 7) yPctFudge = 0.005;
    if (Titles.size() > 9) yPctFudge = 0.015;
    if (Signals.size() > 0) yPctFudge += 0.0345;

    yPctFudge += 0.008;

    for (unsigned int iEntry = 0; iEntry < Titles.size(); iEntry++)  {
      float xPctNDC = xPctFudge+leg->GetX1()+halfFillWidth*0.8;
      float yPctNDC = yPctFudge+leg->GetY1()+(iEntry+yRowOffset)*entryHeight;
      pctTex->SetTextSize(0.022);
      pctTex->SetTextAlign(22);
      pctTex->SetTextFont(42);

      float colR, colG, colB;
      gROOT->GetColor(Colors[iEntry])->GetRGB(colR,colG,colB);
      float darkness = 1.0 - ( 0.299 * colR + 0.587 * colG + 0.114 * colB);
      if(darkness < 0.5) pctTex->SetTextColor(kBlack);
      else pctTex->SetTextColor(kWhite);
      
      pctTex->DrawLatexNDC(xPctNDC,yPctNDC,Form("%i#scale[0.5]{#lower[-0.3]{%%}}",percent[iEntry]));
    }
  }

  //Get number of entries for data, MC
  float nEventsMC = 0.0;
  int nEventsData = Data->Integral(0,Data->GetNbinsX()+doOverflow);
  for (unsigned int i = 0; i < Backgrounds.size(); i++){
      nEventsMC += Backgrounds[i]->Integral(0,Backgrounds[i]->GetNbinsX()+doOverflow);
  }

  //Draw title & subtitle on plot 
  TLatex *tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSize(0.035);
  float title_y_coord = 0.90;
  if (noData || noRatioPlot) title_y_coord = 0.78; 
  if (outOfFrame && (noData || noRatioPlot)) title_y_coord += 0.09;
  if (colorTitle) title = Form("#color[4]{%s}",title);
  if (noTextBetweenPads) title_y_coord+=0.03;
  tex->DrawLatex(0.18,title_y_coord,title);
  tex->SetTextSize(0.045);
  // tex->DrawLatex(0.18,title_y_coord-0.05,title2);
  tex->DrawLatex(0.19,title_y_coord-0.06,title2);
  tex->SetTextSize(0.035);
  float yCounts = (strcmp(title2, "") == 0) ? title_y_coord-0.05 : title_y_coord-0.10; 
  if ( !noData && !noRatioPlot && doCounts) tex->DrawLatex(0.16,yCounts,Form("%i (Data), %0.1f (MC)",nEventsData,nEventsMC)); 
  if (( noData || noRatioPlot) && doCounts) tex->DrawLatex(0.16,yCounts,Form("%0.1f (MC)",nEventsMC)); 

  //Draw a box (convert a string into coordinates to make 2 hlines and 2 vlines)
  TString box(boxLines);
  if(box.CountChar(',') == 3) {
      TObjArray *tokens = box.Tokenize(",");
      std::string xLeft = ((TObjString *)(tokens->At(0)))->String().Data();
      std::string yTop = ((TObjString *)(tokens->At(1)))->String().Data();
      std::string xRight = ((TObjString *)(tokens->At(2)))->String().Data();
      std::string yBottom = ((TObjString *)(tokens->At(3)))->String().Data();
      hLines.push_back(yTop + "," + xLeft + "," + xRight);
      hLines.push_back(yBottom + "," + xLeft + "," + xRight);
      vLines.push_back(xLeft + "," + yBottom + "," + yTop);
      vLines.push_back(xRight + "," + yBottom + "," + yTop);
  }


  //Draw vertical lines
  c0.Update();
  for (unsigned int i = 0; i < vLines.size(); i++) {
    // extract yposition,minx,maxx (last two are optional)
    float xPos;
    float yMin = Backgrounds.size() > 0 ? Backgrounds[0]->GetXaxis()->GetXmin() : Signals[0]->GetXaxis()->GetXmin();
    float yMax = Backgrounds.size() > 0 ? Backgrounds[0]->GetXaxis()->GetXmax() : Signals[0]->GetXaxis()->GetXmax();

    TString s1(vLines[i]);
    if (s1.CountChar(',') == 0) {
      xPos = s1.Atof();
      DrawVerticalLine(xPos); 
    } else if (s1.CountChar(',') == 2) {
      TObjArray *tokens = s1.Tokenize(",");
      xPos = (((TObjString *)(tokens->At(0)))->String()).Atof();
      yMin = (((TObjString *)(tokens->At(1)))->String()).Atof();
      yMax = (((TObjString *)(tokens->At(2)))->String()).Atof();

      TLine linecut;
      c0.Update();
      linecut.SetLineStyle(2);
      linecut.SetLineWidth(2);
      linecut.SetLineColor(kGray+2);
      linecut.DrawLine(xPos, yMin, xPos, yMax);
    } else {
      std::cout << "You goofed with your vLine syntax. Either specify xpos,miny,maxy or just xpos" << std::endl;
      continue;
    }
  }

  //Draw Horizontal lines
  for (unsigned int i = 0; i < hLines.size(); i++){
    // extract yposition,minx,maxx (last two are optional)
    float yPos;
    float xMin = Backgrounds.size() > 0 ? Backgrounds[0]->GetXaxis()->GetXmin() : Signals[0]->GetXaxis()->GetXmin();
    float xMax = Backgrounds.size() > 0 ? Backgrounds[0]->GetXaxis()->GetXmax() : Signals[0]->GetXaxis()->GetXmax();

    TString s1(hLines[i]);
    if (s1.CountChar(',') == 0) {
      yPos = s1.Atof();
    } else if (s1.CountChar(',') == 2) {
      TObjArray *tokens = s1.Tokenize(",");
      yPos = (((TObjString *)(tokens->At(0)))->String()).Atof();
      xMin = (((TObjString *)(tokens->At(1)))->String()).Atof();
      xMax = (((TObjString *)(tokens->At(2)))->String()).Atof();
    } else {
      std::cout << "You goofed with your hLine syntax. Either specify ypos,minx,maxx or just ypos" << std::endl;
      continue;
    }
    TLine linecut;
    c0.Update();
    linecut.SetLineStyle(2);
    linecut.SetLineWidth(2);
    linecut.SetLineColor(kGray+2);
    linecut.DrawLine(xMin, yPos, xMax, yPos);
  }


  //Draw header
  float type_y = .95;
  if ((!noData && !noRatioPlot) || compareMultiple) type_y = .96;
  tex->SetTextSize(0.040);
  tex->SetTextFont(42);
  if (overrideHeader[0] == '\0' and !noTextBetweenPads){
    tex->SetTextAlign(31);
    float xpos = 0.96;
    // if (noTextBetweenPads) {
    //   xpos = 0.92;
    //   type_y = 0.91;
    // }
    if (!noLumi && lumiPrec == 2) tex->DrawLatex(xpos,type_y,Form("%.2f %s^{-1} (%s TeV)", stof(lumi), lumiUnit.c_str(), energy.c_str()));
    if (!noLumi && lumiPrec == 1) tex->DrawLatex(xpos,type_y,Form("%.1f %s^{-1} (%s TeV)", stof(lumi), lumiUnit.c_str(), energy.c_str()));
    if (!noLumi && lumiPrec == 0) tex->DrawLatex(xpos,type_y,Form("%.0f %s^{-1} (%s TeV)", stof(lumi), lumiUnit.c_str(), energy.c_str()));
    // if ( noLumi) tex->DrawLatex(xpos,type_y,Form("           (%s TeV)", energy.c_str()));
    if ( noLumi) tex->DrawLatex(xpos,type_y,"                   "); // FIXME
    tex->SetTextAlign(11);
  }


  // float xshift = -0.00;//configurable?
  float xshift = (linear ? -0.00 : -0.03) ;//configurable?


  if (!noType && !noTextBetweenPads) {
    float ycoord = outOfFrame ? .00 : .08;
    // float ycoord = outOfFrame ? .005 : .08;
    if ((noData || noRatioPlot) && overrideHeader[0] == '\0'){
      tex->DrawLatex(0.16+xshift,type_y-ycoord, "#font[61]{#scale[1.25]{CMS}}");
      float xcoord = outOfFrame ? .27+xshift : .16+xshift;
      if (type!="") tex->DrawLatex(xcoord,type_y-ycoord, Form("#font[52]{%s}",type.c_str()));
    }
    if (!noData && !noRatioPlot && overrideHeader[0] == '\0'){ 
      float xcoord = outOfFrame ? .16+xshift : .83+xshift;
      // if (noTextBetweenPads) {
	// ycoord = 0.00;
	// xcoord = 0.16;
      // }
      tex->DrawLatex(xcoord,type_y-ycoord, "#font[61]{#scale[1.25]{CMS}}");
      xcoord = outOfFrame ? .27+xshift : .73+xshift;
      if (type!="") tex->DrawLatex(xcoord,type_y-ycoord, Form("#font[52]{%s}",type.c_str()));
    }
  }
  if (overrideHeader[0] != '\0') tex->DrawLatex(0.17,type_y,Form("%s", overrideHeader.c_str()));
  if (!noData && !noRatioPlot && stack->GetMaximum() > 80000 && linear) finPad[0]->SetPad(0.0, 0.0, 1.0, 0.84);

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
  TH1F* background_syst_ratio = 0;
  if ((!noData || compareMultiple) && !noRatioPlot){
    if (compareMultiple) Data = (TH1F*)Signals[0]->Clone();
    if (compareMultiple && Signals.size() > 1) for (unsigned int i = 1; i < Signals.size(); i++) Data->Add(Signals[i]); 
    finPad[1]->cd();
    TH1F* err_hist = 0;
    if (compareMultiple) err_hist = (TH1F*)Signals[0]->Clone(); 
    if (!compareMultiple) err_hist = (TH1F*)Backgrounds[0]->Clone(); 
    err_hist->SetTitle("");
    err_hist->Draw();

    if (poissonErrorsNoZeros) err_hist->SetLineColor(0);
    else err_hist->SetLineColor(ratioColor);

    if (!ratioLine) err_hist->SetMarkerColor(ratioColor);
    err_hist->GetYaxis()->SetTitle("Data/MC");
    err_hist->GetYaxis()->SetTitleSize(0.08);
    err_hist->GetYaxis()->SetTitleOffset(1.8);
    if (Background_systs.size() > 0) background_syst_ratio = (TH1F*)background_syst->Clone();
    if(overrideSyst->GetEntries() > 0) {
        background_syst_ratio = (TH1F*)overrideSyst->Clone();
        background_syst_ratio->Sumw2();
        background_syst_ratio->SetFillColor(kGray+2); 
        background_syst_ratio->SetFillStyle(systFillStyle); 
    }
    for (int ib = 1; ib < err_hist->GetNbinsX()+1; ib++){
      float MC_value = 0;
      float MC_error_2 = 0;
      float data_value = Data->GetBinContent(ib);
      float data_err = Data->GetBinError(ib);
      for (unsigned int i = 0; i < Backgrounds.size(); i++){
        if (ratioNumerBG >= 0 && ratioNumerBG == Backgrounds_number[i]) {
            data_value = Backgrounds[i]->GetBinContent(ib);
            data_err = pow(Backgrounds[i]->GetBinError(ib), 2);
        }
        if (ratio >= 0 && ratio != Backgrounds_number[i]) continue; 
        MC_value += Backgrounds[i]->GetBinContent(ib);
        MC_error_2 += pow(Backgrounds[i]->GetBinError(ib), 2);
      }
      float value = (MC_value > 0 ? data_value/MC_value : 1000);
      if (data_value != 0 || MC_value != 0) err_hist->SetBinContent(ib, value);
      if (dontShowZeroRatios && data_value == 0){ err_hist->SetBinContent(ib, -9999);  } 
      float MC_err = sqrt(MC_error_2);
      if(!noErrBars) err_hist->SetBinError(ib, (data_value == 0 || MC_value == 0) ? 0.001 : (value * sqrt( pow(MC_err/MC_value, 2) + pow(data_err/data_value, 2)) ) );
      if (Background_systs.size() > 0 && background_syst->GetBinContent(ib) > 0) background_syst_ratio->SetBinError(ib, background_syst->GetBinError(ib)/background_syst->GetBinContent(ib)); 
      else if (Background_systs.size() > 0) background_syst_ratio->SetBinError(ib, 0); 
      if (Background_systs.size() > 0) background_syst_ratio->SetBinContent(ib, 1); 

      // if (ib == 4) {
      //     std::cout <<  " value: " << value <<  " MC_err: " << MC_err <<  " MC_value: " << MC_value <<  " data_err: " << data_err <<  " data_value: " << data_value <<  std::endl;
      // }
      // // 0.139609 err_hist->GetBinError(ib): 0.0987478
      // // err_hist->SetBinContent(4, 0.139609);
      // // err_hist->SetBinError(4, 0.0987478);
      // std::cout <<  " ib: " << ib <<  " err_hist->GetBinContent(ib): " << err_hist->GetBinContent(ib) <<  " err_hist->GetBinError(ib): " << err_hist->GetBinError(ib) <<  std::endl;

      if (overrideSyst->GetEntries() > 0) {
          if (background_syst_ratio->GetBinContent(ib) > 0) {
              background_syst_ratio->SetBinError(ib, overrideSyst->GetBinError(ib)/overrideSyst->GetBinContent(ib)); 
          }
          else background_syst_ratio->SetBinError(ib, 0); 
          background_syst_ratio->SetBinContent(ib, 1); 
      }

      if (doPull) {
          // float pull = RooStats::NumberCountingUtils::BinomialObsZ(19,41,0.5);
          // Do the below because the stupid line above isn't working with root, even
          // with the proper includes. For reference, the implementation matches
          // https://root.cern.ch/doc/master/NumberCountingUtils_8cxx_source.html#l00090
          int mainObs = data_value;
          float backgroundObs = MC_value;
          float relativeBkgUncert = overrideSyst->GetBinError(ib) / MC_value;

          Double_t tau = 1./backgroundObs/(relativeBkgUncert*relativeBkgUncert);
          Double_t auxiliaryInf = backgroundObs*tau;

          if (mainObs == 0) {
              tau = 999.;
              auxiliaryInf = 1.0;
          }
          Double_t P_Bi = TMath::BetaIncomplete(1./(1.+tau),mainObs,auxiliaryInf+1);
          float pull = ROOT::Math::normal_quantile_c(P_Bi,1);

          // For mainObs==0, P_Bi is 0 and pull becomes infinite
          // Screw it and just use gaussian pull at this point
          if (pull>100) pull = (data_value-MC_value) / sqrt(data_value + pow(overrideSyst->GetBinError(ib),0.5));
          
          // Naive gaussian pulls:
          // float pull = (data_value-MC_value) / sqrt(data_value + pow(overrideSyst->GetBinError(ib),0.5));
          err_hist->SetBinContent(ib, pull);
          err_hist->SetBinError(ib, 0.0);
      }
    }
    if (!ratioLine) {
      err_hist->SetMarkerStyle(20);
      if (err_hist->GetNbinsX() > 150) err_hist->SetMarkerSize(0.5);
      else if (err_hist->GetNbinsX() > 100) err_hist->SetMarkerSize(0.6);
      else if (err_hist->GetNbinsX() > 60) err_hist->SetMarkerSize(0.8);
    }
    if(noErrBars && ratioLine && !poissonErrorsNoZeros) err_hist->Draw("HIST");
    else if(noErrBars && !poissonErrorsNoZeros) err_hist->Draw("P");
    else if(poissonErrorsNoZeros) {
    }
    else err_hist->Draw("PE");
    TText *blah = new TText();
    blah->SetTextFont(42);
    blah->SetTextSize(0.17);
    blah->SetTextAngle(90);
    blah->DrawTextNDC(0.045,topYaxisTitle.length()<6?0.35:0.15,topYaxisTitle.c_str());
    TLine line;
    line.SetLineColor(kGray+2);
    line.SetLineWidth(2);
    int maxbin = err_hist->GetXaxis()->GetNbins();
    line.DrawLine(err_hist->GetXaxis()->GetBinLowEdge(1),doPull?0:1,err_hist->GetXaxis()->GetBinUpEdge(maxbin),doPull?0:1);
    if (do_background_syst && Background_systs.size() > 0) background_syst_ratio->Draw("E2 SAME");//draw the shaded area before the dots
    if (overrideSyst->GetEntries() > 0) background_syst_ratio->Draw("E2 SAME");//draw the shaded area before the dots
    if(noErrBars && ratioLine && !poissonErrorsNoZeros) err_hist->Draw("HIST SAME");
    else if(noErrBars && !poissonErrorsNoZeros) err_hist->Draw("pSAME");
    else if (poissonErrorsNoZeros) {
    }
    else err_hist->Draw("pESAME"); 
    err_hist->GetXaxis()->SetLabelSize(0);
    err_hist->GetYaxis()->SetLabelSize(0.2);
    if (noTextBetweenPads) err_hist->GetYaxis()->SetLabelSize(0.15);
    err_hist->GetYaxis()->SetRangeUser(0., ratioUpperBound);
    if (doPull) {
        err_hist->GetYaxis()->SetRangeUser(-2.5,2.5);
    }
    if (nDivisions != -1 && nDivisions > 0) err_hist->GetXaxis()->SetNdivisions(nDivisions, kTRUE);
    if (nDivisions != -1 && nDivisions < 0) err_hist->GetXaxis()->SetNdivisions(nDivisions, kFALSE);
    err_hist->GetYaxis()->SetNdivisions(505);

    ///////
    ///////
    if (poissonErrorsNoZeros) {
        //do this to avoid showing error bars for zero entries
        const double alpha = 1 - 0.6827;
        TGraphAsymmErrors * g = new TGraphAsymmErrors();
        for (int ib = 1; ib < err_hist->GetNbinsX()+1; ib++){
            float MC_value = 0;
            float MC_error = 0;
            float MC_error_2 = 0;
            float data_value = Data->GetBinContent(ib);
            float data_err = Data->GetBinError(ib);
            for (unsigned int i = 0; i < Backgrounds.size(); i++){
                MC_value += Backgrounds[i]->GetBinContent(ib);
                MC_error_2 += pow(Backgrounds[i]->GetBinError(ib), 2);
            }

            if (MC_value < 1e-6 && data_value == 0) continue;

            if (noGrass) {
                if (data_value == 0) continue;
            }

            // MC_error = pow(MC_error_2, 0.5);
            MC_error = 0.0;

            double data_up = ROOT::Math::gamma_quantile_c(alpha/2,data_value+1,1) - data_value;
            double data_down = data_value == 0 ? 0. : data_value - ROOT::Math::gamma_quantile(alpha/2,data_value,1);

            double ratio = data_value / MC_value;
            double xerr = err_hist->GetBinWidth(ib)/2.;
            if (noDataWidth) xerr = 0.;
            double rerrup = pow(pow(data_up/MC_value,2) + pow(MC_error*data_value/(MC_value*MC_value),2), 0.5);
            double rerrdown = pow(pow(data_down/MC_value,2) + pow(MC_error*data_value/(MC_value*MC_value),2), 0.5);
            int ipoint = g->GetN();
            g->SetPoint(ipoint, err_hist->GetBinCenter(ib), ratio);
            g->SetPointError(ipoint, xerr, xerr, rerrdown, rerrup);

            // std::cout << " ib: " << ib << " ratio: " << ratio << " xerr: " << xerr << " rerrdown: " << rerrdown << " rerrup: " << rerrup << " data_value: " << data_value << " MC_value: " << MC_value << " MC_error: " << MC_error << " data_up: " << data_up << " data_down: " << data_down << std::endl;
            // ib ratio xerr rerrdown rerrup data_value MC_value MC_error data_up data_down
        }
        // g->SetMarkerSize(0);
        g->SetLineWidth(Data->GetLineWidth());
        g->SetLineColor(Data->GetLineColor());
        // g->SetLineColor(kBlue);
        // g->SetLineColor(kBlack);
        g->Draw("PEZSAME0");
        // g->Draw("PEZSAME");
        // g->Draw("PEZ");
    }
    ///////
    ///////

  }
  //--------------------------------

  // Draw US flag
  TString flagString(flagLocation);
  if(flagString.CountChar(',') == 2) {
      TObjArray *tokens = flagString.Tokenize(",");
      float cx = (((TObjString *)(tokens->At(0)))->String()).Atof();
      float cy = (((TObjString *)(tokens->At(1)))->String()).Atof();
      float size = (((TObjString *)(tokens->At(2)))->String()).Atof();
      // drawFlag(&c0, 0.5,0.7, 0.1); // middle for ratio plots
      // drawFlag(&c0, 0.6,0.965, 0.07); // top for nonratio plots
      drawFlag(&c0, cx,cy,size); // custom
  }

  if (noTextBetweenPads) {
      finPad[1]->cd();
      TLatex *textest = new TLatex();
      float ytest = 0.85;
      float basesize = 0.155;
      textest->SetNDC();
      textest->SetTextSize(basesize);
      textest->SetTextFont(42);
      textest->SetLineWidth(2);
      if (!doWide) textest->DrawLatex(0.695,ytest,Form("%.1f %s^{-1} (%s TeV)", stof(lumi), lumiUnit.c_str(), energy.c_str()));
      else textest->DrawLatex(0.745,ytest,Form("%.1f %s^{-1} (%s TeV)", stof(lumi), lumiUnit.c_str(), energy.c_str()));

      textest->SetTextSize(basesize*5./4.);
      textest->SetTextFont(61);
      textest->DrawLatex((linear ? 0.160 : 0.13),ytest,"CMS");

      textest->SetTextSize(basesize);
      textest->SetTextFont(52);
      if (!doWide) textest->DrawLatex((linear ? 0.280 : 0.25),ytest,Form("%s",type.c_str()));
      else textest->DrawLatex(0.23,ytest,Form("%s",type.c_str()));
      finPad[0]->cd();
  }


  //Print plot as pdf 
  if (!noOutput){
    if (outputName.find(".") < outputName.length()) c0.Print(outputName.c_str());
    else if (png) c0.Print(Form("%s.png", outputName.c_str()));
    else c0.Print(Form("%s.pdf", outputName.c_str()));
  }

  if (makeRootFile) {
      TFile *outFile = new TFile(Form("%s.root", outputName.c_str()), "RECREATE");
      Data->Write();
      for (unsigned int ib = 0; ib < Backgrounds.size(); ib++){
          Backgrounds[ib]->Write();
      }
      finPad[0]->Write();
      finPad[1]->Write();
      c0.Write();
      outFile->Close();
  }

#if ROOT_VERSION_CODE > ROOT_VERSION(6,8,0)
  if (makeJSON) {
      TBufferJSON::ExportToFile(Form("%s.json",outputName.c_str()),&c0);
  }
#endif

  //Clean up
  for (unsigned int i = 0; i < Signals.size(); i++) delete Signals[i];
  for (unsigned int i = 0; i < Backgrounds_pair.size(); i++){
    if (Backgrounds_pair[i].first  != 0) delete Backgrounds_pair[i].first;
    if (Backgrounds_pair[i].second != 0) delete Backgrounds_pair[i].second;
  }
  delete background_syst;
  if( background_syst_ratio != 0 ) delete background_syst_ratio;
}

//Overload function for case of no stat errors
void dataMCplotMaker(TH1F* Data_in, std::vector <TH1F*> Backgrounds_in, std::vector <std::string> Titles, std::string titleIn, std::string title2In, std::string options_string, std::vector <TH1F*> Signals_in, std::vector <std::string> SignalTitles, std::vector <Color_t> color_input, TH1F* overrideSyst){

  do_background_syst = false;

  //Make a null pair for each 
  std::vector< std::pair<TH1F*, TH1F*> > Backgrounds_pair_in;
  for (unsigned int i = 0; i < Backgrounds_in.size(); i++){
    TH1F* null_hist = new TH1F(Form("dummy_bkgd_syst_%i", i), Form("dummy_bkgd_syst_%i", i), 1, 0, 1); 
    std::pair<TH1F*, TH1F*> temp = std::make_pair( Backgrounds_in[i], null_hist ); 
    Backgrounds_pair_in.push_back(temp); 
  }

  dataMCplotMaker(Data_in, Backgrounds_pair_in, Titles, titleIn, title2In, options_string, Signals_in, SignalTitles, color_input, overrideSyst); 

  for (unsigned int i = 0; i < Backgrounds_in.size(); i++){
    delete Backgrounds_pair_in[i].second;
  }

}

void dataMCplotMaker(TH1F* Data_in, std::vector <std::pair <TH1F*, float> > Backgrounds_in, std::vector <std::string> Titles, std::string titleIn, std::string title2In, std::string options_string, std::vector <TH1F*> Signals_in, std::vector <std::string> SignalTitles, std::vector <Color_t> color_input){

  do_background_syst = true;

  std::vector< std::pair<TH1F*, TH1F*> > Backgrounds_pair_in;
  for (unsigned int i = 0; i < Backgrounds_in.size(); i++){
    TH1F* temp_hist = new TH1F(*Backgrounds_in[i].first); 
    for (int j = 0; j < Backgrounds_in[i].first->GetNbinsX(); j++) temp_hist->SetBinError(j, Backgrounds_in[i].first->GetBinContent(j)*Backgrounds_in[i].second);
    std::pair <TH1F*, TH1F*> temp = std::make_pair( Backgrounds_in[i].first, temp_hist ); 
    Backgrounds_pair_in.push_back(temp); 
  }

  dataMCplotMaker(Data_in, Backgrounds_pair_in, Titles, titleIn, title2In, options_string, Signals_in, SignalTitles, color_input); 

}

void drawFlag(TCanvas *c1, float cx, float cy, float size) {
    c1->cd();
    float aspect_ratio = c1->GetWindowWidth()/c1->GetWindowHeight();
    float xmin = cx-size/2.;
    float xmax = cx+size/2.;
    float ymin = cy-size/(2./aspect_ratio);
    float ymax = cy+size/(2./aspect_ratio);
    TPad* fp = new TPad("fp","fp",xmin,ymin,xmax,ymax);
    fp->SetFillStyle(0);
    fp->Draw();
    fp->cd();
    float A = 1.;
    float B = 1.9;
    float D = 0.76;
    float G = 0.063/B;
    float H = 0.063/B;
    float E = 0.054;
    float F = 0.054;
    for (int i = 0; i < 13; i++) {
        float xlow = 0.;
        float xhigh = 1.;
        float ylow = 0.5*(1.-A/B) + i*(A/B)/13.;
        float yhigh = 0.5*(1.-A/B) + (i+1)*(A/B)/13.;
        if (i >= 6) xlow = D/B;
        // auto col(i%2 ? kWhite : kRed-10);
        auto col(i%2 ? kWhite : kRed-7);
        TBox* box = new TBox(xlow,ylow,xhigh,yhigh);
        box->SetFillColor(col);
        box->SetLineColor(col);
        box->Draw();
    }
    TBox *starbox = new TBox( 0., 0.5*(1-A/B)+6./13*(A/B), D/B, 1.-0.5*(1-A/B) );
    // starbox->SetFillColor(kBlue-10);
    // starbox->SetLineColor(kBlue-10);
    starbox->SetFillColor(kBlue-7);
    starbox->SetLineColor(kBlue-7);
    starbox->Draw();

    int row = 0;
    int inrow = 0;
    float ybottom = 0.5*(1-A/B)+6./13*(1-A/B);
    float starsize = 0.05+(xmax-xmin)*2.0;
    for (int i = 0; i < 50; i++) {

        float x = -1.;
        float y = -1.;
        if (inrow == 0) x = G;
        else x = G+2*H*inrow;
        if (row == 0) y = ybottom+E;
        else y = ybottom+E+(F*row)*(A/B);
        if (row%2!=0) x += H;

        TMarker *tm = new TMarker(x,y,kFullStar);
        tm->SetMarkerColor(kWhite);
        tm->SetMarkerSize(-1.0*starsize); // negative to flip so points upwards
        tm->Draw();

        inrow++;
        if (row%2 == 0) {
            if (inrow == 6) {
                inrow = 0;
                row += 1;
            }
        } else {
            if (inrow == 5) {
                inrow = 0;
                row += 1;
            }
        }
    }

    TLatex *lab = new TLatex(0.5,0.15,"#font[52]{Mostly made in USA}");
    lab->SetTextAlign(22);
    lab->SetTextSize(0.1);
    // lab->SetTextColor(kGray);
    lab->SetTextColor(kGray+2);
    lab->Draw();

    c1->cd();
}
