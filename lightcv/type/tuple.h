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
#ifndef LIGHTCV_TYPE_TUPLE_H_
#define LIGHTCV_TYPE_TUPLE_H_

#include "lightcv/type/basic.h"
#include "lightcv/type/var.h"

namespace lightcv {

class Tuple {
 public:
  Tuple();

  Tuple(Integer i, Integer cnt = 1);
  Tuple(Real f, Integer cnt = 1);
  Tuple(const char *s, Integer cnt = 1);
  Tuple(const String &s, Integer cnt = 1);
  Tuple(const Var &var, Integer cnt = 1);
  Tuple(const VarRef &var, Integer cnt = 1);
  Tuple(const Tuple &t);

  Tuple &operator=(const Tuple &t);

  ~Tuple();

  VarType type() const { return type_; }
  Integer count() const { return count_; }
  Integer capacity() const { return capacity_; }

  VarRef operator[](Integer index) const;

  // write
  // mixed type cannot back to pure type by using Set or Erase function.
  //   if a variable is a mixed type, it means you want to use it
  //   as dictionary in parameter transfering, so it's not allowd to
  //   changed it back to a pure type by using Set functions,
  //   because the set functions may be too slow.
  void Set(Integer i, Integer index = 0);
  void Set(Real d, Integer index = 0);
  void Set(const String &s, Integer index = 0);

  void Append(const Var &v);
  void Insert(const Var &v, Integer index);
  void Erase(Integer index);

  Integer* I() const;
  Real* D() const;
  String* S() const;
  Var* V() const;

 private:
  void Reset();
  void ClearData();
  void GrowUpOne(VarType type);
  void SetVar(const Var &var, Integer index = 0);

  union {
    Integer *i;
    Real *d;
    String *s;
    Var *var;
  } vec_;

  VarType type_;
  Integer count_;
  Integer capacity_;
};

// Compasison operators
// Equal to
bool operator==(const VarRef &lhs, Integer rhs);
bool operator==(Integer lhs, const VarRef &rhs);
bool operator==(const VarRef &lhs, Real rhs);
bool operator==(const Real lhs, const VarRef &rhs);
bool operator==(const VarRef &lhs, const String &rhs);
bool operator==(const String &lhs, const VarRef &rhs);
bool operator==(const VarRef &lhs, const VarRef &rhs);

// Not equal to
bool operator!=(const VarRef &lhs, Integer rhs);
bool operator!=(Integer lhs, const VarRef &rhs);
bool operator!=(const VarRef &lhs, Real rhs);
bool operator!=(const Real lhs, const VarRef &rhs);
bool operator!=(const VarRef &lhs, const String &rhs);
bool operator!=(const String &lhs, const VarRef &rhs);
bool operator!=(const VarRef &lhs, const VarRef &rhs);

// Less than
bool operator<(const VarRef &lhs, Integer rhs);
bool operator<(Integer lhs, const VarRef &rhs);
bool operator<(const VarRef &lhs, Real rhs);
bool operator<(Real lhs, const VarRef &rhs);
bool operator<(const VarRef &lhs, const String &rhs);
bool operator<(const String &lhs, const VarRef &rhs);
bool operator<(const VarRef &lhs, const VarRef &rhs);

// Greater than or equal
bool operator>=(const VarRef &lhs, Integer rhs);
bool operator>=(Integer lhs, const VarRef &rhs);
bool operator>=(const VarRef &lhs, Real rhs);
bool operator>=(Real lhs, const VarRef &rhs);
bool operator>=(const VarRef &lhs, const String &rhs);
bool operator>=(const String &lhs, const VarRef &rhs);
bool operator>=(const VarRef &lhs, const VarRef &rhs);

// Greater than
bool operator>(const VarRef &lhs, Integer rhs);
bool operator>(Integer lhs, const VarRef &rhs);
bool operator>(const VarRef &lhs, Real rhs);
bool operator>(Real lhs, const VarRef &rhs);
bool operator>(const VarRef &lhs, const String &rhs);
bool operator>(const String &lhs, const VarRef &rhs);
bool operator>(const VarRef &lhs, const VarRef &rhs);

// Less than or equal
bool operator<=(const VarRef &lhs, Integer rhs);
bool operator<=(Integer lhs, const VarRef &rhs);
bool operator<=(const VarRef &lhs, Real rhs);
bool operator<=(Real lhs, const VarRef &rhs);
bool operator<=(const VarRef &lhs, const String &rhs);
bool operator<=(const String &lhs, const VarRef &rhs);
bool operator<=(const VarRef &lhs, const VarRef &rhs);

}  // namespace lightcv

#endif  // LIGHTCV_TYPE_TUPLE_H_

