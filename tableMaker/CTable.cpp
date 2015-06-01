#include "CTable.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <fstream>

// implementation of CTable
// -----------------------------------------------------------------------------------------------------//

CTable::CTable()
  : width_(0)
  , height_(0)
  , defaultWidth_(4)
  , rowLabelWidth_(3)
  , colLabelHeight_(1)
  , precision_(4)
  , delineator_(" | ")
  , lend_("| ")
  , rend_(" |")
  , corner_("+")
  , out_(&std::cout)
  , file_(NULL)
  , dispTitle_(false)
  , dispLines_(false)
  , useVertColLabels_(false)
{
}

CTable::~CTable(){
  if(file_!=NULL){
    file_->close();
    delete file_;
  }
}


CTableCellSetter CTable::setCells() 
{
    return CTableCellSetter(*this);
}


CTableColumnLabeler CTable::setTable() 
{
    return CTableColumnLabeler(*this);
}


void CTable::setCell(const std::string& entry, size_t r, size_t c){
  if(r>=table_.size()){
    std::vector<std::string> tempv;
    for(size_t i=table_.size(); i<=r; i++){
      table_.push_back(tempv);
    }
  }
  if(r>=rowLabels_.size()){
    for(size_t i=rowLabels_.size(); i<=r; i++){
      rowLabels_.push_back(" ");
    }
  }
  if(c>=table_[r].size()){
    for(size_t j=table_[r].size(); j<=c; j++){
      std::string temps;
      table_[r].push_back(temps);
    }
  }
  if(c>=colLabels_.size()){
    for(size_t i=colLabels_.size(); i<=c; i++){
      colLabels_.push_back(" ");
    }
  }
  if(c>=colWidth_.size()){
    for(size_t k=colWidth_.size(); k<=c; k++){
      colWidth_.push_back(defaultWidth_);
    }
  }

  if(colWidth_[c]<entry.length()){
    colWidth_[c]=entry.length();
  }
  if((c+1)>width_){width_=c+1;}
  if((r+1)>height_){height_=r+1;}
  table_[r][c]=entry;
}

void CTable::setCell(const char* entryc, size_t r, size_t c){
  std::string entry=entryc;
  setCell(entry,r,c);
}

void CTable::setCell(int entryi, size_t r, size_t c){
  std::stringstream ss;
  ss<<entryi;
  std::string entry;
  ss>>entry;
  setCell(entry,r,c);
}

void CTable::setCell(float entryf, size_t r, size_t c){
  std::stringstream ss;
  ss<<std::fixed<<std::setprecision(precision_)<<entryf;
  std::string entry;
  ss>>entry;
  setCell(entry,r,c);
}

void CTable::setCell(const TString& entryTS, size_t r, size_t c){
  setCell(std::string(entryTS.Data()),r,c);
}

void CTable::printHLine(int row){
  if (row != 0) hlines_.push_back(row);  
}

void CTable::printCLine(int row, int start, int end){
  clines_row_.push_back(row);  
  clines_start_.push_back(start);  
  clines_end_.push_back(end);  
}

void CTable::setCell(double entryd, size_t r, size_t c){
  std::stringstream ss;
  ss<<std::fixed<<std::setprecision(precision_)<<entryd;
  std::string entry;
  ss>>entry;
  setCell(entry,r,c);
}

void CTable::setCell(const CNumBase<float>& entryn, size_t r, size_t c){
  std::stringstream numss,statss,systss;
  std::string nums,stats,systs,entrys;
  numss<<std::fixed<<std::setprecision(precision_)<<entryn.data();
  numss>>nums;
  statss<<std::fixed<<std::setprecision(precision_)<<entryn.stat();
  statss>>stats;
  entrys=nums+"$\\pm$"+stats;
  if(entryn.syst()!=0){
	systss<<std::fixed<<std::setprecision(precision_)<<entryn.syst();
	systss>>systs;
	entrys+="$\\pm$"+systs;
  }
  setCell(entrys,r,c);
}

void CTable::setCell(const CNumBase<double>& entryn, size_t r, size_t c){
  std::stringstream numss,statss,systss;
  std::string nums,stats,systs,entrys;
  numss<<std::fixed<<std::setprecision(precision_)<<entryn.data();
  numss>>nums;
  statss<<std::fixed<<std::setprecision(precision_)<<entryn.stat();
  statss>>stats;
  entrys=nums+"$\\pm$"+stats;
  if(entryn.syst()!=0){
	systss<<std::fixed<<std::setprecision(precision_)<<entryn.syst();
	systss>>systs;
	entrys+="$\\pm$"+systs;
  }
  setCell(entrys,r,c);
}


