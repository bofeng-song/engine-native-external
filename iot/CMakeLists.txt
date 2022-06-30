
add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libcrypto.a
)

add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/freetype
  IMPORTED_LOCATION ${platform_spec_path}/libfreetype.a
)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libpng.a
)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libssl.a
)

add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libuv.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/uv
)

add_library(openxr SHARED IMPORTED GLOBAL)
set_target_properties(openxr PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libxr_loader.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/openxr
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libwebp.a
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libwebsockets.a
)

add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libz.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/zlib
)

add_library(android_platform STATIC
  ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c
)
target_include_directories(android_platform PUBLIC
  ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures
  ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue
)

add_library(fission STATIC IMPORTED GLOBAL)
set_target_properties(fission PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libfission_sdk.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/fission_sdk/include
)

add_library(sqlite3 STATIC IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libsqlite3.a
)

set(se_libs_name)

if(USE_SE_V8)

    add_library(v8_monolith STATIC IMPORTED GLOBAL)
    set_target_properties(v8_monolith PROPERTIES
      IMPORTED_LOCATION ${platform_spec_path}/v8/libv8_monolith.a
    )

    if(ANDROID_ABI STREQUAL "arm64-v8a" OR ANDROID_ABI STREQUAL "x86_64")
      set_property(TARGET v8_monolith
        APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS
      )
    endif()

    add_library(v8_inspector STATIC IMPORTED GLOBAL)
    set_target_properties(v8_inspector PROPERTIES
      IMPORTED_LOCATION ${platform_spec_path}/v8/libinspector.a
      INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/v8
    )
    set(se_libs_name v8_monolith v8_inspector)
endif()

if(USE_SOCKET)
    list(APPEND CC_EXTERNAL_LIBS
        websockets
        ssl
        crypto
    )
endif()

if(USE_SE_V8 AND USE_V8_DEBUGGER)
    list(APPEND CC_EXTERNAL_LIBS
        v8_inspector
    )
endif()

############################# glslang #############################

set(glslang_libs_name glslang glslang-default-resource-limits MachineIndependent OGLCompiler OSDependent SPIRV SPIRV-Tools-opt SPIRV-Tools GenericCodeGen)
foreach(lib IN LISTS glslang_libs_name)
  add_library(${lib} STATIC IMPORTED GLOBAL)
  set_target_properties(${lib} PROPERTIES
    IMPORTED_LOCATION ${platform_spec_path}/glslang/lib${lib}.a
  )
endforeach()

############################# TBB #############################

add_library(tbb STATIC IMPORTED GLOBAL)
set_target_properties(tbb PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libtbb_static.a
)
set(tbb_libs_name tbb)

if(USE_PHYSICS_PHYSX)
  set(PhysXSDK PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXExtensions PhysX PhysXPvdSDK PhysXCommon PhysXFoundation)
  foreach(PX IN LISTS PhysXSDK)
    add_library(${PX} STATIC IMPORTED GLOBAL)
    set_target_properties(${PX} PROPERTIES
      IMPORTED_LOCATION ${platform_spec_path}/PhysX/lib${PX}_static.a
    )
  endforeach()
else()
  set(PhysXSDK)
endif()

list(APPEND CC_EXTERNAL_LIBS
    freetype
    jpeg
    png
    uv
    fission
    sqlite3
    webp
    android_platform
    ${glslang_libs_name}
    ${tbb_libs_name}
    ${PhysXSDK}
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB}  ${se_libs_name})
endif()



list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/v8
  ${platform_spec_path}/include/uv
  ${platform_spec_path}/include/glslang
  ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue
)
