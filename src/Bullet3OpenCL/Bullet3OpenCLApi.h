#ifndef BULLET3OPENCLAPI_H
#define BULLET3OPENCLAPI_H

#include "bullet3Api.h"

#ifdef Bullet3OpenCL_EXPORTS
#define BULLET3OPENCL_API BULLET_EXPORT
#else
#define BULLET3OPENCL_API BULLET_IMPORT
#endif

#endif
