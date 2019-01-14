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
#include "lightcv/core/c_api.h"
#include "lightcv/core/c_api_cc.h"

void DeleteTuple(Tuple **tup) {
  DeleteTupleCpp(tup);
}

Tuple* CreateTupleInteger(Integer i, Integer cnt) {
  Tuple *tup = (Tuple*)CreateTupleIntegerCpp(i, cnt);
  return tup;
}

Tuple* CreateTupleReal(Real r, Integer cnt) {
  Tuple *tup = (Tuple*)CreateTupleRealCpp(r, cnt);
  return tup;
}

Tuple* CreateTupleString(const char *s, Integer cnt) {
  Tuple *tup = (Tuple*)CreateTupleStringCpp(s, cnt);
  return tup;
}

VarType TupleType(Tuple *tup) {
  return (VarType)TupleTypeCpp(tup);
}

Integer TupleCount(Tuple *tup) {
  return (Integer)TupleCountCpp(tup);
}

Integer TupleCapacity(Tuple *tup) {
  return (Integer)TupleCapacityCpp(tup);
}

VarType TupleItemType(Tuple *tup, Integer index) {
  return (VarType)TupleItemTypeCpp(tup, index);
}

Integer TupleGetIntegerItem(Tuple *tup, Integer index) {
  return (Integer)TupleGetIntegerItemCpp(tup, index);
}

Real TupleGetRealItem(Tuple *tup, Integer index) {
  return (Real)TupleGetRealItemCpp(tup, index);
}

const char* TupleGetStringItem(Tuple *tup, Integer index) {
  return TupleGetStringItemCpp(tup, index);
}

void TupleSetIntegerItem(Tuple *tup, Integer i, Integer index) {
  TupleSetIntegerItemCpp(tup, i, index);
}

void TupleSetRealItem(Tuple *tup, Real r, Integer index) {
  TupleSetRealItemCpp(tup, r, index);
}

void TupleSetStringItem(Tuple *tup, const char* s, Integer index) {
  TupleSetStringItemCpp(tup, s, index);
}

void TupleAppendInteger(Tuple *tup, Integer i) {
  TupleAppendIntegerCpp(tup, i);
}

void TupleAppendReal(Tuple *tup, Real r) {
  TupleAppendRealCpp(tup, r);
}

void TupleAppendString(Tuple *tup, const char *s) {
  TupleAppendStringCpp(tup, s);
}

void TupleInsertInteger(Tuple *tup, Integer i, Integer index) {
  TupleInsertIntegerCpp(tup, i, index);
}

void TupleInsertReal(Tuple *tup, Real r, Integer index) {
  TupleInsertRealCpp(tup, r, index);
}

void TupleInsertString(Tuple *tup, const char *s, Integer index) {
  TupleInsertStringCpp(tup, s, index);
}

void TupleEraseItem(Tuple *tup, Integer index) {
  TupleEraseItemCpp(tup, index);
}

Integer* TupleIntegerItems(Tuple *tup) {
  return (Integer*)TupleIntegerItemsCpp(tup);
}

Real* TupleRealItems(Tuple *tup) {
  return (Real*)TupleRealItemsCpp(tup);
}

ObjectType ObjectGetType(Ref *obj) {
  return (ObjectType)ObjectGetTypeCpp(obj);
}

Ref* RetainObject(Ref *obj) {
  return (Ref*)RetainObjectCpp(obj);
}

void ReleaseObject(Ref **obj) {
  ReleaseObjectCpp(obj);
}
