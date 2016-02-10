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

    h1D_one->FillRandom("gaus",300);
    h1D_two->FillRandom("gaus",100);
    h1D_three->FillRandom("gaus",1000);
    data->FillRandom("gaus",1400);

    std::string common = " --xAxisOverride [GeV] --legendTaller -0.05  --outOfFrame --legendUp 0.1 --percentageInBox  \
        --hLine 100,1,3 --vLine 1.5, 0.1, 120 --hLine 200  --boxLines 3.0,90,4.5,10.0";
    dataMCplotMaker(data,h1D_vec,titles,"this is a title","",common+" --outputName h1D_vec.pdf");
    // dataMCplotMaker(null,h1D_vec,titles,"this is a title","",common+" --outputName "+out+"h1D_vec.pdf");
}
