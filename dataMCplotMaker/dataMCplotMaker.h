#ifndef MAKEPLOT_H
#define MAKEPLOT_H

#include "PlotMakingTools.h"

struct PlotInfo {
  TH1F* Plot;
  string Title;
  Color_t Color;
};

TStyle *tdrStyleAG = NULL;

void dataMCplotMaker(TH1F* Data, std::vector <TH1F*> Backgrounds, std::vector <string> Titles, std::string titleIn = "", std::string title2In = "", std::string options_string = "", std::vector <TH1F*> Signals = std::vector<TH1F*>(), std::vector <string> SignalTitles = std::vector<string>(), std::vector <Color_t> color_input = std::vector<Color_t>());



#endif
