#include "SlideMaker.h"

//General function to allow you to run bash
std::string exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

//Parse Parameters from options input string
vector <std::string> GetParms(std::string blah){
  int a = -1;
  int length = blah.length();
  vector <std::string> options;
  while (a < length){
    int temp = a;
    a = blah.find("--", temp+1);
    if (a <= temp) break;
    int b = blah.find("--", a+3)-1;
    unsigned int myLength = b - a - 2;
    string mySubstring;
    if (a + 2 + myLength > blah.length()) mySubstring = blah.substr(a+2);
    else mySubstring = blah.substr(a+2, b-a-2);
    options.push_back(mySubstring);
  }
  return options;
}

//Turn parsed argument from string into const char*.  Remove leading and trailing whitespace
string getString(std::string initial, std::string result){
  int temp = initial.find(result); 
  std::string substring = initial.substr(temp+result.length());
  while (substring[0] == ' '){
    std::string temp2 = substring.substr(1,substring.length()-1); 
    substring = temp2;
  }
  while (substring[substring.length()-1] == ' '){
    std::string temp2 = substring.substr(0,substring.length()-1); 
    substring = temp2;
  }
  if (substring.length() > 4 && substring.substr(substring.length()-4, substring.length()-1) == ".pdf") substring = substring.substr(0, substring.length()-4);
  return substring;
}

std::string getSize(int size){
  std::string output;
  if (size == -5) output = "tiny"; 
  if (size == -4) output = "scriptsize"; 
  if (size == -3) output = "footnotesize"; 
  if (size == -2) output = "small"; 
  if (size == -1) output = "normalsize"; 
  if (size ==  0) output = "large"; 
  if (size ==  1) output = "Large"; 
  if (size ==  2) output = "LARGE"; 
  if (size ==  3) output = "Huge"; 
  if (size ==  4) output = "HUGE"; 
  return output;
}

void pres::TitleSlide(std::string title){
  std::string title1 = "", title2 = ""; 
  int len = title.size();
  if (len < 30) title2 = title;
  else if (len > 50){
    std::cout << "ERROR!  Title is too long." << std::endl;
    title2 = "Title is too long";
  }
  else{
    int counter = len - 30; 
    title2 = title.substr(len-30, string::npos); 
    while (title2.substr(0,1) != " " && title2.size() > 0){ title2 = title2.substr(1, string::npos); counter++; }
    title1 = title.substr(0, counter); 
  }

  std::string alex = ((underline == "alex") ? "\\underline{\\smash{\\textbf{A. George}}}" : "A. George");
  myfile 
  <<  "\n" 
  <<  "\\defbeamertemplate*{title page}{customized}[1][]{ \n"
  <<  "  \\begin{textblock*}{12.8cm}(0cm,1.5cm)\n"
  <<  "  \\begin{center}\n"
  <<  "  \\usebeamerfont{title}\n"
  <<  "  \\textcolor{" << keyColor << "}{\\textbf{\\huge " << title1 << " \\\\ \\vspace{0.3cm} " << title2 << "}} \%Allowed 20 characters upstairs and 30 downstairs\n"
  <<  "  \\end{center}\n"
  <<  "  \\end{textblock*}\n"
  <<  "  \\begin{center}\n"
  <<  "  \\textcolor{" << keyColor << "}{\\rule{10cm}{2pt}}\n"
  <<  "  \\end{center}\n"
  <<  "  \\begin{textblock*}{12.8cm}(0cm,4.0cm)\n"
  <<  "  \\begin{center}\n"
  <<  "  N. Amin, C. Campagnari, " << alex << ", F. Golf, J. Gran, I. Suarez\\\\ \n"
  <<  "  (UCSB)\\\\ \n"
  <<  "  \\vspace{0.4cm} \n"
  <<  "  G. Cerati, I. Dyckes, D. Klein, I. MacNeill, D. Olivito, \\\\ \n"
  <<  "  G. Zevi Della Porta, C. Welke, J. Wood, F. W\\\"urthwein, A. Yagil \\\\ \n"
  <<  "  (UCSD)\\\\ \n"
  <<  "  \\vspace{0.4cm} \n"
  <<  "  L. Bauerdick, K. Burkett, O. Gutsche, S. Jindariani, \\\\\n"
  <<  "  J. Linacre, M. Liu, R. Lopes de Sa, H. Weber  \\\\ \n"
  <<  "  (FNAL) \\\\ \n"
  <<  "  \\end{center}\n"
  <<  "  \\end{textblock*}\n"
  <<  "  \\begin{textblock*}{2.7cm}(0cm, 0.1cm)\n"
  <<  "  \\includegraphics[width=2.7cm]{ucsb.pdf}\n"
  <<  "  \\end{textblock*}\n"
  <<  "  \\begin{textblock*}{2.2cm}(10.3cm, 0.2cm)\n"
  <<  "  \\includegraphics[width=2.2cm]{CMS.pdf}\n"
  <<  "  \\end{textblock*}\n"
  <<  "}\n"
  <<  "\n" 
  <<  "\\beamertemplatenavigationsymbolsempty\n"
  <<  "\n" 
  <<  "\\hyphenpenalty=10000"
  <<  "\n" 
  <<  "\\begin{document}\n"
  <<  "\n"
  <<  "\\frame[plain]{\\titlepage}\n"
  <<  "\\usebackgroundtemplate{\n"
  <<  "\\begin{tikzpicture}[thick]\n"
  <<  "\\draw[fill=" << keyColor << ", draw=" << keyColor << "](0cm,0.0cm) -- (21.3cm,0.0cm) -- (21.3cm,21.3cm) -- (0.0cm,0.0cm);\n"
  <<  "\\end{tikzpicture}\n"
  <<  "}\n";

}

