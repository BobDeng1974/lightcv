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
#include "lightcv/type/tuple.h"

using namespace lightcv;

TEST(Tuple, DefaultConstructor) {
  Tuple t0;
  EXPECT_EQ(t0.type(), kVarUndef);
  EXPECT_EQ(t0.count(), 0);
}

TEST(Tuple, ConstructorByInteger) {
  Tuple t0(1);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.I()[0], 1);

  Tuple t1(1, 10);
  EXPECT_EQ(t1.type(), kVarInteger);
  EXPECT_EQ(t1.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t1.I()[i], 1);
  }
}

TEST(Tuple, ConstructorByReal) {
  Tuple t0(1.1);
  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_DOUBLE_EQ(t0.D()[0], 1.1);

  Tuple t1(1.1, 10);
  EXPECT_EQ(t1.type(), kVarReal);
  EXPECT_EQ(t1.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_DOUBLE_EQ(t1.D()[i], 1.1);
  }
}

TEST(Tuple, ConstructorByString) {
  // const char *
  Tuple t0("a");
  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.S()[0], "a");

  Tuple t1("a", 10);
  EXPECT_EQ(t1.type(), kVarString);
  EXPECT_EQ(t1.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t1.S()[i], "a");
  }

  // lightcv::String
  String str("a");
  Tuple t2(str);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2.count(), 1);
  EXPECT_EQ(t2.S()[0], "a");

  Tuple t3(str, 10);
  EXPECT_EQ(t3.type(), kVarString);
  EXPECT_EQ(t3.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t3.S()[i], "a");
  }
}

TEST(Tuple, ConstructorByVar) {
  Tuple t0(1, 10);
  t0.Set("a", 2);
  EXPECT_EQ(t0.type(), kVarMixed);

  Var &var1 = t0.V()[0];

  Tuple t1(var1);
  EXPECT_EQ(t1.type(), kVarInteger);
  EXPECT_EQ(t1.count(), 1);
  EXPECT_EQ(t1.I()[0], 1);

  Tuple t2(var1, 10);
  EXPECT_EQ(t2.type(), kVarInteger);
  EXPECT_EQ(t2.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t2.I()[i], 1);
  }

  Var &var2 = t0.V()[2];

  Tuple t3(var2);
  EXPECT_EQ(t3.type(), kVarString);
  EXPECT_EQ(t3.count(), 1);
  EXPECT_EQ(t3.S()[0], "a");

  Tuple t4(var2, 10);
  EXPECT_EQ(t4.type(), kVarString);
  EXPECT_EQ(t4.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t4.S()[i], "a");
  }
}

TEST(Tuple, ConstructorByVarRef) {
  Tuple ref0(1);

  Tuple t0(ref0[0]);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.I()[0], 1);
  Tuple t1(ref0[0], 10);
  EXPECT_EQ(t1.type(), kVarInteger);
  EXPECT_EQ(t1.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t1.I()[i], 1);
  }

  Tuple ref1("a", 10);
  ref1.Set(1, 2);
  ref1.Set(1.1, 3);
  EXPECT_EQ(ref1.type(), kVarMixed);

  Tuple t2(ref1[0]);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2.count(), 1);
  EXPECT_EQ(t2.S()[0], "a");

  Tuple t3(ref1[0], 10);
  EXPECT_EQ(t3.type(), kVarString);
  EXPECT_EQ(t3.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t3.S()[i], "a");
  }

  Tuple t4(ref1[2]);
  EXPECT_EQ(t4.type(), kVarInteger);
  EXPECT_EQ(t4.count(), 1);
  EXPECT_EQ(t4.I()[0], 1);
  Tuple t5(ref1[2], 10);
  EXPECT_EQ(t5.type(), kVarInteger);
  EXPECT_EQ(t5.count(), 10);
  for (Integer i = 0; i < 10; ++i) {
    EXPECT_EQ(t5.I()[i], 1);
  }

  Tuple t6(ref1[3]);
  EXPECT_EQ(t6.type(), kVarReal);
  EXPECT_EQ(t6.count(), 1);
  EXPECT_DOUBLE_EQ(t6.D()[0], 1.1);
  Tuple t7(ref1[3], 10);
  EXPECT_EQ(t7.type(), kVarReal);
  EXPECT_EQ(t7.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t7.D()[i], 1.1);
  }
}

