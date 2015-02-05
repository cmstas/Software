#!/bin/bash

#Needs to be run from CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/scripts/

cmsenv

INDIR="/home/users/jgran/combine/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/test/mt2/cards_selExtendedNJets"
OUTDIR="selExtendedNJets"

declare -a samples=("T1tttt_1500_100" "T1tttt_1200_800" "T1bbbb_1500_100" "T1bbbb_1000_900" "T1qqqq_1400_100" "T1qqqq_1000_800" "T2tt_850_100" "T2tt_500_325" "T2bb_900_100" "T2bb_600_580" "T2qq_1200_100" "T2qq_600_550")
#declare -a samples=("T1tttt_1500_100" "T1tttt_1200_800")

#need to combine cards from multiple signal regions if necessary
for i in "${samples[@]}"
do
  if [ ! -e "$INDIR/card_all_$i.txt" ]; then
    python combineCards.py "$INDIR/card_"*"_$i.txt" > "$INDIR/card_all_$i.txt"  
  fi
done

if [ ! -d "$OUTDIR" ]; then
  mkdir -p "$OUTDIR"
  mkdir -p "$OUTDIR/log"
fi

pushd .
cp make_rValues.C "$OUTDIR"
cp makeLimitTable.C "$OUTDIR"
cd "$OUTDIR"

for i in "${samples[@]}"
do
  echo "Running command: combine -M Asymptotic -n "$i" "$INDIR/card_all_$i.txt" > "log/limit_$i.txt" 2>&1"
  combine -M Asymptotic -n "$i" "$INDIR/card_all_$i.txt" > "log/limit_$i.log" 2>&1
  mv "higgsCombine"$i".Asymptotic.mH120.root" "limit_"$i".root"
  echo "Running command: combine -M ProfileLikelihood --significance -t -1 --expectSignal=1 -n "$i" "$INDIR/card_all_$i.txt" > "log/significance_$i.log" 2>&1"
  combine -M ProfileLikelihood --significance -t -1 --expectSignal=1 -n "$i" "$INDIR/card_all_$i.txt" > "log/significance_$i.log" 2>&1
  mv "higgsCombine"$i".ProfileLikelihood.mH120.root" "significance_"$i".root"
  MODEL=$(echo "$i"|awk -F- 'split($1,a,"_")&&$0=a[1]') #because awk
  MASS1=$(echo "$i"|awk -F- 'split($1,a,"_")&&$0=a[2]')
  MASS2=$(echo "$i"|awk -F- 'split($1,a,"_")&&$0=a[3]')
  root -b -q "make_rValues.C(\"$MODEL\",$MASS1,$MASS2)"
done

rm make_rValues.C
rm makeLimitTable.C
rm roostats*
popd
