{
  gROOT->ProcessLine(".L ../dataMCplotMaker.cc+");
  gROOT->ProcessLine(".L testPlot.C+");

  testPlot(); 
  gROOT->ProcessLine(".! web h1D_vec.pdf")
}
