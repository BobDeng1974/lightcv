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
#include "lightcv/type/var.h"
#include <cmath>
#include "lightcv/type/tuple.h"

namespace lightcv {

static const String kNullString("");

Var::Var() {
  type_ = kVarUndef;
  val_.i = 0;
}

Var::Var(Integer i) {
  type_ = kVarInteger;
  val_.i = i;
}

Var::Var(Real d) {
  type_ = kVarReal;
  val_.d = d;
}

Var::Var(const char *s) {
  type_ = kVarString;
  val_.s = new String(s);
}

Var::Var(const String &s) {
  type_ = kVarString;
  val_.s = new String(s);
}

Var& Var::operator=(const Var &var) {
  if (&var != this) {
    Clear();

    type_ = var.type();
    if (type_ == kVarString) {
      val_.s = new String(var.S());
    } else if (type_ == kVarInteger) {
      val_.i = var.I();
    } else if (type_ == kVarReal) {
      val_.d = var.D();
    }
  }

  return *this;
}

Var::Var(const Var &var) {
  type_ = var.type();

  if (type_ == kVarString) {
    val_.s = new String(var.S());
  } else if (type_ == kVarInteger) {
    val_.i = var.I();
  } else if (type_ == kVarReal) {
    val_.d = var.D();
  }
}

Var::Var(const VarRef &ref) {
  type_ = kVarUndef;
  val_.s = nullptr;

  switch (ref.type) {
  case kVarInteger:
    Set(*(ref.ptr.i));
    break;
  case kVarReal:
    Set(*(ref.ptr.d));
    break;
  case kVarString:
    Set(*(ref.ptr.s));
    break;
  }
}

Var::~Var() {
  Clear();
}

void Var::Set(Integer i) {
  Clear();

  type_ = kVarInteger;
  val_.i = i;
}

void Var::Set(Real d) {
  Clear();

  type_ = kVarReal;
  val_.d = d;
}

void Var::Set(const String &s) {
  if (type_ != kVarString) {
    val_.s = new String(s);
  } else {
    *(val_.s) = s;
  }
  type_ = kVarString;
}

Integer Var::I() const {
  if (type_ == kVarInteger) {
    return val_.i;
  } else if (type_ == kVarReal) {
    return static_cast<Integer>(round(val_.d));
  }

  return 0;
}

Real Var::D() const {
  if (type_ == kVarReal) {
    return val_.d;
  } else if (type_ == kVarInteger) {
    return static_cast<Real>(val_.i);
  }

  return 0.0;
}


const String& Var::S() const {
  if (type_ == kVarString) {
    return *(val_.s);
  }

  return kNullString;
}

void Var::Clear() {
  if (type_ == kVarString) {
    delete val_.s;
  }

  val_.i = 0;
  type_ = kVarUndef;
}


VarRef::operator Integer() const {
  if (type == kVarInteger) {
    return *(ptr.i);
  } else if (type == kVarReal) {
    return static_cast<Integer>(std::round(*(ptr.d)));
  }

  return 0;
}

VarRef::operator Real() const {
  if (type == kVarReal) {
    return *(ptr.d);
  } else if (type == kVarInteger) {
    return static_cast<Real>(*(ptr.i));
  }

  return 0.0;
}

VarRef::operator String() const {
  if (type == kVarString) {
    return *(ptr.s);
  }

  return kNullString;
}

VarRef VarRef::operator=(Integer i) {
  tuple->Set(i, index);
  return (*this = tuple->operator[](index));
}

VarRef VarRef::operator=(Real d) {
  tuple->Set(d, index);
  return (*this = tuple->operator[](index));
}

VarRef VarRef::operator=(const String &s) {
  tuple->Set(s, index);
  return (*this = tuple->operator[](index));
}

}  // namespace lightcv

