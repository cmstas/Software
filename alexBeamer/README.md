#AlexBeamer
This package generates beamer presentations with minimal effort.

###How to run
  - In your do.C, add "alexBeamer.cc+"
  - In your C file, add "alexBeamer.h"

###Instructions:
  1. Declare with "pres name"
  2. Declare "color" with "name.KeyColor('blue')".  You can use use black, red, green, blue, cyan, magenta, yellow, and darkgreen.  Others can be added, follow the procedure for darkgreen.
  3. "name.Underline('name')" to get your name bolded and underlined.  Right now only supported for Alex; add your name in the same way.
  4.  Make title slide with name.TitleSlide("Presentation Name").
  5.  All other sides should be defined with name.NewSlide(), then the body, then name.FinishSlide()

###Options for slide body:
  - name.Title("Slide Title"); 
