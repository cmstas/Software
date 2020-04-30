Random standalone scripts for dealing with ROOT files. Useful to point your PATH here in bashrc to be able to use these as executables.

1. `copyTree.py` - general purpose tool for copying/merging/skimming ROOT trees. See top of file for instructions.
2. `printBranchSizes.py` - print the raw and compressed sizes of each branch in a TTree, along with compression factor and % of
total space that each branch takes up. Usage is `printBranchSizes.py [OPTIONS] input_file.root`. Options are `-t TREENAME` to
specify a tree name other than "Events", `-r` to display raw byte counts instead of human-readable forms, and
`-e` to display branch sizes as per-event averages.
