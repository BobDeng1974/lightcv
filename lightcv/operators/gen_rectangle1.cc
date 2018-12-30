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
#include "lightcv/operators/gen_rectangle1.h"

#include <cmath>
#include <opencv2/opencv.hpp>

#include "lightcv/type/data.h"

namespace lightcv {

GenRectangle1Operator::GenRectangle1Operator() {
}

GenRectangle1Operator::~GenRectangle1Operator() {
}

String GenRectangle1Operator::GetDisplayName() const {
  return "gen_rectangle1";
}

String GenRectangle1Operator::GetName() const {
  return "gen_rectangle1";
}

Error GenRectangle1Operator::VerifyInputs() const {
  // not empty
  if (in_tups_[0].get().count() == 0) {
    return Error::kWIPN1;
  }

  // have same count of number
  if (in_tups_[0].get().count() != in_tups_[1].get().count()) {
    return Error::kWIPN2;
  }
  if (in_tups_[1].get().count() != in_tups_[2].get().count()) {
    return Error::kWIPN3;
  }
  if (in_tups_[2].get().count() != in_tups_[3].get().count()) {
    return Error::kWIPN4;
  }

  for (Integer j = 0; j < in_tups_[0].get().count(); ++j) {
    // must be Integer or Real
    for (int i = 0; i < 4; ++i) {
      VarType type = in_tups_[i].get()[j].type;
      if (type != kVarInteger && type != kVarReal) {
        return static_cast<Error>(static_cast<int>(Error::kWIPT1) + i);
      }
    }

    // top row < bottom row
    if (in_tups_[0].get()[j].D() > in_tups_[2].get()[j].D()) {
      return Error::kWIPV3;
    }

    // left col < right col
    if (in_tups_[1].get()[j].D() > in_tups_[3].get()[j].D()) {
      return Error::kWIPV4;
    }
  }

  return Error::kTrue;
}

Error GenRectangle1Operator::Execute() {
  Integer count = in_tups_[0].get().count();
  std::vector<Ref> regions;
  regions.reserve(count);

  for (Integer i = 0; i < in_tups_[0].get().count(); ++i) {
    Integer top = static_cast<Integer>(std::round(in_tups_[0].get()[i].D()));
    Integer left = static_cast<Integer>(std::round(in_tups_[1].get()[i].D()));
    Integer bottom = static_cast<Integer>(std::round(in_tups_[2].get()[i].D()));
    Integer right = static_cast<Integer>(std::round(in_tups_[3].get()[i].D()));

    Integer rows = bottom - top + 1;
    Region *region = new Region;
    region->runs.resize(rows);
    for (Integer j = 0; j < rows; ++j) {
      region->runs[j].l = top + j;
      region->runs[j].cb = left;
      region->runs[j].ce = right;
    }

    region->features.shape = kRegionRectangle1;
    region->features.def.single.shape = 1;
    region->features.is_convex = true;
    region->features.def.single.is_convex = 1;
    region->features.is_filled = true;
    region->features.def.single.is_filled = 1;
    region->features.is_connected8 = true;
    region->features.def.single.is_connected8 = 1;
    region->features.row1 = top;
    region->features.col1 = left;
    region->features.row2 = bottom;
    region->features.col2 = right;
    region->features.def.single.smallest_rectangle1 = 1;

    Ref obj = CreateObject(region);
    regions.push_back(obj);
  }

  if (count == 1) {
    *out_objs_[0] = regions[0];
  } else {
    ObjectTuple *t = new ObjectTuple;
    for (Integer i = 0; i < count; ++i) {
      t->objs.push_back(regions[i]);
    }

    *out_objs_[0] = CreateObject(t);
  }

  return Error::kTrue;
}

}  // namespace lightcv

