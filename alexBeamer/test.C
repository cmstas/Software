#include "alexBeamer.h"

void test(){

  pres myTest; 
  myTest.KeyColor("blue");
  myTest.Underline("Alex");
  myTest.TitleSlide("This is my Title Slide for this Great Presentation");

  //Second slide
  myTest.NewSlide();
  myTest.Title("This is my Awesome Second Slide with a Really Long Name.");
  myTest.AllText(R"(
  \begin{itemize} 
  \item This is orthogonal to our search region, which has SIP3D $<$ 4 
  \item Derived only on events with: 
  \begin{itemize}
  \item 2+ jets
  \item HT $>$ 80
  \item veto if MET $<$ 30 \&\& HT $<$ 500
  \item Low mass and Z/g* veto
  \item One lepton truth-matched to prompt (from W), the other truth-matched to fake (from b, c, light)
  \begin{itemize}
  \item truth-matching is slightly different than we normally use
  \end{itemize}
  \end{itemize}
  \item Lepton selections for denominator and numerator here are same as elsewhere except for: 
  \begin{itemize}
  \item SIP3D inverted
  \item no dxy cut
  \item Denominator iso: 
  \begin{itemize}
  \item miniIso $<$ 0.4 (FO1 definition)
  \item miniIso $<$ 0.4 \&\& (ptRel $>$ 7.0 (6.7) $||$ jet/lep $<$ 1/0.7 (0.68) + miniIso) (FO4 definition)
  \end{itemize}
  \end{itemize}
  \end{itemize} 
  )", 0);

  myTest.FinishSlide();

  //Third slide
  myTest.NewSlide();
  myTest.Title("This is my Awesome Third Slide with a Really Long Name.");
  myTest.DoubleCompare("result_elec.pdf", "result_muon.pdf"); 
  myTest.Text(R"(Error bars represent errors \underline{in MC}, with binomial uncertainty formula.)", 0);
  myTest.FreeText(0.92, 0.8, "FO1"); 
  myTest.FinishSlide();

}
