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
#ifndef LIGHTCV_TYPE_OPERATOR_H_
#define LIGHTCV_TYPE_OPERATOR_H_

#include "lightcv/type/tuple.h"
#include "lightcv/type/object.h"

#include <vector>
#include <initializer_list>
#include <functional>

namespace lightcv {

class Operator {
 public:
  virtual ~Operator();

  size_t GetHashCode() const;

  int GetNumberOfTupInput() const {
    return static_cast<int>(in_tups_.size());
  }

  int GetNumberOfObjInput() const {
    return static_cast<int>(in_objs_.size());
  }

  int GetNumberOfTupOutput() const {
    return static_cast<int>(out_tups_.size());
  }

  int GetNumberOfObjOutput() const {
    return static_cast<int>(out_objs_.size());
  }

  void SetTupInputs(std::initializer_list<std::reference_wrapper<const Tuple>> tups);
  void SetObjInputs(std::initializer_list<Ref> objs);
  void SetTupOutputs(std::initializer_list<Tuple*> tups);
  void SetObjOutputs(std::initializer_list<Ref> objs);


  virtual String GetDisplayName() const = 0;
  virtual String GetName() const = 0;
  virtual bool VerifyInputs(String *err_msg) = 0;
  virtual int Execute(String *err_msg) = 0;

 protected:
  std::vector<Ref> in_objs_;
  std::vector<std::reference_wrapper<const Tuple>> in_tups_;
  std::vector<Ref> out_objs_;
  std::vector<Tuple*> out_tups_;
};

}  // namespace lightcv

#endif // !LIGHTCV_TYPE_OPERATOR_H_