TEST(Tuple, CopyConstructor) {
  Tuple t0(1);
  Tuple t1(t0);
  EXPECT_EQ(t1.type(), kVarInteger);
  EXPECT_EQ(t1.count(), 1);
  EXPECT_EQ(t1.I()[0], 1);

  Tuple t2(1, 10);
  Tuple t3(t2);
  EXPECT_EQ(t3.type(), kVarInteger);
  EXPECT_EQ(t3.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_EQ(t3.I()[i], 1);
  }

  Tuple t4(1.1);
  Tuple t5(t4);
  EXPECT_EQ(t5.type(), kVarReal);
  EXPECT_EQ(t5.count(), 1);
  EXPECT_DOUBLE_EQ(t5.D()[0], 1.1);

  Tuple t6(1.1, 10);
  Tuple t7(t6);
  EXPECT_EQ(t7.type(), kVarReal);
  EXPECT_EQ(t7.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t7.D()[i], 1.1);
  }

  Tuple t8("a");
  Tuple t9(t8);
  EXPECT_EQ(t9.type(), kVarString);
  EXPECT_EQ(t9.count(), 1);
  EXPECT_EQ(t9.S()[0], "a");

  Tuple t10("a", 10);
  Tuple t11(t10);
  EXPECT_EQ(t11.type(), kVarString);
  EXPECT_EQ(t11.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_EQ(t11.S()[i], "a");
  }

  Tuple t12("a", 10);
  t12.Set(1, 2);
  t12.Set(1.1, 3);
  Tuple t13(t12);
  EXPECT_EQ(t13.type(), kVarMixed);
  EXPECT_EQ(t13.count(), 10);
  EXPECT_EQ(t13.V()[0].S(), "a");
  EXPECT_EQ(t13.V()[1].S(), "a");
  EXPECT_EQ(t13.V()[2].I(), 1);
  EXPECT_DOUBLE_EQ(t13.V()[3].D(), 1.1);
  for (Integer i = 4; i < 10; ++i) {
    EXPECT_EQ(t13.V()[i].S(), "a");
  }
}

TEST(Tuple, Assignment) {
  Tuple t0;

  t0 = 1;
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.I()[0], 1);

  t0 = 1.1;
  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_DOUBLE_EQ(t0.D()[0], 1.1);

  t0 = "a";
  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.S()[0], "a");

  Var var(1);

  t0 = var;
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.I()[0], 1);

  var = 1.1;
  t0 = var;
  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_DOUBLE_EQ(t0.D()[0], 1.1);

  var = "a";
  t0 = var;
  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.S()[0], "a");

  Tuple t1(1, 3);
  t1.Set(1.1, 1);
  t1.Set("a", 2);

  t0 = t1[0];
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.I()[0], 1);

  t0 = t1[1];
  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_DOUBLE_EQ(t0.D()[0], 1.1);

  t0 = t1[2];
  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.S()[0], "a");

  t0 = t1;
  EXPECT_EQ(t0.type(), kVarMixed);
  EXPECT_EQ(t0.count(), 3);
  EXPECT_EQ(t0.V()[0].I(), 1);
  EXPECT_DOUBLE_EQ(t0.V()[1].D(), 1.1);
  EXPECT_EQ(t0.V()[2].S(), "a");

  Tuple t2(1, 10);
  t0 = t2;
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_EQ(t0.I()[0], 1);
  }

  Tuple t3(1.1, 10);
  t0 = t3;
  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t0.D()[i], 1.1);
  }

  Tuple t4("a", 10);
  t0 = t4;
  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_EQ(t0.S()[i], "a");
  }
}

