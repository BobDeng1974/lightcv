/* Copyright 2018-2019 songyuncen. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef LIGHTCV_TYPE_VAR_H_
#define LIGHTCV_TYPE_VAR_H_
#include "lightcv/type/basic.h"

namespace lightcv {

enum VarType {
  kVarUndef = 0,
  kVarInteger,
  kVarReal,
  kVarString,
  kVarMixed
};

class Var;
class Tuple;

struct VarRef {
  VarRef() {
    ptr.i = NULL;
    type = kVarUndef;
    index = -1;
    tuple = NULL;
  }

  union {
    Integer *i;
    Real *d;
    String *s;
  } ptr;

  VarType type;
  int index;
  Tuple *tuple;

  VarRef operator=(Integer i);
  VarRef operator=(Real d);
  VarRef operator=(const String &s);

  operator Integer() const;
  operator Real() const;
  operator String() const;

  Integer I() const {
    return static_cast<Integer>(*this);
  }

  Real D() const {
    return static_cast<Real>(*this);
  }

  String S() const {
    return static_cast<String>(*this);
  }
};

class Var {
 public:
  Var();
  Var(Integer i);
  Var(Real d);
  Var(const char* s);
  Var(const String &s);
  Var(const Var &var);
  Var(const VarRef &ref);
  Var &operator=(const Var &var);

  ~Var();

  void Set(Integer i);
  void Set(Real d);
  void Set(const String &s);

  Integer I() const;
  Real D() const;
  const String& S() const;

  VarType type() const { return type_; }

 private:
  friend class Tuple;
  void Clear();

  union {
    Integer i;
    Real d;
    String *s;
  } val_;

  VarType type_;
};

} // namespace lightcv

#endif  // LIGHTCV_TYPE_VAR_H_

