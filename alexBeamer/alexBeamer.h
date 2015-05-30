#ifndef ALEXBEAMER_H
#define ALEXBEAMER_H

#include "iostream"
#include "fstream"
#include <string.h>

class pres{
  public:
    pres(std::string keyColor_ = "black", bool center = false); 
    ~pres(); 
    void TitleSlide(std::string title);
    void OutputFile(std::string output); 
    void Underline(std::string uline); 
    void NewSlide();
    void FinishSlide();
    void Title(std::string title); 
    void AllText(std::string text, int size); 
    void Text(std::string, std::string options_string = ""); 
    void FreeText(float x, float y, std::string text, std::string options_string = "");
    void TextPlotPlot(std::string plot1, std::string plot2, std::string options = ""); 
    void PlotType2(std::string plot1, std::string plot2, std::string options_string, float ar1, float ar2);
    void PlotType3(std::string plot1, std::string plot2, std::string options_string, float ar1, float ar2);

  private:
    std::string keyColor;
    std::string output;
    std::string underline;
    ofstream myfile;
    int slideType; 
    int titleTwoLines; 
    float move_up;
    vector <float> top; 
    vector <float> bottom;
    int nTextBoxes;

};

#endif
