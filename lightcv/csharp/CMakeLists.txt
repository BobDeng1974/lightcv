project(csharp LANGUAGES CSharp)

add_library(${libname_prefix}csharp SHARED lightcv.cs
                                           lightcv_test.cs
                                           packages.config
)