void pres::NewSlide(){
  myfile 
    << "\\begin{frame}\n";
  titleTwoLines = -1;
  nTextBoxes = 0; 
  top.clear();
  bottom.clear(); 
  width.clear();

}

void pres::FinishSlide(){
  myfile 
    << "\\end{frame}\n";

}

pres::pres(std::string keyColor_, bool center){
  output = "presentation.tex";
  keyColor = keyColor_; 
  underline = ""; 
  myfile.open(output.c_str()); 
  myfile
    << "\\documentclass{beamer}\n"
    << "\\usepackage[absolute,overlay]{textpos}\n"
    << "\\usepackage{tikz}\n"
    << "\\usepackage{microtype}\n"
    << "\\usepackage{graphicx}\n"
    << "\\setbeamertemplate{footline}[frame number]\n"
    << "\\definecolor{darkgreen}{RGB}{0,100,0}\n"
    << "\\definecolor{gray}{RGB}{128,128,128}\n"
    << "\\definecolor{grey}{RGB}{128,128,128}\n"
    << "\\setbeamercolor{frametitle}{fg=" << keyColor << "}\n";
    //<< "\\setbeamertemplate{itemize item}{\\small\\raise1.75pt\\color{" << keyColor << "}$\\blacktriangleright$}\n"
    //<< "\\setbeamertemplate{itemize subitem}{\\footnotesize\\raise1.5pt\\color{" << keyColor << "}$\\blacktriangleright$}\n"
    //<< "\\setbeamertemplate{itemize subsubitem}{\\scriptsize\\raise1.5pt\\color{" << keyColor << "}$\\blacktriangleright$}\n";
    if (center)  myfile << "\\setbeamerfont{frametitle}{size=\\LARGE \\bfseries \\centering}\n";
    if (!center) myfile << "\\setbeamerfont{frametitle}{size=\\LARGE \\bfseries}\n";
    myfile << "\\setbeamertemplate{footline}{\\raisebox{5pt}{\\makebox[\\paperwidth]{\\hfill\\makebox[10pt]{\\scriptsize\\textcolor{white}{\\insertframenumber\\hspace{2mm}}}}}}";
    myfile << "\\setbeamersize{text margin left=10pt,text margin right=10pt}";
    myfile << "\\scriptsize \\let\\small\\scriptsize" << endl;
    myfile << "\\scriptsize \\let\\footnotesize\\scriptsize" << endl;
    myfile << "\\scriptsize \\let\\scriptsize\\scriptsize" << endl;
    myfile << "\\footnotesize \\let\\small\\footnotesize" << endl;
    myfile << "\\footnotesize \\let\\footnotesize\\scriptsize" << endl;
    myfile << "\\footnotesize \\let\\scriptsize\\scriptsize" << endl;
    myfile << "\\small \\let\\small\\small" << endl;
    myfile << "\\small \\let\\footnotesize\\footnotesize" << endl;
    myfile << "\\small \\let\\scriptsize\\scriptsize" << endl;

}

