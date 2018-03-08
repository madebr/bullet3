set(OpenGLWindow_HDRS
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

add_library(OpenGLWindow
	${OpenGLWindow_HDRS}
	${OpenGLWindowCommon_CPP}
)

if(WIN32)
	target_sources(OpenGLWindow
		PRIVATE
			${OpenGLWindowWin32_CPP}
	)
	add_definitions(-DGLEW_STATIC)
elseif(APPLE)
	target_sources(OpenGLWindow
		PRIVATE
			${OpenGLWindowMac_CPP}
			${OpenGLWindowMacObjC_CPP}
	)
else()
	#no Linux detection?
	target_sources(OpenGLWindow
		PRIVATE
			${OpenGLWindowLinux_CPP}
	)
	target_compile_definitions(OpenGLWindow
		PUBLIC
			"GLEW_STATIC"
			"GLEW_INIT_OPENGL11_FUNCTIONS=1"
			"GLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1"
			"DYNAMIC_LOAD_X11_FUNCTIONS=1"
	)
	target_link_libraries(OpenGLWindow
		PUBLIC
			glad_glx
	)
endif()

target_link_libraries(OpenGLWindow
	PUBLIC
		Bullet3Common
		glad
		stb_image
)

if(UNIX AND NOT APPLE)
	target_link_libraries(OpenGLWindow
		PUBLIC
			${DL}
	)
elseif(APPLE)
	target_link_libraries(OpenGLWindow
		PUBLIC
			${COCOA_LIBRARY}
	)
endif()

if (WIN32 OR APPLE)
	target_link_libraries(OpenGLWindow
		PUBLIC
			${OPENGL_gl_LIBRARY}
	)
else()
	set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
	find_package(Threads REQUIRED)
	target_link_libraries(OpenGLWindow
		PUBLIC
			${CMAKE_THREAD_LIBS_INIT}
	)
endif()
