#ifndef ITREE_H
#define ITREE_H

template <class T>
class ITree {
public:
    virtual ~ITree() = default;
    virtual bool Find(const T& value) = 0;
    virtual void Insert(const T& value) = 0;
    virtual void Delete(const T& value) = 0;
};


#endif //ITREE_H
