// implementation of templated functions for CNumBase

// CONSTRUCTORS //
template <class numtype> 
CNumBase<numtype>::CNumBase(numtype datan, numtype statn, numtype systn)
  : data_(datan)
  , stat_(statn)
  , syst_(systn)
{
  //  std::cout<<"Works "<<syst_<<std::endl;
}
template <class numtype> 
CNumBase<numtype>::CNumBase(const CNumBase<numtype>& obj)
  : data_(obj.data_)
  , stat_(obj.stat_)
  , syst_(obj.syst_)
{
  //  std::cout<<"Works "<<syst_<<std::endl;
}
// DATA ACCESS FUNCTIONS //
template <class numtype> 
numtype CNumBase<numtype>::data()  const {return data_;}
template <class numtype> 
numtype CNumBase<numtype>::stat()  const {return stat_;}
template <class numtype> 
numtype CNumBase<numtype>::syst()  const {return syst_;}
template <class numtype> 
//numtype CNumBase<numtype>::error() const {return syst_+stat_;} //is this the correct way to return the total error?
numtype CNumBase<numtype>::error() const {return static_cast<numtype>(sqrt(syst_*syst_+stat_*stat_));} // I think you want to add the error in quadrature
template <class numtype> 
void CNumBase<numtype>::print(bool statn, bool systn) const {
  std::cout<<data_;
  if(statn){std::cout<<" +/- "<<stat_<<" st";}
  if(systn){std::cout<<" +/- "<<syst_<<" sy";}
  std::cout<<std::endl;
}

// DATA SETTING FUNCTIONS //
template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::setData(numtype datan){
  data_=datan;
  return *this;
}
template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::setStat(numtype statn){
  stat_=statn;
  return *this;
}
template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::setSyst(numtype systn){
  syst_=systn;
  return *this;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::gaussian(){
  stat_=static_cast<numtype>(sqrt(abs(data_)));
  return *this;
}

// OVERLOADED OPERATORS //
template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator*(numtype scale) const {
  CNumBase<numtype> temp(data_*scale,stat_*scale,syst_*scale);
  return temp;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator*(const CNumBase<numtype>& mul) const {
  	numtype datan=data_*mul.data();
	numtype statn=datan*static_cast<numtype>(sqrt((stat_*stat_)/(data_*data_)+(mul.stat_*mul.stat_)/(mul.data_*mul.data_)));
	numtype systn=datan*static_cast<numtype>(sqrt((syst_*syst_)/(data_*data_)+(mul.syst_*mul.syst_)/(mul.data_*mul.data_)));  
	CNumBase<numtype> temp(datan,statn,systn);
	return temp;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator/(numtype scale) const {
  CNumBase<numtype> temp(data_/scale,stat_/scale,syst_/scale);
  return temp;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator/(const CNumBase<numtype>& div) const {
  	numtype datan=data_/div.data();
	numtype statn=datan*static_cast<numtype>(sqrt((stat_*stat_)/(data_*data_)+(div.stat_*div.stat_)/(div.data_*div.data_)));
	numtype systn=datan*static_cast<numtype>(sqrt((syst_*syst_)/(data_*data_)+(div.syst_*div.syst_)/(div.data_*div.data_)));  
	CNumBase<numtype> temp(datan,statn,systn);
	return temp;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator+(const CNumBase<numtype>& add) const {
  CNumBase<numtype> temp(data_+add.data(),
								static_cast<numtype>(sqrt(stat_*stat_+add.stat()*add.stat())),
								static_cast<numtype>(sqrt(syst_*syst_+add.syst()*add.syst())));
  //  cout<<temp.syst()<<" "<<syst_<<" "<<add.syst()<<endl;
  return temp;
}

template <class numtype> 
CNumBase<numtype> CNumBase<numtype>::operator-(const CNumBase<numtype>& sub) const {
  CNumBase<numtype> temp(data_-sub.data(),
								static_cast<numtype>(sqrt(stat_*stat_+sub.stat()*sub.stat())),
								static_cast<numtype>(sqrt(syst_*syst_+sub.syst()*sub.syst())));
  return temp;
}

template <class numtype> 
CNumBase<numtype>& CNumBase<numtype>::operator=(const CNumBase<numtype>& equal) {
  data_=equal.data();
  stat_=equal.stat();
  syst_=equal.syst();
  return *this;
}
