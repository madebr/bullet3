add_library(gwenGUISupport STATIC EXCLUDE_FROM_ALL
	GraphingTexture.h
	gwenInternalData.h
	GwenParameterInterface.h
	GwenProfileWindow.h
	GwenTextureWindow.h
	gwenUserInterface.h

	GraphingTexture.cpp
	GwenParameterInterface.cpp
	GwenProfileWindow.cpp
	GwenTextureWindow.cpp
	gwenUserInterface.cpp
)

target_link_libraries(gwenGUISupport
	PUBLIC
		Bullet3Common
		LinearMath
		OpenGLWindow
		gwen
)

target_include_directories(gwenGUISupport
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}/.."
)

set_target_properties(gwenGUISupport
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
