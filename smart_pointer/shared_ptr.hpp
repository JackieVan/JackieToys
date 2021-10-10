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
  explicit shared_ptr(Type *_ptr = nullptr) : __ptr(_ptr), __reference_counter(new long(0)) { if (_ptr) refInc(); }
           shared_ptr(const shared_ptr<Type>& _sp) : __ptr(_sp.__ptr), __reference_counter(_sp.__reference_counter) { refInc(); }
           shared_ptr(std::nullptr_t _null) : __ptr(nullptr), __reference_counter(new long(0)) {}
  
  ~shared_ptr()
  {
    memory();
  }

public:

  // ============================== API ============================== //
  Type *get()       const { return  __ptr;                    }
  long  use_count() const { return *__reference_counter;      }
  bool  unique()    const { return *__reference_counter == 1; }

  void reset(Type *_ptr = nullptr)
  { 
    memory();
    __ptr = _ptr;
    __reference_counter = __ptr == nullptr ? new long(0) : new long(1);
  }

  // ======================= operator overload ======================= //
  bool operator==(const shared_ptr<Type>& _sp) const { return __ptr == _sp.__ptr; }
  bool operator==(std::nullptr_t _null)        const { return __ptr == nullptr;   }
  bool operator!=(std::nullptr_t _null)        const { return __ptr != nullptr;   }
       operator bool()                         const { return __ptr != nullptr;   } // for some special usage scenarios, ie.. assert(ptr)

  Type &operator*()  const { return *__ptr; }
  Type *operator->() const { return __ptr;  }

  shared_ptr<Type>& operator=(const shared_ptr<Type>& _sp)
  {
    if (this == &_sp)
      return *this;
    memory();
    __ptr = _sp.__ptr;
    __reference_counter = _sp.__reference_counter;
    refInc();
    return *this;
  }

  shared_ptr<Type>& operator=(std::nullptr_t _null)
  {
    reset(nullptr);
    return *this;
  }

private:
  long refDec() const { return --(*__reference_counter); }
  long refInc() const { return ++(*__reference_counter); }

  void memory()
  {
    long ref_count = refDec();
    if (ref_count == 0) {
      delete __ptr;
      delete __reference_counter;
      __ptr = nullptr;
      __reference_counter = nullptr;
    } else if (ref_count == -1) {
      delete __reference_counter;
      __reference_counter = nullptr;
    }
  }

private:
  Type *__ptr;                // the ptr this smart pointer shared
  long *__reference_counter;  // the use reference counter
};

//===----------------------------------------------------------------------===//
//                            make_shared function                            //
//===----------------------------------------------------------------------===//
template <class Type, class... Args>
shared_ptr<Type> make_shared(Args&&... _args) 
{
  return shared_ptr<Type>(new Type(std::forward<Args>(_args)...));
}


} // namespace Jackie
