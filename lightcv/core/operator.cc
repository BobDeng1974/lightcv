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
#include "lightcv/core/operator.h"

namespace lightcv {

Operator::~Operator() {
}

size_t Operator::GetHashCode() const {
  static size_t code = 0;
  if (code == 0) {
    std::hash<String> hash_fn;
    code = hash_fn(GetName());
  }

  return code;
}

void Operator::SetInpTups(std::initializer_list<std::reference_wrapper<const Tuple>> tups) {
  in_tups_ = tups;
}

void Operator::SetInpObjs(std::initializer_list<Ref> objs) {
  in_objs_ = objs;
}

void Operator::SetOutpTups(std::initializer_list<Tuple*> tups) {
  out_tups_ = tups;
}

void Operator::SetOuptObjs(std::initializer_list<Ref*> objs) {
  out_objs_ = objs;
}

}  // namespace lightcv