float aspectRatio(std::string pdfFile){
  const char* command = ("./aspect_ratio.sh " + pdfFile).c_str();
  string data = exec(command);
  std::vector <std::string> result = GetParms(data);  
  if (atof(result[2].c_str()) == 0) return atof(result[1].c_str())/atof(result[0].c_str()); 
  else if (atof(result[2].c_str()) == 90) return atof(result[0].c_str())/atof(result[1].c_str()); 
  else cout << "Problem with aspect ratio.  Value was: " << result[0] << " " << result[1] << " " << result[2] << endl;
  return 0;
}


void pres::Text(string text, std::string options_string){
  if (slideType == 1){
    myfile << text << endl;  
    return;
  }
  nTextBoxes++;
  if (nTextBoxes > top.size()){ cout << "ERROR.  Too many text boxes." << endl; abort(); }
  float top_ = top[nTextBoxes-1]; 
  float bottom_ = bottom[nTextBoxes-1]; 
  float width_ = (width.size() == top.size()) ? width[nTextBoxes-1] : 12.0;

  //Parse options
  std::vector <std::string> Options = GetParms(options_string);  
  int size = 0;
  float moveDown = -9999; 
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("size") < Options[i].length()) size = atoi( getString(Options[i], "size").c_str() ) ;
    if (Options[i].find("moveDown") < Options[i].length()) moveDown = atof( getString(Options[i], "moveDown").c_str() ) ;
  }
  moveDown = (moveDown < -9998 ? 0 : moveDown*12.8); 
 

  //Get size
  std::string size_ = getSize(size);
 
  if (titleTwoLines == -1) cout << "Error!!  Need Title on slide X before you can call 'text'." << endl;
  myfile <<  "  \\begin{textblock*}{" << width_ << "cm}[0.0,0.0](0.35cm, " << top_ + moveDown*9.6 << "cm)\n" << endl;
  myfile
  <<  "  \\begin{" << size_ << "} " 
  <<  text
  <<  "  \\end{" << size_ << "}"
  <<  "  \\end{textblock*}\n";

}

pres::~pres(){
  myfile 
  << "\n" 
  << "\\end{document}\n";
  myfile.close();
}

void pres::OutputFile(std::string outputFile){
  output = outputFile;
}

void pres::Underline(std::string uline){
  for (int i=0; uline[i]; i++) uline[i] = tolower(uline[i]);
  underline = uline;

}

void pres::Title(std::string title){
  myfile
  << "\\frametitle{" 
  << title
  << "}\n";
  if (title.size() > 30) titleTwoLines = 1;
  else titleTwoLines = 0;
}


void pres::AllText(std::string options){
  slideType = 1; 
  PlotType1(options); 
}

void pres::PlotType1(std::string options){
  float top_ = 0.7;
  if (titleTwoLines) top_ = 2.0;
  top.push_back(top_); 
  bottom.push_back(9.6); 
}

