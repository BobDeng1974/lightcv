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
#include "lightcv/type/tuple.h"
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

namespace lightcv {

Tuple::Tuple() {
  vec_.i = nullptr;
  type_ = kVarUndef;
  count_ = 0;
  capacity_ = 0;
}

Tuple::Tuple(Integer l, Integer cnt) {
  CV_Assert(cnt > 0);

  type_ = kVarInteger;
  count_ = cnt;
  capacity_ = cnt;
  vec_.i = new Integer[cnt];
  for (Integer i = 0; i < cnt; ++i) {
    vec_.i[i] = l;
  }
}

Tuple::Tuple(Real d, Integer cnt) {
  CV_Assert(cnt > 0);

  type_ = kVarReal;
  count_ = cnt;
  capacity_ = cnt;
  vec_.d = new Real[cnt];
  for (Integer i = 0; i < cnt; ++i) {
    vec_.d[i] = d;
  }
}

Tuple::Tuple(const char *s, Integer cnt) {
  CV_Assert(cnt > 0);

  type_ = kVarString;
  count_ = cnt;
  capacity_ = cnt;
  vec_.s = new String[cnt];
  for (Integer i = 0; i < cnt; ++i) {
    vec_.s[i] = s;
  }
}

Tuple::Tuple(const String &s, Integer cnt) {
  CV_Assert(cnt > 0);

  type_ = kVarString;
  count_ = cnt;
  capacity_ = cnt;
  vec_.s = new String[cnt];
  for (Integer i = 0; i < cnt; ++i) {
    vec_.s[i] = s;
  }
}

Tuple::Tuple(const Var &v, Integer cnt) {
  CV_Assert(cnt > 0);

  bool allocated = true;
  switch (v.type()) {
  case kVarInteger:
    vec_.i = new Integer[cnt];
    for (Integer i = 0; i < cnt; ++i) {
      vec_.i[i] = v.I();
    }
    break;
  case kVarReal:
    vec_.d = new Real[cnt];
    for (Integer i = 0; i < cnt; ++i) {
      vec_.d[i] = v.D();
    }
    break;
  case kVarString:
    vec_.s = new String[cnt];
    for (Integer i = 0; i < cnt; ++i) {
      vec_.s[i] = v.S();
    }
    break;
  default:
    allocated = false;
    break;
  }

  if (allocated) {
    type_ = v.type();
    count_ = cnt;
    capacity_ = cnt;
  } else {
    type_ = kVarUndef;
    count_ = 0;
    capacity_ = 0;
    vec_.i = nullptr;
  }
}

Tuple::Tuple(const VarRef &r, Integer cnt) : Tuple(Var(r), cnt) {
}

Tuple::Tuple(const Tuple &t) {
  type_ = t.type();
  count_ = t.count();
  capacity_ = t.capacity();

  switch (type_) {
  case kVarInteger:
    vec_.i = new Integer[capacity_];
    memcpy(vec_.i, t.I(), sizeof(Integer)* count_);
    break;
  case kVarReal:
    vec_.d = new Real[capacity_];
    memcpy(vec_.d, t.D(), sizeof(Real) * count_);
    break;
  case kVarString:
    vec_.s = new String[capacity_];
    for (Integer i = 0; i < count_; ++i) {
      vec_.s[i] = t.S()[i];
    }
    break;
  case kVarMixed:
    vec_.var = new Var[capacity_];
    for (Integer i = 0; i < count_; ++i) {
      vec_.var[i] = t.V()[i];
    }
    break;
  default:
    break;
  }
}

Tuple &Tuple::operator=(const Tuple &t) {
  if (this == &t) {
    return *this;
  }

  Reset();

  type_ = t.type();
  count_ = t.count();
  capacity_ = t.capacity();

  switch (type_) {
  case kVarInteger:
    vec_.i = new Integer[capacity_];
    memcpy(vec_.i, t.I(), sizeof(Integer) * count_);
    break;
  case kVarReal:
    vec_.d = new Real[capacity_];
    memcpy(vec_.d, t.D(), sizeof(Real) * count_);
    break;
  case kVarString:
    vec_.s = new String[capacity_];
    for (Integer i = 0; i < count_; ++i) {
      vec_.s[i] = t.S()[i];
    }
    break;
  case kVarMixed:
    vec_.var = new Var[capacity_];
    for (Integer i = 0; i < count_; ++i) {
      vec_.var[i] = t.V()[i];
    }
    break;
  default:
    break;
  }
  return *this;
}

Tuple::~Tuple() {
  ClearData();
}

void Tuple::ClearData() {
  if (capacity() != 0) {
    switch (type_) {
    case kVarInteger:
      delete[] vec_.i;
      break;
    case kVarReal:
      delete[] vec_.d;
      break;
    case kVarString:
      delete[] vec_.s;
      break;
    case kVarMixed:
      delete[] vec_.var;
      break;
    default:
      break;
    }
  }
}

void Tuple::Reset() {
  ClearData();

  vec_.i = nullptr;
  count_ = 0;
  capacity_ = 0;
  type_ = kVarUndef;
}

VarRef Tuple::operator[](Integer index) const {
  CV_Assert(index >= 0 && index < count_);

  VarRef ref;
  ref.index = index;
  ref.tuple = const_cast<Tuple*>(this);

  if (type_ != kVarMixed) {
    switch (type_) {
    case kVarInteger:
      ref.ptr.i = vec_.i + index;
      break;
    case kVarReal:
      ref.ptr.d = vec_.d + index;
      break;
    case kVarString:
      ref.ptr.s = vec_.s + index;
      break;
    default:
      break;
    }
    ref.type = type_;
  } else {
    Var *v = vec_.var + index;
    switch (v->type_) {
    case kVarInteger:
      ref.ptr.i = &(v->val_.i);
      break;
    case kVarReal:
      ref.ptr.d = &(v->val_.d);
      break;
    case kVarString:
      ref.ptr.s = v->val_.s;
      break;
    default:
      break;
    }
    ref.type = v->type_;
  }

  return ref;
}

void Tuple::Set(Integer i, Integer index) {
  CV_Assert(index >= 0 && index < count_);

  if (type_ == kVarInteger) {
    vec_.i[index] = i;
  } else {
    if (count_ == 1) {
      if (type_ == kVarReal) {
        delete[] vec_.d;
      } else if (type_ == kVarString) {
        delete[] vec_.s;
      }

      vec_.i = new Integer[1];
      vec_.i[0] = i;
      type_ = kVarInteger;
    } else {
      Real *d = nullptr;
      String *s = nullptr;
      switch (type_) {
      case kVarReal:
        d = vec_.d;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(d[i]);
        }
        delete[] d;
        break;
      case kVarString:
        s = vec_.s;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(s[i]);
        }
        delete[] s;
        break;
      default:
        break;
      }

      vec_.var[index].Set(i);
      type_ = kVarMixed;
    }
  }
}

