#TableMaker
An SNT Class to make well-formatted simple tables.

###INSTALL:
Run make to create libSimpleTable.so

###Test:
root do.C will run a working example.  

###USAGE:
  - In your do.C file, add something like gSystem->Load("libSimpleTable.so");
  - In your working file, include CTable.h to use tables
  - In your working file, include CNumBase.h to use CNumBase

###Basic Operations
This contains two main advantages -- CNumBase and Tables.  

CNumBase:
  - CNumBase<float>(1.0, 2.0, 3.0) to define 1.0 \pm 2.0 \pm 3.0
  - Or one at a time with CNumBase blah; blah.setData(1.0), blah.setSyst(2.0), blah.setStat(3.0)
  - blah.gaussian() will set stat error = sqrt(data)
  - Now you can access these: blah.data(), etc.
  - And you can add, divide, etc., and it will handle all the errors properly.  

Tables:
  - Set a simple table with the following syntax:
```
        CNumBase Vud;
        Vud.setData(0.97427);
        CTable table;
        table.setTable() (         "col 1", "col 2",  "col 3")
                         ( "row1", Vud.data(), 0.22534,  0.00351)
                         ( "row2", 0.22520, 0.97344,   0.0412)
                         ( "row3", 0.00867,  0.0404, "0.999146");
```
  - You can use t1.SetPrecision(N) to get N units of precision.  This does NOT work if you type in the values, but works otherwise.
  - Add title with: table.setTitle("Table Title"), table.useTitle();
  - Remove horiz. lines between rows: table.useLines(0);
  - Print column labels vertically: table.useVertColLabels();
  - Print \hline: table.printHLine(row); 
  - Print \cline{a-b}: table.printCLine(row, a, b); 
  - Multicolumn: table.multiColumn(row, column start, column finish); 
  - Vertical lines: table.setColLine(col); 

###Cool Features
  - table.print() will print a nicely-formatted table
  - table.saveTex("output.tex") will create output.tex with the table.

Send bugs, feature requests, etc., to no one.  This was originally written by Ian MacNeill and revived by Alex George, but I don't think anyone is willing to assume ownership at this point.  Accepting volunteers! Until then, use at your own peril.  
