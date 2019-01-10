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
#ifndef LIGHTCV_CC_GEN_RECTANGLE1_H_
#define LIGHTCV_CC_GEN_RECTANGLE1_H_

#include "lightcv/core/basic.h"
#include "lightcv/core/error.h"
#include "lightcv/core/tuple.h"
#include "lightcv/core/object.h"

namespace lightcv {

Error GenRectangle1(Ref *rectangle, const Tuple &row1, const Tuple &col1,
                                    const Tuple &row2, const Tuple &col2);

}  // namespace lightcv

#endif  // LIGHTCV_CC_GEN_RECTANGLE1_H_