void Tuple::Set(Real d, Integer index) {
  CV_Assert(index >= 0 && index < count_);

  if (type_ == kVarReal) {
    vec_.d[index] = d;
  } else {
    if (count_ == 1) {
      if (type_ == kVarInteger) {
        delete[] vec_.i;
      } else if (type_ == kVarString) {
        delete[] vec_.s;
      }

      vec_.d = new double[1];
      vec_.d[0] = d;
      type_ = kVarReal;
    } else {
      Integer *l = nullptr;
      String *s = nullptr;

      switch (type_) {
      case kVarInteger:
        l = vec_.i;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(l[i]);
        }
        delete[] l;
        break;
      case kVarString:
        s = vec_.s;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(s[i]);
        }
        delete[] s;
        break;
      default:
        break;
      }

      vec_.var[index].Set(d);
      type_ = kVarMixed;
    }
  }
}

void Tuple::Set(const String &s, Integer index) {
  CV_Assert(index >= 0 && index < count_);

  if (type_ == kVarString) {
    vec_.s[index] = s;
  } else {
    if (count_ == 1) {
      if (type_ == kVarInteger) {
        delete[] vec_.i;
      } else if (type_ == kVarReal) {
        delete[] vec_.d;
      }

      vec_.s = new String[1];
      vec_.s[0] = s;
      type_ = kVarString;
    } else {
      Integer *l = nullptr;
      Real *d = nullptr;

      switch (type_) {
      case kVarInteger:
        l = vec_.i;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(l[i]);
        }
        delete[] l;
        break;
      case kVarReal:
        d = vec_.d;
        vec_.var = new Var[count_];
        for (Integer i = 0; i < count_; ++i) {
          vec_.var[i].Set(d[i]);
        }
        delete[] d;
        break;
      default:
        break;
      }

      vec_.var[index].Set(s);
      type_ = kVarMixed;
    }
  }
}

