{
  gROOT->ProcessLine(".L alexBeamer.cc+");
  gROOT->ProcessLine(".L test.C+");
  gROOT->ProcessLine("test()");
}
