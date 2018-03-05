include_directories(
	..
	../ThirdPartyLibs
	../../src
	../ThirdPartyLibs/glad
)

file(GLOB OpenGLWindow_HDRS
	EGLOpenGLWindow.h
	fontstash.h
	GLFWOpenGLWindow.h
	GLInstanceGraphicsShape.h
	GLInstanceRendererInternalData.h
	GLInstancingRenderer.h
	GLPrimInternalData.h
	GLPrimitiveRenderer.h
	GLRenderToTexture.h
	GwenOpenGL3CoreRenderer.h
	LoadShader.h
	MacOpenGLWindow.h
	MacOpenGLWindowObjC.h
	OpenGL2Include.h
	opengl_fontstashcallbacks.h
	OpenGLInclude.h
	ShapeData.h
	SimpleCamera.h
	SimpleOpenGL2App.h
	SimpleOpenGL2Renderer.h
	SimpleOpenGL3App.h
	TwFonts.h
	Win32InternalWindowData.h
	Win32OpenGLWindow.h
	Win32Window.h
	X11OpenGLWindow.h
)

set(OpenGLWindowMac_CPP
	MacOpenGLWindow.cpp
)

set(OpenGLWindowMacObjC_CPP
	MacOpenGLWindowObjC.m
)

set(OpenGLWindowWin32_CPP
	Win32OpenGLWindow.cpp
	Win32Window.cpp
)

set(OpenGLWindowLinux_CPP
	X11OpenGLWindow.cpp
)

set(OpenGLWindowCommon_CPP
	EGLOpenGLWindow.cpp
	fontstash.cpp
	GLFWOpenGLWindow.cpp
	GLInstancingRenderer.cpp
	GLPrimitiveRenderer.cpp
	GLRenderToTexture.cpp
	LoadShader.cpp
	opengl_fontstashcallbacks.cpp
	OpenSans.cpp
	SimpleCamera.cpp
	SimpleOpenGL2App.cpp
	SimpleOpenGL2Renderer.cpp
	SimpleOpenGL3App.cpp
	TwFonts.cpp
)

if(WIN32)
	set(OpenGLWindow_SRCS
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/glad.c"
		${OpenGLWindowWin32_CPP}
		${OpenGLWindowCommon_CPP}
	)
	include_directories(
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
	)
	add_definitions(-DGLEW_STATIC)
endif()

if(APPLE)
	set(OpenGLWindow_SRCS
		${OpenGLWindowMac_CPP}
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/glad.c"
		${OpenGLWindowMacObjC_CPP}
		${OpenGLWindowCommon_CPP}
	)
endif()

#no Linux detection?
if(NOT WIN32 AND NOT APPLE)
	include_directories(
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad"
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/optionalX11"
	)
	add_definitions(-DGLEW_STATIC)
	add_definitions("-DGLEW_INIT_OPENGL11_FUNCTIONS=1")
       	add_definitions("-DGLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1")
	add_definitions("-DDYNAMIC_LOAD_X11_FUNCTIONS=1")
	set(OpenGLWindow_SRCS
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/glad_glx.c"
		"${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs/glad/glad.c"
		${OpenGLWindowLinux_CPP}
		${OpenGLWindowCommon_CPP}
	)
endif()


add_library(OpenGLWindow ${OpenGLWindow_SRCS} ${OpenGLWindow_HDRS})

if(UNIX AND NOT APPLE)
	target_link_libraries(OpenGLWindow ${DL})
elseif(APPLE)
	target_link_libraries(OpenGLWindow ${COCOA_LIBRARY})
endif()

if(BUILD_SHARED_LIBS)
	target_link_libraries(OpenGLWindow Bullet3Common)
	if (WIN32 OR APPLE)
		target_link_libraries(OpenGLWindow ${OPENGL_gl_LIBRARY})
	else()
		set (CMAKE_THREAD_PREFER_PTHREAD TRUE)
		find_package(Threads REQUIRED)
		target_link_libraries(OpenGLWindow ${CMAKE_THREAD_LIBS_INIT})
	endif()
endif()

#target_link_libraries(OpenGLWindow ${OPENGL_gl_LIBRARY})
