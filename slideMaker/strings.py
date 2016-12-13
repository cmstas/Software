### Long template strings go here

institute = """
    N. Amin, C. Campagnari, A. George, F. Golf, J. Gran,\\\\ B. Marsh, I. Suarez, S. Wang\\\\ (\\textit{UCSB})\\\\ \\vspace{0.3cm} 
    G. Cerati, M. Derdzinski, D. Klein, D. Olivito, G. Zevi Della Porta, \\\\ C. Welke, J. Wood, F. W\\"urthwein, A. Yagil \\\\ (\\textit{UCSD})\\\\ \\vspace{0.3cm} 
    L. Bauerdick, K. Burkett, O. Gutsche, S. Jindariani, \\\\ J. Linacre, M. Liu, R. Lopes de Sa, H. Weber  \\\\ (\\textit{FNAL}) \\\\ 
"""

commonHeader = """
%% \\documentclass[aspectratio=1610]{beamer}
\\documentclass{beamer}
\\usepackage[absolute,overlay]{textpos}
%% \\usepackage[absolute,overlay,showboxes]{textpos} %% showboxes for position debugging
\\usepackage{tikz}
\\usetikzlibrary{arrows,shapes,shadows,shadows.blur,shapes.geometric,calc,decorations.pathmorphing,positioning,automata,decorations.pathreplacing}
\\usepackage{microtype}
\\usepackage{graphicx}
\\usepackage{xcolor}
\\usepackage{slashed}
\\usepackage{appendixnumberbeamer} 
\\usepackage{amssymb}
\\usepackage{multicol}
\\graphicspath{ GRAPHICSPATHHERE }
\\setbeamertemplate{navigation symbols}{}


\\definecolor{darkgreen}{RGB}{0,100,0}
\\definecolor{gray}{RGB}{128,128,128}
\\definecolor{grey}{RGB}{128,128,128}
\\definecolor{orange}{RGB}{230,97,1}
\\definecolor{babyblue}{RGB}{56,147,214}
\\definecolor{coolblue}{RGB}{51,51,179}
\\definecolor{darkyellow}{RGB}{204,204,0}
\\definecolor{thethemecolor}{RGB}{0,0,255}
\\setbeamercolor{alerted text}{fg=thethemecolor}


\\newcommand{\\met}{\\slashed{E}_T}
\\newcommand{\\ifb}{fb${}^{-1}$}
\\newcommand{\\pt}{p_{T}}
\\newcommand{\\Ht}{H_{T}}
\\newcommand{\\mt}{m_{T}}
\\newcommand{\\mtmin}{m_{T}^\\text{min}}
\\newcommand{\\ttbar}{t\\bar{t}}
\\newcommand{\\red}[1]{\\textcolor{red}{#1}}
\\newcommand{\\babyblue}[1]{\\textcolor{babyblue}{#1}}
\\newcommand{\\blue}[1]{\\textcolor{blue}{#1}}
\\newcommand{\\coolblue}[1]{\\textcolor{coolblue}{#1}}
\\newcommand{\\orange}[1]{\\textcolor{orange}{#1}}
\\newcommand{\\themecolor}[1]{\\textcolor{thethemecolor}{#1}}



\\author[AUTHORHERE]{}
\\date{\\today} 
\\institute[SNT] 
{
    \\vspace*{-1cm}
    \\begin{center}
    INSTITUTEHERE
        \\end{center}
}

%% code from http://tex.stackexchange.com/questions/218907/smooth-out-drop-shadow-at-the-edge-of-the-graph-in-pgf-blur
\\tikzset{
  shadowed/.style={preaction={
      transform canvas={shift={(0.5pt,-1pt)}},draw opacity=.2,#1,preaction={
        transform canvas={shift={(1.0pt,-1.5pt)}},draw opacity=.1,#1,preaction={
          transform canvas={shift={(1.5pt,-2pt)}},draw opacity=.05,#1,
        }}}},
}

%% code adapted from http://tex.stackexchange.com/a/11483/3954
%% some parameters for customization
\\def\\shadowshift{0pt,0pt}
\\def\\shadowradius{4pt}
\\colorlet{innercolor}{black!60}
\\colorlet{outercolor}{gray!05}
%% this draws a shadow under a rectangle node
\\newcommand\\drawshadow[1]{
    \\begin{pgfonlayer}{shadow}
        \\shade[outercolor,inner color=innercolor,outer color=outercolor] ($(#1.south west)+(\\shadowshift)+(\\shadowradius/2,\\shadowradius/2)$) circle (\\shadowradius);
        \\shade[outercolor,inner color=innercolor,outer color=outercolor] ($(#1.north west)+(\\shadowshift)+(\\shadowradius/2,-\\shadowradius/2)$) circle (\\shadowradius);
        \\shade[outercolor,inner color=innercolor,outer color=outercolor] ($(#1.south east)+(\\shadowshift)+(-\\shadowradius/2,\\shadowradius/2)$) circle (\\shadowradius);
        \\shade[outercolor,inner color=innercolor,outer color=outercolor] ($(#1.north east)+(\\shadowshift)+(-\\shadowradius/2,-\\shadowradius/2)$) circle (\\shadowradius);
        \\shade[top color=innercolor,bottom color=outercolor] ($(#1.south west)+(\\shadowshift)+(\\shadowradius/2,-\\shadowradius/2)$) rectangle ($(#1.south east)+(\\shadowshift)+(-\\shadowradius/2,\\shadowradius/2)$);
        \\shade[left color=innercolor,right color=outercolor] ($(#1.south east)+(\\shadowshift)+(-\\shadowradius/2,\\shadowradius/2)$) rectangle ($(#1.north east)+(\\shadowshift)+(\\shadowradius/2,-\\shadowradius/2)$);
        \\shade[bottom color=innercolor,top color=outercolor] ($(#1.north west)+(\\shadowshift)+(\\shadowradius/2,-\\shadowradius/2)$) rectangle ($(#1.north east)+(\\shadowshift)+(-\\shadowradius/2,\\shadowradius/2)$);
        \\shade[outercolor,right color=innercolor,left color=outercolor] ($(#1.south west)+(\\shadowshift)+(-\\shadowradius/2,\\shadowradius/2)$) rectangle ($(#1.north west)+(\\shadowshift)+(\\shadowradius/2,-\\shadowradius/2)$);
        \\filldraw ($(#1.south west)+(\\shadowshift)+(\\shadowradius/2,\\shadowradius/2)$) rectangle ($(#1.north east)+(\\shadowshift)-(\\shadowradius/2,\\shadowradius/2)$);
    \\end{pgfonlayer}
}
%% create a shadow layer, so that we don't need to worry about overdrawing other things
\\pgfdeclarelayer{shadow}
\\pgfsetlayers{shadow,main}

\\newcommand\\shadowimage[2][]{%%
\\begin{tikzpicture}
\\node[anchor=south west,inner sep=0] (image) at (0,0) {\\includegraphics[#1]{#2}};
\\drawshadow{image}
\\end{tikzpicture}}



"""

