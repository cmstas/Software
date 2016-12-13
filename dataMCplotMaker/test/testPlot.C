#include <iostream>
#include <vector>
#include <stdlib.h>
#include "TROOT.h"
#include "../dataMCplotMaker.h"

using namespace std;

void testPlot() {
    std::vector<std::string> titles = { "first", "second", "third"};
    std::vector<TH1F*> h1D_vec;
    TH1F* data = new TH1F("data","",50,0,5);
    TH1F *null = new TH1F("null","",1,0,1);
    TH1F *h1D_one = new TH1F("h1D_one","",50,0,5);
    TH1F *h1D_two = new TH1F("h1D_two","",50,0,5);
    TH1F *h1D_three = new TH1F("h1D_three","",50,0,5);
    h1D_vec.push_back(h1D_one);
    h1D_vec.push_back(h1D_two);
    h1D_vec.push_back(h1D_three);

    int mult = 3;
    h1D_one->FillRandom("gaus",mult*300);
    h1D_two->FillRandom("gaus",mult*100);
    h1D_three->FillRandom("gaus",mult*1000);
    data->FillRandom("gaus",mult*1400);

    std::string common = "";
    common += " --xAxisOverride [GeV]";
    common += " --legendTaller -0.05 ";
    common += " --outOfFrame"; // move CMS and lumi stuff to top of frame
    common += " --legendUp 0.1";
    common += " --legendRight -0.1";
    common += " --percentageInBox  "; // show percentage of backgrounds out of total
    common += " --hLine 100,1,3"; // horizontal line at y=100 from x=1 to x=3
    common += " --vLine 1.5, 0.1, 120"; // vertical line at x=1.5 from y=0.1 to y=120
    common += " --hLine 200 "; // horizontal line at y=200 across whole range
    common += " --boxLines 3.0,90,4.5,10.0 "; // box with top left corner at x,y=3.0,90 and bottom right at 4.5,10.0
    // common += " --darkColorLines"; // make the black lines for filled histograms into darker variants of the fill color
    common += " --totalBlackLine"; // make the black lines for filled histograms into darker variants of the fill color
    common += " --legendCounts"; // show counts for backgrounds in legend in brackets
    common += " --type Preliminary";
    common += " --poissonErrorsNoZeros"; // proper asymmetric errors
    common += " --makeTable"; // print out table to text file
    common += " --makeRootFile"; // make ROOT file
    common += " --isLinear";

    dataMCplotMaker(data,h1D_vec,titles,"this is a title","",common+" --outputName h1D_vec.pdf");
}
