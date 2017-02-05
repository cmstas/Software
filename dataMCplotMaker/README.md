dataMCplotMaker
===============

Function to quickly make nice data/MC plots or data plots, with or without signal.  In addition to formatting, it automatically makes overflow/underflow bins, automatically puts the smallest backgrounds on the bottom, and automatically chooses a reasonable maximum and minimum.  

To download this:
git clone ssh://git@github.com/cmstas/software.git

To run:
  1.  Put both .cc and .h files in the same directory as your macro.  dataMCplotMaker for 1D plots; PlotMaker2D for 2D plots.
  2.  "Include" the .h file (#include "path/dataMCplotMaker.h") in your file
  3.  In root, compile the .cc file (.L path/dataMCplotMaker.cc+) before loading and compiling your file.

Quick start/testing:
  1.  cd test/
  2.  root -b -q doAll.C

##Instructions for Python usage
This is all that matters. Simply open dataMCplotMaker.py and execute it to see an example. This is perfectly importable.

##Instructions for 1D plots

To call the function (first 3 are required):
````
  dataMCplotMaker(TH1F* data, vector<TH1F*> Backgrounds, vector<string> Bkg_titles, string title = "", string Title2, string Options, vector<TH1F*> Signals, vector<string> SignalTitles, vector<Color_t> colors)
````

Mandatory arguments:
  - data: a histogram of the data.  If you have no data, set this equal to a null histogram [TH1F* null = new TH1F("","",1,0,1) ].  The code is smart enough to give you a good-looking plot.  
  - backgrounds: a vector of histograms, each representing a background.  If you want to compare various quantities, set them both here and use the --noStack option
  - titles: the name of each background, in the same order as the backgrounds vector
  - title: the title of the distribution
  - title2: the subtitle of the distribution

Systematic Uncertainties:
  - You can replace the background vector with a vector of pairs.  The first part of the pair is the normal background.  The second part of the pair can be:
    - Another histogram with the error set equal to the syst error you want, OR
    - A float showing a fractional syst error (ie 0.3)
  - **The errors will always appear around the total (even with --noStack, --noFill, etc.), no other options are supported.**

Optional arguments:
  - options: a string with any optional flags you want (see supported options below)
  - signals: a vector of histograms, each representing a signal (enter std::vector <TH1F*>() if you have no signal but want to specify colors)
  - signal title: the name of each signal, in the same order as the signals vector (enter std::vector <string>() if you have no signal but want to specify colors)
  - colors: a vector of kColors that you want to use instead of the defaults [ex: vector.push_back(kRed)], starting with the backgrounds and ending with signals

Supported flags for "options" string:

  - --outputName X: change the name of the output file produced from its default of "data_MC_plot" in pdf (you may also specify other file type like xxx.ps)
  - --png: to make output as png rather than pdf (must specify output name)
  - --noOutput: if by any chance you don't want an output to file
  - --noRatioPlot: for when you have data and MC but don't want the ratio pad
  - --xAxisLabel X: change the x-axis label from its default of "M_T"
  - --noDivisionLabel: to remove the divisions label on the y-axis (ex: "Entries/30 GeV" becomes "Entries")
  - --yAxisLabel X: change the y-axis label from its default of "Entries"
  - --yAxisUnit X: change the y-axis unit from its default of ""
  - --yAxisOverride X: replace the entire y-axis label with X
  - --noXaxisUnit: do not display a unit for the x-axis
  - --xAxisUnit X: change the x-axis unit from its default of ""
  - --xAxisOverride X: override the entire x-axis label to the user-defined value
  - --xAxisBinLabels X: replace x-axis bin labels with comma-separated list of strings
  - --xAxisVerticalBinLabels: if using xAxisBinLabels, specify vertical orientation (default is diagonal)
  - --dataName X: replace the name for "data" in the legend with the user-defined value
  - --topYaxisTitle X: change the y-axis label in the top histogram from its default of "data/MC"
  - --type X: additional label to "CMS" on the top-left (i.e. Preliminary, Summplementary, Simulation, etc.)
  - --overrideHeader X: override the entire top line to the user-defined value
  - --energy X: change the energy from its default of 13 TeV
  - --lumi X: change the lumi from its default of 10.0 fb-1.
  - --noStack: to prevent backgrounds from being stacked (useful for comparisons)
  - --noType: suppress CMS Preliminary text
  - --doCounts: show event counts: "__ (Data), __ (MC)"
  - --outOfFrame: CMS Preliminary goes on top instead of in the frame
  - --lumiUnit: change the lumi unit from its default of "fb" (the 'inverse' part is automatic)
  - --noLumi: don't display lumi (for MC studies, for example)
  - --noFill: set all colors to white
  - --colorTitle: apply a color to the distribution title (blue)
  - --dataColor: to change the data color to something other than black
  - --ratioColor: to change the ratio color to something other than black
  - --blackSignals: make signals black
  - --normalize: to normalize all backgrounds
  - --isLinear: to use linear instead of log on y-axis
  - --preserveBackgroundOrder: to keep the backgrounds in the order you specified, rather than putting the smallest backgrounds on the bottom
  - --noOverflow: do not make the last bin an overflow bin (important if your last bin is already an overflow bin).  Also underflow.
  - --noBlackLines: don't put a black line between the various backgrounds
  - --totalBlackLine: put a black line only on the total background
  - --darkColorLines: make the black line a darker variant of the fill color
  - --vLine X: insert a vertical line where the x-axis = X; alternatively to only draw a part of the line, you can do --vLine xpos,ymin,ymax
  - --hLine X: insert a horizontal line where the y-axis = X; alternatively, can do --hLine ypos,xmin,xmax
  - --box xleft,ytop,xright,ybottom: draws a box between top left and bottom right coordinates
  - --setMaximum X: change the y-axis maximum from its default value (originally chosen such that the top of the top-most error bar appears at 3/4 of the histogram's height)
  - --setMaxMultiplier X: factor to multiply the script-set maximum value for the y-axis
  - --setMinimum X: change the y-axis minimum from its default value (originally chosen to be 90% of the smallest bin's height on the bottom background)
  - --noLegend: to suppress the legend
  - --percentageInBox: visual alternative to showPercentage which puts the percentage in the marker boxes of the legend
  - --legendUp X: move the legend up by X (number from 0 to 1; you probably want around 0.05), negative numbers to move it down
  - --legendRight X: move the legend to the right by X (number from 0 to 1; you probably want around 0.05), negative numbers to move it to the left
  - --legendTextSize X: change the legend text size from its default value of 0.035
  - --legendBox: put stupid box around legend
  - --legendCounts: show counts in brackets next to entries in the legend
  - --largeLabel: use larger legend and axis label size
  -- --legendTaller X: increase legend size by X (only when using legendBox)
  -- --legendWider X: increase legend size by X (only when using legendBox)
  - --divHalf: reduce the number of x-axis divisions by half
  - --nDivisions X: change the number of x-axis divisions to X, where X = number of primary divisions + 100*number of secondary divisions + 10000*number of tertiary divisions; positive to allow it to optimize (strongly recommended), negative to require it to use your values
  - --drawDots: to draw the backgrounds as dots rather than lines (recommended only for ratios like fake or flip rates) 
  - --showPercentage: to show the percentage of the integral of each MC plot contributing to the total background
  - --histoErrors: if you want your backgrounds to have error bars (usually only the data does)
  - --sigError: show statistical error on signal plots
  - --markerStyle2: alternate marker style for signals (alternates between filled and unfilled)
  - --bkgd_width N: set background thickness to an integer larger than 1 
  - --ratioOnly: don't show data on the plot, just use it for the ratio plot on top 
  - --errHistAtBottom: to make the Data/MC comparison histogram at the bottom
  - --ratio N: show the ratio plot with the denominator = the Nth background rather than the sum of backgrounds
  - --ratioNumerBG N: use the Nth background as the numerator in the ratio plot. If used with the --ratio N option, you can plot the ratio of two arbitrary backgrounds
  - --noErrBars: if by any chance you don't want the data points to have error bars (it may be annoying when error bars are too big) (effective at both main hist and err hist)
  - --compareMultiple: useful for when validating new MC.  Put the old plots under backgrounds and the new plots under signals and enable this option.  This will stack the signals and manipulate the colors so you can see the agreement for each background.  Also prints the ratio for the total.
  - --systFillStyle: change the fill style of the systematics, for example to 3005
  - --systBlack: change the color of the syst errors to black
  - --showZeroRatios: show the ratio plots as zero when the bin is empty.  
  - --noTextBetweenPads: bring ratio pad closer to main pad, no text in between them. All thex inside main pad. Used for SUS-15-008
  - --poissonErrorsNoZeros: avoid showing poissonian error bars for data entries with zero yield (used for SUS-15-008)
  - --makeTable: makes a table .txt file with the bin contents/totals/errors for data and backgrounds
  - --makeRootFile: makes a ROOT file with data and the backgrounds
  - --doPull: ratio plot is a pull plot, must feed in overrideSyst

Example:
````
  std::vector <TH1F*> myVector;
  myVector.push_back(CR1_ttsl);
  myVector.push_back(CR1_ttdl);
  std::vector <string> myTitles;
  myTitles.push_back("ttsl");
  myTitles.push_back("ttdl");
  dataMCplotMaker(CR1_data, myVector, myTitles, "#tilde{t} #rightarrow t#tilde{#chi} _ {1}^{0} ISR", "CR-0b", "--vLine 120 --outputName test _ plot");
````

Advanced Usage
  - If you run with more than 5 signals, it will automatically set your backgrounds to gray and striped.

E-mail Alex with bug reports or feature requests, george AT physics DOT ucsb

##Instructions for 2D plots

To call the function:
````
  PlotMaker2D(TH2F* plot, std::string options);
````
Mandatory argument:
  - A 2D histogram.  Can be TH2F* or TH2D*.

Options:
  - --outputName X: to specify the name of the output PDF. 
  - --noOverflow: if you don't want underflow/overflow to be put into first/last bin.
  - --setTitle X
  - --Xaxis X
  - --Yaxis X
  - --sciNot X: to put your bin contents into scientific notation.  X is a printf string (ie --sciNot .2 will give you two decimal places)
  - --colors: if you want each bin to be colored proportional to its value
  - --text: if you want each bin to have value and error written on it 
  - --text90: if you want each bin to have value and error written on it at a 90 degree angle
  - --isLogx: if you want logx
  - --isLogy: if you want logy
  - --isLogz: if you want logz