themeNick = """
\\usepackage{enumitem}
\\addtobeamertemplate{frametitle}{}{%
    \\begin{textblock*}{2.1cm}(0.84\\textwidth,0.15cm)
        \\includegraphics[height=0.70cm]{ucsbquark.pdf}
    %% \\begin{textblock*}{2.1cm}(0.80\\textwidth,0.08cm)
        %% \\includegraphics[height=0.82cm]{ucsbwave.pdf}
    \\end{textblock*}
    \\begin{textblock*}{2.1cm}(0.98\\textwidth,0.09cm)
        \\includegraphics[height=0.82cm]{cmsbwlogothick.png}
    \\end{textblock*}
} \n\n

\\usetheme{AnnArbor}
\\usecolortheme{dolphin}
\\setbeamercolor*{frametitle}{fg=blue!70!yellow,bg=blue!70!black!10}
\\setbeamercolor{title}{fg=white,bg=blue!70!yellow}
\\setbeamertemplate{headline}{} % suppress that top bar
\\useinnertheme{rectangles}
\\setlist[itemize]{label=$\\textcolor{thethemecolor}{\\blacktriangleright}$,leftmargin=*}

\\begin{document}
"""

themeAlex = """
\\setbeamertemplate{footline}[frame number]
\\setbeamertemplate{itemize item}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamertemplate{itemize subitem}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamertemplate{itemize subsubitem}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamercolor{frametitle}{fg=thethemecolor}
\\setbeamerfont{frametitle}{size=\\LARGE \\bfseries}
\\setbeamertemplate{footline}{\\raisebox{5pt}{\\makebox[\\paperwidth]{\\hfill\\makebox[10pt]{\\scriptsize\\textcolor{white}{\\insertframenumber\\hspace{2mm}}}}}}\\setbeamersize{text margin left=10pt,text margin right=10pt}


\\defbeamertemplate*{title page}{customized}[1][]{ 
  \\begin{textblock*}{12.8cm}(0cm,1.5cm)
  \\begin{center}
  \\usebeamerfont{title}
  \\textcolor{thethemecolor}{\\textbf{\\huge TITLEHERE} } %% Allowed 20 characters upstairs and 30 downstairs
  \\textcolor{thethemecolor}{\\rule{10cm}{2pt}}
  \\end{center}
  \\end{textblock*}
  \\begin{center}
  \\end{center}
  \\begin{textblock*}{12.8cm}(0cm,4.0cm)
  \\begin{center}
  INSTITUTEHERE
  \\end{center}
  \\end{textblock*}
  \\begin{textblock*}{2.7cm}(0cm, 0.1cm)
  \\includegraphics[width=2.7cm]{SCHOOLLOGO}
  \\end{textblock*}
  \\begin{textblock*}{2.2cm}(10.3cm, 0.2cm)
  \\includegraphics[width=2.2cm]{CMS.pdf}
  \\end{textblock*}
}

\\usebackgroundtemplate{
\\begin{tikzpicture}
   \\draw[fill=thethemecolor, draw=thethemecolor](0.0cm,0.0cm) -- (21.3cm,0.0cm) -- (21.3cm,21.3cm) -- (0.0cm,0.0cm);
\\end{tikzpicture}
}

  %% \\draw[fill=thethemecolor, draw=thethemecolor](0.0cm,0.0cm) -- (21.3cm,0.0cm) -- (21.3cm,21.3cm) -- (0.0cm,0.0cm);
    %% \\shade[top color=thethemecolor!15,bottom color=white,middle color=white] (0,0) rectangle (21.3cm,3cm);

\\begin{document}
"""

