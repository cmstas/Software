### utility functions that don't directly touch the latex source go here
import commands, os, sys, json

basepath = os.path.dirname(os.path.abspath(__file__))
listOfOptions = ["dump", "copy", "compile", "graphicspaths", "shorttitle", "themecolor", "sidebyside", "modernfont", "noarrowhead","rotate","drawtype","crayon","shadow","makegrid","makegui","dashed","brace","flip","casual"]
def parseOptions(optString):
    opts = { }
    for optName in listOfOptions:
        opts[optName] = False

    optString = optString.replace(*"\n ")
    for opt in optString.split("--"):
        opt = opt.strip()
        if(len(opt.split()) < 1): continue
        optName = opt.split()[0].strip()
        if(optName not in listOfOptions): 
            print "[SM] Warning: unrecognized option:",optName
            continue

        if(len(opt.split()) < 2):
            opts[optName] = True
        else:
            opts[optName] = " ".join(opt.split()[1:])

    return opts

def bulletsToCode(bullets):
    code = "  \\begin{itemize}\n"
    wasSubpoint=False
    bullets = [bullet.strip() for bullet in bullets if len(bullet.strip()) > 3]
    if(len(bullets) < 1): return ""
    for i,bullet in enumerate(bullets):
        isSubpoint = bullet.strip().startswith("--")
        isLast = i == (len(bullets)-1)
        bullet = bullet.replace("--","",1).replace("-","",1).strip()

        if(isSubpoint and not wasSubpoint):
            code += "      \\begin{itemize}\n"
            code += "        \\item %s \n" % (bullet)
        elif(wasSubpoint and not isSubpoint):
            code += "      \\end{itemize}\n"
            code += "    \\item %s \n" % (bullet)
        elif(wasSubpoint and isSubpoint):
            code += "        \\item %s \n" % (bullet)
        elif(not wasSubpoint and not isSubpoint):
            code += "    \\item %s \n" % (bullet)
        else: print "You goofed with your logic"

        if(isLast and isSubpoint): code += "    \\end{itemize}\n"

        wasSubpoint = isSubpoint

    code += "  \\end{itemize}\n"
    return code

def getFreetextCode(obj):
    w = obj["width"]
    x = obj["x1"]
    y = obj["y1"]
    color = obj["color"]
    size = obj["size"]
    text = obj["text"]
    opts = parseOptions(obj["opts"])
    if(obj["bold"]): text = "\\textbf{%s}" % text
    if(opts["rotate"]): text = "\\rotatebox{%s}{%s}" % (opts["rotate"],text)

    code = """
    \\begin{textblock*}{%.2f cm}[0.5,0.5](%.2f cm,%.2f cm)
        \\begin{center}
        \\begin{%s}
            \\textcolor{%s}{%s}
        \\end{%s}
        \\end{center}
    \\end{textblock*}
    """ % (12.8*w,12.8*x,9.6*y, size, color, text, size)

    return code

def getArrowCode(obj):
    x1 = obj["x1"]
    y1 = obj["y1"]
    x2 = obj["x2"]
    y2 = obj["y2"]
    color = obj["color"]
    opts = parseOptions(obj["opts"])

    if(opts["flip"]): x1,y1,x2,y2 = x2,y2,x1,y1

    type = ""
    if(opts["brace"]):
        type += ",decorate,decoration={brace}"
    else:
        if(not opts["noarrowhead"]):
            type += ",-latex"
    if(opts["crayon"]): type += ",crayon"
    if(opts["shadow"]): type += ",shadowed={double=gray,draw=gray}"
    if(opts["dashed"]): type += ",dashed"

    code = """
    \\begin{textblock*}{12.8cm}[1.0,0.0](12.8cm,9.6cm)
        %% \\begin{tikzpicture}[overlay,remember picture]
        \\begin{tikzpicture}[overlay,remember picture,crayon/.style={thick, line cap=round, line join=round,decoration={random steps, segment length=0.15pt, amplitude=0.25pt}, decorate}]
            \\coordinate (0) at (%.2fcm,%.2fcm);   (0)  node  {};
            \\coordinate (1) at (%.2fcm,%.2fcm);   (1)  node  {};
            \\draw[draw=%s,solid,thick %s] (0) -- (1);
        \\end{tikzpicture}
    \\end{textblock*}
    """ % (12.8*x1,9.6*(1-y1),12.8*x2,9.6*(1-y2),color,type)

    return code

def getBoxCode(obj):
    x1 = obj["x1"]
    y1 = obj["y1"]
    x2 = obj["x2"]
    y2 = obj["y2"]
    color = obj["color"]
    opts = parseOptions(obj["opts"])
    type = ""
    if(opts["crayon"]): type += ",crayon"
    if(opts["shadow"]): type += ",shadowed={double=gray,draw=gray}"
    if(opts["dashed"]): type += ",dashed"

    code = """
    \\begin{textblock*}{12.8cm}[1.0,0.0](12.8cm,9.6cm)
        %% \\begin{tikzpicture}[overlay,remember picture]
        \\begin{tikzpicture}[overlay,remember picture,crayon/.style={thick, line cap=round, line join=round,decoration={random steps, segment length=0.15pt, amplitude=0.25pt}, decorate}]
            \\coordinate (0) at (%.2fcm,%.2fcm);   (0)  node  {};
            \\coordinate (1) at (%.2fcm,%.2fcm);   (1)  node  {};
            \\coordinate (2) at (%.2fcm,%.2fcm);   (2)  node  {};
            \\coordinate (3) at (%.2fcm,%.2fcm);   (3)  node  {};
            \\draw[draw=%s,solid,thick %s] (0) -- (1) -- (2) -- (3) -- (0);
        \\end{tikzpicture}
    \\end{textblock*}
    """ % (12.8*x1,9.6*(1-y1), 12.8*x2,9.6*(1-y1), 12.8*x2,9.6*(1-y2), 12.8*x1,9.6*(1-y2), color,type)

    return code

