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
#include "lightcv/core/object.h"
#include "lightcv/core/data.h"

namespace lightcv {

Object::Object()
  : data_(nullptr) {
}

Object::~Object() {
  if (type() != kObjNull && data_) {
    delete data_;
  }
}

Object::Type Object::type() const {
  if (data_) {
    return data_->type();
  }

  return kObjNull;
}

Ref CreateObject(Data *data) {
  Ref obj = std::make_shared<Object>();
  obj->data_ = data;
  return obj;
}

}  // namespace lightcv