void Tuple::SetVar(const Var &var, Integer index) {
  switch (var.type()) {
  case kVarInteger:
    Set(var.val_.i, index);
    break;
  case kVarReal:
    Set(var.val_.d, index);
    break;
  case kVarString:
    Set(*(var.val_.s), index);
    break;
  default:
    break;
  }
}

void Tuple::GrowUpOne(VarType type) {
  if (type_ == kVarUndef) { // capacity is also zero.
    switch (type) {
    case kVarInteger:
      vec_.i = new Integer[1];
      capacity_ = 1;
      break;
    case kVarReal:
      vec_.d = new Real[1];
      capacity_ = 1;
      break;
    case kVarString:
      vec_.s = new String[1];
      capacity_ = 1;
      break;
    default:
      break;
    }
    count_ = 0;
    type_ = type;
  } else {
    Integer c = std::max(1, capacity_ * 2);
    int targetType = type_;
    if (type_ != type) {
      targetType = kVarMixed;
    }

    VarRef buf;
    Var *bufVar;
    switch (targetType) {
    case kVarInteger:
      buf.ptr.i = new Integer[c];
      memcpy(buf.ptr.i, vec_.i, sizeof(Integer) * count_);
      delete[] vec_.i;
      vec_.i = buf.ptr.i;
      break;
    case kVarReal:
      buf.ptr.d = new Real[c];
      memcpy(buf.ptr.d, vec_.d, sizeof(Real) * count_);
      delete[] vec_.d;
      vec_.d = buf.ptr.d;
      break;
    case kVarString:
      buf.ptr.s = new String[c];
      for (Integer i = 0; i < count_; ++i) buf.ptr.s[i] = vec_.s[i];
      delete[] vec_.s;
      vec_.s = buf.ptr.s;
      break;
    case kVarMixed:
      bufVar = new Var[c];
      for (Integer i = 0; i < count_; ++i) {
        bufVar[i] = this->operator[](i);
      }
      switch (type_) {
      case kVarInteger:
        delete[] vec_.i;
        break;
      case kVarReal:
        delete[] vec_.d;
        break;
      case kVarString:
        delete[] vec_.s;
        break;
      case kVarMixed:
        delete[] vec_.var;
        break;
      default:
        break;
      }
      vec_.var = bufVar;
      type_ = kVarMixed;
      break;
    }
    capacity_ = c;
  }
}

void Tuple::Append(const Var &v) {
  if (count_ == capacity_) {
    GrowUpOne(v.type());
  }

  ++count_;
  SetVar(v, static_cast<int>(count_ - 1));
}

