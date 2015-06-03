#include "SlideMaker.h"

void test(){

  pres myTest("red"); 
  myTest.Underline("Alex");
  myTest.TitleSlide("This is my Title Slide for this Great Presentation");

  //Second slide
  myTest.NewSlide();
  myTest.Title("This is my Awesome Second Slide with a Really Long Name.");
  myTest.AllText(); 
  myTest.Text(R"(
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
  )");
  myTest.FinishSlide();

  //Third slide
  myTest.NewSlide();
  myTest.Title("Third Slide Short Title");
  myTest.TextPlotPlot("result_elec.pdf", "result_muon.pdf", "--label1 electron --label2 muon --labelColor red --tall"); 
  myTest.Text(R"(Error bars represent errors \underline{in MC}, with binomial uncertainty formula.)", "--size 0");
  myTest.FreeText(0.92, 0.8, "FO1", "--color darkgreen --bold"); 
  myTest.FinishSlide();

  //Fourth slide
  myTest.NewSlide();
  myTest.Title("This is my Awesome Fourth Slide with a Really Long Name.");
  myTest.TextPlotPlot("result_elec2.pdf", "result_muon2.pdf", "--label1 electrons --label2 muons --labelColor purple --tall"); 
  myTest.Text(R"(Error bars represent errors \underline{in data}, with binomial uncertainty formula.)", "--size 0");
  myTest.FreeText(0.92, 0.8, "FO1", "--color darkgreen --bold"); 
  myTest.FinishSlide();

  //Fifth slide
  myTest.NewSlide();
  myTest.Title("Fifth Slide Short Title");
  myTest.TextPlotPlot("gt_elec.pdf", "gt_muon.pdf", ""); 
  myTest.Text(R"(Error bars represent errors \underline{in data}, with binomial uncertainty formula. \\
              \textcolor{gray}{(called Sumw2 after filling numer and denom but before dividing)})", "--size -1");
  myTest.Text(R"(\textcolor{gray}{See backup for this with SIP3D $<$ 4})", "--down");
  myTest.FreeText(0.82, 0.87, "FO1", "--color darkgreen --bold"); 
  myTest.FinishSlide();

  //Sixth slide
  myTest.NewSlide();
  myTest.Title("This is my awesome sixth slide with a Really Long Name"); 
  myTest.TextPlotPlot("gt_elec.pdf", "gt_muon.pdf", "--label1 3 invfb --label2 10 invfb --labelUnderline --labelColor red"); 
  myTest.Text(R"(
    Error bars represent errors \underline{in data}, with binomial uncertainty formula. \\
    \textcolor{gray}{(called Sumw2 after filling numer and denom but before dividing)}
    )", "--size -1");
  myTest.Text(R"(\textcolor{gray}{See backup for this with SIP3D $<$ 4})", "");
  myTest.FreeText(0.82, 0.87, "FO1", "--color darkgreen --bold"); 
  myTest.FinishSlide();

  //Seventh slide
  myTest.NewSlide();
  myTest.Title("This is my awesome seventh slide with a Really Long Name"); 
  myTest.TextPlot("gt_elec.pdf", "--label 3 invfb --labelUnderline --labelColor red"); 
  myTest.Text(R"(
    Error bars represent errors \underline{in data}, with binomial uncertainty formula. \\
    \textcolor{gray}{(called Sumw2 after filling numer and denom but before dividing)}
    )", "--size -1");
  myTest.FinishSlide();

  //Eighth slide
  myTest.NewSlide();
  myTest.Title("This is my awesome eighth slide with a Really Really Long Name"); 
  myTest.Plot("gt_elec.pdf", "--label 3 invfb --labelUnderline --labelColor red"); 
  myTest.FinishSlide();

  //Ninth slide
  myTest.NewSlide();
  myTest.Plot("result_elec.pdf");
  myTest.FinishSlide();

  //Tenth slide
  myTest.NewSlide();
  myTest.Plot("result_elec2.pdf");
  myTest.FinishSlide();

  //Eleventh slide
  myTest.NewSlide();
  myTest.Title("This is my awesome eleventh slide with a Really Really Long Name"); 
  myTest.Table("table.tex", "--tableTextSize -2");
  myTest.FinishSlide();

  //Twelfth slide
  myTest.NewSlide();
  myTest.Title("This is my awesome twelfth slide with a Really Really Long Name"); 
  myTest.TableText("table.tex", "--tableTextSize -2 --width 0.3125 --moveDown -0.15");
  myTest.Text(R"(
    \underline{\textbf{Observed}}: number of numer events with SIP $<$ 4 \\  \vspace{5mm} 
    \underline{\textbf{Predicted}}: number of exclusive denom events with SIP $< 4 \times \frac{FR}{(1-FR)}$
  )", ""); 
  myTest.FreeText(0.82, 0.87, "FO1", "--color darkgreen --bold"); 
  myTest.FinishSlide();

}
