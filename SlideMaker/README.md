#AlexBeamer
This package generates beamer presentations with minimal effort.

###How to run
  - In your do.C, add "alexBeamer.cc+"
  - In your C file, add "alexBeamer.h"
  - YOU MUST USE ROOT 6!! (or at least some version of C++11, if you plan to feed in long patches of LaTeX).  

###Instructions:
  1. Declare with "pres name(blue)", where "blue" is any supported color: black, gray, red, green, blue, cyan, magnenta, yellow, and darkgreen.  Others can be added, follow the procedure for darkgreen.
  2. "name.Underline('Alex')" to get your name bolded and underlined.  Right now only supported for Alex; add your name in the same way.
  3.  Make title slide with name.TitleSlide("Presentation Name").
  4.  All other sides should be started with name.NewSlide() and finished with name.FinishSlide()
  5.  Add a title to the slide with name.Title("The Title") -- if you want a title on your slide
  5.  Then choose the template you want and feed it the necessary arguments.
  6.  If your template has a text box, feed it with name->Text(R"(  blah  )"), where blah is your text in regular LaTeX format.  You can use multiple lines, etc., this is just normal LaTeX.  If your template supports multiple text boxes, just call this command twice -- they get filled from upper left to bottom right.

###Templates
  - TextPlotPlot("plot1", "plot2", "options");
    - This gives you two plots on the bottom of the slide, and one text bex between that and the title.  Fill the text box with name->Text()
    - Exception is if your plots are very wide, in which case it will usually put the plots in the middle of the slide, and give you two text boxes, one below and one above.  In this case, you can override this setting with --position bottom (put the wide plots at the bottom of the slide) or --position top. 
  - AllText("options")
    - This gives you text only.  I can't figure out how to detect when there's too much text (without a huge, error-prone function), but you can manually change the size with option --size N, where N can be anywhere from -5 to +4).
  - TextPlot("plot", "options"); 
    - This gives you text on the left (fill with name->Text()) and an image on the right.  
    - Options are --label X, --labelColor red, and --labelUnderline, to label the figure
  - Plot("plot", "options"); 
    - This gives you an image only.  You can add a title in the usual way if you want a title as well (most images will be larger if no title).
    - Options are --label X, --labelColor red, and --labelUnderline, to label the figure
  - Table("table", "options"); 
    - This gives you a slide with a table centered on it (beamer defaults).  You can add a title in the usual way if you want a title as well (most images will be larger if no title).
  - TableText("table", "options")
    - This gives you a slide with text on the left and a table on the right.
    - Some effort is made to vertically center the table, but you can fine tune with the --moveDown X option, where X is a fraction
    - For particularly wide or narrow tables, you should use the --width X option, where X is a fraction, to specify the width of the TEXT.
    - Captions and titles for the tables should be added to the table directly.  Hint: if you use the SNT Table Maker, the table->ForSlideMaker method will add your title in the appropriate place. 


###Other options
  - To add free text, the command is FreeText(x, y, text, options); 
    - supported options are --width (as fraction), --size (of text, from -5 to +4), --underline, and --bold.  
    - This is designed for only short text snippets; choose a different template if you need substantial input
    - name->FreeText(R"( blah )") will allow you to write regular LaTeX  for the ``blah.'' Otherwise you will have to comment out escape characters, stay on one line, etc.