void pres::FreeText(float x, float y, std::string text, std::string options_string){ 
  float width = 0.5;
  int size = 0; 
  bool bold = false;
  std::string color = keyColor;
  std::vector <std::string> Options = GetParms(options_string);  
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("width") < Options[i].length()) width = atof( getString(Options[i], "width").c_str() ) ;
    if (Options[i].find("size") < Options[i].length()) size = atoi( getString(Options[i], "size").c_str() ) ;
    if (Options[i].find("color") < Options[i].length()) color = getString(Options[i], "color").c_str() ;
    if (Options[i].find("bold") < Options[i].length()) bold = true;
  }
  std::string size_ = getSize(size);
  myfile 
  << "\\begin{textblock*}{" << width*12.8 << "cm}(" << x*12.8 << "cm, " << y*9.6 << "cm)\n"
  << "\\begin{" << size_ << "}\n"; 
  if (color == "keyColor") myfile << "\\textcolor{" <<keyColor << "}{"<< text << "}\n";
  else myfile << "\\textcolor{" << color << "}{"; 
  if (bold) myfile << "\\textbf{" << text << "}}\n";
  else  myfile << text << "}\n";
  myfile << "\\end{" << size_ << "}\n";
  myfile << "\\end{textblock*}\n"; 
} 

void pres::TextPlotPlot(std::string plot1, std::string plot2, std::string options){
  float ar1 = aspectRatio(plot1); 
  float ar2 = aspectRatio(plot2); 
  float ar = std::max(ar1, ar2); 
  if (ar > 1.05) slideType = 2; 
  else slideType = 3;
  if (slideType == 2) pres::PlotType2(plot1, plot2, options, ar1, ar2); 
  if (slideType == 3) pres::PlotType3(plot1, plot2, options, ar1, ar2); 
}

void pres::PlotType2(std::string plot1, std::string plot2, std::string options_string, float ar1, float ar2){
 
  //Deal with Options
  std::vector <std::string> Options = GetParms(options_string);  
  std::string label1 = "";
  std::string label2 = "";
  std::string labelColor = "black";
  bool labelUnderline = false;
  bool squish = false;
  bool tall = false;
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("label1") < Options[i].length()) label1 = getString(Options[i], "label1");
    if (Options[i].find("label2") < Options[i].length()) label2 = getString(Options[i], "label2");
    if (Options[i].find("labelUnderline") < Options[i].length()) labelUnderline = true;
    if (Options[i].find("labelColor") < Options[i].length()) labelColor = getString(Options[i], "labelColor");
    if (Options[i].find("squish") < Options[i].length()) squish = true;
    if (Options[i].find("tall") < Options[i].length()) tall = true;
  }
  if (label1.find("invfb") < label1.length()) label1.replace(label1.find("invfb"), 5, "$\\textrm{fb}^{-1}$");
  if (label2.find("invfb") < label2.length()) label2.replace(label2.find("invfb"), 5, "$\\textrm{fb}^{-1}$");

  //Parameters
  float width = tall ? 5.8 : 5.3;
  if (tall) squish = true;
  float x1 = squish ? 0.0 : 0.6; 
  float x2 = squish ? width : 1.2+width;

  //Figure One
  myfile
  <<  "  \\begin{textblock*}{" << width << "cm}[0.0,1.0](" << x1 << "cm,9.6cm)\n"
  <<  "  \\includegraphics[width=" << width << "cm]{" << plot1 << "}\n"
  <<  "  \\end{textblock*}\n";
 
  //Figure Two
  myfile
  <<  "  \\begin{textblock*}{" << width << "cm}[0.0,1.0](" << x2 << "cm,9.6cm)\n"
  <<  "  \\includegraphics[width=" << width << "cm]{" << plot2 << "}\n"
  <<  "  \\end{textblock*}\n";

  //Coordinates of text box
  float top_ = 1.1;
  if (titleTwoLines) top_ = 2.0;
  float bottom_ = 9.6-5.8*std::max(ar1, ar2);  
  if (label1 != "" || label2 != "") bottom_ -= 0.7; 
  top.push_back(top_);
  bottom.push_back(bottom_);

  //Label on figures 1, if requested
  myfile <<  "\\begin{textblock*}{5.8cm}[0.5,1.0](" << x1 + width/2.0 << "cm, " << 9.6-width*ar1+0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label1 << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label1 << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;
  
  //Label on figures 2, if requested
  myfile <<  "\\begin{textblock*}{5.8cm}[0.5,1.0](" << x2 + width/2.0 << "cm, " << 9.6-width*ar2+0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label2 << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label2 << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;

}

