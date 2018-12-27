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
#ifndef LIGHTCV_TYPE_DATA_H_
#define LIGHTCV_TYPE_DATA_H_

#include "lightcv/type/basic.h"
#include "lightcv/type/object.h"

#include <vector>
#include <map>
#include <opencv2/core.hpp>

namespace lightcv {

class Data {
public:
  virtual ~Data() {}
  virtual Object::Type type() const { return Object::kObjNull; }
};

struct RegionHRun {
  RegionHRun() : l(0), cb(0), ce(0) {}
  Integer l;  //!< line number (row) of run
  Integer cb; //!< column index of beginning of run
  Integer ce; //!< column index of ending of run
};

struct RegionFeatureFlags {
  unsigned int shape : 1;
  unsigned int is_convex : 1;
  unsigned int is_filled : 1;
  unsigned int is_connected4 : 1;
  unsigned int is_connected8 : 1;
  unsigned int is_thin : 1;
  unsigned int circularity : 1;
  unsigned int compactness : 1;
  unsigned int contlength : 1;
  unsigned int convexity : 1;
  unsigned int phi : 1;
  unsigned int elliptic_axis : 1;       /* ra, rb                         */
  unsigned int elliptic_shape : 1;      /* ra_, rb_                       */
  unsigned int excentricity : 1;        /* anisometry,bulkiness,str_faktor*/
  unsigned int moments : 1;             /* m11, m20, m02, ia, ib          */
  unsigned int center_area : 1;         /* row, col, area                 */
  unsigned int smallest_rectangle1 : 1; /* row1,col1,row2,col2            */
  unsigned int smallest_rectangle2 : 1; /* row_rect, col_rect, phi_rect,  */
                                        /* length1, length2               */
  unsigned int smallest_circle : 1;     /* row_circle, col_circle, radius */
  unsigned int min_max_chord : 1;       /* longest/shortest run           */
  unsigned int min_max_chord_gap : 1;   /* longest/shortest run (holes)   */
  unsigned int rectangularity : 1;
};

struct RegionFeatures {
  union {
    RegionFeatureFlags single;
    long all;
  } def;

  uint8_t shape;

  bool is_convex;
  bool is_filled;
  bool is_connected4;
  bool is_connected8;
  bool is_thin; //!< one pixel thin
  long long area;
  Real circularity;
  Real compactness;
  Real contlength;
  Real convexity;
  Real rectangularity;
  Real phi;
  Real ra, rb;  //!< elliptic_axis
  Real ra_, rb_; //!< elliptic_shape
  Real anisometry, bulkiness, structure_factor;
  Real m11, m20, m02, ia, ib;
  Real row, col;
  Real row_rect, col_rect, phi_rect, length1, length2;
  Real row_circle, col_circle, radius;
  Integer row1, col1, row2, col2;
  Integer min_chord, max_chord;
  Integer min_chord_gap, max_chord_gap;
};

class Region : public Data {
 public:
  Region();
  ~Region();

  Object::Type type() const override { return Object::kObjRegion; }

  std::vector<RegionHRun> runs;
  RegionFeatures features;
};


class Image : public Data {
 public:
  Image();
  ~Image();

  Object::Type type() const override { return Object::kObjImage; }

  cv::Mat pix;
  Ref domain;
};


class Curve : public Data {
 public:
  enum CurveType {
    kCurveNull,
    kCurvePointList,
    kCurveLines
  };

  enum LocalAttributeType {
    kCurveLAttribNVAngle   //!< angle of normal vector by rad
  };

  enum GlobalAttributeType {
    kCurveGAttribApproximate  //!< approximate method
  };

  typedef std::map<LocalAttributeType, std::vector<Real>> LocalAttribute;
  typedef std::map<GlobalAttributeType, Real> GlobalAttribute;


  Curve();
  ~Curve();

  Object::Type type() const override { return Object::kObjCurve; }

  std::vector<cv::Point2f> cps;  //!< control points
  LocalAttribute local_attrib;
  GlobalAttribute global_attrib;

  CurveType curve_type;
};

class ObjectTuple : public Data {
 public:
  ObjectTuple();
  ~ObjectTuple();

  Object::Type type() const override { return Object::kObjTuple; }

  std::vector<Ref> objs;
};

}  // namespace lightcv

#endif  // LIGHTCV_TYPE_DATA_H_

