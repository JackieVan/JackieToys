/*==Header-File=====================================tab=2==============//

  FileName    [Jackie_vector.hpp]

  Synopsis    [A simple C++ header-file implementation of STL: vector]

  Author      [JackieVan]
  
  Date        [Oct 4, 2021]

  Vision      [ 0.1 ]

=======================================================================*/


// typedef and macro added here..
//=======================================================//
#define Vcetor JackieVector
//=======================================================//


//===----------------------------------------------------------------------===//
//                               JackieVcetor class
//===----------------------------------------------------------------------===//
template <class type>
class JackieVector {
public:
  // default constructor
  JackieVector() : __size(0), __capacity(2){ __data = new type[__capacity]; } 
  ~JackieVector() {
    delete []__data;
  }

public:
  void push_back(const type& _val) {
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

private:
  size_t __size;
  size_t __capacity;
  type  *__data;
};