#ifndef MAKEPLOTTOOLS_H
#define MAKEPLOTTOOLS_H

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

//Parse Parameters from options input string
vector <std::string> GetParms(std::string blah){
  int a = -1;
  int length = blah.length();
  vector <std::string> options;
  while (a < length){
    int temp = a;
    a = blah.find("--", temp+1);
    if (a <= temp) break;
    int b = blah.find("--", a+3)-1;
    unsigned int myLength = b - a - 2;
    string mySubstring;
    if (a + 2 + myLength > blah.length()) mySubstring = blah.substr(a+2);
    else mySubstring = blah.substr(a+2, b-a-2);
    options.push_back(mySubstring);
  }
  return options;
}

//Turn parsed argument from string into const char*.  Remove leading and trailing whitespace
string getString(std::string initial, std::string result){
  int temp = initial.find(result); 
  std::string substring = initial.substr(temp+result.length());
  while (substring[0] == ' '){
    std::string temp2 = substring.substr(1,substring.length()-1); 
    substring = temp2;
  }
  while (substring[substring.length()-1] == ' '){
    std::string temp2 = substring.substr(0,substring.length()-1); 
    substring = temp2;
  }
  if (substring.length() > 4 && substring.substr(substring.length()-4, substring.length()-1) == ".pdf") substring = substring.substr(0, substring.length()-4);
  return substring;
}

#endif
