import os,sys,commands
import utils
from strings import *
from collections import defaultdict

slideNumber = 0
source = ""
theme = ""
graphicspaths = [os.path.dirname(os.path.abspath(__file__))+"/test/", os.path.dirname(os.path.abspath(__file__))+"/logos/"]
objectslides = []
globalOpts = utils.parseOptions("")
# objs = defaultdict(list)
objs = {}

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
        %% http://tex.stackexchange.com/questions/41344/tikz-picture-on-the-entire-frame-in-beamer-without-using-overlays
        \\makebox[\\textwidth][c]{
            \\begin{tikzpicture}[thick]
            \\draw[fill=white, draw=white](0cm,0cm) -- (12.8cm,0cm) -- (12.8cm,9.6cm) -- (0cm,9.6cm) -- (0cm,0cm);
            \\end{tikzpicture}
        }
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
    elif(theme == "alex" or theme == "alexmod"):
        source = source.replace("TITLEHERE",utils.splitTitle(title))
        source += titlePageAlex
    elif(theme == "madrid"):
        source += titlePageMadrid
    else:
        source += "\\begin{frame} \\titlepage"

def addSlideTeX(slideTitle, tex,opts=""):
    opts = utils.parseOptions(opts)
    code = """
    \\begin{frame}\\frametitle{%s}
    """ % slideTitle
    code += tex
    return code

def addSlidePlot(slideTitle, plotName,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = """
    \\begin{frame}\\frametitle{%s}
    \\begin{center}
    """
    if(opts["fithorizontal"]): code += "\\vspace*{-0.035\\textheight}\\%s[width=0.99\\textwidth,keepaspectratio]{%s}"
    else: code += "\\vspace*{-0.025\\textheight}\\%s[height=0.87\\textheight,keepaspectratio]{%s}"
    code += "\\end{center}"
    code = code % (slideTitle, drawType, plotName)
    return code

def addSlidePlotPlot(slideTitle, plotName1, plotName2,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = ""
    if(opts["vertical"]): 
        totalSize = 0.84
        size1, size2 = 0.5*totalSize, 0.5*totalSize
        if(opts["sizeratio"]):
            size1, size2 = float(opts["sizeratio"])*totalSize, (1.0-float(opts["sizeratio"]))*totalSize

        code = "\\begin{frame}\\frametitle{%s}" % (slideTitle)
        code += utils.handleStartingOpts(opts)
        code += """
        \\begin{center}
        \\%s[height=%.2f\\textheight,keepaspectratio]{%s}\\vfill
        \\%s[height=%.2f\\textheight,keepaspectratio]{%s}
        \\end{center}
        """ % (drawType, size1, plotName1, drawType, size2, plotName2)
    else:
        totalSize = 0.96
        size1, size2 = 0.5*totalSize, 0.5*totalSize
        if(opts["sizeratio"]):
            size1, size2 = float(opts["sizeratio"])*totalSize, (1.0-float(opts["sizeratio"]))*totalSize

        code = "\\begin{frame}\\frametitle{%s}" % (slideTitle)
        code += utils.handleStartingOpts(opts)
        code += """
        \\begin{center}
        \\vspace*{-0.035\\textheight}\\%s[width=%.2f\\textwidth,keepaspectratio]{%s} \\hfill
        \\vspace*{-0.035\\textheight}\\%s[width=%.2f\\textwidth,keepaspectratio]{%s}
        \\end{center}
        """ % (drawType, size1, plotName1, drawType, size2, plotName2)

    return code

def addSlideTextText(slideTitle, bullets1, bullets2,opts=""):
    opts = utils.parseOptions(opts)
    pos = ""
    if(opts["texttop"]): pos = "[t]"
    if(opts["textbottom"]): pos = "[b]"

    code = "\\begin{frame}%s\\frametitle{%s} \n" % (pos,slideTitle)
    code += utils.handleStartingOpts(opts)
    code += "\\begin{columns}\n  \\begin{column}{0.5\\textwidth} \n"
    code += utils.bulletsToCode(bullets1, opts)
    code += "\\end{column}\n  \\begin{column}{0.5\\textwidth}"
    code += utils.bulletsToCode(bullets2, opts)
    code += "\\end{column}\n\\end{columns} \n"

    return code

def addSlideText(slideTitle,bullets,opts=""):
    opts = utils.parseOptions(opts)
    pos = ""
    if(opts["texttop"]): pos = "[t]"
    if(opts["textbottom"]): pos = "[b]"
    code = "\\begin{frame}%s\\frametitle{%s} \n" % (pos,slideTitle)
    code += utils.handleStartingOpts(opts)
    code += utils.bulletsToCode(bullets, opts)
    return code

def addSlideTextPlot(slideTitle,bullets,plotName,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.handleStartingOpts(opts)
    
    if(opts["sidebyside"]):
        code += "\\begin{columns}\n  \\begin{column}{0.5\\textwidth} \n"
        code += utils.bulletsToCode(bullets, opts)
        code += "\\end{column}\n  \\begin{column}{0.5\\textwidth}"
        code += "    \\begin{center}"
        code += "      \\%s[width=\\textwidth,keepaspectratio]{%s} \n" % (drawType, plotName)
        code += "    \\end{center}\n  \\end{column}\n\\end{columns} \n"
    elif(opts["plottop"]):
        code += "\\begin{center}"
        code += "  \\%s[height=%.2f\\textheight,keepaspectratio]{%s} \n" \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName)
        code += "\\end{center}\n"
        code += utils.bulletsToCode(bullets, opts)
    else:
        code += utils.bulletsToCode(bullets, opts)
        code += "\\begin{center}"
        if(opts["fithorizontal"]):
            code += "  \\vspace*{%.2f\\textheight}\\%s[width=0.99\\textwidth,keepaspectratio]{%s} \n" \
                        % (0.9-utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),drawType,plotName)
        else:
            code += "  \\%s[height=%.2f\\textheight,keepaspectratio]{%s} \n" \
                        % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName)

        code += "\\end{center}\n"

    return code


