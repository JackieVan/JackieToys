/*==Header-File=====================================tab=2==============//

  FileName    [shared_ptr.hpp]

  Synopsis    [A simple C++ header-file implementation of smart pointer: shared_ptr]

  Author      [JackieVan]
  
  Date        [Oct 7, 2021]

  Vision      [ 0.1 ]

=======================================================================*/

#pragma once

#include <iostream>
#include <cassert>

namespace Jackie {

// typedef and macro added here..
//=======================================================//
//=======================================================//

//===----------------------------------------------------------------------===//
//                               shared_ptr class                             //
//===----------------------------------------------------------------------===//
template <class Type>
class shared_ptr {
public:
           shared_ptr() : __ptr(nullptr), __reference_counter(new long(0)) { std::cout << "constructor functiion: 0\n"; }
  explicit shared_ptr(Type *_ptr) : __ptr(_ptr), __reference_counter(new long(1)) { std::cout << "constructor functiion: 1\n"; }
           shared_ptr(const shared_ptr<Type>& _sp) : __ptr(_sp.__ptr), __reference_counter(_sp.__reference_counter) { refInc();  std::cout << "constructor functiion: 2\n"; }

  ~shared_ptr()
  {
    memory();
    std::cout << "destructor function\n";
  }

public:

  // ============================== API ============================== //
  Type *get()        { return  __ptr;                  }
  long  use_count()  { return *__reference_counter;      }
  bool  unique()     { return *__reference_counter == 1; }

  void reset(Type *_ptr = nullptr)
  { 
    memory();
    __ptr = _ptr;
    __reference_counter = __ptr == nullptr ? new long(0) : new long(1);
  }

  // ======================= operator overload ======================= //
  bool operator==(const shared_ptr<Type>& _sp){ return __ptr == _sp.__ptr; }
  bool operator==(std::nullptr_t _null)       { return __ptr == nullptr;   }

  shared_ptr<Type>& operator=(const shared_ptr<Type>& _sp)
  {
    std::cout << "operator= overload 0 is called\n";
    if (this == &_sp)   
      return *this;
    memory();
    __ptr = _sp.__ptr;
    __reference_counter = _sp.__reference_counter;
    refInc();
    return *this;
  }

  Type &operator*(){ assert(__ptr && "invalid operator* for nullptr"); return *__ptr; }
  
  Type *operator->(){ return __ptr; }

private:
  long refDec() const { return --(*__reference_counter); }
  long refInc() const { return ++(*__reference_counter); }

  void memory()
  {
    long ref_count = refDec();
    if (ref_count == 0) {
      delete __ptr;
      delete __reference_counter;
    } else if (ref_count == -1) {
      delete __reference_counter;
    }
  }

private:
  Type *__ptr;                // the ptr this smart pointer shared
  long *__reference_counter;  // the use reference counter
};

//===----------------------------------------------------------------------===//
//                        make_shared<Type> function                          //
//===----------------------------------------------------------------------===//
template <typename Type>
shared_ptr<Type> make_shared(Type *_ptr) { return shared_ptr<Type>(_ptr); } 


} // namespace Jackie
