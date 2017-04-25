function remove_preliminary() {
    rename_pdf "Preliminary" "" $@
}
export -f remove_preliminary
function rename_pdf() {
    # Stolen from claudio
    oldtext="$1"
    newtext="$2"
    shift
    shift
    for pdffile in $@; do
        echo "Processing $pdffile..."
        cp $pdffile $pdffile.bak
        pdftk $pdffile output $pdffile.tmp uncompress
        rm $pdffile
        # the LANG=C hack may or may not be needed
        LANG=C && sed -i -e "s/$oldtext/$newtext/g" $pdffile.tmp
        pdftk $pdffile.tmp output $pdffile compress
        rm -f $pdffile.tmp
        rm -f $pdffile.tmp-e
    done
}
export -f rename_pdf
