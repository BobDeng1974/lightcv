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
#ifndef LIGHTCV_CC_READ_IMAGE_H_
#define LIGHTCV_CC_READ_IMAGE_H_

#include "lightcv/type/basic.h"
#include "lightcv/type/error.h"
#include "lightcv/type/tuple.h"
#include "lightcv/type/object.h"

namespace lightcv {

Error ReadImage(Ref *image, const Tuple &file_name);

}  // namespace lightcv

#endif  // LIGHTCV_CC_READ_IMAGE_H_

