/* Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
using System;
using System.Runtime.InteropServices;

namespace LightCV
{
  using Tup = IntPtr;
  using Obj = IntPtr;

  public enum VarType
  {
    kVarUndef = 0,
    kVarInteger,
    kVarReal,
    kVarString,
    kVarMixed
  }

  public enum ObjectType
  {
    kObjNull = 0,
    kObjImage,
    kObjRegion,
    kObjCurve,
    kObjTuple
  }

  public class Core
  {
    [DllImport("lightcv_core")]
    public static extern void DeleteTuple(out Tup tup);

    [DllImport("lightcv_core")]
    public static extern Tup CreateTupleInteger(int i, int cnt);

    [DllImport("lightcv_core")]
    public static extern Tup CreateTupleReal(double r, int cnt);

    [DllImport("lightcv_core")]
    public static extern Tup CreateTupleString(string s, int cnt);

    [DllImport("lightcv_core")]
    public static extern VarType TupleType(Tup tup);

    [DllImport("lightcv_core")]
    public static extern int TupleCount(Tup tup);

    [DllImport("lightcv_core")]
    public static extern int TupleCapacity(Tup tup);

    [DllImport("lightcv_core")]
    public static extern VarType TupleItemType(Tup tup, int index);

    [DllImport("lightcv_core")]
    public static extern int TupleGetIntegerItem(Tup tup, int index);

    [DllImport("lightcv_core")]
    public static extern double TupleGetRealItem(Tup tup, int index);

    [DllImport("lightcv_core")]
    public static extern string TupleGetStringItem(Tup tup, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleSetIntegerItem(Tup tup, int i, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleSetRealItem(Tup tup, double r, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleSetStringItem(Tup tup, string s, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleAppendInteger(Tup tup, int i);

    [DllImport("lightcv_core")]
    public static extern void TupleAppendReal(Tup tup, double r);

    [DllImport("lightcv_core")]
    public static extern void TupleAppendString(Tup tup, string s);

    [DllImport("lightcv_core")]
    public static extern void TupleInsertInteger(Tup tup, int i, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleInsertReal(Tup tup, double r, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleInsertString(Tup tup, string s, int index);

    [DllImport("lightcv_core")]
    public static extern void TupleEraseItem(Tup tup, int index);

    [DllImport("lightcv_core")]
    private static extern IntPtr TupleIntegerItems(Tup tup);
    public static void TupleIntegerArray(out int [] array, Tup tup)
    {
      int cnt = TupleCount(tup);
      array = new int[cnt];
      IntPtr p = TupleIntegerItems(tup);

      Marshal.Copy(p, array, 0, cnt);
    }

    [DllImport("lightcv_core")]
    private static extern IntPtr TupleRealItems(Tup tup);
    public static void TupleRealArray(out double [] array, Tup tup)
    {
      int cnt = TupleCount(tup);
      array = new double[cnt];
      IntPtr p = TupleRealItems(tup);
      Marshal.Copy(p, array, 0, cnt);
    }

    [DllImport("lightcv_core")]
    public static extern ObjectType ObjectType(Obj obj);

    [DllImport("lightcv_core")]
    public static extern Obj RetainObject(Obj obj);

    [DllImport("lightcv_core")]
    public static extern void ReleaseObject(out Obj obj);
  }

  class Operator
  {
    [DllImport("lightcv_c")]
    public static extern int gen_rectangle1(out Obj rectangle, Tup row1, Tup col1, Tup row2, Tup col2);
  }
}

