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
#include "lightcv/cc/read_image.h"
#include "lightcv/operators/read_image.h"

namespace lightcv {

Error ReadImage(Ref* image, const Tuple &file_name) {
  ReadImageOperator op;
  op.SetOuptObjs({ image });
  op.SetInpTups({ file_name });

  Error err = op.VerifyInputs();
  if (err == Error::kMsgTrue) {
    return op.Execute();
  }

  return err;
}

}  // namespace lightcv
