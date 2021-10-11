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
  explicit  shared_ptr(Type *_ptr = nullptr) : __ptr(_ptr), 
                                               __reference_counter(nullptr)
            { 
              if (_ptr)  __reference_counter = new long(1);
            }

            shared_ptr(const shared_ptr<Type>& _sp) : __ptr(_sp.__ptr), 
                                                     __reference_counter(_sp.__reference_counter)
            { 
              if (__ptr != nullptr)   refInc();
            }

           shared_ptr(std::nullptr_t _null) : __ptr(nullptr), __reference_counter(nullptr) {}
  
  ~shared_ptr()
  {
    put_down();
  }

public:

  // ============================== API ============================== //
  Type *get()       const { return  __ptr;                                            }
  bool  unique()    const { return  __reference_counter && *__reference_counter == 1; }
  long  use_count() const { return  __reference_counter ?  *__reference_counter :  0; }

  void reset(Type *_ptr = nullptr)
  { 
    put_down();
    __ptr = _ptr;
    __reference_counter = __ptr == nullptr ? nullptr : new long(1);
  }

  void swap(shared_ptr<Type>& _sp) // exchange the ownership of ptr
  {
    long *tmp_ref = __reference_counter;
    Type *tmp_ptr = __ptr;
    __reference_counter = _sp.__reference_counter;
    __ptr = _sp.__ptr;
    _sp.__reference_counter = tmp_ref;
    _sp.__ptr = tmp_ptr;
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
    if (_sp == nullptr) {
      reset(nullptr);
    } else {
      put_down();
      __ptr = _sp.__ptr;
      __reference_counter = _sp.__reference_counter;
      refInc();
    }
    return *this;
  }

  shared_ptr<Type>& operator=(std::nullptr_t _null)
  {
    reset(nullptr);
    return *this;
  }

private:
  inline long refDec() const { return __reference_counter ? --(*__reference_counter) : -1; }
  inline long refInc() const { return ++(*__reference_counter);                            }

  void put_down() // reference dec and set __ptr and __reference_counter to nullptr
  {
    if (__reference_counter == nullptr)
      return;
    if (refDec() == 0) {
      delete __ptr;
      delete __reference_counter;
    }
    __ptr = nullptr;
    __reference_counter = nullptr;
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
