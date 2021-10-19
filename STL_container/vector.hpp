/*==Header-File=====================================tab=2==============//

  FileName    [Jackie_vector.hpp]

  Synopsis    [A simple C++ header-file implementation of STL: vector]

  Author      [JackieVan]
  
  Date        [Oct 4, 2021]

  Vision      [ 0.1 : basic function, do not include iterator and algorithms ]

=======================================================================*/

#pragma once

// typedef and macro added here..
//=======================================================//
//=======================================================//


//===----------------------------------------------------------------------===//
//                                  vector class                              //
//===----------------------------------------------------------------------===//
template <class Type>
class vector {
public:
  vector() : __size(0), __capacity(2){ __data = new Type[__capacity]; } 
  ~vector() {
    delete []__data;
  }

public:
  void push_back(const Type& _val) {
    if (__size == __capacity) 
    {
      __capacity *= 2;
      Type *__ptr = new Type[__capacity];
      for (size_t i = 0; i < __size; ++i) {
        __ptr[i] = __data[i];
      }
      delete []__data;
      __data = __ptr;
    }
    __data[__size++] = _val;
  }

  void clear() {
    __size = 0;
    for (size_t i = 0; i < __size; ++i) {
      __data[i] = nullptr;
    }
  }

  size_t size()     const { return __size;     }
  size_t capacity() const { return __capacity; }
  void   resize()   

private:
  void erase_from_end_to(size_t _index)
  {
    
  }

private:
  size_t __size;      // the first index of unused __date ptr, it also be the real size
  size_t __capacity;  // the length of __data ptr owned
  Type  *__data;
};