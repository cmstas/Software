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

  private:
    std::string keyColor;
    std::string output;
    std::string underline;
    ofstream myfile;

};
