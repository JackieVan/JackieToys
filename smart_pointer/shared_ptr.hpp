/*==Header-File=====================================tab=2==============//

  FileName    [shared_ptr.hpp]

  Synopsis    [A simple C++ header-file implementation of smart pointer: shared_ptr]

  Author      [JackieVan]
  
  Date        [Oct 7, 2021]

  Vision      [ 0.1 ]

=======================================================================*/


namespace Jackie {

// typedef and macro added here..
//=======================================================//
//=======================================================//

//===----------------------------------------------------------------------===//
//                               shared_ptr class
//===----------------------------------------------------------------------===//
template <class Type>
class shared_ptr {
public:
  explicit shared_ptr() : __ptr(nullptr), __reference_count(new long(0)) {}
  explicit shared_ptr(Type *_ptr) : __ptr(_ptr), __reference_count(new long(1)) {}
  explicit shared_ptr(const shared_ptr& _sp) : __ptr(_sp.__ptr), __reference_count(sp.__reference_count) { *__reference_count++; }

  ~shared_ptr()
  {
    long ref_count = --(*__reference_count);
    if (ref_count == 0) {
      delete __ptr;
      delete __reference_count;
    } else if (ref_count == -1) {
      delete __reference_count;
    }
  }

public:
  Type *get()        { return  __ptr;                  }
  long  use_count()  { return *__reference_count;      }
  bool  unique()     { return *__reference_count == 1; }

  bool operator==(const shared_ptr<Type>& _sp){ return __ptr == _sp.__ptr; }

  shared_ptr<Type>& operator=(const shared_ptr<Type>& _sp)
  {
    if (this == &_sp)   return *this;
    if (--(*__reference_count) == 0) {
      delete __ptr;
      delete __reference_count;
    } else if ()
  }

private:



private:
  Type *__ptr; // the ptr this smart pointer shared
  long *__reference_count;
};
  
} // namespace Jackie
