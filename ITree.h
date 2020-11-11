#ifndef ITREE_H
#define ITREE_H

#include <cstdint>

class ITree {
public:
    using Int_t = int_fast32_t;
    virtual ~ITree() = default;
    virtual bool Find(const Int_t& value) = 0;
    virtual void Insert(const Int_t& value) = 0;
    virtual void Delete(const Int_t& value) = 0;
};


#endif ITREE_H