void pres::PlotType3(std::string plot1, std::string plot2, std::string options_string, float ar1, float ar2){
 
  //Determine height used by pictures + title
  float titlebottom = 0.7;
  if (titleTwoLines) titlebottom = 2.0;
  float width = 12.8/2.0;
  float yeaten = titlebottom + width*std::max(ar1, ar2); 

  //Deal with Options
  std::vector <std::string> Options = GetParms(options_string);  
  std::string label1 = "";
  std::string label2 = "";
  std::string labelColor = "black";
  bool labelUnderline = false;
  string position = (yeaten > 7.6 ? "bottom" : "middle");
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("label1") < Options[i].length()) label1 = getString(Options[i], "label1");
    if (Options[i].find("label2") < Options[i].length()) label2 = getString(Options[i], "label2");
    if (Options[i].find("labelUnderline") < Options[i].length()) labelUnderline = true;
    if (Options[i].find("labelColor") < Options[i].length()) labelColor = getString(Options[i], "labelColor");
    if (Options[i].find("position") < Options[i].length()) position = getString(Options[i], "position");
  }
  if (label1.find("invfb") < label1.length()) label1.replace(label1.find("invfb"), 5, "$\\textrm{fb}^{-1}$");
  if (label2.find("invfb") < label2.length()) label2.replace(label2.find("invfb"), 5, "$\\textrm{fb}^{-1}$");

  //Parameters
  float x1 = 0;
  float x2 = width;
  float yplot = titlebottom + ((label1 != "" || label2 != "") ? 0.5 : 0.0);
  float yrel = 0.0;
  if (position == "middle"){ yplot = titlebottom + 0.5*(9.6-titlebottom) + ((label1 != "" || label2 != "") ? 0.25 : 0.0); yrel = 0.5; }
  if (position == "bottom"){ yplot = 9.6 - 0.5; yrel = 1.0; }

  //Figure One
  myfile
  <<  "  \\begin{textblock*}{" << width << "cm}[0.0, " << yrel << "](" << x1 << "cm," << yplot << "cm)\n"
  <<  "  \\includegraphics[width=" << width << "cm]{" << plot1 << "}\n"
  <<  "  \\end{textblock*}\n";
 
  //Figure Two
  myfile
  <<  "  \\begin{textblock*}{" << width << "cm}[0.0, " << yrel << "](" << x2 << "cm," << yplot << "cm)\n"
  <<  "  \\includegraphics[width=" << width << "cm]{" << plot2 << "}\n"
  <<  "  \\end{textblock*}\n";

  //Determine top of figures
  float top_of_figure_1 = yplot;
  float top_of_figure_2 = yplot;
  if (position == "middle") top_of_figure_1 = yplot - 0.5*width*ar1;
  if (position == "middle") top_of_figure_2 = yplot - 0.5*width*ar2;
  if (position == "bottom") top_of_figure_1 = yplot - width*ar1;
  if (position == "bottom") top_of_figure_2 = yplot - width*ar2;

  //Label on figures 1, if requested
  myfile <<  "\\begin{textblock*}{5.8cm}[0.5,1.0](" << x1 + width/2.0 << "cm, " << top_of_figure_1 + 0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label1 << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label1 << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;
  
  //Label on figures 2, if requested
  myfile <<  "\\begin{textblock*}{5.8cm}[0.5,1.0](" << x2 + width/2.0 << "cm, " << top_of_figure_2 + 0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label2 << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label2 << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;

  //Coordinates of text box
  if (position == "top") top.push_back(yplot + std::max(ar1, ar2)*width); 
  if (position == "top") bottom.push_back(9.6); 
  if (position == "bottom") top.push_back(titlebottom); 
  if (position == "bottom") bottom.push_back(std::max(top_of_figure_1, top_of_figure_2)); 
  if (position == "middle"){
    top.push_back(titlebottom+(titleTwoLines ? 0 : 0.4));
    bottom.push_back(std::max(top_of_figure_1, top_of_figure_2));
    top.push_back(yplot + 0.5*std::max(ar1, ar2)*width + 0.2);
    bottom.push_back(9.6);
  }

}

