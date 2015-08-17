#!/usr/bin/python
import cgi, cgitb 
import os, sys, commands

form = cgi.FieldStorage()

filename = "objectsgui.txt"
wd, output = "", ""
wd, output = form["wd"].value, form["output"].value

output = output.replace("<b>","")
output = output.replace("</b>","")
output = output.replace("<br>","\n")

fh = open("%s/%s" % (wd,filename), "w")
fh.write(output)
fh.close()

print "Content-type:text/html\r\n"
print "Wrote the output to %s/%s" % (wd,filename)