TEST(Tuple, ArraySubscriptOperator) {
  Tuple t0(1, 3);
  t0.Set(1.1, 1);
  t0.Set("a", 2);

  VarRef r0 = t0[0];
  VarRef r1 = t0[1];
  VarRef r2 = t0[2];

  EXPECT_EQ(r0.type, kVarInteger);
  EXPECT_EQ(r0.I(), 1);
  EXPECT_EQ(r1.type, kVarReal);
  EXPECT_DOUBLE_EQ(r1.D(), 1.1);
  EXPECT_EQ(r2.type, kVarString);
  EXPECT_EQ(r2.S(), "a");

  r0 = 2;
  EXPECT_EQ(r0.type, kVarInteger);
  EXPECT_EQ(r0.I(), 2);
  EXPECT_EQ(t0.V()[0].I(), 2);
  r0 = 2.2;
  EXPECT_EQ(r0.type, kVarReal);
  EXPECT_DOUBLE_EQ(r0.D(), 2.2);
  EXPECT_DOUBLE_EQ(t0.V()[0].D(), 2.2);

  r1 = 3.3;
  EXPECT_EQ(r1.type, kVarReal);
  EXPECT_DOUBLE_EQ(r1.D(), 3.3);
  EXPECT_DOUBLE_EQ(t0.V()[1].D(), 3.3);
  r1 = 3;
  EXPECT_EQ(r1.type, kVarInteger);
  EXPECT_EQ(r1.I(), 3);
  EXPECT_EQ(t0.V()[1].I(), 3);

  r2 = "b";
  EXPECT_EQ(r2.type, kVarString);
  EXPECT_EQ(r2.S(), "b");
  EXPECT_EQ(t0.V()[2].S(), "b");
  r2 = 4;
  EXPECT_EQ(r2.type, kVarInteger);
  EXPECT_EQ(r2.I(), 4);
  EXPECT_EQ(t0.V()[2].I(), 4);
}

TEST(Tuple, SetInteger) {
  Tuple t0(0, 10);
  for (Integer i = 0; i < 10; ++i) {
    t0.Set(i, i);
  }

  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_EQ(t0.I()[i], i);
  }

  Tuple t1(1.1, 10);
  t1.Set(1);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_EQ(t1.V()[0].I(), 1);
  t1.Set(2, 1);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_EQ(t1.V()[1].I(), 2);
  for (Integer i = 2; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t1.V()[i].D(), 1.1);
  }

  Tuple t2("a", 10);
  t2.Set(1);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_EQ(t2.V()[0].I(), 1);
  t2.Set(2, 1);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_EQ(t2.V()[1].I(), 2);
  for (Integer i = 2; i < 10; i++) {
    EXPECT_EQ(t2.V()[i].S(), "a");
  }
}

TEST(Tuple, SetReal) {
  Tuple t0(0.0, 10);
  for (Integer i = 0; i < 10; ++i) {
    t0.Set(1.1 * i, i);
  }

  EXPECT_EQ(t0.type(), kVarReal);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t0.D()[i], 1.1 * i);
  }

  Tuple t1(1, 10);
  t1.Set(1.1);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_DOUBLE_EQ(t1.V()[0].D(), 1.1);
  t1.Set(2.2, 1);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_DOUBLE_EQ(t1.V()[1].D(), 2.2);
  for (Integer i = 2; i < 10; i++) {
    EXPECT_EQ(t1.V()[i].I(), 1);
  }

  Tuple t2("a", 10);
  t2.Set(1.1);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_DOUBLE_EQ(t2.V()[0].D(), 1.1);
  t2.Set(2.2, 1);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_DOUBLE_EQ(t2.V()[1].D(), 2.2);
  for (Integer i = 2; i < 10; i++) {
    EXPECT_EQ(t2.V()[i].S(), "a");
  }
}

TEST(Tuple, SetString) {
  Tuple t0("", 10);
  for (Integer i = 0; i < 10; ++i) {
    char c = 'a' + i;
    String s(1, c);
    t0.Set(s, i);
  }

  EXPECT_EQ(t0.type(), kVarString);
  EXPECT_EQ(t0.count(), 10);
  for (Integer i = 0; i < 10; i++) {
    char c = 'a' + i;
    String s(1, c);
    EXPECT_EQ(t0.S()[i], s);
  }

  Tuple t1(1.1, 10);
  t1.Set("a");
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_EQ(t1.V()[0].S(), "a");
  t1.Set("b", 1);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1.count(), 10);
  EXPECT_EQ(t1.V()[1].S(), "b");
  for (Integer i = 2; i < 10; i++) {
    EXPECT_DOUBLE_EQ(t1.V()[i].D(), 1.1);
  }

  Tuple t2(1, 10);
  t2.Set("a");
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_EQ(t2.V()[0].S(), "a");
  t2.Set("b", 1);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2.count(), 10);
  EXPECT_EQ(t2.V()[1].S(), "b");
  for (Integer i = 2; i < 10; i++) {
    EXPECT_EQ(t2.V()[i].I(), 1);
  }
}

