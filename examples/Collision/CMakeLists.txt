add_library(CollisionTutorialBullet2 STATIC EXCLUDE_FROM_ALL
	Internal/Bullet2CollisionSdk.h
	Internal/CollisionSdkInterface.h
	Internal/RealTimeBullet3CollisionSdk.h

	Internal/Bullet2CollisionSdk.cpp
	Internal/RealTimeBullet3CollisionSdk.cpp

	CollisionSdkC_Api.h
	CollisionTutorialBullet2.h

	CollisionSdkC_Api.cpp
	CollisionTutorialBullet2.cpp
)

target_link_libraries(CollisionTutorialBullet2
	PUBLIC
		Bullet3Common
		LinearMath
		stb_image
		TimeSeriesCanvas
)

set_target_properties(CollisionTutorialBullet2
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