void pres::TextPlot(std::string plot, std::string options_string){
  slideType = 4;
  pres::PlotType4(plot, options_string); 
} 

void pres::PlotType4(std::string plot, std::string options_string){
  //Deal with Options
  std::vector <std::string> Options = GetParms(options_string);  
  std::string label = "";
  std::string labelColor = "black";
  bool labelUnderline = false;
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("label ") < Options[i].length()) label = getString(Options[i], "label");
    if (Options[i].find("labelUnderline") < Options[i].length()) labelUnderline = true;
    if (Options[i].find("labelColor") < Options[i].length()) labelColor = getString(Options[i], "labelColor");
  }
  if (label.find("invfb") < label.length()) label.replace(label.find("invfb"), 5, "$\\textrm{fb}^{-1}$");

  //Aspect ratio
  float ar = aspectRatio(plot); 
  if (ar <= 0){ cout << "ERROR!  Aspect ratio makes no sense." << endl; abort(); }

  //Title bottom
  float titlebottom = 0.7;
  if (titleTwoLines) titlebottom = 2.0;

  //Natural height and width
  float naturalheight = 9.6 - titlebottom - 0.5; 
  float naturalwidth = naturalheight/ar;

  //Actual height and width
  float width_ = 12.8/2.0;
  if (naturalwidth < width_) width_ = naturalwidth;

  //Place image
  float center_of_figure = titlebottom + (9.6-titlebottom-0.8)/2.0;
  myfile
  <<  "  \\begin{textblock*}{" << width_ << "cm}[0.0,0.5](" << 12.8-width_ << "cm," << center_of_figure << "cm)\n"
  <<  "  \\includegraphics[width=" << width_ << "cm]{" << plot << "}\n"
  <<  "  \\end{textblock*}\n";

  //Place text box
  top.push_back(titlebottom); 
  bottom.push_back(9.6); 
  width.push_back(12.8-width_-0.3); 

  //Determine top of figures
  float top_of_figure = center_of_figure - width_*ar/2.0;

  //Label on figures, if requested
  myfile <<  "\\begin{textblock*}{" << width_ << "cm}[0.0,1.0](" << 12.8 - width_ << "cm, " << top_of_figure + 0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;

}

void pres::Plot(std::string plot, std::string options_string){
  slideType = 5;
  pres::PlotType5(plot, options_string); 
} 

