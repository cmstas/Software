## setup
1) `export PATH=/nfs-7/texlive/2015/bin/x86_64-linux:$PATH`

2) `cd` to slideMaker directory and add it to the path: `export PYTHONPATH=$PYTHONPATH:$(pwd)`

3) If you want to use tables, `cd` to the slideMaker directory and do `curl -O https://raw.githubusercontent.com/aminnj/makers/master/tableMaker/tableMaker.py`

I recommend putting these in your .bashrc.

## minimal minimal minimal working example
1) `cd project/`

2) `python test.py`

This will produce test_1.pdf with an example slide for each of the possible slide types, and copy them to your public_html folder

## testing working example
Instead of test.py, you could execute slideMaker.py. This makes it simpler to test things on the fly.

## Options
### addGlobalOptions options
  * --graphicspaths X: X is a comma separated list of paths for images/plots (note that a trailing / is required)
  * --makegui: make a GUI if invalid objects are created
  * --makegrid: draw a grid on a slide if invalid objects are created

### initSlides options
  * --modernfont: use Helvetica font
  * --themecolor r,g,b: takes RGB values for overall theme color.
  * --themecolor random: the "random" keyword will make slideMaker pick one for you
  * --casual X: only display X as your name on title slide, not full SNT list

### addSlide options
  * --drawtype shadowimage: draw images on slide with a shadow
  * --shorttitle X: only applies to title slide. uses a short title for the footer bar
  * --sidebyside: displays text and plot side by side rather than text on top and plot on bottom
  * --texttop: for a slide with text only, this aligns text at the top rather than center
  * --textbottom: for a slide with text only, this aligns text at the bottom rather than center
  * --movedowntext X: for a slide containing text, this shifts the text down by a fraction of the slide (0.5 is half the slide)
  * --vertical: for slides with two figures, this places them on top of each other
  * --sizeratio: for slides with two figures, this is the fraction of the slide to give the first object
  * --textsize: for slides with text, this number (between -4 and 5) will change the text size (0 is normal)
  * --plottop: for slides with text and plot(s), this places the text on the bottom (default is on top)
  * --fithorizontal: for slides with a single plot, this aligns the plot to fit the width of the slide (default is height)
  * --numrows: for slides with a list of plots, this specifies the number of rows for the grid of plots (default is 2)

### addObject options
  * supported object types: text, brace, arrow, line, box, circle
  * --noarrowhead: draw arrow with no arrowhead
  * --rotate X: rotate textbox by X degrees
  * --crayon: draw object with crayon theme (looks sort of like Keynote)
  * --shadow: draw object with shadow
  * --dashed: draw object with dashed lines
  * --flip: flip direction of arrows and braces (reverses opening of braces)

### startBackup options
  * --resetnumbering: reset the slide numbers once you hit the backup

### writeSlides options
  * --compile: compile slides (twice, for slide numbers) after writing .tex source (enabled by default)
  * --copy: copy output .pdf file to web directory (default: public_html)
  * --dump: copy to "dump" directory within web directory
  * --provenance: append a slide with the python source in small white font. using "pdftotext" on pdf you can recover the source

## Misc tips
  * Writing the text "ENDL" without quotes in the title of the title slide or when specifying --casual X will force
    a new line. This is helpful for when the function that wraps titles automatically is being stupid.
  * Make sure to always escape backslashes and underscores in the text, e.g., "\\\\met" instead of "\met" and
    "h1D\\\\_njets" instead of "h1D_njets". You don't need to escape underscores when inside the $ $ environment.
  * Common symbols are built in, so you can do "$\\\\met \\\\gt 30$" or "$\\\\pt$" or even "$\\\\ht$". Feel free to add in more useful 
    commands into strings.py.
  * Place the date in the document via "\\\\today"
  * Supplying the parameter "tex" will let you write your own TeX code for a slide
  * If you put the word "fixme" in the path for any plot, slideMaker puts a FIXME placeholder for you

## TODO:
  * figure out good algorithm for resizing images so that they don't overlap with text
  ** see http://www.latex-community.org/forum/viewtopic.php?f=45&t=22655
  * table maker
