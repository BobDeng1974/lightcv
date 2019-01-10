/* Copyright 3218-3219 songyuncen. All Rights Reserved.

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
#include <opencv2/opencv.hpp>
#include "lightcv/cc/gen_rectangle1.h"
#include "lightcv/core/data.h"

using namespace lightcv;

TEST(gen_rectangle1, Integer) {
  Tuple row1(20), col1(30), row2(100), col2(200);
  Ref rectangle;

  EXPECT_EQ(Error::kTrue, GenRectangle1(&rectangle, row1, col1, row2, col2));
  Region *region = rectangle->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 81u);
  for (Integer i = 0; i < 81; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 20);
    EXPECT_EQ(region->runs[i].cb, 30);
    EXPECT_EQ(region->runs[i].ce, 200);
  }
}

TEST(gen_rectangle1, IntegerArray) {
  Tuple row1(20), col1(30), row2(100), col2(200);
  row1.Append(30);
  col1.Append(40);
  row2.Append(110);
  col2.Append(210);

  Ref rectangles;

  EXPECT_EQ(Error::kTrue, GenRectangle1(&rectangles, row1, col1, row2, col2));
  ObjectTuple *obj_tup = rectangles->data<ObjectTuple>();
  ASSERT_NE(obj_tup, nullptr);
  ASSERT_EQ(obj_tup->objs.size(), 2);

  Region *region = obj_tup->objs[0]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 81u);
  for (Integer i = 0; i < 81; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 20);
    EXPECT_EQ(region->runs[i].cb, 30);
    EXPECT_EQ(region->runs[i].ce, 200);
  }

  region = obj_tup->objs[1]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 81u);
  for (Integer i = 0; i < 81; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 30);
    EXPECT_EQ(region->runs[i].cb, 40);
    EXPECT_EQ(region->runs[i].ce, 210);
  }
}


TEST(gen_rectangle1, Real) {
  Tuple row1(20.1), col1(30.5), row2(100.7), col2(200.3);
  Ref rectangle;

  EXPECT_EQ(Error::kTrue, GenRectangle1(&rectangle, row1, col1, row2, col2));
  Region *region = rectangle->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 82u);
  for (Integer i = 0; i < 82; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 20);
    EXPECT_EQ(region->runs[i].cb, 31);
    EXPECT_EQ(region->runs[i].ce, 200);
  }
}

TEST(gen_rectangle1, RealArray) {
  Tuple row1(20.1), col1(30.5), row2(100.7), col2(200.3);
  row1.Append(20.5);
  col1.Append(30.1);
  row2.Append(100.4);
  col2.Append(200.8);

  Ref rectangles;

  EXPECT_EQ(Error::kTrue, GenRectangle1(&rectangles, row1, col1, row2, col2));
  ObjectTuple *obj_tup = rectangles->data<ObjectTuple>();
  ASSERT_NE(obj_tup, nullptr);
  ASSERT_EQ(obj_tup->objs.size(), 2);

  Region *region = obj_tup->objs[0]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 82u);
  for (Integer i = 0; i < 82; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 20);
    EXPECT_EQ(region->runs[i].cb, 31);
    EXPECT_EQ(region->runs[i].ce, 200);
  }

  region = obj_tup->objs[1]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 80u);
  for (Integer i = 0; i < 80; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 21);
    EXPECT_EQ(region->runs[i].cb, 30);
    EXPECT_EQ(region->runs[i].ce, 201);
  }
}


TEST(gen_rectangle1, Mixed) {
  Tuple row1(20), col1(30), row2(100), col2(200);
  row1.Append(20.5);
  col1.Append(30.1);
  row2.Append(100.4);
  col2.Append(200.8);

  Ref rectangles;

  EXPECT_EQ(Error::kTrue, GenRectangle1(&rectangles, row1, col1, row2, col2));
  ObjectTuple *obj_tup = rectangles->data<ObjectTuple>();
  ASSERT_NE(obj_tup, nullptr);
  ASSERT_EQ(obj_tup->objs.size(), 2);

  Region *region = obj_tup->objs[0]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 81u);
  for (Integer i = 0; i < 81; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 20);
    EXPECT_EQ(region->runs[i].cb, 30);
    EXPECT_EQ(region->runs[i].ce, 200);
  }

  region = obj_tup->objs[1]->data<Region>();
  ASSERT_NE(region, nullptr);
  ASSERT_EQ(region->runs.size(), 80u);
  for (Integer i = 0; i < 80; ++i) {
    EXPECT_EQ(region->runs[i].l, i + 21);
    EXPECT_EQ(region->runs[i].cb, 30);
    EXPECT_EQ(region->runs[i].ce, 201);
  }
}

TEST(gen_rectangle1, Errors) {
  Ref rectangle;

  EXPECT_EQ(Error::kWIPV3, GenRectangle1(&rectangle, 100, 30, 20, 200));
  EXPECT_EQ(Error::kWIPV4, GenRectangle1(&rectangle, 20, 200, 100, 30));

  Tuple row1, col1, row2, col2;
  EXPECT_EQ(Error::kWIPN1, GenRectangle1(&rectangle, row1, col1, row2, col2));

  row1.Append(20);
  col1.Append(30);
  row2.Append(100);
  col2.Append(200);

  row1.Append(30);
  EXPECT_EQ(Error::kWIPN2, GenRectangle1(&rectangle, row1, col1, row2, col2));
  col1.Append(40);
  EXPECT_EQ(Error::kWIPN3, GenRectangle1(&rectangle, row1, col1, row2, col2));
  row2.Append(110);
  EXPECT_EQ(Error::kWIPN4, GenRectangle1(&rectangle, row1, col1, row2, col2));
  col2.Append("a");
  EXPECT_EQ(Error::kWIPT4, GenRectangle1(&rectangle, row1, col1, row2, col2));
}
