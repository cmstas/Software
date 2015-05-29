#include "alexBeamer.h"

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

void pres::KeyColor(std::string color){
  keyColor = color; 
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
  <<  "\\begin{document}\n"
  <<  "\n"
  <<  "\\frame[plain]{\\titlepage}\n"
  <<  "\\usebackgroundtemplate{\n"
  <<  "\\begin{tikzpicture}[thick]\n"
  <<  "\\draw[fill=" << keyColor << "](0cm,0.0cm) -- (21.3cm,0.0cm) -- (21.3cm,21.3cm) -- (0.0cm,0.0cm);\n"
  <<  "\\end{tikzpicture}\n"
  <<  "}\n";

}

void pres::NewSlide(){
  myfile 
    << "\\begin{frame}\n";
  titleTwoLines = -1;

}

void pres::FinishSlide(){
  myfile 
    << "\\end{frame}\n";

}

pres::pres(bool center){
  output = "presentation.tex";
  keyColor = "blue";
  underline = ""; 
  myfile.open(output.c_str()); 
  myfile
    << "\\documentclass{beamer}\n"
    << "\\usepackage[absolute,overlay]{textpos}\n"
    << "\\usepackage{tikz}\n"
    << "\\usepackage{graphicx}\n"
    << "\\setbeamertemplate{footline}[frame number]\n"
    << "\\definecolor{darkgreen}{RGB}{0,100,0}\n"
    << "\\setbeamercolor{frametitle}{fg=" << keyColor << "}\n";
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

void pres::DoubleCompare(std::string plot1, std::string plot2){
  slideType = 2;
  myfile
  <<  "  \\begin{textblock*}{2.7cm}(0.5cm, 3.1cm)\n"
  <<  "  \\includegraphics[width=5.5cm]{" << plot1 << "}\n"
  <<  "  \\end{textblock*}\n"
  <<  "  \\begin{textblock*}{2.7cm}(6.3cm, 3.1cm)\n"
  <<  "  \\includegraphics[width=5.5cm]{" << plot2 << "}\n"
  <<  "  \\end{textblock*}\n";
}

void pres::Text(string text, int size){
  if (titleTwoLines == -1) cout << "Error!!  Need Title on slide X before you can call 'text'." << endl;
  std::string size_ = getSize(size);
  if (slideType == 2){
    if (titleTwoLines == 1) myfile <<  "  \\begin{textblock*}{10.8cm}[0,0.5](0.35cm, 2.3cm)\n" << endl;
    if (titleTwoLines == 0) myfile <<  "  \\begin{textblock*}{10.8cm}[0,0.5](0.35cm, 1.9cm)\n" << endl;
    myfile
    <<  "  \\begin{" << size_ << "} " 
    <<  text
    <<  "  \\end{" << size_ << "}"
    <<  "  \\end{textblock*}\n";
  }
  else{
    cout << "Error!!  Not sure what to do with 'text' on slide X.  Call other functions first." << endl;
  }
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


void pres::AllText(std::string text, int size){
  std::string size_ = getSize(size);
  myfile
  << "\\begin{" << size_ << "}" 
  << "\\vspace{2mm}" 
  << text  
  << "\\end{" << size_ << "}" << endl;
}

void pres::FreeText(float x, float y, std::string text, float width, int size, std::string color){
  std::string size_ = getSize(size);
  myfile 
  << "\\begin{textblock*}{" << width*12.8 << "cm}(" << x*12.8 << "cm, " << y*9.6 << "cm)\n"
  << "\\begin{" << size_ << "}\n"; 
  if (color == "keyColor") myfile << "\\textcolor{" << keyColor << "}{"<< text << "}\n";
  else myfile << "\\textcolor{" << color << "}{"<< text << "}\n";
  myfile << "\\end{" << size_ << "}\n"
  << "\\end{textblock*}\n"; 
} 
