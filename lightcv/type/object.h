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
#ifndef LIGHTCV_TYPE_OBJECT_H_
#define LIGHTCV_TYPE_OBJECT_H_

#include "lightcv/type/basic.h"
#include <memory>

namespace lightcv {

class Data;

/*! \brief Object is used as arguments of operators.
 *   
 *  Purpose
 * 
 *  - The unified types in operator function calling.
 *  - Container of Data, access data by using static type conversion.
 *  - Life time of Data is controlled by using std::shared_ptr (Object::Ref)
 *
 *  Data is used by developer of lightcv, Object is used by client of lightcv.
 */
class Object {
 public:
  enum Type {
    kObjNull,
    kObjImage,
    kObjRegion,
    kObjCurve,
    kObjTuple
  };

  typedef std::shared_ptr<Object> Ref;

  Object();
  ~Object();

  Object(const Object &) = delete;
  Object& operator=(const Object &) = delete;

  Type type() const { return type_; }
  Data *data() const { return data_; }

 private:
  friend Ref CreateObject(Type, Data*);

  Type type_;
  Data *data_;
};

Object::Ref CreateObject(Object::Type type, Data *data);

}  // namespace lightcv

#endif  // LIGHTCV_TYPE_OBJECT_H_

