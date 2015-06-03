//------------------------------------------------------------------------//
// SimpleTableLinkDef.h Kelley 2011-05-01
//------------------------------------------------------------------------//

#ifdef __CINT__  // interpreter and ACLiC

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions; 

#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

// templated classes
#pragma link C++ class std::vector<std::string>+; 
#pragma link C++ class std::vector<vector<std::string> >+; 
#pragma link C++ class CNumBase<float>+; 
#pragma link C++ class CNumBase<double>+; 
#pragma link C++ class CTable+; 

#endif // __CINT__