void CTable::setTitle(const char* title){title_=title;}
void CTable::setTitle(const std::string& title){title_=title;}
void CTable::setTitle(const TString& title){title_=title;}
void CTable::setPrecision(size_t precision){precision_=precision;}

void CTable::printTitle() const {
  size_t line=calcLine();
  if((title_.length()+4)>line){line=title_.length()+4;}
  (*out_)<<corner_;
  printLine('-',line-2,false);
  (*out_)<<corner_<<std::endl;
  (*out_)<<lend_<<std::left<<std::setw(line-4)<<title_<<std::right<<rend_<<std::endl;
  (*out_)<<corner_;
  printLine('-',line-2,false);
  (*out_)<<corner_<<std::endl<<std::endl;
}

size_t CTable::calcLine() const {
  size_t line=0;
  line+=rowLabelWidth_;
  line+=3;
  for(size_t k=0; k<colWidth_.size(); k++){
    if(colLabels_[k].length()>colWidth_[k]){colWidth_[k]=colLabels_[k].length();}
	line+=colWidth_[k];
    line+=3;
  }
  return line;
}

void CTable::printLine(char symbol, size_t length, bool endline) const {
  for(size_t i=0; i<length; i++){
    (*out_)<<symbol;
  }
  if(endline){(*out_)<<std::endl;}
}

std::string CTable::delineator(int i, int j) const {
  for (unsigned int r = 0; r < multicolumn_row.size(); r++){
    int row = multicolumn_row[r]; 
    if (row != i) continue;
    int start = multicolumn_start[r];
    if (start > j) continue; 
    int finish = multicolumn_finish[r]; 
    if (finish <= j) continue; 
    return "   "; 
  }
  return delineator_;
}

int CTable::isMultiColumn(int i, int j) const {
  for (unsigned int r = 0; r < multicolumn_row.size(); r++){
    int row = multicolumn_row[r]; 
    if (row != i) continue;
    int start = multicolumn_start[r];
    if (start > j) continue; 
    int finish = multicolumn_finish[r]; 
    if (finish < j) continue; 
    if (start == j) return finish-start; 
    else return -1; 
  }
  return 0;

}

void CTable::multiColumn(int row, int start, int finish){
  multicolumn_row.push_back(row);
  multicolumn_start.push_back(start);
  multicolumn_finish.push_back(finish);
}

void CTable::print() const {
  if(dispTitle_){printTitle();}
  if(height_>0 || width_>0){

	printColLabels();
	size_t line=calcLine();
    for(size_t i=0; i<height_; i++){
      for (unsigned int j = 0; j < hlines_.size(); j++){
        if (hlines_[j] == i) printLine('-', line);  
      }
      if(dispLines_){printLine('-',line);}
      (*out_)<<" "<<std::setw(rowLabelWidth_)<<std::left<<rowLabels_[i]<<std::right;
      (*out_)<<delineator_;
      for(size_t j=0; j<width_; j++){
	if(table_[i].size()>j){
	  if (isMultiColumn(i,j) >= 0) (*out_)<<std::setw(colWidth_[j])<<std::left<<table_[i][j]<<delineator(i,j);
	  else (*out_)<<std::setw(colWidth_[j])<<std::left<<" "<<delineator(i,j);
	}else{
	  (*out_)<<std::setw(colWidth_[j])<<" "<<delineator_;
	}
      }
      (*out_)<<std::endl;
    }
    if(dispLines_){printLine('-',line);}
  }else{
    (*out_)<<"->  Table Empty  <-"<<std::endl;
    
  }
}

