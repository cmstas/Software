#AlexBeamer
This package generates beamer presentations with minimal effort.

###How to run
  - In your do.C, add "alexBeamer.cc+"
  - In your C file, add "alexBeamer.h"

###Instructions:
  1. Declare with "pres name(blue)", where "blue" is any supported color: black, gray, red, green, blue, cyan, magnenta, yellow, and darkgreen.  Others can be added, follow the procedure for darkgreen.
  2. "name.Underline('Alex')" to get your name bolded and underlined.  Right now only supported for Alex; add your name in the same way.
  3.  Make title slide with name.TitleSlide("Presentation Name").
  4.  All other sides should be started with name.NewSlide() and finished with name.FinishSlide()
  5.  Add a title to the slide with name.Title("The Title");
  5.  Then choose the template you want and feed it the necessary arguments.
  6.  If your template has a text box, feed it with name->Text(R"(  blah  )"), where blah is your text in regular LaTeX format.  You can use multiple lines, etc., this is just normal LaTeX.  For multiple text boxes, just call this command twice -- they get filled from top to bottom. 

###Templates
  -TextPlotPlot("plot1", "plot2", "options");
    -This gives you two plots on the bottom of the slide, and one text bex between that and the title -- unless your plots are very wide, in which case it will usually put the plots in the middle of the slide, and give you two text boxes, one below and one above.  In this latter case, you can override this setting with --position bottom (put the wide plots at the bottom of the plot) or --position top. 

