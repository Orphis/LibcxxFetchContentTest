set(CMAKE_CXX_COMPILER_CLANG_SCAN_DEPS clang-scan-deps)

cmake_minimum_required(VERSION 3.28)
project(LibCxxTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)

if (WIN32)
  set(LLVM_ENABLE_RUNTIMES "libcxx" CACHE INTERNAL "")
else()
  set(LLVM_ENABLE_RUNTIMES "libcxx;libcxxabi;libunwind" CACHE INTERNAL "")
endif()
set(LIBCXX_ENABLE_STATIC ON CACHE INTERNAL "")
set(LIBCXX_ENABLE_SHARED OFF CACHE INTERNAL "")

if (NOT WIN32)
  set(LIBCXXABI_ENABLE_STATIC ON CACHE INTERNAL "")
  set(LIBCXXABI_ENABLE_SHARED OFF CACHE INTERNAL "")
  set(LIBUNWIND_ENABLE_STATIC ON CACHE INTERNAL "")
  set(LIBUNWIND_ENABLE_SHARED OFF CACHE INTERNAL "")
endif()

if (WIN32)
  set(LIBCXX_CXX_ABI "vcruntime" CACHE INTERNAL "")
  set(LIBCXXABI_USE_LLVM_UNWINDER OFF CACHE INTERNAL "")
endif()

FetchContent_Declare(
  llvm
  GIT_REPOSITORY https://github.com/llvm/llvm-project.git
  GIT_TAG llvmorg-20.1.2
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  SOURCE_SUBDIR runtimes
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_MakeAvailable(llvm)

link_libraries(cxx_static)
if (WIN32)
  add_compile_definitions(_CRT_STDIO_ISO_WIDE_SPECIFIERS)
  set(CXX_LIB "msvcprt")
  if(CMAKE_MSVC_RUNTIME_LIBRARY MATCHES "Debug")
    set(CXX_LIB "${CXX_LIB}d")
  endif()

  link_libraries(${CXX_LIB})
endif()

add_executable(test_libcxx
    test_libcxx.cpp
)