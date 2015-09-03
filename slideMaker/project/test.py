import sys

import slideMaker as sm

sm.addGlobalOptions("--makegui")

content = """
 - first \\textbf{bullet} \\red{point} and if I make it long enough, it should wrap to the next line
   -- first secondary bullet \\textcolor{blue}{point}. similarly this should wrap to the next line given enough length
   -- second secondary bullet point $\\met$
   -- third secondary bullet \\orange{test}
"""

sm.addObject("t1","text",(0.25,0.15),width=0.3, text="testlabel", color="red", size=0, bold=False,opts="--rotate -45") 
sm.addObject("t2","text",(0.75,0.15),width=0.3, text="testlabel", color="coolblue", size=0, bold=False) 
sm.addObject("a1","arrow", (0.31,0.15), (0.69,0.15))
sm.addObject("a2","arrow", (0.31,0.15), (0.65,0.46), opts="--crayon --noarrowhead")

sm.addObject("a0","arrow")
sm.addObject("c0","circle")

# supported themes are "nick", "alex", and "madrid"
# test2 and test3 can be folders with your plots, so you can execute this script anywhere really
# themecolor takes RGB. could put in explicit color names, but RGB more robust
# also try the --modernfont option
sm.initSlides(me="Nick",themeName="nick",opts="--graphicspaths ./test2/,./test3/ --themecolor 51,51,179")
sm.addSlide(title="Perturbation Theory on $H_m(dS_n,\\mathbb{R})$ Orbifolds", opts="--shorttitle snarxiv hep-th")

# pass in a list of textobjects (which are just dicts, so they can be modified too)
sm.addSlide(p1="yields.pdf",p2="yields.pdf", objects=["t1","t2","a1","a2"])
sm.addSlide(p1="yields.pdf",p2="yields.pdf")

# when I specify an empty object, a helper grid gets printed on the slide if I've specified
# the global option "--makegrid". A gui is produced if I specify "--makegui" instead
sm.addSlide(p1="zmass.pdf", objects=["a0","c0"])
sm.addSlide(text=content+content)

# slides reset their numbering when you start the backup section
# default (no option) does not do this
sm.startBackup(opts="--resetnumbering")
sm.addSlide(text=content, p1="filt.pdf", opts="--sidebyside")
sm.addSlide(text=content, p1="zmass.pdf", p2="zmass.pdf")

sm.writeSlides("test_1.tex", opts="--compile --copy")
