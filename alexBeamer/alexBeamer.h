#ifndef ALEXBEAMER_H
#define ALEXBEAMER_H

#include "iostream"
#include "fstream"
#include <string.h>

class pres{
  public:
    pres(bool center = false); 
    ~pres(); 
    void KeyColor(std::string color); 
    void TitleSlide(std::string title);
    void OutputFile(std::string output); 
    void Underline(std::string uline); 
    void NewSlide();
    void FinishSlide();
    void Title(std::string title); 
    void AllText(std::string text, int size); 
    void DoubleCompare(string plot1, string plot2);
    void Text(std::string, int size); 
    void FreeText(float x, float y, std::string text, float width = 0.5, int size = 0, std::string color = "keyColor"); 

  private:
    std::string keyColor;
    std::string output;
    std::string underline;
    ofstream myfile;
    int slideType; 
    int titleTwoLines; 

};

#endif
