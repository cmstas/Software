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

For a skeleton looper:
  Doing the above will also make ScanChain.C and doAll.C, which is a skeleton looper.  

For New Students:
  1.  Download this and run it.  For the first argument, use any sample in /hadoop/cms/store/group/snt/phys14 (ideally pick the most recent SMS sample you can find in that directory, but any sample really should work for most purposes).  This will produce CMS3.cc CMS3.h doAll.C and ScanChain.C.  
  2.  Test this by running "root doAll.C".  If you have troubles, your ROOT is probably installed incorrectly, ask smart people for help.
  3.  Now you write your code in looper.C and run it in doAll.C.  You can use this ScanChain to fill plots, make babies, whatever you want.  

E-mail Alex with bug reports or feature requests, george AT physics DOT ucsb
