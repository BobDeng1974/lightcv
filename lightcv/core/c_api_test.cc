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
#include "gtest/gtest.h"

extern "C" {
#include "lightcv/core/c_api.h"
}

TEST(Tuple, Create) {
  Tuple *tup = CreateTupleInteger(10, 2);
  EXPECT_EQ(TupleType(tup), static_cast<int>(kVarInteger));
  EXPECT_EQ(TupleItemType(tup, 0), static_cast<int>(kVarInteger));
  EXPECT_EQ(TupleItemType(tup, 1), static_cast<int>(kVarInteger));
  EXPECT_EQ(TupleCount(tup), 2);
  DeleteTuple(&tup);

  tup = CreateTupleReal(1.0, 2);
  EXPECT_EQ(TupleType(tup), static_cast<int>(kVarReal));
  EXPECT_EQ(TupleItemType(tup, 0), static_cast<int>(kVarReal));
  EXPECT_EQ(TupleItemType(tup, 1), static_cast<int>(kVarReal));
  EXPECT_EQ(TupleCount(tup), 2);
  DeleteTuple(&tup);

  tup = CreateTupleString("A", 2);
  EXPECT_EQ(TupleType(tup), static_cast<int>(kVarString));
  EXPECT_EQ(TupleItemType(tup, 0), static_cast<int>(kVarString));
  EXPECT_EQ(TupleItemType(tup, 1), static_cast<int>(kVarString));
  EXPECT_EQ(TupleCount(tup), 2);
  DeleteTuple(&tup);
}

TEST(Tuple, Access) {
  Tuple *tup = CreateTupleInteger(10, 10);
  EXPECT_EQ(TupleGetIntegerItem(tup, 0), 10);
  Integer *integers = TupleIntegerItems(tup);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(integers[i], 10);
  }
  DeleteTuple(&tup);

  tup = CreateTupleReal(1.0, 10);
  EXPECT_DOUBLE_EQ(TupleGetRealItem(tup, 0), 1.0);
  Real *reals = TupleRealItems(tup);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_DOUBLE_EQ(reals[i], 1.0);
  }
  DeleteTuple(&tup);

  tup = CreateTupleString("A", 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_STREQ(TupleGetStringItem(tup, i), "A");
  }
  DeleteTuple(&tup);
}

TEST(Tuple, Edit) {
  Tuple *tup = CreateTupleInteger(1, 5);
  TupleSetIntegerItem(tup, 2, 1);
  EXPECT_EQ(TupleGetIntegerItem(tup, 1), 2);

  TupleSetRealItem(tup, 3.0, 2);
  EXPECT_EQ(TupleType(tup), static_cast<int>(kVarMixed));
  EXPECT_DOUBLE_EQ(TupleGetRealItem(tup, 2), 3.0);

  TupleSetStringItem(tup, "a", 3);
  EXPECT_EQ(TupleType(tup), static_cast<int>(kVarMixed));
  EXPECT_STREQ(TupleGetStringItem(tup, 3), "a");

  TupleAppendInteger(tup, 6);
  EXPECT_EQ(TupleCount(tup), 6);
  EXPECT_EQ(TupleGetIntegerItem(tup, 5), 6);

  TupleAppendReal(tup, 7.0);
  EXPECT_EQ(TupleCount(tup), 7);
  EXPECT_DOUBLE_EQ(TupleGetRealItem(tup, 6), 7.0);

  TupleAppendString(tup, "b");
  EXPECT_EQ(TupleCount(tup), 8);
  EXPECT_STREQ(TupleGetStringItem(tup, 7), "b");

  // 1 2 3.0 a 1 6 7.0 b

  TupleInsertInteger(tup, 10, 3);
  // 1 2 3.0 10 a 1 6 7.0 b
  EXPECT_EQ(TupleCount(tup), 9);
  EXPECT_EQ(TupleGetIntegerItem(tup, 3), 10);
  EXPECT_STREQ(TupleGetStringItem(tup, 4), "a");

  TupleEraseItem(tup, 7);
  EXPECT_EQ(TupleCount(tup), 8);
  EXPECT_STREQ(TupleGetStringItem(tup, 7), "b");

  DeleteTuple(&tup);
}

