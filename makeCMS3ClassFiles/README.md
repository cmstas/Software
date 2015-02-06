makeCMS3ClassFiles
===============

This function quickly makes class files -- for CMS3 or anything else -- as well as the skeleton for a looper.

To download this:
git clone https://github.com/cmstas/software.git

To run:
  1.  root
  2.  .L makeCMS3ClassFiles.C++
  3.  makeCMS3ClassFiles("file you want to run on.root", "tree within that file", "class name", "namespace name", "object name")

N.B. The branchNamesFile variable is hardcoded to null, and paranoid is an optional sixth argument that defaults to false.  If you want to change the branchNamesFile, you should do so in the file directly.  If you have no idea what I'm talking about, don't worry about it.  

E-mail Alex with bug reports or feature requests, george AT physics DOT ucsb
