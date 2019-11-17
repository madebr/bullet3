#ifndef BULLETDYNAMICSAPI_H
#define BULLETDYNAMICSAPI_H

#include "bullet3Api.h"

#ifdef BulletDynamics_EXPORTS
#define BULLETDYNAMICS_API BULLET_EXPORT
#else
#define BULLETDYNAMICS_API BULLET_IMPORT
#endif

#endif