def addSlideTextPlotPlot(slideTitle,bullets,plotName1,plotName2,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.handleStartingOpts(opts)

    if(opts["plottop"]):
        code += "\\begin{center}"
        code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n" \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName1)
        code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n"  \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName2)
        code += "\\end{center}"
        code += utils.bulletsToCode(bullets, opts)
    elif(opts["plotsleft"]):
        height = 0.45
        width = 0.55
        code += "\\begin{columns}\n"
        code += "\\column{%.2f\\textwidth}\n" % width
        code += "\\centering"
        code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}\\\\ \n" % (drawType,height,1.0,plotName1)
        code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}     \n" % (drawType,height,1.0,plotName2)
        code += "\\column{%.2f\\textwidth}\n" % (1.0-width)
        code += "\\centering"
        code += utils.bulletsToCode(bullets, opts)

        code += "\\end{columns}"
    else:
        code += utils.bulletsToCode(bullets, opts)
        code += "\\begin{center}"
        code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n" \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName1)
        code += "\\%s[height=%.2f\\textheight,width=0.48\\textwidth,keepaspectratio]{%s} \n"  \
                    % (drawType, utils.textLinesToPlotHeight(utils.bulletNLines(bullets)),plotName2)
        code += "\\end{center}"
    return code

def addSlideTextPlotPlotPlotPlot(slideTitle,bullets,plotName1,plotName2,plotName3,plotName4,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.handleStartingOpts(opts)
    height = 0.5*utils.textLinesToPlotHeight(utils.bulletNLines(bullets))
    width = 1.0

    code += utils.bulletsToCode(bullets, opts)
    code += "\\begin{columns}[t]\n"

    code += "\\column{0.5\\textwidth}\n"
    code += "\\centering"
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}\\\\ \n" % (drawType,height,width,plotName1)
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}     \n" % (drawType,height,width,plotName3)

    code += "\\column{0.5\\textwidth}\n"
    code += "\\centering"
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}\\\\ \n" % (drawType,height,width,plotName2)
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}     \n" % (drawType,height,width,plotName4)

    code += "\\end{columns}"
    return code