TEST(Tuple, Append) {
  Tuple t0;
  t0.Append(1);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[0].I(), 1);
  t0.Append(2);
  EXPECT_EQ(t0.count(), 2);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[1].I(), 2);
  t0.Append(1.2);
  EXPECT_EQ(t0.count(), 3);
  EXPECT_EQ(t0.type(), kVarMixed);
  EXPECT_DOUBLE_EQ(t0[2].D(), 1.2);

  Tuple t1;
  t1.Append(1);
  t1.Append(2);
  t1.Append("a");
  EXPECT_EQ(t1.count(), 3);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1[2].S(), "a");
  t1.Append(1.1);
  EXPECT_EQ(t1.count(), 4);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_DOUBLE_EQ(t1[3].D(), 1.1);
  t1.Append(3);
  EXPECT_EQ(t1.count(), 5);
  EXPECT_EQ(t1.type(), kVarMixed);
  EXPECT_EQ(t1[4].I(), 3);


  Tuple t2;
  t2.Append(1.1);
  EXPECT_EQ(t2.count(), 1);
  EXPECT_EQ(t2.type(), kVarReal);
  EXPECT_DOUBLE_EQ(t2[0].D(), 1.1);
  t2.Append(2.2);
  EXPECT_EQ(t2.count(), 2);
  EXPECT_EQ(t2.type(), kVarReal);
  EXPECT_DOUBLE_EQ(t2[1].D(), 2.2);
  t2.Append(3);
  EXPECT_EQ(t2.count(), 3);
  EXPECT_EQ(t2.type(), kVarMixed);
  EXPECT_EQ(t2[2].I(), 3);

  Tuple t3;
  t3.Append(1.1);
  t3.Append(2.2);
  t3.Append("a");
  EXPECT_EQ(t3.count(), 3);
  EXPECT_EQ(t3.type(), kVarMixed);
  EXPECT_EQ(t3[2].S(), "a");
  t3.Append(3);
  EXPECT_EQ(t3.count(), 4);
  EXPECT_EQ(t3.type(), kVarMixed);
  EXPECT_EQ(t3[3].I(), 3);
  t3.Append(3.3);
  EXPECT_EQ(t3.count(), 5);
  EXPECT_EQ(t3.type(), kVarMixed);
  EXPECT_DOUBLE_EQ(t3[4].D(), 3.3);

  Tuple t4;
  t4.Append("a");
  EXPECT_EQ(t4.count(), 1);
  EXPECT_EQ(t4.type(), kVarString);
  EXPECT_EQ(t4[0].S(), "a");
  t4.Append("b");
  EXPECT_EQ(t4.count(), 2);
  EXPECT_EQ(t4.type(), kVarString);
  EXPECT_EQ(t4[1].S(), "b");
  t4.Append(1);
  EXPECT_EQ(t4.count(), 3);
  EXPECT_EQ(t4.type(), kVarMixed);
  EXPECT_EQ(t4[2].I(), 1);

  Tuple t5;
  t5.Append("a");
  t5.Append("b");
  t5.Append(1.1);
  EXPECT_EQ(t5.count(), 3);
  EXPECT_EQ(t5.type(), kVarMixed);
  EXPECT_DOUBLE_EQ(t5[2].D(), 1.1);
  t5.Append(1);
  EXPECT_EQ(t5.count(), 4);
  EXPECT_EQ(t5.type(), kVarMixed);
  EXPECT_EQ(t5[3].I(), 1);
  t5.Append("c");
  EXPECT_EQ(t5.count(), 5);
  EXPECT_EQ(t5.type(), kVarMixed);
  EXPECT_EQ(t5[4].S(), "c");
}

