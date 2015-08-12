import os,sys,commands
import utils
from strings import *
from collections import defaultdict

slideNumber = 0
source = ""
theme = ""
graphicspaths = ["./test/", "./logos/", os.path.dirname(os.path.abspath(__file__))+"/logos/"]
gridslides = []
globalOpts = utils.parseOptions("")
objs = defaultdict(list)

def addSlideTitle(title="", opts=""):
    global source

    opts = utils.parseOptions(opts)
    shorttitle = opts["shorttitle"] if opts["shorttitle"] else title

    titlePageNick = """
    \\title[%s]{%s}
    \\begin{frame}
    \\titlepage
        \\begin{textblock*}{2.1cm}(0.12\\textwidth,0.8\\textheight)
            \\includegraphics[height=1.3cm]{ucsbwave.pdf}
        \\end{textblock*}
        \\begin{textblock*}{2.1cm}(0.8\\textwidth,0.8\\textheight)
            \\includegraphics[height=1.3cm]{cmsbwlogothick.png}
        \\end{textblock*}
    """ % (shorttitle,title)

    titlePageAlex = """
    \\begin{frame}[plain]
        %% draw over global triangle so that it doesn't show up on the title slide
        \\begin{tikzpicture}[thick]
        \\draw[fill=white, draw=white](0cm,0.0cm) -- (20.3cm,0.0cm) -- (20.3cm,20.3cm) -- (0.0cm,0.0cm);
        \\end{tikzpicture}
        \\titlepage 
    """

    titlePageMadrid = """
    \\title[%s]{%s}
    \\begin{frame}
    \\titlepage
        \\begin{textblock*}{2.1cm}(0.12\\textwidth,0.8\\textheight)
            \\includegraphics[height=1.3cm]{ucsbwave.pdf}
        \\end{textblock*}
        \\begin{textblock*}{2.1cm}(0.8\\textwidth,0.8\\textheight)
            \\includegraphics[height=1.3cm]{cmsbwlogothick.png}
        \\end{textblock*}
    """ % (shorttitle,title)

    if(theme == "nick"):
        source += titlePageNick
    elif(theme == "alex"):
        source = source.replace("TITLEHERE",utils.splitTitle(title))
        source += titlePageAlex
    elif(theme == "madrid"):
        source += titlePageMadrid
    else:
        source += "\\begin{frame} \\titlepage"


def addSlidePlot(slideTitle, plotName,drawType="includegraphics",opts=""):
    code = """
    \\begin{frame}\\frametitle{%s}
    \\begin{center}
    \\vspace*{-0.035\\textheight}\\%s[height=0.88\\textheight,keepaspectratio]{%s}
    \\end{center}
    """ % (slideTitle, drawType, plotName)
    return code

def addSlidePlotPlot(slideTitle, plotName1, plotName2,drawType="includegraphics",opts=""):
    code = """
    \\begin{frame}\\frametitle{%s}
    \\begin{center}
    \\vspace*{-0.035\\textheight}\\%s[height=0.95\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \\hfill
    \\vspace*{-0.035\\textheight}\\%s[height=0.95\\textheight,width=0.48\\textwidth,keepaspectratio]{%s}
    \\end{center}
    """ % (slideTitle, drawType, plotName1, drawType, plotName2)
    return code

def addSlideText(slideTitle,bullets,opts=""):
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.bulletsToCode(bullets)
    return code

def addSlideTextPlot(slideTitle,bullets,plotName,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    
    if(opts["sidebyside"]):
        code += "\\begin{columns}\n  \\begin{column}{0.5\\textwidth} \n"
        code += utils.bulletsToCode(bullets)
        code += "\\end{column}\n  \\begin{column}{0.5\\textwidth}"
        code += "    \\begin{center}"
        code += "      \\%s[width=\\textwidth,keepaspectratio]{%s} \n" % (drawType, plotName)
        code += "    \\end{center}\n  \\end{column}\n\\end{columns} \n"
    else:
        code += utils.bulletsToCode(bullets)
        code += "\\begin{center}"
        code += "  \\%s[height=%.2f\\textheight,keepaspectratio]{%s} \n" \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName)
        code += "\\end{center}\n"

    return code

