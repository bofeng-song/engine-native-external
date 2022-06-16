// Copyright 2016 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FISSION_APP_WRAPPER_H
#define FISSION_APP_WRAPPER_H

#include <stdio.h>

#include <android/log.h>

#include "fission_app.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * log
*/
#define f_logi(tag, format, ...) \
    do { \
        printf("%s: " format "\n", tag, ##__VA_ARGS__); \
        __android_log_print(ANDROID_LOG_INFO, tag, format, ##__VA_ARGS__); \
    } while (0)

#define f_logd(tag, format, ...) \
    do { \
        printf("%s: " format "\n", tag, ##__VA_ARGS__); \
        __android_log_print(ANDROID_LOG_DEBUG, tag, format, ##__VA_ARGS__); \
    } while (0)

#define f_loge(tag, format, ...) \
    do { \
        printf("%s: " format "\n", tag, ##__VA_ARGS__); \
        __android_log_print(ANDROID_LOG_ERROR, tag, format, ##__VA_ARGS__); \
    } while (0)

/// define fission funcs.
#define DECLARE_FISSION_FUNCS(func) extern FNAPP_##func func
#define DEFINE_FISSION_FUNCS(func) FNAPP_##func func

/**
 * Initialize the fission app function pointer variables.
 *
 * The function should be called once and before calling FNAPP_xxx functions.
 *
 * \return 0 for success, or a negative value on error.
 */
int fissionInitApp(void);

/**
 * Get the sdk version.
 *
 * \return the version.
 */
uint32_t fissionGetSdkVersion(void);

void fissionRealseApp(void);

#if 1
/**
 * Display funcs, reference to the file 'fission_app.h'
 */
DECLARE_FISSION_FUNCS(fnGetDisplayIds);
DECLARE_FISSION_FUNCS(fnGetDisplayIdByType);
DECLARE_FISSION_FUNCS(fnGetDisplayInfo);

/**
 * Surface funcs, reference to the file 'fission_app.h'
 */
DECLARE_FISSION_FUNCS(fnCreateSurface);
DECLARE_FISSION_FUNCS(fnReleaseSurface);
DECLARE_FISSION_FUNCS(fnSetSurfaceSize);
DECLARE_FISSION_FUNCS(fnSetSurfaceAlpha);
DECLARE_FISSION_FUNCS(fnSetSurfacePos);
DECLARE_FISSION_FUNCS(fnSetSurfaceZ);
#endif
/**
 * Input funcs, reference to the file 'fission_app.h'
 */
DECLARE_FISSION_FUNCS(fnGetInstance);

DECLARE_FISSION_FUNCS(fnSetInputCallback);
// extern FNAPP_fnSetInputCallback fnSetInputCallback;

DECLARE_FISSION_FUNCS(fnReleaseInstance);
// FNAPP_fnReleaseInstance

#ifdef __cplusplus
};
#endif

#endif  // FISSION_APP_WRAPPER_H
