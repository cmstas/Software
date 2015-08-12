## minimal minimal minimal working example
0) export PATH=/nfs-7/texlive/2015/bin/x86_64-linux:$PATH

1) check out repo and make sure there's a folder called "dump" inside the public_html directory

2) python slideMaker.py

3) look at the output

This makes it easy to edit the slideMaker and test it on-the-fly.

## standalone minimal working example
1) python test.py

This will produce test_1.pdf with an example slide for each of the possible slide types, and copy them to your public_html folder

## Notes:
* put updated style files into style and include them in a way similar to enumitem

## TODO:
* figure out good algorithm for resizing images so that they don't overlap with text
** see http://www.latex-community.org/forum/viewtopic.php?f=45&t=22655