TEST(Tuple, Insert) {
  // 0
  Tuple t0;
  t0.Insert(0, 0);
  EXPECT_EQ(t0.count(), 1);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[0].I(), 0);
  t0.Insert(1, 0);
  EXPECT_EQ(t0.count(), 2);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[0].I(), 1);
  EXPECT_EQ(t0[1].I(), 0);
  t0.Insert(2, 1);
  EXPECT_EQ(t0.count(), 3);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[0].I(), 1);
  EXPECT_EQ(t0[1].I(), 2);
  EXPECT_EQ(t0[2].I(), 0);
  t0.Insert(3, 3);
  EXPECT_EQ(t0.count(), 4);
  EXPECT_EQ(t0.type(), kVarInteger);
  EXPECT_EQ(t0[0].I(), 1);
  EXPECT_EQ(t0[1].I(), 2);
  EXPECT_EQ(t0[2].I(), 0);
  EXPECT_EQ(t0[3].I(), 3);

  Tuple t1;
  t1.Insert(1.1, 0);
  EXPECT_EQ(t1.count(), 1);
  EXPECT_EQ(t1.type(), kVarReal);
  EXPECT_DOUBLE_EQ(t1[0].D(), 1.1);
  t1.Insert(2.2, 0);
  EXPECT_EQ(t1.count(), 2);
  EXPECT_EQ(t1.type(), kVarReal);
  EXPECT_DOUBLE_EQ(t1[0].D(), 2.2);
  EXPECT_DOUBLE_EQ(t1[1].D(), 1.1);
  t1.Insert(3.3, 1);
  EXPECT_EQ(t1.count(), 3);
  EXPECT_EQ(t1.type(), kVarReal);
  EXPECT_DOUBLE_EQ(t1[0].D(), 2.2);
  EXPECT_DOUBLE_EQ(t1[1].D(), 3.3);
  EXPECT_DOUBLE_EQ(t1[2].D(), 1.1);
  t1.Insert(4.4, 3);
  EXPECT_EQ(t1.type(), kVarReal);
  EXPECT_EQ(t1.count(), 4);
  EXPECT_DOUBLE_EQ(t1[0].D(), 2.2);
  EXPECT_DOUBLE_EQ(t1[1].D(), 3.3);
  EXPECT_DOUBLE_EQ(t1[2].D(), 1.1);
  EXPECT_DOUBLE_EQ(t1[3].D(), 4.4);

  Tuple t2;
  t2.Insert("a", 0);
  EXPECT_EQ(t2.count(), 1);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2[0].S(), "a");
  t2.Insert("b", 0);
  EXPECT_EQ(t2.count(), 2);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2[0].S(), "b");
  EXPECT_EQ(t2[1].S(), "a");
  t2.Insert("c", 1);
  EXPECT_EQ(t2.count(), 3);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2[0].S(), "b");
  EXPECT_EQ(t2[1].S(), "c");
  EXPECT_EQ(t2[2].S(), "a");
  t2.Insert("d", 3);
  EXPECT_EQ(t2.count(), 4);
  EXPECT_EQ(t2.type(), kVarString);
  EXPECT_EQ(t2[0].S(), "b");
  EXPECT_EQ(t2[1].S(), "c");
  EXPECT_EQ(t2[2].S(), "a");
  EXPECT_EQ(t2[3].S(), "d");

  //
  Tuple t3(1, 10);
  t3.Insert(2, 5);
  EXPECT_EQ(t3.count(), 11);
  EXPECT_EQ(t3.type(), kVarInteger);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_EQ(t3[i].I(), 2);
    } else {
      EXPECT_EQ(t3[i].I(), 1);
    }
  }
  t3.Insert(1.1, 5);
  EXPECT_EQ(t3.count(), 12);
  EXPECT_EQ(t3.type(), kVarMixed);
  for (Integer i = 0; i < 12; ++i) {
    if (i == 5) {
      EXPECT_DOUBLE_EQ(t3[i].D(), 1.1);
    } else if (i == 6) {
      EXPECT_EQ(t3[i].I(), 2);
    } else {
      EXPECT_EQ(t3[i].I(), 1);
    }
  }

  Tuple t4(1, 10);
  t4.Insert("a", 5);
  EXPECT_EQ(t4.count(), 11);
  EXPECT_EQ(t4.type(), kVarMixed);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_EQ(t4[i].S(), "a");
    } else {
      EXPECT_EQ(t4[i].I(), 1);
    }
  }
  t4.Insert(1.1, 5);
  EXPECT_EQ(t4.count(), 12);
  EXPECT_EQ(t4.type(), kVarMixed);
  for (Integer i = 0; i < 12; ++i) {
    if (i == 5) {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1);
    } else if (i == 6) {
      EXPECT_EQ(t4[i].S(), "a");
    } else {
      EXPECT_EQ(t4[i].I(), 1);
    }
  }

  Tuple t5(1.1, 10);
  t5.Insert(2.2, 5);
  EXPECT_EQ(t5.count(), 11);
  EXPECT_EQ(t5.type(), kVarReal);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_DOUBLE_EQ(t5[i].D(), 2.2);
    } else {
      EXPECT_DOUBLE_EQ(t5[i].D(), 1.1);
    }
  }
  t5.Insert(1, 5);
  EXPECT_EQ(t5.count(), 12);
  EXPECT_EQ(t5.type(), kVarMixed);
  for (Integer i = 0; i < 12; ++i) {
    if (i == 5) {
      EXPECT_EQ(t5[i].I(), 1);
    } else if (i == 6) {
      EXPECT_DOUBLE_EQ(t5[i].D(), 2.2);
    } else {
      EXPECT_DOUBLE_EQ(t5[i].D(), 1.1);
    }
  }

  Tuple t6(1.1, 10);
  t6.Insert("a", 5);
  EXPECT_EQ(t6.count(), 11);
  EXPECT_EQ(t6.type(), kVarMixed);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_EQ(t6[i].S(), "a");
    } else {
      EXPECT_DOUBLE_EQ(t6[i].D(), 1.1);
    }
  }
  t6.Insert(1, 10);
  EXPECT_EQ(t6.count(), 12);
  EXPECT_EQ(t6.type(), kVarMixed);
  for (Integer i = 0; i < 12; ++i) {
    if (i == 5) {
      EXPECT_EQ(t6[i].S(), "a");
    } else if (i == 10) {
      EXPECT_EQ(t6[i].I(), 1);
    } else {
      EXPECT_DOUBLE_EQ(t6[i].D(), 1.1);
    }
  }

  Tuple t7("a", 10);
  t7.Insert("b", 5);
  EXPECT_EQ(t7.count(), 11);
  EXPECT_EQ(t7.type(), kVarString);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_EQ(t7[i].S(), "b");
    } else {
      EXPECT_EQ(t7[i].S(), "a");
    }
  }
  t7.Insert(1, 5);
  EXPECT_EQ(t7.count(), 12);
  EXPECT_EQ(t7.type(), kVarMixed);
  for (Integer i = 0; i < 12; ++i) {
    if (i == 5) {
      EXPECT_EQ(t7[i].I(), 1);
    } else if (i == 6) {
      EXPECT_EQ(t7[i].S(), "b");
    } else {
      EXPECT_EQ(t7[i].S(), "a");
    }
  }

  Tuple t8("a", 10);
  t8.Insert(1.1, 5);
  EXPECT_EQ(t8.count(), 11);
  EXPECT_EQ(t8.type(), kVarMixed);
  for (Integer i = 0; i < 11; ++i) {
    if (i == 5) {
      EXPECT_DOUBLE_EQ(t8[i].D(), 1.1);
    } else {
      EXPECT_EQ(t8[i].S(), "a");
    }
  }
}