void CTable::printColLabels() const {
  if(useVertColLabels_){
	for(size_t i=0; i<colLabels_.size(); i++){
	  if(colLabels_[i].length()>colLabelHeight_){colLabelHeight_=colLabels_[i].length();}
	}
	for(size_t j=0; j<colLabelHeight_; j++){
	  for(size_t k=0; k<rowLabelWidth_+1; k++){
		(*out_)<<" ";
	  }
	  for(size_t l=0; l<colLabels_.size(); l++){
		if(j==colLabelHeight_-1){(*out_)<<delineator_;}
		else{                    (*out_)<<"   ";}
		if((colLabelHeight_-j)>colLabels_[l].length()){(*out_)<<std::setw(colWidth_[l])<<" ";}
		else{(*out_)<<std::setw(colWidth_[l])<<colLabels_[l][j+colLabels_[l].length()-colLabelHeight_];}
	  }
	  if(j==colLabelHeight_-1){(*out_)<<delineator_<<std::endl;;}
	  else{                   (*out_)<<"   "<<std::endl;;}
	}
  }
  else{
	for(size_t k=0; k<rowLabelWidth_+1; k++){
	  (*out_)<<" ";
	}
	for(size_t i=0; i<colLabels_.size(); i++){
	  if (colLabels_[i].length()>colWidth_[i]) colWidth_[i]=colLabels_[i].length();
	  (*out_)<<delineator(-1,i-1)<<std::setw(colWidth_[i])<<colLabels_[i];
	}
		(*out_)<<delineator_ <<std::endl;
  }
}

void CTable::useLines(bool line){dispLines_=line;}
void CTable::useTitle(bool title){dispTitle_=title;}
void CTable::useVertColLabels(bool vert){useVertColLabels_=vert;}

void CTable::setColLabel(const std::string& label, size_t c){
  if(c>=colLabels_.size()){
    for(size_t i=colLabels_.size(); i<=c; i++){
      colLabels_.push_back(" ");
      colWidth_.push_back(defaultWidth_);
    }
  }
  colLabels_[c]=label;
  if((c+1)>width_){width_=c+1;}
}
void CTable::setColLabel(const char* labelc, size_t c){
  std::string label=labelc;
  setColLabel(label,c);
}

void CTable::setColLabel(const TString& labelTS, size_t c){
  std::string label;
  label=labelTS;
  setColLabel(label,c);
}

void CTable::setRowLabel(const std::string& label, size_t r){
  if(r>=rowLabels_.size()){
    for(size_t i=rowLabels_.size(); i<=r; i++){
      rowLabels_.push_back(" ");
    }
  }
  if(label.length()>rowLabelWidth_){rowLabelWidth_=label.length();}
  if(r>=table_.size()){
    std::vector<std::string> tempv;
    for(size_t i=table_.size(); i<=r; i++){
      table_.push_back(tempv);
    }
  }
  rowLabels_[r]=label;
  if((r+1)>height_){height_=r+1;}
}

void CTable::setRowLabel(const char* labelc, size_t r){
  std::string label=labelc;
  setRowLabel(label,r);
}

void CTable::setRowLabel(const TString& labelTS, size_t r){
  std::string label;
  label=labelTS;
  setRowLabel(label,r);
}


void CTable::saveAs(const std::string& filename, bool overwrite){
  if(filename.length()>0){
    if(file_==NULL){file_=new ofstream;}
    if(file_->good()){file_->close();}
    if(overwrite){file_->open(filename.c_str());}
    else{file_->open(filename.c_str(),ofstream::out | ofstream::app);}
    if(!file_->fail()){out_=file_;}
    else{
      std::cout<<"Failed to open file "<<filename<<", defaulting to terminal."<<std::endl;
      out_=&std::cout;
    }
  }else{out_=&std::cout;}
}

void CTable::setColLine(int i){
  colLines_.push_back(i); 
}

bool CTable::isColLine(int i){
  bool result = false;
  for (unsigned int j = 0; j < colLines_.size(); j++) if (i == colLines_[j]) result = true;
  return result;
}

