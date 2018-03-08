add_library(TimeSeriesCanvas STATIC EXCLUDE_FROM_ALL
	TimeSeriesCanvas.h
	TimeSeriesFontData.h

	TimeSeriesCanvas.cpp
	TimeSeriesFontData.cpp
)

target_include_directories(TimeSeriesCanvas
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(TimeSeriesCanvas
	PUBLIC
		LinearMath
)

set_target_properties(TimeSeriesCanvas
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)

#############

add_library(TinyVRGui STATIC EXCLUDE_FROM_ALL
	TinyVRGui.h
	TinyVRGui.cpp
)

target_include_directories(TinyVRGui
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(TinyVRGui
	PUBLIC
		Bullet3Common
		TimeSeriesCanvas
)

set_target_properties(TinyVRGui
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)

#############

add_library(RenderingExamples STATIC EXCLUDE_FROM_ALL
	CoordinateSystemDemo.h
	CoordinateSystemDemo.cpp

	DynamicTexturedCubeDemo.h
	DynamicTexturedCubeDemo.cpp

	RaytracerSetup.h
	RaytracerSetup.cpp

	RenderInstancingDemo.h
	RenderInstancingDemo.cpp

	TimeSeriesExample.h
	TimeSeriesExample.cpp

	TinyRendererSetup.h
	TinyRendererSetup.cpp
)

target_include_directories(RenderingExamples
	INTERFACE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(RenderingExamples
	PUBLIC
		LinearMath
		Bullet3Common
		BulletCollision
		OpenGLWindow
		TimeSeriesCanvas
		TinyVRGui
		gwenGUISupport
)

set_target_properties(RenderingExamples
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