void Tuple::Insert(const Var &v, Integer index) {
  CV_Assert(index >= 0 && index <= count_);

  if (count_ == capacity_) {
    GrowUpOne(v.type());
  }

  size_t n = count_ - index;
  if (n > 0) {
    switch (type_) {
    case kVarInteger:
      if (count_ != 0) {
        memmove(vec_.i + index + 1, vec_.i + index, sizeof(Integer) * n);
      }
      break;
    case kVarReal:
      if (count_ != 0) {
        memmove(vec_.d + index + 1, vec_.d + index, sizeof(Real) * n);
      }
      break;
    case kVarString:
      if (count_ != 0) {
        for (Integer i = count_ - 1; i >= index; --i) {
          vec_.s[i + 1] = vec_.s[i];
        }
      }
      break;
    case kVarMixed:
      if (count_ != 0) {
        for (Integer i = count_ - 1; i >= index; --i) {
          vec_.var[i + 1] = vec_.var[i];
        }
      }
      break;
    default:
      break;
    }
    ++count_;
    SetVar(v, index);
  } else {
    Append(v);
  }
}

void Tuple::Erase(Integer index) {
  if (count_ == 0 || index < 0 || index >= count_) {
    return;
  }

  if (count_ == 1) {
    switch (type_) {
    case kVarInteger:
      delete[] vec_.i;
      break;
    case kVarReal:
      delete[] vec_.d;
      break;
    case kVarString:
      delete[] vec_.s;
      break;
    case kVarMixed:
      delete[] vec_.var;
      break;
    default:
      break;
    }
    vec_.i = nullptr;
    type_ = kVarUndef;
  } else if (index != count_ - 1) {
    Integer n = count_ - index - 1;
    switch (type_) {
    case kVarInteger:
      memmove(vec_.i + index, vec_.i + index + 1, n * sizeof(Integer));
      break;
    case kVarReal:
      memmove(vec_.d + index, vec_.d + index + 1, n * sizeof(Real));
      break;
    case kVarString:
      for (Integer i = index; i < count_ - 1; ++i) {
        vec_.s[i] = vec_.s[i + 1];
      }
      break;
    case kVarMixed:
      for (Integer i = index; i < count_ - 1; ++i) {
        vec_.var[i] = vec_.var[i + 1];
      }
      break;
    default:
      break;
    }
  }
  --count_;
}

inline Integer* Tuple::I() const {
  CV_Assert(type_ == kVarInteger);
  return vec_.i;
}

inline Real* Tuple::D() const {
  CV_Assert(type_ == kVarReal);
  return vec_.d;
}

inline String * Tuple::S() const {
  CV_Assert(type_ == kVarString);
  return vec_.s;
}

Var* Tuple::V() const {
  CV_Assert(type_ == kVarMixed);
  return vec_.var;
}


bool operator==(const VarRef &lhs, Integer rhs) {
  if (lhs.type == kVarInteger) {
    return lhs.I() == rhs;
  } else if (lhs.type == kVarReal) {
    return lhs.D() == rhs;
  }
  return false;
}

bool operator==(Integer lhs, const VarRef &rhs) {
  return operator==(rhs, lhs);
}

bool operator==(const VarRef &lhs, Real rhs) {
  if (lhs.type == kVarReal) {
    return lhs.D() == rhs;
  } else if (lhs.type == kVarInteger) {
    return lhs.I() == rhs;
  }

  return false;
}

bool operator==(Real lhs, const VarRef &rhs) {
  return operator==(rhs, lhs);
}

bool operator==(const VarRef &lhs, const String &rhs) {
  if (lhs.type == kVarString) {
    return lhs.S() == rhs;
  }

  return false;
}

bool operator==(const String &lhs, const VarRef &rhs) {
  return operator==(rhs, lhs);
}

bool operator==(const VarRef &lhs, const VarRef &rhs) {
  if (rhs.type == kVarInteger) {
    return operator==(lhs, rhs.I());
  } else if (rhs.type == kVarReal) {
    return operator==(lhs, rhs.D());
  } else if (rhs.type == kVarString) {
    return operator==(lhs, rhs.S());
  }

  return false;
}

bool operator!=(const VarRef &lhs, Integer rhs) {
  return !operator==(lhs, rhs);
}

bool operator!=(Integer lhs, const VarRef &rhs) {
  return !operator==(lhs, rhs);
}

bool operator!=(const VarRef &lhs, Real rhs) {
  return !operator==(lhs, rhs);
}

