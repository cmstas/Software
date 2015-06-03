#if !defined(__CINT__) || defined(__MAKECINT__)
#include <iostream>
#include "CTable.h"
#include "CNumBase.h"
#endif

using namespace std;

void test_ctable_creator(){
  cout << "CTable::setCells() - to fill all the cells in a table (supports up to 10 columns right now)\n" << endl;
  CTable t1;
  t1.setCells() ( "v11", "v12", "v13")
                ( "v21", "v22", "v23")
                ( "v31", "v32", "v33");
  t1.print(); std::cout << std::endl;

  cout << "\nCTable::setTable() - to fill all the columns, rows, and cells in a table (supports up to 10 columns right now)\n" << endl;
  CTable t2;
  t2.setTable() (          "col 1", "col 2", "col 3")
                ( "row 1",   "v11",   "v12",   "v13")
                ( "row 2",   "v21",   "v22",   "v23")
                ( "row 3",   "v31",   "v32",   "v33");
  t2.print(); std::cout << std::endl;

  cout << "\nCTable::setCells() - large table (any number of rows; supports up to 10 columns right now)\n" << endl;
  CTable t3;
  t3.setCells() (  "v00",   "v01",   "v02",   "v03",   "v04",   "v05",   "v06",   "v07",   "v08",   "v09")
                (  "v10",   "v11",   "v12",   "v13",   "v14",   "v15",   "v16",   "v17",   "v18",   "v19")
                (  "v20",   "v21",   "v22",   "v23",   "v24",   "v25",   "v26",   "v27",   "v28",   "v29")
                (  "v40",   "v41",   "v42",   "v43",   "v44",   "v45",   "v46",   "v47",   "v48",   "v49")
                (  "v50",   "v51",   "v52",   "v53",   "v54",   "v55",   "v56",   "v57",   "v58",   "v59")
                (  "v60",   "v61",   "v62",   "v63",   "v64",   "v65",   "v66",   "v67",   "v68",   "v69")
                (  "v70",   "v71",   "v72",   "v73",   "v74",   "v75",   "v76",   "v77",   "v78",   "v79")
                (  "v80",   "v81",   "v82",   "v83",   "v84",   "v85",   "v86",   "v87",   "v88",   "v89")
                (  "v90",   "v91",   "v92",   "v93",   "v94",   "v95",   "v96",   "v97",   "v98",   "v99")
                ( "v100",  "v101",  "v102",  "v103",  "v104",  "v105",  "v106",  "v107",  "v108",  "v109")
                ( "v110",  "v111",  "v112",  "v113",  "v114",  "v115",  "v116",  "v117",  "v118",  "v119")
                ( "v120",  "v121",  "v122",  "v123",  "v124",  "v125",  "v126",  "v127",  "v128",  "v129")
                ( "v130",  "v131",  "v132",  "v133",  "v134",  "v135",  "v136",  "v137",  "v138",  "v139")
                ( "v140",  "v141",  "v142",  "v143",  "v144",  "v145",  "v146",  "v147",  "v148",  "v149")
                ( "v150",  "v151",  "v152",  "v153",  "v154",  "v155",  "v156",  "v157",  "v158",  "v159");
  t3.print(); std::cout << std::endl;
  
  cout << "\nCTable::setTable() - large table with columns and row labels (any number of rows; supports up to 10 columns right now)\n" << endl;
  CTable t4;
  t4.setTable() (           "col 0", "col 1", "col 2", "col 3", "col 4", "col 5", "col 6", "col 7", "col 8", "col 9")
                ( "row 0" ,   "v00",   "v01",   "v02",   "v03",   "v04",   "v05",   "v06",   "v07",   "v08",   "v09")
                ( "row 1" ,   "v10",   "v11",   "v12",   "v13",   "v14",   "v15",   "v16",   "v17",   "v18",   "v19")
                ( "row 2" ,   "v20",   "v21",   "v22",   "v23",   "v24",   "v25",   "v26",   "v27",   "v28",   "v29")
                ( "row 4" ,   "v40",   "v41",   "v42",   "v43",   "v44",   "v45",   "v46",   "v47",   "v48",   "v49")
                ( "row 5" ,   "v50",   "v51",   "v52",   "v53",   "v54",   "v55",   "v56",   "v57",   "v58",   "v59")
                ( "row 6" ,   "v60",   "v61",   "v62",   "v63",   "v64",   "v65",   "v66",   "v67",   "v68",   "v69")
                ( "row 7" ,   "v70",   "v71",   "v72",   "v73",   "v74",   "v75",   "v76",   "v77",   "v78",   "v79")
                ( "row 8" ,   "v80",   "v81",   "v82",   "v83",   "v84",   "v85",   "v86",   "v87",   "v88",   "v89")
                ( "row 9" ,   "v90",   "v91",   "v92",   "v93",   "v94",   "v95",   "v96",   "v97",   "v98",   "v99")
                ( "row 10",  "v100",  "v101",  "v102",  "v103",  "v104",  "v105",  "v106",  "v107",  "v108",  "v109")
                ( "row 11",  "v110",  "v111",  "v112",  "v113",  "v114",  "v115",  "v116",  "v117",  "v118",  "v119")
                ( "row 12",  "v120",  "v121",  "v122",  "v123",  "v124",  "v125",  "v126",  "v127",  "v128",  "v129")
                ( "row 13",  "v130",  "v131",  "v132",  "v133",  "v134",  "v135",  "v136",  "v137",  "v138",  "v139")
                ( "row 14",  "v140",  "v141",  "v142",  "v143",  "v144",  "v145",  "v146",  "v147",  "v148",  "v149")
                ( "row 15",  "v150",  "v151",  "v152",  "v153",  "v154",  "v155",  "v156",  "v157",  "v158",  "v159");
  t4.print(); std::cout << std::endl;

  cout << "\nCTable::setTable() - mixed types of cells (any number of rows; supports up to 10 columns right now)\n" << endl;
  CTable t5;
  t5.setTitle("test with heterogenous types");
  t5.useTitle();
  t5.setTable() (          "decimal", "int", "string literal",       "TSring",        "std::string",              "CNumBase<float>" )
                ( "row 0" ,      0.1,     0,             "v0", TString( "v04"), std::string( "v05"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 1" ,      1.1,     1,             "v1", TString( "v14"), std::string( "v15"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 2" ,      2.1,     2,             "v2", TString( "v24"), std::string( "v25"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 4" ,      4.1,     4,             "v4", TString( "v44"), std::string( "v45"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 5" ,      5.1,     5,             "v5", TString( "v54"), std::string( "v55"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 6" ,      6.1,     6,             "v6", TString( "v64"), std::string( "v65"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 7" ,      7.1,     7,             "v7", TString( "v74"), std::string( "v75"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 8" ,      8.1,     8,             "v8", TString( "v84"), std::string( "v85"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 9" ,      9.1,     9,             "v9", TString( "v94"), std::string( "v95"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 10",     10.1,    10,            "v10", TString("v104"), std::string("v105"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 11",     11.1,    11,            "v11", TString("v114"), std::string("v115"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 12",     12.1,    12,            "v12", TString("v124"), std::string("v125"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 13",     13.1,    13,            "v13", TString("v134"), std::string("v135"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 14",     14.1,    14,            "v14", TString("v144"), std::string("v145"), CNumBase<float>(1.0, 2.0, 3.0) )
                ( "row 15",     15.1,    15,            "v15", TString("v154"), std::string("v155"), CNumBase<float>(1.0, 2.0, 3.0) );
  t5.print(); std::cout << std::endl;

  return;
}

int test_usage(){
  CTable table;

  //Place horizontal lines between rows, recommended, use false to remove them
  table.useLines(); 

  //Print a title above the table, use false to remove it
  table.useTitle(); 

  //Print the column labels vertically to save space if labels long or a lot of columns
  table.useVertColLabels(); 

  //sets the precision of the floating point entries, default is 4
  table.setPrecision(2); 

  //Set the table title
  table.setTitle("Table Title");

  //Use setCell(entry, row #, column #) to add elements.  Indexing starts at (0, 0)
  //If a cell exists it is overwritten, and if it does not, the table is resized
  table.setCell("a", 0, 0);
  table.setCell("abcdefghi", 1, 1);
  table.setCell(3, 0, 1);
  table.setCell(60.32123, 0, 3);

  //Use setRowLabel(label, row #) and setColLabel to set the labels for row and column respectively. Indexing starts at 0
  //If a row or column exists, its label is overwritten; if it does not, the table is resized
  table.setRowLabel("row 1", 0);
  table.setRowLabel("row 2", 5);
  table.setColLabel("column 1", 1);
  table.setColLabel("really long label", 4);

  //Prints the full table.  Column labels are printed vertically.  Use argument to specify a file to print to.
  table.print(); 
  //table.saveTex("$HOME/temp/example.tex");

  cout << endl;

  return 0;
}

void test(){

  //Simple usage test
  test_usage();

  //Test table creator and setter
  test_ctable_creator();
}

#ifndef __CINT__
int main(){
  test();
}
#endif
