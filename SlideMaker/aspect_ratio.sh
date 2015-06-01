#!/bin/bash

gs -dNODISPLAY -q -sFile=$1 -dDumpMediaSizes pdf_info.ps | grep "MediaBox" | awk '{print $9, $10, $11, $15, $12 }' | rev | cut -c 1 --complement | rev | cut -c 1 --complement | awk '{print "--" $3 - $1, "--" $5 - $2, "--" $4}' 

