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
using NUnit.Framework;
using LightCV;

namespace LightCVTest
{
  using Tup = IntPtr;
  using Obj = IntPtr;

  [TestFixture]
  public class CallbackTests
  {
    [Test]
    public static void GenRectangle1Test()
    {
      Tup row1 = Core.CreateTupleInteger(0, 2);
      Tup col1 = Core.CreateTupleInteger(0, 2);
      Tup row2 = Core.CreateTupleInteger(10, 2);
      Tup col2 = Core.CreateTupleInteger(20, 2);

      Obj rectangle;
      int rc = Operator.gen_rectangle1(out rectangle, row1, col1, row2, col2);
      Assert.AreEqual(rc, 2);
      Core.ReleaseObject(out rectangle);
      Core.DeleteTuple(out row1);
      Core.DeleteTuple(out col1);
      Core.DeleteTuple(out row2);
      Core.DeleteTuple(out col2);
    }
  }
}

