/*!
 * @author  chenghua.wang
 * @file    src/Object/_obj_base_.h
 * @brief   definitions of base types, macros functions
 */

#ifndef __obj_base__H_
#define __obj_base__H_

#ifdef _MSC_VER
#pragma once
#endif

#include <stdio.h>
#include <stdlib.h>
#ifdef _MSC_VER
typedef signed char int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned char uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <inttypes.h>
#endif  // _MSC_VER

// Value Number.
#define _CPYTOY_PI_ 3.1415926535897932

#endif  // __obj_base__H_