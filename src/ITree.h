// Copyright 2020 Alexander Izyurov, Semen Matrenok, Michael Pavlov

#ifndef SRC_ITREE_H_
#define SRC_ITREE_H_

template<class T>
class ITree {
 public:
  virtual ~ITree() = default;
  virtual bool Find(const T &value) = 0;
  virtual void Insert(const T &value) = 0;
  virtual void Delete(const T &value) = 0;
};

#endif  // SRC_ITREE_H_
