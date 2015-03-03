+Examples of dataMCplotMaker

SRs.pdf: signal and background yields in various signal regions. Note that if you give five signals or more, it automatically sets your backgrounds to gray with patter.





[1] dataMCplotMaker(null, backgrounds2, titles2, "SS H-H ptrel", Form("%i/%i, %i/%i, %i/%i%s", ht_low_c, ht_high_c, met_low_c, met_high_c, njets_low_c, njets_high_c, manual_cut_string) , "--outputName SRs.pdf --xAxisLabel SR --energy 13 --lumi 10 --legendTextSize 0.025 --legendRight -0.13 --legendUp 0.05 --noDivisionLabel  --noXaxisUnit --setMinimum 0.1 --setMaximum 10000 --hLine 1.0", signal_vector, signal_title, colors); 