def addSlideTextPlotPlot(slideTitle,bullets,plotName1,plotName2,drawType="includegraphics",opts=""):
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.bulletsToCode(bullets)
    code += "\\begin{center}"
    code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n" \
                % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName1)
    code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n"  \
                % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName2)
    code += "\\end{center}"
    return code

def addSlide(title=None,text=None,p1=None,p2=None,opts="",textobjects=[],arrowobjects=[],boxobjects=[],objects=[]):
    global source, slideNumber
    slideNumber += 1

    parsedOpts = utils.parseOptions(opts)
    drawtype = parsedOpts["drawtype"] if parsedOpts["drawtype"] else "includegraphics"

    bullets = []
    if( text ): bullets = text.split("\n")

    if( not title ):
        cleanP1 = p1.replace("_","\\_").rsplit(".",1)[0].split("/")[-1] if p1 else ""
        cleanP2 = p2.replace("_","\\_").rsplit(".",1)[0].split("/")[-1] if p2 else ""
        if( p1 and not p2 ): title = cleanP1
        elif( p2 and not p1 ): title = cleanP2
        elif( p1 and p2 ): title = cleanP1 + ", " + cleanP2
        else: title = "\\phantom{}"

    if( p1 and p2 ):
        if( text ):
            print "[SM] Adding TextPlotPlot slide #%s" % slideNumber
            source += addSlideTextPlotPlot(title,bullets,p1,p2,drawType=drawtype,opts=opts)
        else:
            print "[SM] Adding PlotPlot slide #%s" % slideNumber
            source += addSlidePlotPlot(title,p1,p2,drawType=drawtype,opts=opts)
    elif( p1 ):
        if( text ):
            print "[SM] Adding TextPlot slide #%s" % slideNumber
            source += addSlideTextPlot(title,bullets,p1,drawType=drawtype,opts=opts)
        else:
            print "[SM] Adding Plot slide #%s" % slideNumber
            source += addSlidePlot(title,p1,drawType=drawtype,opts=opts)
    elif( text ):
        print "[SM] Adding Text slide #%s" % slideNumber
        source += addSlideText(title,bullets,opts=opts)
    elif( title ):
        print "[SM] Adding Title slide #%s" % slideNumber
        addSlideTitle(title,opts)
    else:
        print "couldn't figure out what you want"

    drawGrid = False

    objects.extend(objs[slideNumber])
    for object in objects:
        if("grid" in object):
            drawGrid = True
            continue
        if(object["type"] == "box"): source += utils.getBoxCode(object)
        if(object["type"] == "arrow"): source += utils.getArrowCode(object)
        if(object["type"] == "text"): source += utils.getFreetextCode(object)

    if(drawGrid and globalOpts["makegui"]):
        gridslides.append( slideNumber )
        print "[SM] Unspecified coordinates for object, will add to GUI"


    if( drawGrid and globalOpts["makegrid"]):
        print "[SM] Unspecified coordinates for object, will print out a grid for you"
        texts, arrows = [], []
        ndivs = 20
        for i in range(1,ndivs):
            texts.append( object("text",p1=(0.03,1.0*i/ndivs-0.010),width=0.3, text="\\scalebox{0.7}{%.2f}" % (1.0*i/ndivs), color="red", size=-4, bold=False) )
            arrows.append( object("arrow", (0.0,1.0*i/ndivs), (1.0,1.0*i/ndivs), color="grey",opts="--noarrowhead" ) )

            texts.append( object("text",p1=(1.0*i/ndivs-0.015,0.01),width=0.3, text="\\scalebox{0.7}{%.2f}" % (1.0*i/ndivs), color="red", size=-4, bold=False) )
            arrows.append( object("arrow", (1.0*i/ndivs,0.0), (1.0*i/ndivs,1.0), color="grey",opts="--noarrowhead" ) )
        for text in texts: source += utils.getFreetextCode(text)
        for arrow in arrows: source += utils.getArrowCode(arrow)

    source += "\\end{frame} \n\n"


