#pragma once

#ifdef _MSC_VER
#define HW_INLINE __forceinline 	/* use __forceinline (VC++ specific) */
#else
#define HW_INLINE inline        	/* use standard inline */
#endif


#include "cuvector.h"
#include "DebugLogger.h"
#include "Function.h"
#include "cumath.h"
#include "InputHelper.h"
