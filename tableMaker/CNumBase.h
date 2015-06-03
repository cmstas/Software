#ifndef CNumBase_h
#define CNumBase_h
#include <iostream>
#include <cmath>
  
template <class numtype=float> 
class CNumBase {
  public:
    CNumBase(numtype datan=0.0, numtype statn=0.0, numtype systn=0.0);
    CNumBase(const CNumBase<numtype>& obj);
    numtype data()  const;
    numtype stat()  const;
    numtype syst()  const;
    numtype error() const;
    void print(bool statn=true, bool systn=true) const;
    CNumBase<numtype> setData(numtype datan);
    CNumBase<numtype> setStat(numtype statn);
    CNumBase<numtype> setSyst(numtype systn);
    CNumBase<numtype> gaussian();
    CNumBase<numtype> operator*(numtype scale) const;
    CNumBase<numtype> operator*(const CNumBase<numtype>& mul) const;
    CNumBase<numtype> operator/(numtype scale) const;
    CNumBase<numtype> operator/(const CNumBase<numtype>& div) const;
    CNumBase<numtype> operator+(const CNumBase<numtype>& add) const;
    CNumBase<numtype> operator-(const CNumBase<numtype>& sub) const;
    CNumBase<numtype>& operator=(const CNumBase<numtype>& equal);
  protected:
  private:
    numtype data_;
    numtype stat_; 
    numtype syst_;
};

#include "CNumBase.impl.h"

#endif
