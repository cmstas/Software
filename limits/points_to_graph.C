#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "TGraph.h"
#include "TFile.h"

using namespace std;

// !!!!!!! this code only works if compiled because of some weird CINTEX feature (DO 22/5/2015)

void points_to_graph (const string& name = "points.txt") {

  ifstream infile(name.c_str());
  vector<float> xvals;
  vector<float> yvals;

  std::string line;
  while (std::getline(infile, line))
    {
      if (line.find("#") != string::npos) continue;
      if (!line.size()) continue;
      // std::cout << "parsing line: " << line << endl;
      std::istringstream iss(line);
      float x,y;
      if (!(iss >> x >> y)) { std::cout << "ERROR" << endl; break; } // error
      //      if (!(iss >> x >> y >> z)) { std::cout << "ERROR" << endl; break; } // error
      // std::cout << "-- read x: " << x << ", y: " << y << endl;

      xvals.push_back(x);
      yvals.push_back(y);
    }

  string outname = "graph_";
  outname += name;
  outname.replace(outname.find(".txt"),4,".root");

  string graphname = "g_";
  graphname += name;
  graphname.replace(graphname.find(".txt"),4,"");
  if (graphname.find("_points") != string::npos) {
    graphname.replace(graphname.find("_points"),7,"");
  }
  if (graphname.find("_fix") != string::npos) {
    graphname.replace(graphname.find("_fix"),4,"");
  }

  TFile* fout = new TFile(outname.c_str(),"RECREATE");
  fout->cd();
  TGraph* g = new TGraph(xvals.size());
  g->SetName(graphname.c_str());

  for (unsigned int i = 0; i < xvals.size(); ++i) {
    float x = xvals.at(i);
    float y = yvals.at(i);
    g->SetPoint(i,x,y);
  }

  g->Write();
  fout->Close();

}
