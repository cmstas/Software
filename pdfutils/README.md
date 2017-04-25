### pdf utilities for editing plots
#### pdftk
Needed for these operations, and is provided as an executable here. 
Please put it in your path before using the scripts here.

#### renamingutils.sh
```bash
# source to get some bash functions
source renamingutils.sh
```
Let's say you have a plot with "CMS Preliminary" and you want to
get rid of that pesky Preliminary. Do
```bash
cp input.pdf input_test.pdf
remove_preliminary input_test.pdf
# now look at input_test.pdf
```
Or let's say "Preliminary" should actually be "Cake". No problem:
```bash
cp input.pdf input_test.pdf
rename_pdf "Preliminary" "Cake" input_test.pdf 
```
Note: this takes wildcards too.

### addingutils.py
Or let's say that someone asks you to go through all your plots
and add, say, some arxiv label because it's trivial to do that 
when your plots are made with several different macros, right??? 
That's where this comes in.

This one is more manual since there's more customization.
Note that you may need a CMSSW environment since pyROOT is used.
Edit the file to have the proper root object to overlay.
To run the example, do
```bash
cp input.pdf input_test.pdf
python addingutils.py
# examine input_test_overlay.pdf
```


