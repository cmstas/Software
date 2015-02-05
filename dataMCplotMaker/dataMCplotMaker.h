#ifndef MAKEPLOT_H
#define MAKEPLOT_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "TH1F.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"
#include "TLatex.h"
#include "TChain.h"
#include "TCut.h"
#include "TROOT.h"

struct PlotInfo {
  TH1F* Plot;
  char* Title;
  Color_t Color;
};

TStyle *tdrStyleAG = NULL;

void dataMCplotMaker(TH1F* Data, std::vector <TH1F*> Backgrounds, std::vector <char*> Titles, std::string titleIn = "", std::string title2In = "", std::string options_string = "", std::vector <TH1F*> Signals = std::vector<TH1F*>(), std::vector <char*> SignalTitles = std::vector<char*>(), std::vector <Color_t> color_input = std::vector<Color_t>());



#endif
