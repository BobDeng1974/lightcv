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
#include "lightcv/type/data.h"
#include "lightcv/type/object.h"
#include <opencv2/opencv.hpp>

using namespace lightcv;

TEST(Object, Region) {
  Region *region = new Region;
  EXPECT_EQ(region->features.def.all, 0x0);
  EXPECT_EQ(region->runs.size(), 0u);

  Ref region_obj = CreateObject(region);
  EXPECT_EQ(region_obj->type(), Object::kObjRegion);
  Region *r = region_obj->data<Region>();
  EXPECT_EQ(region, r);

  r->runs.resize(2);
  EXPECT_EQ(r->runs[0].l, 0);
  EXPECT_EQ(r->runs[0].cb, 0);
  EXPECT_EQ(r->runs[0].ce, 0);
}

TEST(Object, Image) {
  Region *region = new Region;
  cv::Mat pix(100, 100, CV_8UC1, cv::Scalar(0));
  Ref domain = CreateObject(region);
  Image *image = new Image;
  image->domain = domain;
  image->pix = pix;
  Ref image_obj = CreateObject(image);
  EXPECT_EQ(image_obj->type(), Object::kObjImage);

  Image *i = image_obj->data<Image>();
  EXPECT_EQ(i, image);
}

TEST(Object, Curve) {
  Curve *curve = new Curve;
  EXPECT_EQ(curve->curve_type, Curve::kCurveNull);
  curve->curve_type = Curve::kCurvePointList;
  curve->cps.resize(2);
  EXPECT_EQ(curve->cps[0], cv::Point2f());
  EXPECT_EQ(curve->cps[1], cv::Point2f());

  Ref obj = CreateObject(curve);
  Curve *c = obj->data<Curve>();
  EXPECT_EQ(c, curve);
}

TEST(Object, ObjectTuple) {
  Region *r = new Region;
  Ref region = CreateObject(r);

  Image *i = new Image;
  i->domain = region;
  i->pix = cv::Mat(100, 100, CV_32FC1, cv::Scalar(0.0));
  Ref image = CreateObject(i);

  Curve *c = new Curve;
  Ref curve = CreateObject(c);

  ObjectTuple *obj_tup = new ObjectTuple;
  obj_tup->objs.push_back(region);
  obj_tup->objs.push_back(image);
  obj_tup->objs.push_back(curve);
}