def addSlideTextPlots(slideTitle,bullets,plots=[],drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.handleStartingOpts(opts)
    nRows = int(opts["numrows"]) if opts["numrows"] else 2
    plotChunks = [plots[i:i+nRows] for i in range(0,len(plots),nRows)]
    nCols = len(plotChunks)
    height = (1.0/nRows)*utils.textLinesToPlotHeight(utils.bulletNLines(bullets))
    width = 1.0

    code += utils.bulletsToCode(bullets, opts)
    code += "\\begin{columns}[t]\n"

    for chunk in plotChunks:
        code += "\\column{%.2f\\textwidth}\n" % (1.0/nCols)
        code += "\\centering"
        for plot in chunk:
            code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}\\\\ \n" % (drawType,height,width,plot)

    code += "\\end{columns}"
        
    return code

def addSlideTextPlotPlotPlot(slideTitle,bullets,plotName1,plotName2,plotName3,drawType="includegraphics",opts=""):
    opts = utils.parseOptions(opts)
    code = "\\begin{frame}\\frametitle{%s} \n" % (slideTitle)
    code += utils.handleStartingOpts(opts)
    height = 0.5*utils.textLinesToPlotHeight(utils.bulletNLines(bullets))
    width = 1.0

    code += utils.bulletsToCode(bullets, opts)
    code += "\\begin{columns}[c]\n"

    code += "\\column{0.5\\textwidth}\n"
    code += "\\centering"
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}\\\\ \n" % (drawType,height,width,plotName1)
    code += "\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s}     \n" % (drawType,height,width,plotName2)

    code += "\\column{0.55\\textwidth}\n"
    code += "\\centering"
    code += "\\hspace*{-0.10\\textwidth}\\%s[height=%.2f\\textheight,width=%.2f\\textwidth,keepaspectratio]{%s} \n" % (drawType,1.5*height,width,plotName3)

    code += "\\end{columns}"
    return code

def replaceFixme(p):
    if type(p) == type([]):
        return ["fixme.jpg" if "fixme" in path.lower() else path for path in p]
    else:
        if not p: return p
        return "fixme.jpg" if "fixme" in p.lower() else p

