#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "../CommonUtilities/CommonSTL.h"
#include "../CommonUtilities/CommonCU.h"

#define SAFE_DELETE(ptr) delete ptr; ptr = nullptr
