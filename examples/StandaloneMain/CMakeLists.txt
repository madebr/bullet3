add_library(hellovr_opengl_main STATIC EXCLUDE_FROM_ALL
	hellovr_opengl_main.cpp
)

target_link_libraries(hellovr_opengl_main
	PUBLIC
		LinearMath
		Bullet3Common
		BulletCollision
		BulletDynamics
#		openvr
)

if(APPLE)
	target_link_libraries(hellovr_opengl_main
		PUBLIC
			${COCOA_LIBRARY}
	)
endif()

####################

add_library(main_console_single_example STATIC EXCLUDE_FROM_ALL
	main_console_single_example.cpp
)

target_link_libraries(main_console_single_example
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
#		CommonInterfaces
)

####################

add_library(main_opengl_single_example STATIC EXCLUDE_FROM_ALL
	main_opengl_single_example.cpp
)

target_link_libraries(main_opengl_single_example
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
#		CommonInterfaces
		b3Clock
)

####################

add_library(main_sw_tinyrenderer_single_example STATIC EXCLUDE_FROM_ALL
	main_sw_tinyrenderer_single_example.cpp
)

target_link_libraries(main_sw_tinyrenderer_single_example
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
#		TinyRenderer
#		CommonInterfaces
		b3Clock
# "../OpenGLWindow/SimpleOpenGL3App.h" and "../ExampleBrowser/OpenGLGuiHelper.h"
)

####################

add_library(main_tinyrenderer_single_example STATIC EXCLUDE_FROM_ALL
	main_tinyrenderer_single_example.cpp
)

target_link_libraries(main_tinyrenderer_single_example
	PUBLIC
		LinearMath
		BulletCollision
		BulletDynamics
#		TinyRenderer
#		CommonInterfaces
#		b3clock
# "../OpenGLWindow/GLInstanceGraphicsShape.h" and "../OpenGLWindow/SimpleCamera.h"
)