def object(type="box",p1=(0,0),p2=(0,0),text="",width=0.3,size=0,bold=False,color="coolblue",opts=""):
    obj = { }
    obj["width"] = width
    obj["text"] = text
    obj["bold"] = bold
    obj["color"] = color
    obj["opts"] = opts
    obj["size"] = utils.numToSize(size)
    obj["x1"], obj["y1"] = p1
    obj["x2"], obj["y2"] = p2
    obj["type"] = type

    # let's flag this slide and put a grid on it to help the user
    if(p1 == (0,0) and p2 == (0,0)): obj["grid"] = 1
    return obj

def addGlobalOptions(optstr):
    global globalOpts
    globalOpts = utils.parseOptions(optstr)
    
def initSlides(me="Nick", themeName="nick", opts=""):
    global source, commonHeader, theme, themeAlex, slideNumber
    source = ""
    theme = themeName.lower()
    opts = utils.parseOptions(opts)
    slideNumber = 0


    print "[SM] Hi",me
    print "[SM] Using theme:",theme

    source += commonHeader
    if(opts["modernfont"]):
        source += "\\usepackage{helvet} %% only modern font that works on uaf?"

    if(theme == "nick"):
        source += themeNick
        if(opts["themecolor"]): source = source.replace("\\definecolor{nickcolor}{RGB}{51,51,179}","\\definecolor{nickcolor}{RGB}{%s}" % opts["themecolor"])
    elif(theme == "alex"):
        source += themeAlex
        if(opts["themecolor"]): source = source.replace("\\definecolor{alexcolor}{RGB}{0,0,255}","\\definecolor{alexcolor}{RGB}{%s}" % opts["themecolor"])
    elif(theme == "madrid"):
        source += themeMadrid
        if(opts["themecolor"]): source = source.replace("\\definecolor{madridcolor}{RGB}{51,51,179}","\\definecolor{madridcolor}{RGB}{%s}" % opts["themecolor"])
    else:
        print "unsupported theme:", theme
    

    if("Nick" in me): 
        source = source.replace("AUTHORHERE", "Nick Amin")
        source = source.replace("N. Amin", "\\underline{\\textbf{N. Amin}}")
    elif("Sicheng" in me): 
        source = source.replace("AUTHORHERE", "Sicheng Wang")
        source = source.replace("S. Wang", "\\underline{\\textbf{S. Wang}}")
    elif("Alex" in me): 
        source = source.replace("AUTHORHERE", "Alex George")
        source = source.replace("A. George", "\\underline{\\textbf{A. George}}")
    else:
        print "who are you?"

    if(opts["graphicspaths"]):
        graphicspaths.extend(opts["graphicspaths"].split(","))
        print "[SM] Adding these to the graphics path:", opts["graphicspaths"].split(",")

    source = source.replace("GRAPHICSPATHHERE", "".join(["{"+p+"}" for p in graphicspaths]))

    print "[SM] Initializing slides"

def writeSlides(output="output.tex", opts="--compile"):
    global source
    source += footer
    fh = open(output,"w")
    fh.write(source)
    fh.close()
    print "[SM] Wrote slides"

    opts = utils.parseOptions(opts)

    if(opts["compile"]):
        # compile twice to get correct slide numbers. latex is dumb. is this the only way?
        stat,out = commands.getstatusoutput("pdflatex -interaction=nonstopmode %s && \
                                             pdflatex -interaction=nonstopmode %s " % (output,output) )
        if("Fatal error" in out):
            print "[SM] ERROR: Tried to compile, but failed. Last few lines of printout below."
            print "_"*40
            print "\n".join(out.split("\n")[-30:])
            return
        else:
            print "[SM] Compiled slides to", output.replace(".tex",".pdf")

        if(opts["copy"]):
            stat,out = commands.getstatusoutput("cp %s ~/public_html/%s/" % (output.replace(".tex",".pdf"), "dump" if opts["dump"] else ""))
            print "[SM] Copied output to uaf-6.t2.ucsd.edu/~%s/%s%s" % (os.getenv("USER"), "dump/" if opts["dump"] else "", output.replace(".tex",".pdf"))

    if(globalOpts["makegui"]):
        utils.makeGUI(gridslides, output.replace(".tex",".pdf"))