themeAlexMod = """
\\setbeamertemplate{footline}[frame number]
\\setbeamertemplate{itemize item}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamertemplate{itemize subitem}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamertemplate{itemize subsubitem}{\\color{thethemecolor}$\\blacktriangleright$}
\\setbeamercolor{frametitle}{fg=thethemecolor}
\\setbeamerfont{frametitle}{size=\\LARGE \\bfseries}
\\setbeamertemplate{footline}{\\raisebox{5pt}{\\makebox[\\paperwidth]{\\hfill\\makebox[10pt]{\\scriptsize\\textcolor{white}{\\insertframenumber\\hspace{2mm}}}}}}\\setbeamersize{text margin left=10pt,text margin right=10pt}
\\addtobeamertemplate{frametitle}{\\vskip-0.13cm}{}


\\defbeamertemplate*{title page}{customized}[1][]{ 
  \\begin{textblock*}{12.8cm}(0cm,1.5cm)
  \\begin{center}
  \\usebeamerfont{title}
  \\textcolor{thethemecolor}{\\textbf{\\huge TITLEHERE} } %% Allowed 20 characters upstairs and 30 downstairs
  \\textcolor{thethemecolor}{\\rule{10cm}{2pt}}
  \\end{center}
  \\end{textblock*}
  \\begin{center}
  \\end{center}
  \\begin{textblock*}{12.8cm}(0cm,4.0cm)
  \\begin{center}
  INSTITUTEHERE
  \\end{center}
  \\end{textblock*}
  \\begin{textblock*}{2.7cm}(0cm, 0.0cm)
  \\includegraphics[width=2.7cm]{SCHOOLLOGO}
  \\end{textblock*}
  \\begin{textblock*}{2.2cm}(10.3cm, 0.2cm)
  \\includegraphics[width=2.2cm]{CMS.pdf}
  \\end{textblock*}
}

\\usebackgroundtemplate{
%\\begin{tikzpicture}[line width=2pt, remember picture, overlay]
\\begin{tikzpicture}
   %\\shade[top color=thethemecolor!15,middle color=thethemecolor!20,bottom color=white!0] (0cm,0cm) rectangle (12.8cm,0.6cm);
   %\\draw[thick, draw=thethemecolor] (0cm,-0.21cm) -- (12.8cm,-0.21cm);
   %\\draw[fill=thethemecolor,thick,draw=thethemecolor](11.8cm,-9cm) -- (12.8cm,-9cm) -- (12.8cm,-8cm) -- (11.8cm,-9cm);
   %
   \\node [rectangle, top color=thethemecolor!25, middle color=thethemecolor!20, bottom color=white!0, anchor=north, minimum width=\\paperwidth, minimum height=0.8cm] (box) at (current page.north){};
   \\draw[fill=thethemecolor,thick,draw=thethemecolor](11.65cm,0cm) -- (12.8cm,0cm) -- (12.8cm,1.15cm) -- (11.65cm,0cm);
\\end{tikzpicture}
}

\\begin{document}
"""

themeMadrid = """
\\usepackage{enumitem}
\\addtobeamertemplate{frametitle}{}{%
    \\begin{textblock*}{2.1cm}(0.80\\textwidth,0.08cm)
        \\includegraphics[height=0.82cm]{ucsbwave.pdf}
    \\end{textblock*}
    \\begin{textblock*}{2.1cm}(0.98\\textwidth,0.09cm)
        \\includegraphics[height=0.82cm]{cmsbwlogothick.png}
    \\end{textblock*}
} \n\n

\\usetheme{AnnArbor}
\\usecolortheme{wolverine}
\\setbeamertemplate{headline}{} % suppress that top bar
\\setlist[itemize]{label=$\\textcolor{thethemecolor}{\\blacktriangleright}$,leftmargin=*}

\\begin{document}
"""

footer = "\\end{document}"
