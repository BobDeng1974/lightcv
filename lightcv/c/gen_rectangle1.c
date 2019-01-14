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
#include "lightcv/c/gen_rectangle1.h"
#include "lightcv/c/gen_rectangle1.hpp"

Integer gen_rectangle1(Obj *rectangle, Tup row1, Tup col1, Tup row2, Tup col2) {
  Integer e = gen_rectangle1_cpp(rectangle, row1, col1, row2, col2);
  return e;
}

