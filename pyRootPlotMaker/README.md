# pyRootPlotMaker

General-purpose plot maker, for use with pyROOT.  To use, clone the Software repository and do the following:

1. `export PYTHONPATH=$PYTHONPATH:/path/to/Software/pyRootPlotMaker`. Probably should put it in your .bashrc.
2. include the lines `import ROOT` and `import pyRootPlotMaker as ppm` or similar at the top of your python script.
3. To avoid annoying ROOT windows from popping up, put the following in your main script: `ROOT.gROOT.SetBatch(1)`.

Below is a more detailed list of instructions and options, or just look at `example.py` for a working example.

### Data/MC  (or just MC) plots
Use `ppm.plotDataMC` to make a stacked histogram of MC backgrounds and overlay with data. If you want to just plot the backgrounds, simply use the argument `h_data=None`. Don't use `ppm.plotBackgrounds`, that is for internal use only. 

Arugments are as follows:

REQUIRED arguments (don't need to use keywords, just pass them as the first 2 arguments in order).

1. A python list of ROOT.TH1 objects (one for each background)
2. A python list of strings for the names of the backgrounds. These go in the legend.

OPTIONAL arguments (required to use argument keywords. e.g., pass the argument `title="My Histogram"`). If you don't specify the default value will be used.

1. `h_data` - ROOT.TH1 histogram of data. Pass `None` to not plot data.
2. `title` - main title string. This is placed inside the plot canvas, upper left corner.
3. `subtitles` - list of subtitle strings. Placed one per line below the title.
4. `doRatio` - boolean of whether or not to plot ratio below the main canvas`
5. `scaleMCtoData` - scale MC by a constant so that the total integral matches that of data.
6. `saveAs` - filename to save the plot as. File type is inferred from the extension.
7. `isLog` - boolean, whether or not to use logarithmic y-axis
8. `dataTitle` - title to use for data in the legend. Defaults to "Data"
9. `xRangeUser` - custom x-axis range. Pass a 2-tuple of floats. One of the entries can be None to leave as the default.
10. `doPause` - mainly for debugging, pauses after plotting so the window doesn't immediately disappear. Don't use batch mode if you want to see anything.
11. `lumi` - floating point number of the lumi value you want.
12. `lumiUnit` - string of unit (e.g. "pb", "fb", "ab" (maybe one day...))
13. `noLumi` - set to True if you don't want to plot lumi at all.
14. `energy` - numerical value of sqrt(s), in TeV
15. `xAxisTitle` - title to put below x-axis. Can use ROOT's version of latex, e.g. "#Delta#phi_{min}"
16. `xAxisUnit` - unit of x-axis variable. Use None for dimensionless quantities.
17. `userMax` - Maximum of y-axis. Defaults to putting the maximum of data or MC at roughly 3/4 of the way up the canvas.
18. `userMin` - see above, but for minimum.
19. `doSort` - Sort backgrounds so the larger contributions (by integral) are on top.
20. `doMT2Colors` - use MT2 color scheme.
21. `markerSize` - size of data and ratio markers.
22. `doOverflow` - Add the overflow bin to the last bin. Note that this automatically handles situations where the x-range maximum is changed via `xRangeUser` (sums all of the bins to the right of xmax).
23. `titleSize` - size of title text.
24. `subtitleSize` - size of subtitle text.
25. `subLegText` - like `subtitles`, a list of strings. These are placed one per line immediately below the legend. Useful for displaying data/MC scale factor or other relevant information. Note that you can use the following special substrings to get certain info:
  * "{datamcsf}" - the Data/MC scale factor, if `scaleMCtoData==True`
  * "{datamcsferr}" - statistical error on this scale factor, computed using ROOT's `IntegralAndError` method.
  * "{ndata}" - total number of data events.
26. `cmsText` - Text in upper-left of canvas, above plot. Defaults to "CMS Preliminary"
27. `cmsTextSize` - size of the above
28. `doBkgError` - show shaded error boxes over the stacked background histogram.
29. `functions` - list of ROOT.TF1 objects to draw on top of plot.
30. `legCoords` - 4-tuple of legend coordinates, as passed to the ROOT.TLegend constructor.
31. `convertToPoisson` - set to true to automatically convert data histogram to proper asymmetric poisson errors (see [here](https://twiki.cern.ch/twiki/bin/view/CMS/PoissonErrorBars))
32. `drawZeros` - if `convertToPoisson` is set to True, this determines whether do draw markers at bins with 0 contents (note that the Poisson error according to the formula at the above link in this case is 1.8)
33. `drawSystematicBand` - draw a band in the ratio plot to show systematic errors.
34. `systematics` - if the above option is set to True, this is a list of relative systematic errors (i.e., 0.4 for a 40% uncertainty). Must be the same length as the number of bins.
35. `h_sig_vec` - list of signal histograms to overlay on top of data/MC.
36. `sig_names` - list of names for the signals to put in legend.
37. `customColors` - list of root colors to use for backgrounds. Must be at least the size of background list.
38. `verticalLines` - list of x-values to draw vertcal lines at. Useful for showing cuts.

### Comparison plots
Use `ppm.plotComparison` to plot a comparison between 2 histograms. This needs more work.

### Efficiency plots
Use `ppm.plotEfficiency` to make pretty trigger efficiency plots. Should be moslty self-explanatory, should document later

###TODO

1. Custom color schemes
2. More customizability for positioning, size, etc of text/legend
3. Ability for multiple data histograms, e.g. for comparing 2 different years.
4. Option to draw signal histograms on top of MC
5. More than 2 histograms in `plotComparison`
