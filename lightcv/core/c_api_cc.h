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
#ifndef LIGHTCV_CORE_C_API_CC_H_
#define LIGHTCV_CORE_C_API_CC_H_

#ifdef __cplusplus
#include "lightcv/core/tuple.h"
#include "lightcv/core/object.h"
using namespace lightcv;
#endif  // __cplusplus


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

extern void DeleteTupleCpp(Tuple **tup);
extern Tuple* CreateTupleIntegerCpp(Integer i, Integer cnt);
extern Tuple* CreateTupleRealCpp(Real r, Integer cnt);
extern Tuple* CreateTupleStringCpp(const char* s, Integer cnt);
extern int TupleTypeCpp(const Tuple *tup);
extern Integer TupleCountCpp(const Tuple* tup);
extern Integer TupleCapacityCpp(const Tuple *tup);
extern int TupleItemTypeCpp(const Tuple *tup, Integer index);
extern Integer TupleGetIntegerItemCpp(const Tuple *tup, Integer index);
extern Real TupleGetRealItemCpp(Tuple *tup, Integer index);
extern const char* TupleGetStringItemCpp(Tuple *tup, Integer index);
extern void TupleSetIntegerItemCpp(Tuple *tup, Integer i, Integer index);
extern void TupleSetRealItemCpp(Tuple *tup, Real r, Integer index);
extern void TupleSetStringItemCpp(Tuple *tup, const char* s, Integer index);
extern void TupleAppendIntegerCpp(Tuple *tup, Integer i);
extern void TupleAppendRealCpp(Tuple *tup, Real r);
extern void TupleAppendStringCpp(Tuple *tup, const char *s);
extern void TupleInsertIntegerCpp(Tuple *tup, Integer i, Integer index);
extern void TupleInsertRealCpp(Tuple *tup, Real r, Integer index);
extern void TupleInsertStringCpp(Tuple *tup, const char *s, Integer index);
extern void TupleEraseItemCpp(Tuple *tup, Integer index);
extern Integer* TupleIntegerItemsCpp(Tuple *tup);
extern Real* TupleRealItemsCpp(Tuple *tup);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // LIGHTCV_CORE_C_API_CC_H_