void pres::PlotType5(std::string plot, std::string options_string){
  //Deal with Options
  std::vector <std::string> Options = GetParms(options_string);  
  std::string label = "";
  std::string labelColor = "black";
  bool labelUnderline = false;
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("label ") < Options[i].length()) label = getString(Options[i], "label");
    if (Options[i].find("labelUnderline") < Options[i].length()) labelUnderline = true;
    if (Options[i].find("labelColor") < Options[i].length()) labelColor = getString(Options[i], "labelColor");
  }
  if (label.find("invfb") < label.length()) label.replace(label.find("invfb"), 5, "$\\textrm{fb}^{-1}$");

  //Aspect ratio
  float ar = aspectRatio(plot); 
  if (ar <= 0){ cout << "ERROR!  Aspect ratio makes no sense." << endl; abort(); }

  //Title bottom
  float titlebottom = 0.7;
  if (titleTwoLines < 0) titlebottom = 0; 
  if (titleTwoLines == 1) titlebottom = 2.0;

  //Natural height and width
  float naturalheight = 9.6 - titlebottom - (label == "" ? 0.2 : (titleTwoLines < 0 ? 0.8: 0.4)); 
  float naturalwidth = naturalheight/ar;

  //Actual height and width
  float width_ = 12.8;
  if (naturalwidth < width_) width_ = naturalwidth;

  //Place image
  float center_of_figure = titlebottom + (9.6-titlebottom-0.8 + (label == "" ? (titleTwoLines < 0 ? 0.9 : 0.3) : (titleTwoLines < 0 ? 1.4 : 1.0)))/2.0;
  myfile
  <<  "  \\begin{textblock*}{" << width_ << "cm}[0.5,0.5](" << 12.8/2.0 << "cm," << center_of_figure << "cm)\n"
  <<  "  \\includegraphics[width=" << width_ << "cm]{" << plot << "}\n"
  <<  "  \\end{textblock*}\n";

  //Determine top of figures
  float top_of_figure = center_of_figure - width_*ar/2.0;

  //Label on figures, if requested
  myfile <<  "\\begin{textblock*}{" << width_ << "cm}[0.5,1.0](" << 12.8/2.0 << "cm, " << top_of_figure + 0.3 << "cm) \\begin{center}";
  if (labelUnderline) myfile << " \\textcolor{" << labelColor << "}{ \\underline{" << label << "}} " << endl;
  else myfile << "\\textcolor{" << labelColor << "}{" << label << "}";
  myfile << "\\end{center} \\end{textblock*}" << endl;

}

void pres::Table(std::string table, std::string options_string){ 
  slideType = 6;
  PlotType6(table, options_string); 
}

void pres::PlotType6(std::string table, std::string options_string){
  myfile << "\\input{" << table << "}" << endl;
}

void pres::TableText(std::string table, std::string options_string){ 
  slideType = 7;
  PlotType7(table, options_string); 
}

void pres::PlotType7(std::string table, std::string options_string){
  //Options
  std::vector <std::string> Options = GetParms(options_string);  
  int tableTextSize = 0;
  float width_ = -1;
  float moveDown = -9999; 
  for (unsigned int i = 0; i < Options.size(); i++){
    if (Options[i].find("tableTextSize") < Options[i].length()) tableTextSize = atoi( getString(Options[i], "tableTextSize").c_str() );
    if (Options[i].find("width") < Options[i].length()) width_ = atof( getString(Options[i], "width").c_str() );
    if (Options[i].find("moveDown") < Options[i].length()) moveDown = atof( getString(Options[i], "moveDown").c_str() ); 
  }
  width_ = (width_ < 0 ? 5 : width_*12.8);
  moveDown = (moveDown < -9998 ? 0 : moveDown*12.8); 

  //Title
  float titlebottom = 0.7;
  if (titleTwoLines < 0) titlebottom = 0.0;
  if (titleTwoLines == 1) titlebottom = 2.0;

  //Size
  std::string size_ = getSize(tableTextSize);

  //Table
  float y = titlebottom + (9.6-titlebottom)/2.0 - 0.2 + moveDown;
  myfile << "\\begin{textblock*}{" << 12.8 << "cm}[1.0,0.5](" << 12.8 << "cm, " << y << "cm)";
  myfile << "\\begin{" << size_ << "} " << endl;
  myfile << "\\begin{" << "flushright" << "} " << endl;
  myfile << "\\input{" << table << "}" << endl;
  myfile << "\\end{" << "flushright" << "} " << endl;
  myfile << "\\end{" << size_ << "} "  << endl;
  myfile << "\\end{textblock*}" << endl;

  //Set up text box
  top.push_back( (titleTwoLines ? 2.0 : 0.7) ); 
  bottom.push_back( 9.6 ); 
  width.push_back( width_ ); 
}
