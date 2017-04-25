#!/bin/bash

if [ $# -lt 1 ]; then
    echo "usage: $(basename $BASH_SOURCE) <folder name> [,new folder name]"
    echo "no slashes anywhere"
    return 1
fi

dir=$1
outdir=$1
index=index.php

if [ $# -gt 1 ]; then 
    echo "Will put the stuff in $outdir instead"
    outdir=$2;
fi


function pdftopng {
if [ $# -gt 0 ]; then
    echo "$1 ==> ${1%%.pdf}.png" 
    density=150
    if [ $# -gt 1 ]; then
        density=$2
    fi
    convert -density ${density} -trim $1 -fuzz 1% ${1%%.pdf}.png

    # fi
else
    echo "Usage: pdftopng <pdf name> [optional density]"
fi
}
export -f pdftopng

ls -1 ${dir}/*.pdf | xargs -I%  -n 1 -P 15 sh -c "pdftopng % 150;"
ls -1 ${dir}/*/*.pdf | xargs -I%  -n 1 -P 15 sh -c "pdftopng % 150;"


# ln -s $index $dir/index.php
cp $index $dir/index.php

# wait
chmod -R a+r $dir
mkdir -p ~/public_html/dump/$outdir/
if [[ $(hostname) == *uaf-* ]]; then 
    mkdir -p ~/public_html/dump/
    cp -rp $dir/* ~/public_html/dump/$outdir/
else
    ssh $USER@uaf-6.t2.ucsd.edu "mkdir -p ~/public_html/dump/$outdir; rm ~/public_html/dump/$outdir/*.png"
    scp -rp $dir/* $USER@uaf-6.t2.ucsd.edu:~/public_html/dump/$outdir/
fi
echo "uaf-6.t2.ucsd.edu/~$USER/dump/$outdir/"
