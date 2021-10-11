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

private:
  void erase_from_end_to(size_t _index)
  {
    
  }

private:
  size_t __size;      // the current data valid end index
  size_t __capacity;  // the length of __data ptr ownered
  Type  *__data;
};