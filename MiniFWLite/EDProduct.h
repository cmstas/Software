#ifndef EDProduct_h
#define EDProduct_h

namespace edm
{
    class EDProduct {
        public:
            EDProduct() {}
            virtual ~EDProduct() {}

            bool isPresent() const {return isPresent_();}
#ifndef __REFLEX__
            bool isMergeable() const {return isMergeable_();}
            bool mergeProduct(EDProduct const* newProduct) {return mergeProduct_(newProduct);}
            bool hasIsProductEqual() const {return hasIsProductEqual_();}
            bool isProductEqual(EDProduct const* newProduct) const {return isProductEqual_(newProduct);}
#endif

        private:
            // These will never be called.
            // For technical ROOT related reasons, we cannot
            // declare it = 0.
            virtual bool isPresent_() const {return true;}
#ifndef __REFLEX__
            virtual bool isMergeable_() const {return true;}
            virtual bool mergeProduct_(EDProduct const* newProduct) {return true;}
            virtual bool hasIsProductEqual_() const {return true;}
            virtual bool isProductEqual_(EDProduct const* newProduct) const {return true;}
#endif
    };
}

#endif
