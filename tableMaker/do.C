{
  // test2
  gSystem->Load("libSimpleTable.so");
  gROOT->ProcessLine(".L test.cpp+"); 
  gROOT->ProcessLine("test()"); 
}
