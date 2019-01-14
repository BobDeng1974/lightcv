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
#ifndef LIGHTCV_C_GEN_RECTANGLE1_HPP_
#define LIGHTCV_C_GEN_RECTANGLE1_HPP_

#ifdef __cplusplus
#include "lightcv/core/tuple.h"
#include "lightcv/core/object.h"
using namespace lightcv;
#endif  // __cplusplus


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

Integer gen_rectangle1_cpp(Ref **rectangle, Tuple *row1, Tuple *col1, Tuple *row2, Tuple *col2);

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // LIGHTCV_C_GEN_RECTANGLE1_HPP_