bool operator!=(const Real lhs, const VarRef &rhs) {
  return !operator==(lhs, rhs);
}
bool operator!=(const VarRef &lhs, const String &rhs) {
  return !operator==(lhs, rhs);
}

bool operator!=(const String &lhs, const VarRef &rhs) {
  return !operator==(lhs, rhs);
}

bool operator!=(const VarRef &lhs, const VarRef &rhs) {
  return !operator==(lhs, rhs);
}

bool operator<(const VarRef &lhs, Integer rhs) {
  if (lhs.type == kVarInteger) {
    return lhs.I() < rhs;
  } else if (lhs.type == kVarReal) {
    return lhs.D() < rhs;
  }

  return false;
}

bool operator<(Integer lhs, const VarRef &rhs) {
  return operator>(rhs, lhs);
}

bool operator<(const VarRef &lhs, Real rhs) {
  if (lhs.type == kVarReal) {
    return lhs.D() < rhs;
  } else if (lhs.type == kVarInteger) {
    return lhs.I() < rhs;
  }

  return false;
}

bool operator<(Real lhs, const VarRef &rhs) {
  return operator>(rhs, lhs);
}

bool operator<(const VarRef &lhs, const String &rhs) {
  if (lhs.type == kVarString) {
    return lhs.S() < rhs;
  }

  return false;
}

bool operator<(const String &lhs, const VarRef &rhs) {
  return operator>(rhs, lhs);
}

bool operator<(const VarRef &lhs, const VarRef &rhs) {
  if (rhs.type == kVarInteger) {
    return operator<(lhs, rhs.I());
  } else if (rhs.type == kVarReal) {
    return operator<(lhs, rhs.D());
  } else if (rhs.type == kVarString) {
    return operator<(lhs, rhs.S());
  }

  return false;
}

bool operator>=(const VarRef &lhs, Integer rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(Integer lhs, const VarRef &rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(const VarRef &lhs, Real rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(Real lhs, const VarRef &rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(const VarRef &lhs, const String &rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(const String &lhs, const VarRef &rhs) {
  return !operator<(lhs, rhs);
}

bool operator>=(const VarRef &lhs, const VarRef &rhs) {
  return !operator<(lhs, rhs);
}

bool operator>(const VarRef &lhs, Integer rhs) {
  if (lhs.type == kVarInteger) {
    return lhs.I() > rhs;
  } else if (lhs.type == kVarReal) {
    return lhs.D() > rhs;
  }

  return false;
}

bool operator>(Integer lhs, const VarRef &rhs) {
  return operator<(rhs, lhs);
}

bool operator>(const VarRef &lhs, Real rhs) {
  if (lhs.type == kVarReal) {
    return lhs.D() > rhs;
  } else if (lhs.type == kVarInteger) {
    return lhs.I() > rhs;
  }

  return false;
}

bool operator>(Real lhs, const VarRef &rhs) {
  return operator<(rhs, lhs);
}

bool operator>(const VarRef &lhs, const String &rhs) {
  if (lhs.type == kVarString) {
    return lhs.S() > rhs;
  }

  return false;
}

bool operator>(const String &lhs, const VarRef &rhs) {
  return operator<(rhs, lhs);
}

bool operator>(const VarRef &lhs, const VarRef &rhs) {
  if (rhs.type == kVarInteger) {
    return operator>(lhs, rhs.I());
  } else if (rhs.type == kVarReal) {
    return operator>(lhs, rhs.D());
  } else if (rhs.type == kVarString) {
    return operator>(lhs, rhs.S());
  }

  return false;
}

bool operator<=(const VarRef &lhs, Integer rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(Integer lhs, const VarRef &rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(const VarRef &lhs, Real rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(Real lhs, const VarRef &rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(const VarRef &lhs, const String &rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(const String &lhs, const VarRef &rhs) {
  return !operator>(lhs, rhs);
}

bool operator<=(const VarRef &lhs, const VarRef &rhs) {
  return !operator>(lhs, rhs);
}

}  // namespace lightcv

