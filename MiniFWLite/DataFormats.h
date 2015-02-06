#ifndef DataFormats_h
#define DataFormats_h

#include <set>
#include <map>

namespace edm
{
    struct BranchKey {};
    struct EventAuxiliary {};
    struct FileFormatVersion {};
    struct LuminosityBlockAuxiliary {};
    struct ParameterSetBlob {};
    struct RunAuxiliary {};

    class BranchChildren {};
    class BranchDescription {
        public:
            struct Transients {};
    };
    class BranchID {
        public:
          bool operator<(BranchID const& rhs) const {return true;}
    };
    class EventEntryDescription {
        public:
            struct Transients {};
    };
    class EventEntryInfo {
        public:
            struct Transients {};
    };
    class EventID {};
    class FileID {};
    class FileIndex {
        public:
            class Element {};
            struct Transients {};
    };
    template <int I> class Hash {};
    class History {};
    class LuminosityBlockID {};
    class ModuleDescription {};
    class Parentage {
        public:
            struct Transients {};
    };
    class ProcessConfiguration {
        public:
            struct Transients {};
    };
    class ProcessHistory {
        public:
            struct Transients {};
    };
    class ProductID {};
    class StoredProductProvenance {
        public:
            struct Transients {};
    };
    class ProductProvenance {
        public:
            struct Transients {};
    };
    class ProductRegistry {
        public:
            struct Transients {};
    };
    class RunID {};
    class Timestamp {};
    class IndexIntoFile {
        public:
            struct Transients {};
            struct RunOrLumiEntry {};
    };
    template <typename T> class Transient {};
}

#endif
