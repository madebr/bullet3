file(GLOB gwen_SRCS "*.cpp" "Controls/*.cpp" "Controls/Dialog/*.cpp" "Controls/Dialogs/*.cpp" "Controls/Layout/*.cpp" "Controls/Property/*.cpp" "Input/*.cpp" "Platforms/*.cpp" "Renderers/*.cpp" "Skins/*.cpp")
file(GLOB gwen_HDRS "*.h" "Controls/*.h" "Controls/Dialog/*.h" "Controls/Dialogs/*.h" "Controls/Layout/*.h" "Controls/Property/*.h" "Input/*.h" "Platforms/*.h" "Renderers/*.h" "Skins/*.h")

add_library(gwen
	${gwen_HDRS}
	${gwen_SRCS}
)

target_include_directories(gwen
	PUBLIC
		"${CMAKE_CURRENT_LIST_DIR}/.."
)

target_link_libraries(gwen
	PUBLIC
		glad
)

target_compile_definitions(gwen
	PUBLIC
		"GLEW_STATIC"
		"GWEN_COMPILE_STATIC"
		"_HAS_EXCEPTIONS=0"
)

if(UNIX AND NOT APPLE)
	target_link_libraries(gwen
		PUBLIC
			optionalX11
	)
	target_compile_definitions(gwen
		PUBLIC
			"GLEW_INIT_OPENGL11_FUNCTIONS=1"
			"GLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1"
			"DYNAMIC_LOAD_X11_FUNCTIONS=1"
	)
endif()

if(WIN32 OR APPLE)
	target_link_libraries(gwen
		PUBLIC
			${OPENGL_gl_LIBRARY}
	)
endif()
