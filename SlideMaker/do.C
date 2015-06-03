{
  gROOT->ProcessLine(".L SlideMaker.cc++");
  gROOT->ProcessLine(".L test.C++");
  gROOT->ProcessLine("test()");
}