def startBackup():
    global source, slideNumber
    slideNumber += 1

    color = "black"
    if(theme == "alex"): color = "alexcolor"
    if(theme == "nick"): color = "nickcolor"
    if(theme == "madrid"): color = "madridcolor"

    source += """
    \\appendix
    \\begin{frame}[plain]
    \\centering
    \\begin{textblock*}{12.8cm}[0.5,0.5](6.4cm,4.8cm)
    \\begin{LARGE} \\centering \\textcolor{%s}{\\textbf{Backup}} \\end{LARGE}
    \\end{textblock*}
    \\end{frame}
    """ % (color)

if __name__ == '__main__':
    content = """
     - first \\textbf{bullet} point and if I make it long enough, it should wrap to the next line
     -- first secondary bullet \\textcolor{blue}{point} similarly this should wrap to the next line given enough length
     - lorem ipsum Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed   
     -- tempor incididunt ut labore et dolore magna aliqua. Ut enim ad mini aa 
     -- second secondary bullet point $\\met$
     -- third secondary bullet \\orange{test}
     - second \\textcolor{red}{point}
     - third bullet point
     -- fourth secondary bullet point $Z\\rightarrow\\mu\\mu$
    """
    content2 = "\n".join(content.split("\n")[0:4])

    # global options that aren't slide specific
    addGlobalOptions("--makegui")

    # coordinates are for top left and bottom right corners (or tail and head for arrow), respectively
    t1 = object("text",(0.25,0.15),width=0.3, text="testlabel", color="red", size=0, bold=False,opts="--rotate -45") 
    t2 = object("text",(0.75,0.15),width=0.3, text="testlabel", color="coolblue", size=0, bold=False) 
    a3 = object("arrow", (0.31,0.15), (0.69,0.15))
    a4 = object("arrow", (0.31,0.15), (0.65,0.46), opts="--crayon --noarrowhead")
    b5 = object("box", (0.65,0.46), (0.75,0.52), color="red", opts="--crayon")
    b6 = object("box", (0.85,0.66), (0.55,0.32), color="coolblue", opts="--shadow")

    # for t in ["nick", "alex", "madrid"]:
    for t in ["nick"]:
        initSlides(me="Nick",themeName=t,opts="--graphicspaths ./test2/,./test3/ --themecolor 51,51,179 ")
        addSlide(title="Perturbation Theory on $H_m(dS_n,\\mathbb{R})$ Orbifolds", opts="--shorttitle hep-th crap")
        addSlide(text="UCSB Logo generated in LaTeX: \\[ \\begin{bmatrix} u \\\\ \\textcolor{gray!40!white}{d} \\end{bmatrix}\\!\\!  \\begin{bmatrix} c \\\\ s \\end{bmatrix}\\!\\!  \\begin{bmatrix} \\textcolor{gray!40!white}{t}   \\\\ b \\end{bmatrix} \\]")
        addSlide(p1="yields.pdf",p2="yields.pdf", objects=[t1,t2,a3,a4,b5,b6])
        addSlide(text=content, objects=[t2,a4])
        addSlide(text=content2, p1="zmass.pdf",opts="--drawtype shadowimage")
        addSlide(text=content2, p1="zmass.pdf", opts="--sidebyside --drawtype shadowimage", objects=[object("arrow")])
        startBackup()
        addSlide(text=content2, p1="filt.pdf", objects=[object("text")])
        addSlide(text=content2, p1="zmass.pdf", p2="zmass.pdf")
        writeSlides("test_%s.tex" % t, opts="--compile --copy --dump")


