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
#include "lightcv/core/c_api_cc.h"
#include "lightcv/core/var.h"

void DeleteTupleCpp(Tuple **tup) {
  if (*tup) {
    delete *tup;
    *tup = nullptr;
  }
}

Tuple* CreateTupleIntegerCpp(Integer i, Integer cnt) {
  Tuple *tup = new Tuple(i, cnt);
  return tup;
}

Tuple* CreateTupleRealCpp(Real r, Integer cnt) {
  Tuple *tup = new Tuple(r, cnt);
  return tup;
}

Tuple* CreateTupleStringCpp(const char* s, Integer cnt) {
  Tuple *tup = new Tuple(s, cnt);
  return tup;
}

int TupleTypeCpp(const Tuple* tup) {
  return static_cast<int>(tup->type());
}

Integer TupleCountCpp(const Tuple* tup) {
  return tup->count();
}

Integer TupleCapacityCpp(const Tuple *tup) {
  return tup->capacity();
}

int TupleItemTypeCpp(const Tuple *tup, Integer index) {
  return static_cast<int>(tup->operator[](index).type);
}

Integer TupleGetIntegerItemCpp(const Tuple *tup, Integer index) {
  return (*tup)[index].I();
}

Real TupleGetRealItemCpp(Tuple *tup, Integer index) {
  return (*tup)[index].D();
}

// std::string::c_str() return temporary data if the string is temorary.
// Do not return const char* by using Tuple::operator[].S().c_str(), this will create a temporary std::string
static const char *g_null_string = "";
const char* TupleGetStringItemCpp(Tuple *tup, Integer index) {
  if (tup->type() == kVarString) {
    return tup->S()[index].c_str();
  } else if (tup->type() == kVarMixed && (*tup)[index].type == kVarString) {
    return tup->V()[index].S().c_str();
  }

  return g_null_string;
}

void TupleSetIntegerItemCpp(Tuple *tup, Integer i, Integer index) {
  tup->Set(i, index);
}

void TupleSetRealItemCpp(Tuple *tup, Real r, Integer index) {
  tup->Set(r, index);
}

void TupleSetStringItemCpp(Tuple *tup, const char* s, Integer index) {
  tup->Set(s, index);
}

void TupleAppendIntegerCpp(Tuple *tup, Integer i) {
  tup->Append(i);
}

void TupleAppendRealCpp(Tuple *tup, Real r) {
  tup->Append(r);
}

void TupleAppendStringCpp(Tuple *tup, const char *s) {
  tup->Append(s);
}

void TupleInsertIntegerCpp(Tuple *tup, Integer i, Integer index) {
  tup->Insert(i, index);
}

void TupleInsertRealCpp(Tuple *tup, Real r, Integer index) {
  tup->Insert(r, index);
}

void TupleInsertStringCpp(Tuple *tup, const char *s, Integer index) {
  tup->Insert(s, index);
}

void TupleEraseItemCpp(Tuple *tup, Integer index) {
  tup->Erase(index);
}

Integer* TupleIntegerItemsCpp(Tuple *tup) {
  return tup->I();
}

Real* TupleRealItemsCpp(Tuple *tup) {
  return tup->D();
}

int ObjectGetTypeCpp(Ref *obj) {
  if (obj) {
    return static_cast<int>((*obj)->type());
  }

  return 0;
}

Ref* RetainObjectCpp(Ref *obj) {
  Ref *ref = new Ref(*obj);
  return ref;
}

void ReleaseObjectCpp(Ref **obj) {
  if (*obj) {
    delete (*obj);
    *obj = nullptr;
  }
}