def addSlide(title=None,text=None,text1=None,text2=None,p1=None,p2=None,p3=None,p4=None,tex=None,opts="",plots=[],objects=[]):
    global source, slideNumber
    slideNumber += 1

    parsedOpts = utils.parseOptions(opts)
    drawtype = parsedOpts["drawtype"] if parsedOpts["drawtype"] else "includegraphics"
    if( text1 ): text = text1 # Compatibility

    bullets = []
    if( text ): bullets = text.split("\n")
    if( text2 ): bullets2 = text2.split("\n")

    if( not title ):
        cleanP1 = p1.replace("_","\\_").rsplit(".",1)[0].split("/")[-1] if p1 else ""
        cleanP2 = p2.replace("_","\\_").rsplit(".",1)[0].split("/")[-1] if p2 else ""
        if( p1 and not p2 ): title = cleanP1
        elif( p2 and not p1 ): title = cleanP2
        elif( p1 and p2 ): title = cleanP1 + ", " + cleanP2
        else: title = "\\phantom{}"

    p1 = replaceFixme(p1)
    p2 = replaceFixme(p2)
    p3 = replaceFixme(p3)
    p4 = replaceFixme(p4)
    plots = replaceFixme(plots)

    if( not tex ) :
        if( p1 and p2 ):
            if not text: bullets = []
            if( p3 and not p4 ):
                print "[SM] Adding TextPlotPlotPlot slide #%s" % slideNumber
                source += addSlideTextPlotPlotPlot(title,bullets,p1,p2,p3,drawType=drawtype,opts=opts)
            elif( p3 and p4 ):
                print "[SM] Adding TextPlotPlotPlotPlot slide #%s" % slideNumber
                source += addSlideTextPlotPlotPlotPlot(title,bullets,p1,p2,p3,p4,drawType=drawtype,opts=opts)
            else:
                if( text ):
                    print "[SM] Adding TextPlotPlot slide #%s" % slideNumber
                    source += addSlideTextPlotPlot(title,bullets,p1,p2,drawType=drawtype,opts=opts)
                else:
                    print "[SM] Adding PlotPlot slide #%s" % slideNumber
                    source += addSlidePlotPlot(title,p1,p2,drawType=drawtype,opts=opts)

        elif( len(plots) > 0):
            print "[SM] Adding TextPlots slide #%s" % slideNumber
            source += addSlideTextPlots(title,bullets,plots,drawType=drawtype,opts=opts)

        elif( p1 ):
            if( text ):
                print "[SM] Adding TextPlot slide #%s" % slideNumber
                source += addSlideTextPlot(title,bullets,p1,drawType=drawtype,opts=opts)
            else:
                print "[SM] Adding Plot slide #%s" % slideNumber
                source += addSlidePlot(title,p1,drawType=drawtype,opts=opts)
        elif( text ):
            if ( text2 ):
                pass
                print "[SM] Adding TextText slide #%s" % slideNumber
                source += addSlideTextText(title,bullets,bullets2,opts=opts)
            else:
                print "[SM] Adding Text slide #%s" % slideNumber
                source += addSlideText(title,bullets,opts=opts)
        elif( title ):
            print "[SM] Adding Title slide #%s" % slideNumber
            addSlideTitle(title,opts)
        else:
            print "couldn't figure out what you want"
    else:
        print "[SM] Adding custom TeX slide #%s" % slideNumber
        source += addSlideTeX(title,tex,opts=opts)

    drawGrid = False

    # objects.extend(objs[slideNumber])
    objsGUI = []
    for objectName in objects:
        object = {}
        if objectName in objs:
            object = objs[objectName]
        else:
            print "couldn't find object with id %s. did you define it?" % objectName
            continue

        if("grid" in object):
            drawGrid = True
            objsGUI.append(object)
            continue
        if(object["type"] == "box"): source += utils.getBoxCode(object)
        if(object["type"] == "circle"): source += utils.getCircleCode(object)
        if(object["type"] == "arrow"): source += utils.getArrowCode(object)
        if(object["type"] == "text"): source += utils.getFreetextCode(object)
        if(object["type"] == "line"): 
            object["opts"] += " --noarrowhead "
            source += utils.getArrowCode(object)
        if(object["type"] == "brace"): 
            object["opts"] += " --brace "
            source += utils.getArrowCode(object)

    if(drawGrid and globalOpts["makegui"]):
        objectslides.append( {"slideNumber": slideNumber, "objects": objsGUI} )
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

def addObject(name,type="box",p1=(0,0),p2=(0,0),text="",width=0.3,size=0,bold=False,color="coolblue",opts=""):
    obj = { }
    obj["name"] = name
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

    # only add the object if it's not already there
    # this is important for when the GUI makes objects
    if name not in objs.keys(): objs[name] = obj

def addGlobalOptions(optstr):
    global globalOpts
    globalOpts = utils.parseOptions(optstr)

    if(globalOpts["graphicspaths"]):
        graphicspaths.extend(globalOpts["graphicspaths"].split(","))
        print "[SM] Adding these to the graphics path:", globalOpts["graphicspaths"].split(",")

    if(globalOpts["makegui"]):
        try:
            fname = "objectsgui.txt"
            execfile(os.getcwd()+"/"+fname)
            print "[SM] Found file (%s) with objects from GUI. Importing them." % (fname)
        except:
            print "[SM] Didn't find file with objects from GUI."



