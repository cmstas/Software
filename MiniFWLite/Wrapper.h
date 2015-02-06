#ifndef Wrapper_h
#define Wrapper_h

#include <typeinfo>
#include "EDProduct.h"

namespace edm
{
    template <class T>
        class Wrapper : public EDProduct {
            public:
                Wrapper() {}
                virtual ~Wrapper() {}

                T const * product() const {return (present ? &obj : 0);}
                T const * operator->() const {return product();}

                // these are used by FWLite
                static const std::type_info& productTypeInfo() {return typeid(T);}
                static const std::type_info& typeInfo() {return typeid(Wrapper<T>);}

            private:
                Wrapper(Wrapper<T> const& rh); // disallow copy construction
                Wrapper<T> & operator=(Wrapper<T> const&); // disallow assignment

                bool present;
                T obj;
        };
}

#endif