TEST(Tuple, Erase) {
  Tuple t0(1);
  t0.Erase(0);
  EXPECT_EQ(t0.type(), kVarUndef);
  EXPECT_EQ(t0.count(), 0);

  Tuple t1(1.1);
  t1.Erase(0);
  EXPECT_EQ(t1.type(), kVarUndef);
  EXPECT_EQ(t1.count(), 0);

  Tuple t2("a");
  t2.Erase(0);
  EXPECT_EQ(t2.type(), kVarUndef);
  EXPECT_EQ(t2.count(), 0);

  Tuple t3(1, 10);
  for (Integer i = 0; i < 10; ++i) {
    t3[i] = i;
  }
  // 0,1,2,3,4,5,6,7,8,9
  t3.Erase(5);
  // 0,1,2,3,4,6,7,8,9
  EXPECT_EQ(t3.count(), 9);
  EXPECT_EQ(t3.type(), kVarInteger);
  for (Integer i = 0; i < 9; ++i) {
    if (i < 5) {
      EXPECT_EQ(t3[i].I(), i);
    } else {
      EXPECT_EQ(t3[i].I(), i + 1);
    }
  }
  t3.Erase(0);
  // 1,2,3,4,6,7,8,9
  EXPECT_EQ(t3.count(), 8);
  EXPECT_EQ(t3.type(), kVarInteger);
  for (Integer i = 0; i < 8; ++i) {
    if (i < 4) {
      EXPECT_EQ(t3[i].I(), i + 1);
    } else {
      EXPECT_EQ(t3[i].I(), i + 2);
    }
  }
  t3.Erase(7);
  // 1,2,3,4,6,7,8
  EXPECT_EQ(t3.count(), 7);
  EXPECT_EQ(t3.type(), kVarInteger);
  for (Integer i = 0; i < 7; ++i) {
    if (i < 4) {
      EXPECT_EQ(t3[i].I(), i + 1);
    } else {
      EXPECT_EQ(t3[i].I(), i + 2);
    }
  }

  Tuple t4(1.1, 10);
  for (Integer i = 0; i < 10; ++i) {
    t4[i] = i * 1.1;
  }
  // 0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9
  t4.Erase(5);
  // 0.0, 1.1, 2.2, 3.3, 4.4, 6.6, 7.7, 8.8, 9.9
  EXPECT_EQ(t4.count(), 9);
  EXPECT_EQ(t4.type(), kVarReal);
  for (Integer i = 0; i < 9; ++i) {
    if (i < 5) {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * i);
    } else {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * (i + 1));
    }
  }
  t4.Erase(0);
  // 1.1, 2.2, 3.3, 4.4, 6.6, 7.7, 8.8, 9.9
  EXPECT_EQ(t4.count(), 8);
  EXPECT_EQ(t4.type(), kVarReal);
  for (Integer i = 0; i < 8; ++i) {
    if (i < 4) {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * (i + 1));
    } else {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * (i + 2));
    }
  }
  t4.Erase(7);
  // 1.1, 2.2, 3.3, 4.4, 6.6, 7.7, 8.8
  EXPECT_EQ(t4.count(), 7);
  EXPECT_EQ(t4.type(), kVarReal);
  for (Integer i = 0; i < 7; ++i) {
    if (i < 4) {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * (i + 1));
    } else {
      EXPECT_DOUBLE_EQ(t4[i].D(), 1.1 * (i + 2));
    }
  }

  Tuple t5("a", 4);
  t5[1] = "b";
  t5[2] = "c";
  t5[3] = "d";
  t5.Erase(1);
  EXPECT_EQ(t5.count(), 3);
  EXPECT_EQ(t5.type(), kVarString);
  EXPECT_EQ(t5[0].S(), "a");
  EXPECT_EQ(t5[1].S(), "c");
  EXPECT_EQ(t5[2].S(), "d");
  t5.Erase(0);
  EXPECT_EQ(t5.count(), 2);
  EXPECT_EQ(t5.type(), kVarString);
  EXPECT_EQ(t5[0].S(), "c");
  EXPECT_EQ(t5[1].S(), "d");
  t5.Erase(1);
  EXPECT_EQ(t5.count(), 1);
  EXPECT_EQ(t5.type(), kVarString);
  EXPECT_EQ(t5[0].S(), "c");

  Tuple t6(1, 5);
  for (Integer i = 0; i < 5; ++i) {
    t6[i] = i;
  }
  t6[3] = "a";
  EXPECT_EQ(t6.type(), kVarMixed);
  t6.Erase(2);
  EXPECT_EQ(t6.count(), 4);
  EXPECT_EQ(t6.type(), kVarMixed);
  EXPECT_EQ(t6[0].I(), 0);
  EXPECT_EQ(t6[1].I(), 1);
  EXPECT_EQ(t6[2].S(), "a");
  EXPECT_EQ(t6[3].I(), 4);
}
