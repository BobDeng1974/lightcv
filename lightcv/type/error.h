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
#ifndef LIGHTCV_TYPE_ERROR_H_
#define LIGHTCV_TYPE_ERROR_H_

namespace lightcv {

enum class Error {
  kTrue = 2,
  kFalse = 3,
  kWIPN1 = 1401,
  kWIPN2 = 1402,
  kWIPN3 = 1403,
  kWIPN4 = 1404,
  kWIPN5 = 1405,
  kWIPN6 = 1406,
  kWIPT1 = 1201,
  kWIPT2 = 1202,
  kWIPT3 = 1203,
  kWIPT4 = 1204,
  kWIPT5 = 1205,
  kWIPV1 = 1301,
  kWIPV2 = 1302,
  kWIPV3 = 1303,
  kWIPV4 = 1304,
  kWIPV5 = 1305,
  kWIPV6 = 1306
};

}  // namespace lightcv

#endif // !LIGHTCV_TYPE_ERROR_H_
