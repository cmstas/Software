#ifndef MAKEPLOT_H
#define MAKEPLOT_H

#include "PlotMakingTools.h"

struct PlotInfo {
  TH1F* Plot;
  string Title;
  Color_t Color;
  TH1F* Signal;
  Color_t SignalColor;
  string SignalTitle;
};

TStyle *tdrStyleAG = NULL;

//Main function
void dataMCplotMaker(TH1F* Data_in, std::vector <std::pair <TH1F*, TH1F*> > Backgrounds_pair_in, std::vector <string> Titles, std::string titleIn = "", std::string title2In = "", std::string options_string = "", std::vector <TH1F*> Signals_in = std::vector<TH1F*>(), std::vector <string> SignalTitles = std::vector<string>(), std::vector <Color_t> color_input = std::vector<Color_t>());

//Overload for the case of no stat errors
void dataMCplotMaker(TH1F* Data_in, std::vector <TH1F*> Backgrounds_in, std::vector <string> Titles, std::string titleIn = "", std::string title2In = "", std::string options_string = "", std::vector <TH1F*> Signals_in = std::vector<TH1F*>(), std::vector <string> SignalTitles = std::vector<string>(), std::vector <Color_t> color_input = std::vector<Color_t>());

//Overload for the case of numeric stat errors
void dataMCplotMaker(TH1F* Data_in, std::vector <std::pair <TH1F*, float> > Backgrounds_in, std::vector <string> Titles, std::string titleIn = "", std::string title2In = "", std::string options_string = "", std::vector <TH1F*> Signals_in = std::vector<TH1F*>(), std::vector <string> SignalTitles = std::vector<string>(), std::vector <Color_t> color_input = std::vector<Color_t>());

//Quick wrapper
void singlePlotMaker(TH1F* h1, std::string title="", std::string options_string="");


#endif
