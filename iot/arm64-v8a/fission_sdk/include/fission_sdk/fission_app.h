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

// This file is generated.
#ifndef FISSION_APP_H
#define FISSION_APP_H

#include <EGL/egl.h>
#include <android/input.h>
#include <android/native_window.h>
#include "FissionInputManager.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The unique id for display.
 * Used to get display info and create surface.
*/
typedef uint64_t FnDisplayId;

/**
 * Display type.
*/
typedef enum {
    /// The main display or internal display
    FnDispTypeDefalut,
    /// the external display
    FnDispTypeExternal,
    FnDispTypeMax
} FnDisplayType;

/**
 * Struct of the display info.
*/
typedef struct _FnDisplayInfo_ {
    /// Display type, {@link FnDisplayType}
    uint8_t type;
    /// Display width
    uint32_t w;
    /// Display height
    uint32_t h;
    float xdpi;
    float ydpi;
    float density;
    /*float fps;*/
    /*uint8_t orientation;*/
} FnDisplayInfo, *pFnDisplayInfo;

/// Display funcs
/**
 * Get all display ids.
 *
 * If displayIds is nullptr, then the numIds return the num of displays.
 *
 * \param displayIds out value of all displays' id.
 * \param numIds out value of displays' num.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnGetDisplayIds)(FnDisplayId *displayIds, int *numIds);

/**
 * Get display id by type.
 *
 * \param type the value of display type, {@link FnDisplayType}.
 * \param displayId out value of display id.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnGetDisplayIdByType)(const FnDisplayType type, FnDisplayId *displayId);

/**
 * Get display info by id.
 *
 * \param dispId the value of display id, {@link FnDisplayId}.
 * \param outDisplayInfo out value of display info, {@link FnDisplayInfo}.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnGetDisplayInfo)(const FnDisplayId dispId, pFnDisplayInfo outDisplayInfo);

/// Surface funcs
/**
 * Create a native window on the display.
 *
 * NOTE: If the native window is not used, need to be released.
 *
 * \param dispId the value of display id, {@link FnDisplayId}.
 * \param name the name of native window.
 * \param x the x position of native window.
 * \param y the y position of native window.
 * \param z the z position of native window, suggest to set the z postion above 0x70000000.
 * \param w the width of native window.
 * \param h the height of native window.
 * \param pixelFormat the pixel format of native window, {@link ANativeWindow_LegacyFormat} in file 'android/native_window.h'.
 * \return the native window ptr, nullptr for error, or a abave 0 value on success.
*/
typedef ANativeWindow* (*FNAPP_fnCreateSurface)(const FnDisplayId dispId,
                     const char *name, int x, int y, int z, int w, int h, int pixelFormat);

/**
 * Release the native window.
 *
 * \param surface the native window.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnReleaseSurface)(ANativeWindow* surface);

/**
 * Update the native window size.
 *
 * \param surface the native window.
 * \param w the new width of native window.
 * \param h the new height of native window.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnSetSurfaceSize)(ANativeWindow* surface, int w, int h);

/**
 * Update the native window alpha.
 *
 * \param surface the native window.
 * \param w the new alpha of native window.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnSetSurfaceAlpha)(ANativeWindow* surface, float alpha);

/**
 * Update the native window x and y position.
 *
 * \param surface the native window.
 * \param x the new x position of native window.
 * \param y the new y position of native window.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnSetSurfacePos)(ANativeWindow* surface, int x, int y);

/**
 * Update the native window z position.
 *
 * \param surface the native window.
 * \param z the new z position of native window.
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnSetSurfaceZ)(ANativeWindow* surface, int z);

/// Input funcs
/**
 * Set callback to receive the input event.
 *
 * \param pFInput  Fission Input handler.
 * \param ptr   the callback function pointer
 * \return 0 for success, or a negative value on error.
*/
typedef int (*FNAPP_fnSetInputCallback)(struct FissionInputManager *pFInput, filong ptr);

/**
 * @brief get Fission input handler instance
 * \param void
 * \return Fission Input handler.
 */
typedef struct FissionInputManager *(*FNAPP_fnGetInstance)(void);

/**
 * @brief release Fission input handler instance
 * \param pFInput  Fission Input handler.
 * \return void
 */
typedef void (*FNAPP_fnReleaseInstance)(struct FissionInputManager *pInstance);

/**
 * @brief get fission system version
 * \param void
 * \return system version
 */
typedef uint32_t (*FNAPP_fissionGetFissionVersion)(void);

#ifdef __cplusplus
};
#endif

#endif  // FISSION_APP_H
