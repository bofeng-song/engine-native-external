/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FISSIONINPUTMANAGER_H__
#define _FISSIONINPUTMANAGER_H__

#include <stdint.h>
#include "FissionXDJA.h"

struct FissionInputManager;

/*FISSION_ANDROID_ENV在ndk环境编译环境下不需要，会报函数重定义；
 * 因为ndk测试程序中使用了宏定义了这些函数指针
 */
// #define FISSION_ANDROID_ENV

#ifdef __cplusplus
extern "C" {
#endif

#ifdef FISSION_ANDROID_ENV
struct FissionInputManager *fnGetInstance(void);
void fnReleaseInstance(struct FissionInputManager *pInstance);
extern void fnSetColor(struct FissionInputManager *pFInput, int color);
extern int fnGetColor(struct FissionInputManager *pFInput);
extern int fnSetInputCallback(struct FissionInputManager *pFInput, filong ptr);

extern uint32_t fissionGetFissionVersion(void);
#endif

#ifdef __cplusplus
};
#endif

#endif // _FISSIONINPUTMANAGER_H__
