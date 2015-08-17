{
  gROOT->ProcessLine(".L ../dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L testPlot.C+");

  testPlot(); 
}