def getCircleCode(obj):
    x1 = obj["x1"]
    y1 = obj["y1"]
    x2 = obj["x2"]
    y2 = obj["y2"]
    color = obj["color"]
    opts = parseOptions(obj["opts"])
    type = ""
    if(opts["crayon"]): type += ",crayon"
    if(opts["shadow"]): type += ",shadowed={double=gray,draw=gray}"
    if(opts["dashed"]): type += ",dashed"

    tl = 12.8*x1, 9.6*(1-y1)
    br = 12.8*x2, 9.6*(1-y2)
    midpoint = (tl[0]+br[0])/2, (tl[1]+br[1])/2
    rad = abs((br[0]-tl[0])/2)

    code = """
    \\begin{textblock*}{12.8cm}[1.0,0.0](12.8cm,9.6cm)
        %% \\begin{tikzpicture}[overlay,remember picture]
        \\begin{tikzpicture}[overlay,remember picture,crayon/.style={thick, line cap=round, line join=round,decoration={random steps, segment length=0.15pt, amplitude=0.25pt}, decorate}]
            \\coordinate (0) at (%.2fcm,%.2fcm);   (0)  node  {};
            \\draw[draw=%s,solid,thick %s] (0) circle  (%.2fcm);
        \\end{tikzpicture}
    \\end{textblock*}
    """ % (midpoint[0], midpoint[1], color,type, rad)

    return code

def cleanTex(text):
    text = text.replace("\\","@")
    text = text.replace("\\\\","@")
    cleanwords = []
    for word in text.split():
        if("@" in word):
            if("{" in word and "}" in word):
                word = word.replace("}","").split("{")[-1]
                pass
            else:
                word = "XXX"
        cleanwords.append(word)
    return " ".join(cleanwords)

def numToSize(size):
    if   (size == -4): return "tiny"; 
    elif (size == -3): return "scriptsize"; 
    elif (size == -2): return "footnotesize"; 
    elif (size == -1): return "small"; 
    elif (size ==  0): return "normalsize"; 
    elif (size ==  1): return "large"; 
    elif (size ==  2): return "Large"; 
    elif (size ==  3): return "LARGE"; 
    elif (size ==  4): return "Huge"; 
    elif (size ==  5): return "HUGE"; 
    else: return "normalsize"; 

def bulletLength(text,subpoint=False):
    cleanline = cleanTex(text)
    return len(cleanline)+5*subpoint

def bulletNLines(bullets):
    nlines = 0
    for bullet in bullets:
        if(len(bullet) < 4): continue
        nlines += bulletLength(bullet)//71 + 1
    return nlines

def textLinesToPlotHeight(nlines):
    return 0.85 - nlines*0.05

def splitTitle(title):
    # title = cleanTex(title) # this removes the tex from the title!
    cutoff = 16
    if(len(title) <= cutoff):
        return "\\\\ \\vspace{0.4cm} "+title
    else:
        return title[:cutoff]+title[cutoff:].split()[0] + "\\\\ \\vspace{0.4cm}" + " ".join(title[cutoff:].split()[1:])

def slideToPng(slidenumber,output,outdir):
    # note that output is the pdf file we produce from writeSlides()
    # but outdir is where we want to store the individual pages
    output = output.replace("tex","pdf")
    cmd1 = "gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -dFirstPage=%i -dLastPage=%i -sOutputFile=%s/page_%i.pdf %s" % (slidenumber, slidenumber, outdir, slidenumber, output)
    cmd2 = "gs -q -sDEVICE=pngalpha -dBATCH -dNOPAUSE -dDOINTERPOLATE -o %s/page_%i.png -sDEVICE=pngalpha -r200 %s/page_%i.pdf" % (outdir, slidenumber, outdir, slidenumber)
    stat,out = commands.getstatusoutput(cmd1)
    stat,out = commands.getstatusoutput(cmd2)

def makeGUI(guiInfo, output, workingdir):
    os.system("mkdir -p pages/")
    os.system("rm pages/*.{png,pdf}")
    slidenumbers = [e["slideNumber"] for e in guiInfo]
    
    # print json.dumps(guiInfo)

    for slidenumber in slidenumbers:
        slideToPng(slidenumber, output, "pages/")

    pngFiles = [file for file in os.listdir("./pages/") if file.endswith(".png")]
    pngFiles.sort()

    html = open("%s/html/gui.html" % basepath,"r").read()

    slideStr = "'"+"', '".join(pngFiles)+"'"
    html = html.replace("SLIDESHERE", slideStr)
    html = html.replace("INFOHERE", json.dumps(guiInfo))
    html = html.replace("WORKINGDIRHERE", workingdir)

    newhtml = open("./pages/gui.html","w")
    newhtml.write(html)
    newhtml.close()

    stat,out = commands.getstatusoutput("cp %s/html/*.{js,py} pages/" % basepath)
    # need 755 permissions or else cgi-bin stuff doesn't work
    stat,out = commands.getstatusoutput("chmod 755 pages")
    stat,out = commands.getstatusoutput("cp -r pages ~/public_html/dump/")
    print "[SM] Copied GUI to uaf-6.t2.ucsd.edu/~%s/dump/pages/gui.html" % (os.getenv("USER"))

