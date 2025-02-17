#[==[.rst:
*********
spsAsan
*********
  Address sanitizer for any product. Include for convenience.

  We could add the following
    -fsanitize-recover=address: Allows program continuation after an ASan error (optional).
    -fsanitize=leak: Detects memory leaks.
    -fsanitize-address-use-after-scope: Detects use-after-scope bugs.

    -fsanitize=address,undefined
#]==]

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
  if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
  endif()
else()
  set(allowedBuildTypes Asan Debug Release RelWithDebInfo MinSizeRel)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

  if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

set(CMAKE_C_FLAGS_ASAN
  "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C compiler for Asan build type or configuration." FORCE)

set(CMAKE_CXX_FLAGS_ASAN
  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C++ compiler for Asan build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
  "Linker flags to be used to create executables for Asan build type." FORCE)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
  "Linker lags to be used to create shared libraries for Asan build type." FORCE)

# For single-config generators, apply the flags directly
if(NOT isMultiConfig AND CMAKE_BUILD_TYPE STREQUAL "Asan")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS_ASAN}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_ASAN}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_ASAN}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS_ASAN}")
endif()
