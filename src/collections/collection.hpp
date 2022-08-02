#ifndef CPT_COLLECTION_H_INCLUDED
#define CPT_COLLECTION_H_INCLUDED

#include <vector>
#include <span>

namespace cpt
{
    template<class T>
    using Collection = typename std::vector<T>;

    template<class T>
    using View = typename std::span<T>;
} // namespace cpt

#endif