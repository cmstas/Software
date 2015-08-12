## minimal minimal minimal working example
0) export PATH=/nfs-7/texlive/2015/bin/x86_64-linux:$PATH
1) cd project/
2) python test.py
This will produce test_1.pdf with an example slide for each of the possible slide types, and copy them to your public_html folder

## testing working example
Instead of test.py, you could execute slideMaker.py. This makes it simpler to test things on the fly.

## Notes:
* put updated style files into style and include them in a way similar to enumitem

## TODO:
* figure out good algorithm for resizing images so that they don't overlap with text
** see http://www.latex-community.org/forum/viewtopic.php?f=45&t=22655
