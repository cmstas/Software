## setup
1) `export PATH=/nfs-7/texlive/2015/bin/x86_64-linux:$PATH`

2) `cd` to slideMaker directory and add it to the path: `export PYTHONPATH=$PYTHONPATH:$(pwd)`

I recommend putting these in your .bashrc.

## minimal minimal minimal working example
1) `cd project/`

2) `python test.py`

This will produce test_1.pdf with an example slide for each of the possible slide types, and copy them to your public_html folder

## testing working example
Instead of test.py, you could execute slideMaker.py. This makes it simpler to test things on the fly.

## Options
### addGlobalOptions options
  * --graphicspaths X: X is a comma separated list of paths for images/plots
  * --makegui: make a GUI if invalid objects are created
  * --makegrid: draw a grid on a slide if invalid objects are created

### initSlides options
  * --modernfont: use Helvetica font
  * --themecolor r,g,b: takes RGB values for overall theme color
  * --casual X: only display X as your name on title slide, not full SNT list

### addSlide options
  * --drawtype shadowimage: draw images on slide with a shadow
  * --shorttitle X: only applies to title slide. uses a short title for the footer bar
  * --sidebyside: displays text and plot side by side rather than text on top and plot on bottom
  * --texttop: for a slide with text only, this aligns text at the top rather than center

### addObject options
  * supported object types: text, brace, arrow, line, box, circle
  * --noarrowhead: draw arrow with no arrowhead
  * --rotate X: rotate textbox by X degrees
  * --crayon: draw object with crayon theme (looks sort of like Keynote)
  * --shadow: draw object with shadow
  * --dashed: draw object with dashed lines
  * --flip: flip direction of arrows and braces (reverses opening of braces)

### writeSlides options
  * --compile: compile slides (twice, for slide numbers) after writing .tex source (enabled by default)
  * --copy: copy output .pdf file to web directory (default: public_html)
  * --dump: copy to "dump" directory within web directory

## TODO:
* figure out good algorithm for resizing images so that they don't overlap with text

** see http://www.latex-community.org/forum/viewtopic.php?f=45&t=22655