def initSlides(me="Nick", themeName="nick", opts=""):
    global source, commonHeader, theme, themeAlex, themeAlexMod, slideNumber, institute
    source = ""
    theme = themeName.lower()
    opts = utils.parseOptions(opts)
    slideNumber = 0


    print "[SM] Hi",me
    print "[SM] Using theme:",theme

    source += commonHeader
    if(opts["modernfont"]):
        source += "\\usepackage{helvet} %% only modern font that works on uaf?"

    if(opts["font"]):
        # list at http://www.tug.dk/FontCatalogue/sansseriffonts.html
        # I personally like "--font gillius"
        source += "\\usepackage{%s}" % opts["font"]

    if(theme == "nick"): source += themeNick
    elif(theme == "alex"): source += themeAlex
    elif(theme == "alexmod"): source += themeAlexMod
    elif(theme == "madrid"): source += themeMadrid
    else: print "unsupported theme:", theme

    if(opts["themecolor"]):
        themecolor = opts["themecolor"]
        if "random" in themecolor:
            themecolor = "%s,%s,%s" % utils.randomColor()
            print "[SM] Using random theme color: %s" % themecolor

        source = source.replace("\\definecolor{thethemecolor}{RGB}{0,0,255}","\\definecolor{thethemecolor}{RGB}{%s}" % themecolor)
    
    if(opts["casual"]): institute = "\\large{%s}" % opts["casual"].replace("ENDL", "\\\\ \\vspace{0.4cm}")
    source = source.replace("INSTITUTEHERE", institute)

    school = "ucsb"

    fullname = ""
    if("Nick" in me): 
        source = source.replace("AUTHORHERE", "Nick Amin")
        source = source.replace("N. Amin", "\\underline{\\textbf{N. Amin}}")
        school = "ucsb"
    elif("Sicheng" in me): 
        source = source.replace("AUTHORHERE", "Sicheng Wang")
        source = source.replace("S. Wang", "\\underline{\\textbf{S. Wang}}")
        school = "ucsb"
    elif("Alex" in me): 
        source = source.replace("AUTHORHERE", "Alex George")
        source = source.replace("A. George", "\\underline{\\textbf{A. George}}")
        school = "ucsb"
    elif("Jason" in me): 
        source = source.replace("AUTHORHERE", "Jason Gran")
        source = source.replace("J. Gran", "\\underline{\\textbf{J. Gran}}")
        school = "ucsb"
    elif("Giuseppe" in me): 
        source = source.replace("AUTHORHERE", "G. Cerati")
        source = source.replace("G. Cerati", "\\underline{\\textbf{G. Cerati}}")
        school = "ucsd"
    else:
        print "who are you? add your name to slideMaker."

    if school == "ucsb":
        source = source.replace("SCHOOLLOGO", "ucsb.pdf")
    elif school == "ucsd":
        source = source.replace("SCHOOLLOGO", "ucsd.png")



    source = source.replace("GRAPHICSPATHHERE", "".join(["{"+p+"}" for p in graphicspaths]))


    print "[SM] Initializing slides"

def makeProvenance():
    global source
    # get path to script that is importing this one
    contents = ""
    try:
        fname = os.path.abspath(sys.modules['__main__'].__file__)
        with open(fname,"r") as rfile: contents = rfile.read()
        contents = contents.replace("{","{{")
        contents = contents.replace("}","}}")
        contents = contents.replace("\\","\\\\")
        # contents = "\n".join([line for line in contents.split("\n") if len(line.strip()) > 2])
        code = r"""
        \begin{frame}[plain,fragile=singleslide,shrink=75]
        \fontsize{0}{0}\color{white}
        \begin{semiverbatim}
        ### BEGIN PROVENANCE
        %s
        ### END PROVENANCE
        \end{semiverbatim}
        \end{frame}
        """ % contents
        source += code
        print "[SM] Stored provenance"
    except: print "[SM] [WARNING] Couldn't make provenance!"


