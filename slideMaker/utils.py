### utility functions that don't directly touch the latex source go here
import commands, os, sys

listOfOptions = ["dump", "copy", "compile", "graphicspaths", "shorttitle", "themecolor", "sidebyside", "modernfont", "noarrowhead","rotate","drawtype","crayon","shadow"]
def parseOptions(optString):
    opts = { }
    for optName in listOfOptions:
        opts[optName] = False

    for opt in optString.split("--"):
        opt = opt.strip()
        if(len(opt.split()) < 1): continue
        optName = opt.split()[0].strip()
        if(optName not in listOfOptions): 
            print ">>> Warning: unrecognized option:",optName
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
    cutoff = 20
    if(len(title) <= cutoff):
        return "\\\\ \\vspace{0.4cm} "+title
    else:
        return title[:cutoff]+title[cutoff:].split()[0] + "\\\\ \\vspace{0.4cm}" + " ".join(title[cutoff:].split()[1:])

def slideToPng(slidenumber,output,outdir):
    # note that output is the pdf file we produce from writeSlides()
    # but outdir is where we want to store the individual pages
    output = output.replace("tex","pdf")
    stat,out = commands.getstatusoutput("gs -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -dFirstPage=%i -dLastPage=%i -sOutputFile=%s/page_%i.pdf %s" % (slidenumber, slidenumber, outdir, slidenumber, output))
    stat,out = commands.getstatusoutput("gs -q -sDEVICE=pngalpha -dBATCH -dNOPAUSE -dDOINTERPOLATE -o %s/page_%i.png -sDEVICE=pngalpha -r480 %s/page_%i.pdf" % (outdir, slidenumber, outdir, slidenumber))

def makeGUI(slidenumbers, output):
    os.system("mkdir -p pages/")
    os.system("rm pages/*.png")
    for slidenumber in slidenumbers:
        slideToPng(slidenumber, output, "pages/")

    pngFiles = [file for file in os.listdir("./pages/") if file.endswith(".png")]

    html = open("./html/gui.html","r").read()

    slideStr = "'"+"', '".join(pngFiles)+"'"
    html = html.replace("SLIDESHERE", slideStr)

    newhtml = open("./pages/gui.html","w")
    newhtml.write(html)
    newhtml.close()

    stat,out = commands.getstatusoutput("cp -rp pages ~/public_html/dump/")
    print ">>> Copied GUI to uaf-6.t2.ucsd.edu/~%s/dump/pages/gui.html" % (os.getenv("USER"))



# print parseOptions("--dump --title left --caption this is stupid --unrecognizedopt")
