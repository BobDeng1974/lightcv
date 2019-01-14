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
#ifndef LIGHTCV_CORE_C_API_H_
#define LIGHTCV_CORE_C_API_H_

// Call C++ objects from C, see https://isocpp.org/wiki/faq/mixing-c-and-cpp#get-cpp-data-members-from-c
// This is the header for C API
#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct Tuple Tuple;
typedef struct Ref Ref;
typedef struct Tuple* Tup;
typedef struct Ref* Obj;

typedef int Integer;
typedef double Real;

typedef enum VarType {
  kVarUndef = 0,
  kVarInteger,
  kVarReal,
  kVarString,
  kVarMixed
} VarType;

extern void DeleteTuple(Tuple **tup);
extern Tuple* CreateTupleInteger(Integer i, Integer cnt);
extern Tuple* CreateTupleReal(Real r, Integer cnt);
extern Tuple* CreateTupleString(const char* s, Integer cnt);
extern VarType TupleType(Tuple* tup);
extern Integer TupleCount(Tuple* tup);
extern Integer TupleCapacity(Tuple *tup);
extern VarType TupleItemType(Tuple *tup, Integer index);
extern Integer TupleGetIntegerItem(Tuple *tup, Integer index);
extern Real TupleGetRealItem(Tuple *tup, Integer index);
extern const char* TupleGetStringItem(Tuple *tup, Integer index);
extern void TupleSetIntegerItem(Tuple *tup, Integer i, Integer index);
extern void TupleSetRealItem(Tuple *tup, Real r, Integer index);
extern void TupleSetStringItem(Tuple *tup, const char* s, Integer index);
extern void TupleAppendInteger(Tuple *tup, Integer i);
extern void TupleAppendReal(Tuple *tup, Real r);
extern void TupleAppendString(Tuple *tup, const char *s);
extern void TupleInsertInteger(Tuple *tup, Integer i, Integer index);
extern void TupleInsertReal(Tuple *tup, Real r, Integer index);
extern void TupleInsertString(Tuple *tup, const char *s, Integer index);
extern void TupleEraseItem(Tuple *tup, Integer index);
extern Integer* TupleIntegerItems(Tuple *tup);
extern Real* TupleRealItems(Tuple *tup);

typedef struct Ref Ref;
typedef enum ObjectType {
  kObjNull = 0,
  kObjImage,
  kObjRegion,
  kObjCurve,
  kObjTuple
} ObjectType;

extern ObjectType ObjectGetType(Ref *obj);
extern Ref* RetainObject(Ref *obj);
extern void ReleaseObject(Ref **obj);

#ifdef __cplusplus
}
#endif  // __cplusplus

// types
#endif  // LIGHTCV_CORE_C_API_H_