def writeSlides(output="output.tex", opts="--compile --copy --dump"):
    global source

    opts = utils.parseOptions(opts)
    if(opts["provenance"]): makeProvenance()

    source += footer
    output = output.replace(".pdf",".tex")
    output = output.replace(".py",".tex") # just so I don't idiotically overwrite the slides!!! SO MAD.
    fh = open(output,"w")
    fh.write(source)
    fh.close()
    print "[SM] Wrote slides"


    if(opts["compile"]):
        # compile twice to get correct slide numbers. latex is dumb. is this the only way?
        # stat,out = commands.getstatusoutput("pdflatex -interaction=nonstopmode %s && \
        #                                      pdflatex -interaction=nonstopmode %s " % (output,output) )
        stat,out = commands.getstatusoutput("pdflatex -interaction=nonstopmode %s " % (output) )
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

    if(globalOpts["makegui"] and len(objectslides) > 0):
        utils.makeGUI(objectslides, output.replace(".tex",".pdf"), os.getcwd())

def startBackup(opts=""):
    global source, slideNumber
    slideNumber += 1

    opts = utils.parseOptions(opts)

    print "[SM] Beginning backup"

    color = "black"
    # if(theme == "alex"): color = "alexcolor"
    # if(theme == "nick"): color = "nickcolor"
    # if(theme == "madrid"): color = "madridcolor"

    if(opts["resetnumbering"]): source += "\n\\appendix\n"

    source += """
    \\begin{frame}[plain]
    \\centering
    \\begin{textblock*}{12.8cm}[0.5,0.5](6.4cm,4.8cm)
    \\begin{LARGE} \\centering \\textcolor{thethemecolor}{\\textbf{Backup}} \\end{LARGE}
    \\end{textblock*}
    \\end{frame}
    """

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
    # addGlobalOptions(""" 
    addGlobalOptions("""--makegui 
                        --graphicspaths ./test2/,./test3/ """)


    # coordinates are for top left and bottom right corners (or tail and head for arrow), respectively
    addObject("t1","text",(0.25,0.15),width=0.3, text="testlabel", color="red", size=0, bold=False,opts="--rotate -45") 
    addObject("t2","text",(0.75,0.15),width=0.3, text="testlabel", color="coolblue", size=0, bold=False) 
    addObject("a3","brace", (0.31,0.15), (0.69,0.15), opts="--flip")
    addObject("a4","arrow", (0.31,0.15), (0.65,0.46), opts="")
    addObject("l4","line", (0.31,0.15), (0.65,0.46), opts="--shadow")
    addObject("b5","box", (0.65,0.46), (0.75,0.52), color="red", opts="--crayon")
    addObject("b6","box", (0.85,0.66), (0.55,0.32), color="coolblue", opts="--shadow")
    addObject("c7","circle", (0.85,0.66), (0.55,0.32), color="coolblue", opts="--dashed ")

    addObject("a10","arrow")
    addObject("a11","arrow", (0,0))
    addObject("t10","text", (0,0))

    # for t in ["nick", "alex", "madrid"]:
    for t in ["nick"]:
        initSlides(me="Nick",themeName=t,opts="--themecolor 51,51,179 ")
        addSlide(title="Perturbation Theory on $H_m(dS_n,\\mathbb{R})$ Orbifolds", opts="--shorttitle hep-th crap")
        addSlide(text="UCSB Logo generated in LaTeX: \\[ \\begin{bmatrix} u \\\\ \\textcolor{gray!40!white}{d} \\end{bmatrix}\\!\\!  \\begin{bmatrix} c \\\\ s \\end{bmatrix}\\!\\!  \\begin{bmatrix} \\textcolor{gray!40!white}{t}   \\\\ b \\end{bmatrix} \\]", objects=["c7","b6","l4"])
        addSlide(p1="yields.pdf",p2="yields.pdf", objects=["t1","t2","a3","a4","b5","b6"])
        addSlide(text=content, objects=["t2"])
        addSlide(text=content2, p1="zmass.pdf",opts="--drawtype shadowimage")
        addSlide(text=content2, p1="zmass.pdf", opts="--sidebyside --drawtype shadowimage", objects=["a4","a11"])
        startBackup()
        addSlide(text=content2, p1="filt.pdf", objects=["t10","a10"])
        addSlide(text=content2, p1="zmass.pdf", p2="zmass.pdf")
        writeSlides("test_%s.tex" % t, opts="--compile --copy --dump")