void CTable::saveTex(const std::string& filename, bool standalone, bool withtitle){
  if(filename.length()>0){
    if(file_==NULL){file_=new ofstream;}
    if(file_->good()){file_->close();}
    file_->open(filename.c_str());
    if(!file_->fail()){out_=file_;}
    else{
      std::cout<<"Failed to open file "<<filename<<", defaulting to terminal."<<std::endl;
      out_=&std::cout;
    }
  }else{out_=&std::cout;}
  std::string cols= isColLine(0) ? "|c|" :  "c|";
  for(size_t i=0;i<colLabels_.size();i++){(isColLine(i) && i != 0) ? cols+="c|" : cols+="c";}
  if (standalone) (*out_)<<"\\documentclass{article}"<<std::endl
                         << "\\usepackage{fullpage}"<<std::endl
                         << "\\usepackage{multicolumn}"<<std::endl
                         <<"\\begin{document}"<<std::endl
                        <<"\\begin{table}[ht!]"<<std::endl;
  if (!standalone) (*out_)<<"\\begin{table}"<<std::endl;
  if (standalone) (*out_)<<"\\begin{center}"<<std::endl;
    (*out_) <<"\\begin{tabular}{"<<cols<<"}";
  if (withtitle) (*out_) << "\\multicolumn{" << colLabels_.size()+1 << "}{c}{" << title_ << "} \\\\ ";  
    (*out_) << "\\hline"<<std::endl 
         <<" ";
  for(size_t i=0;i<colLabels_.size();i++){
	if (isMultiColumn(-1, i) > 0 ) (*out_) << Form("& \\multicolumn{%i}{%sc%s}{%s}", isMultiColumn(-1,i)+1, isColLine(i)  ? "|" : "", (isColLine(i+(isMultiColumn(-1,i)))) ? "|" : "", colLabels_[i].c_str()); 
    if (isMultiColumn(-1, i) == 0) (*out_)<<"&"<<colLabels_[i];
  }
  if (rowLabels_[0] != "") (*out_)<<"\\\\"<<std::endl<<"\\hline"<<std::endl;
  if (rowLabels_[0] == "") (*out_)<<"\\\\"<<std::endl<<"\\cline{2-" << width_+1 << "}" <<std::endl;
  if(height_>0 || width_>0){
    for(size_t i=0; i<height_; i++){
      for (unsigned int j = 0; j < hlines_.size(); j++){
        if (hlines_[j] == i) (*out_)<<"\\hline"<<std::endl;
      }
      for (unsigned int j = 0; j < clines_row_.size(); j++){
        if (clines_row_[i] == i) (*out_) << "\\cline{" << clines_start_[i] << "," << clines_end_[i] << "}" << std::endl;
      }
      (*out_)<<rowLabels_[i];
      for(size_t j=0; j<width_; j++){
		if(table_[i].size()>j){
	      if (isMultiColumn(i,j) > 0 ) (*out_) << Form("& \\multicolumn{%i}{l}{%s}", isMultiColumn(i,j)+1, table_[i][j].c_str()); 
		  if (isMultiColumn(i,j) == 0) (*out_) << " & " << table_[i][j];
		}else{
		  (*out_)<<" &  ";
		}
      }
      (*out_)<<"\\\\"<<std::endl;
    }
  }else{
    (*out_)<<" & ->  Table Empty  <-"<<std::endl;
  }  
  (*out_)<<"\\hline"<<std::endl<<"\\end{tabular}"<<std::endl;
  if (standalone) (*out_) <<"\\end{center}"<<std::endl;
  (*out_) <<"\\end{table}"<<std::endl;
  if (standalone) (*out_) <<"\\end{document}"<<std::endl;
}

void CTable::printTex() const {
  using namespace std;
  std::string cols="c|";
  for(size_t i=0;i<colLabels_.size();i++){cols+="c";}
//  cout   <<"\\documentclass{article}"<<std::endl
//         <<"\\begin{document}"<<std::endl
//	     <<"\\begin{table}[ht!]"<<std::endl
  cout   <<"\\begin{table}"<<std::endl
	     <<"\\begin{center}"<<std::endl
         <<"\\begin{tabular}{"<<cols<<"}\\hline"<<std::endl
         <<" ";
  for(size_t i=0;i<colLabels_.size();i++){
	cout   <<"&"<<colLabels_[i];
  }
  if (colLabels_[0] != "") cout   <<"\\\\"<<std::endl<<"\\hline \\hline"<<std::endl;
  else cout   <<"\\\\"<<std::endl<<"\\cline{1-" << width_+1 << "}" <<std::endl;
  if(height_>0 || width_>0){
    for(size_t i=0; i<height_; i++){
      cout   <<rowLabels_[i];
      for(size_t j=0; j<width_; j++){
		if(table_[i].size()>j){
		  cout   <<" & "<<table_[i][j];
		}else{
		  cout   <<" &  ";
		}
      }
      cout   <<"\\\\"<<std::endl;
    }
  }else{
    cout   <<" & ->  Table Empty  <-"<<std::endl;
  }  
  cout   <<"\\hline"<<std::endl<<"\\end{tabular}"<<std::endl
         <<"\\end{center}"<<std::endl<<"\\end{table}"<<std::endl;
         //<<"\\end{document}"<<std::endl;
}
