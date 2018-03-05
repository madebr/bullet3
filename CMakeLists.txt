cmake_minimum_required(VERSION 3.2.2)

#this line has to appear before 'PROJECT' in order to be able to disable incremental linking
set(MSVC_INCREMENTAL_DEFAULT ON)

project(BULLET_PHYSICS)
file(STRINGS "VERSION" BULLET_VERSION)

if(NOT CMAKE_BUILD_TYPE)
#	set(CMAKE_BUILD_TYPE "Debug")
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
#message("CMAKE_CXX_FLAGS_DEBUG="+${CMAKE_CXX_FLAGS_DEBUG})

option(USE_DOUBLE_PRECISION "Use double precision" OFF)
option(USE_GRAPHICAL_BENCHMARK "Use Graphical Benchmark" ON)
option(BUILD_SHARED_LIBS "Use shared libraries" OFF)
option(USE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD "Use btSoftMultiBodyDynamicsWorld" ON)

option(BULLET2_USE_THREAD_LOCKS "Build Bullet 2 libraries with mutex locking around certain operations (required for multi-threading)" OFF)
if(BULLET2_USE_THREAD_LOCKS)
    option(BULLET2_USE_OPEN_MP_MULTITHREADING "Build Bullet 2 with support for multi-threading with OpenMP (requires a compiler with OpenMP support)" OFF)
    option(BULLET2_USE_TBB_MULTITHREADING "Build Bullet 2 with support for multi-threading with Intel Threading Building Blocks (requires the TBB library to be already installed)" OFF)
    if(MSVC)
        option(BULLET2_USE_PPL_MULTITHREADING "Build Bullet 2 with support for multi-threading with Microsoft Parallel Patterns Library (requires MSVC compiler)" OFF)
    endif()
endif()


if(NOT WIN32)
	set(DL ${CMAKE_DL_LIBS})
	if(CMAKE_SYSTEM_NAME MATCHES "Linux")
		message("Linux")
		set(OSDEF -D_LINUX)
	else()
		if(APPLE)
			message("Apple")
			set(OSDEF -D_DARWIN)
		else()
			message(AUTHOR_WARNING "BSD?")
			set(OSDEF -D_BSD)
		endif()
	endif()
endif()

option(USE_CUSTOM_VECTOR_MATH "Use custom vector math library" OFF)

#statically linking VC++ isn't supported for WindowsPhone/WindowsStore
if(CMAKE_SYSTEM_NAME STREQUAL WindowsPhone OR CMAKE_SYSTEM_NAME STREQUAL WindowsStore)
	option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC Runtime Library DLL (/MD or /MDd)" ON)
else()
	option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC Runtime Library DLL (/MD or /MDd)" OFF)
endif()

#set(CMAKE_EXE_LINKER_FLAGS_INIT "/STACK:10000000 /INCREMENTAL:NO")
#set(CMAKE_EXE_LINKER_FLAGS "/STACK:10000000 /INCREMENTAL:NO")

#message("MSVC_INCREMENTAL_YES_FLAG"+${MSVC_INCREMENTAL_YES_FLAG})


if(MSVC)
	option(USE_MSVC_INCREMENTAL_LINKING "Use MSVC Incremental Linking" OFF)
	if(NOT USE_MSVC_INCREMENTAL_LINKING)
		#message("MSVC_INCREMENTAL_DEFAULT"+${MSVC_INCREMENTAL_DEFAULT})
		set(MSVC_INCREMENTAL_YES_FLAG "/INCREMENTAL:NO")

		string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
		set(CMAKE_EXE_LINKER_FLAGS_DEBUG "/INCREMENTAL:NO ${replacementFlags}" )
		message("CMAKE_EXE_LINKER_FLAGS_DEBUG=${CMAKE_EXE_LINKER_FLAGS_DEBUG}")

		string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags2 ${CMAKE_EXE_LINKER_FLAGS})

		set(CMAKE_EXE_LINKER_FLAGS ${replacementFlag2})
		string(REPLACE "INCREMENTAL:YES" "" replacementFlags3 "${CMAKE_EXTRA_LINK_FLAGS}")

		set(CMAKE_EXTRA_LINK_FLAGS ${replacementFlag3})

		string(REPLACE "INCREMENTAL:YES" "INCREMENTAL:NO" replacementFlags3 "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}")
		set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO ${replacementFlags3})
		set(CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO "/INCREMENTAL:NO ${replacementFlags3}" )
	endif()

	if(NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
		#We statically link to reduce dependancies
		foreach(flag_var CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO )
			if(${flag_var} MATCHES "/MD")
				STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
			endif()
			if(${flag_var} MATCHES "/MDd")
				STRING(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
			endif()
		endforeach()
	endif()

	if(CMAKE_CL_64)
		add_definitions(-D_WIN64)
	else()
		option(USE_MSVC_SSE "Use MSVC /arch:sse option" OFF)
		option(USE_MSVC_SSE2 "Compile your program with SSE2 instructions" ON)

		if(USE_MSVC_SSE)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE")
		endif()
		if(USE_MSVC_SSE2)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
		endif()
	endif()

	option(USE_MSVC_AVX "Compile your program with AVX instructions" OFF)
	if(USE_MSVC_AVX)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:AVX")
	endif()

	option(USE_MSVC_FAST_FLOATINGPOINT "Use MSVC /fp:fast option" ON)
	if(USE_MSVC_FAST_FLOATINGPOINT)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /fp:fast")
	endif()

	option(USE_MSVC_STRING_POOLING "Use MSVC /GF string pooling option" ON)
	if(USE_MSVC_STRING_POOLING)
		set(CMAKE_C_FLAGS "/GF ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "/GF ${CMAKE_CXX_FLAGS}")
	endif()

	option(USE_MSVC_FUNCTION_LEVEL_LINKING "Use MSVC /Gy function level linking option" ON)
	if(USE_MSVC_FUNCTION_LEVEL_LINKING)
		set(CMAKE_C_FLAGS "/Gy ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "/Gy ${CMAKE_CXX_FLAGS}")
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:REF")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:REF")
	endif()

	option(USE_MSVC_COMDAT_FOLDING "Use MSVC /OPT:ICF COMDAT folding option"	ON)
	if(USE_MSVC_COMDAT_FOLDING)
		set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /OPT:ICF")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:ICF")
	endif()

	option(USE_MSVC_DISABLE_RTTI "Use MSVC /GR- disabled RTTI flags option"	ON)
	if(USE_MSVC_DISABLE_RTTI)
		string(REGEX REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) # Disable RTTI
		set(CMAKE_C_FLAGS "/GR- ${CMAKE_C_FLAGS}")
		set(CMAKE_CXX_FLAGS "/GR- ${CMAKE_CXX_FLAGS}")
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244 /wd4267")
endif()

if(WIN32)
	option(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES "Create MSVC projectfiles that can be distributed" OFF)

	if(INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		set(LIBRARY_OUTPUT_PATH ${BULLET_PHYSICS_SOURCE_DIR}/lib CACHE PATH "Single output directory for building all libraries.")
		SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BULLET_PHYSICS_SOURCE_DIR})
		SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BULLET_PHYSICS_SOURCE_DIR})
		SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BULLET_PHYSICS_SOURCE_DIR})
		SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${BULLET_PHYSICS_SOURCE_DIR})
		SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BULLET_PHYSICS_SOURCE_DIR})
	else()
		set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Single output directory for building all libraries.")
	endif()

	option(INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES "Create MSVC projectfiles with relative paths" OFF)
	option(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES "Add MSVC postfix for executable names (_Debug)" OFF)

	set(CMAKE_DEBUG_POSTFIX "_Debug" CACHE STRING "Adds a postfix for debug-built libraries.")
	set(CMAKE_MINSIZEREL_POSTFIX "_MinsizeRel" CACHE STRING "Adds a postfix for MinsizeRelease-built libraries.")
	set(CMAKE_RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo" CACHE STRING "Adds a postfix for ReleaseWithDebug-built libraries.")

	if(INTERNAL_CREATE_MSVC_RELATIVE_PATH_PROJECTFILES)
		set(CMAKE_SUPPRESS_REGENERATION  1)
		set(CMAKE_USE_RELATIVE_PATHS 1)
	endif()
endif()

option(BUILD_CPU_DEMOS "Build original Bullet CPU examples" ON)

option(INTERNAL_UPDATE_SERIALIZATION_STRUCTURES "Internal update serialization structures" OFF)
if(INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
	add_definitions(-DBT_INTERNAL_UPDATE_SERIALIZATION_STRUCTURES)
endif()

if(USE_DOUBLE_PRECISION)
	add_definitions(-DBT_USE_DOUBLE_PRECISION)
	set(BULLET_DOUBLE_DEF "-DBT_USE_DOUBLE_PRECISION")
endif()

if(NOT USE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD)
	add_definitions(-DSKIP_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD)
endif()

if(USE_GRAPHICAL_BENCHMARK)
	add_definitions(-DUSE_GRAPHICAL_BENCHMARK)
endif()

if(BULLET2_USE_THREAD_LOCKS)
	add_definitions( -DBT_THREADSAFE=1 )
	if(NOT MSVC)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()

if(BULLET2_USE_OPEN_MP_MULTITHREADING)
	add_definitions("-DBT_USE_OPENMP=1")
	if(MSVC)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
	else()
		# GCC, Clang
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")
	endif()
endif()

if(BULLET2_USE_TBB_MULTITHREADING)
	set(BULLET2_TBB_INCLUDE_DIR "not found" CACHE PATH "Directory for Intel TBB includes.")
	set(BULLET2_TBB_LIB_DIR "not found" CACHE PATH "Directory for Intel TBB libraries.")
	find_library(TBB_LIBRARY tbb PATHS ${BULLET2_TBB_LIB_DIR})
	find_library(TBBMALLOC_LIBRARY tbbmalloc PATHS ${BULLET2_TBB_LIB_DIR})
	add_definitions("-DBT_USE_TBB=1")
	include_directories(${BULLET2_TBB_INCLUDE_DIR})
	link_libraries(${TBB_LIBRARY} ${TBBMALLOC_LIBRARY})
endif()

if(BULLET2_USE_PPL_MULTITHREADING)
	add_definitions("-DBT_USE_PPL=1")
endif()

if(WIN32)
	option(USE_GLUT "Use Glut" ON)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)

	if(USE_GLUT AND MSVC)
		string(REPLACE "/D_WINDOWS" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
		remove_definitions(-D_WINDOWS)
	endif()
else()
	option(USE_GLUT "Use Glut" ON)
endif()

# This is the shortcut to finding GLU, GLUT and OpenGL if they are properly installed on your system
# This should be the case.

find_package(OpenGL)
if(OPENGL_FOUND)
	message("OPENGL FOUND")
	message(${OPENGL_LIBRARIES})
else()
	message("OPENGL NOT FOUND")
	set(OPENGL_gl_LIBRARY opengl32)
	set(OPENGL_glu_LIBRARY glu32)
endif()

if(APPLE)
	find_library(COCOA_LIBRARY Cocoa)
endif()

option(BUILD_BULLET3 "Set when you want to build Bullet 3" ON)

option(BUILD_ENET "Set when you want to build apps with enet UDP networking support" ON)
option(BUILD_CLSOCKET "Set when you want to build apps with enet TCP networking support" ON)

# Optional Python configuration
# Will not probe environment for Python configuration (which can abort the
# build process) unless you explicitly turn on BUILD_PYBULLET.
option(BUILD_PYBULLET "Set when you want to build pybullet (Python bindings for Bullet)" OFF)
if(BUILD_PYBULLET)
	set(PYTHON_VERSION_PYBULLET "" CACHE STRING "Python version pybullet will use.")
	set(Python_ADDITIONAL_VERSIONS 3 3.6 3.5 3.4 3.3 3.2 3.1 3.0 2.7 2.7.12 2.7.10 2.7.3 )
	set_property(CACHE PYTHON_VERSION_PYBULLET PROPERTY STRINGS ${Python_ADDITIONAL_VERSIONS})
	set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build3/cmake ${CMAKE_MODULE_PATH})
	option(EXACT_PYTHON_VERSION "Require Python and match PYTHON_VERSION_PYBULLET exactly, e.g. 2.7.12" OFF)
	if(EXACT_PYTHON_VERSION)
		set(EXACT_PYTHON_VERSION_FLAG EXACT REQUIRED)
	endif(EXACT_PYTHON_VERSION)

	# first find the python interpreter
	find_package(PythonInterp ${PYTHON_VERSION_PYBULLET} ${EXACT_PYTHON_VERSION_FLAG})
	# python library should exactly match that of the interpreter
	# the following can result in fatal error if you don't have the right python configuration
	find_package(PythonLibs ${PYTHON_VERSION_STRING} EXACT)

	option(BUILD_PYBULLET_NUMPY "Set when you want to build pybullet with NumPy support" OFF)
	option(BUILD_PYBULLET_ENET "Set when you want to build pybullet with enet UDP networking support" ON)
	option(BUILD_PYBULLET_CLSOCKET "Set when you want to build pybullet with enet TCP networking support" ON)

	option(BUILD_PYBULLET_MAC_USE_PYTHON_FRAMEWORK "Set when you want to use the Python Framework on Mac" OFF)

	if(BUILD_PYBULLET_NUMPY)
		find_package(NumPy)
		if(PYTHON_NUMPY_FOUND)
			message("NumPy found")
			add_definitions(-DPYBULLET_USE_NUMPY)
		else()
			message("NumPy not found")
		endif()
	endif()

	if(WIN32)
		set(BUILD_SHARED_LIBS OFF CACHE BOOL "Shared Libs" FORCE)
	else()
		set(BUILD_SHARED_LIBS ON CACHE BOOL "Shared Libs" FORCE)
	endif()

	if(APPLE)
		option(BUILD_PYBULLET_MAC_USE_PYTHON_FRAMEWORK "Set when you want to use the Python Framework on Mac" ON)
		if(NOT BUILD_PYBULLET_MAC_USE_PYTHON_FRAMEWORK)
			add_definitions(-DB3_NO_PYTHON_FRAMEWORK)
		endif(NOT BUILD_PYBULLET_MAC_USE_PYTHON_FRAMEWORK)
		option(BUILD_PYBULLET_SHOW_PY_VERSION "Set when you want to show the PY_MAJOR_VERSION and PY_MAJOR_VERSION using #pragme message." OFF)
		if(BUILD_PYBULLET_SHOW_PY_VERSION)
			add_definitions(-DB3_DUMP_PYTHON_VERSION)
		endif()
	endif()

endif()

set(OPENGL3_DEMOS_DEFAULT ON)
if(APPLE)
	message("Mac OSX Version is ${_CURRENT_OSX_VERSION}")
	if(_CURRENT_OSX_VERSION VERSION_LESS 10.9)
		message("Mac OSX below 10.9 has no OpenGL 3 support so please disable the BUILD_OPENGL3_DEMOS option")
		set(OPENGL3_DEMOS_DEFAULT OFF)
	endif()
endif()
option(BUILD_OPENGL3_DEMOS "Set when you want to build Bullet 3 OpenGL3+ demos" ${OPENGL3_DEMOS_DEFAULT})

option(INSTALL_LIBS "Set when you want to install libraries" ON)

subdirs(src)

if(INSTALL_LIBS)
	#INSTALL of other files requires CMake 2.6
	if(BUILD_EXTRAS)
		if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
			option(INSTALL_EXTRA_LIBS "Set when you want extra libraries installed" ON)
		endif(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
	endif(BUILD_EXTRAS)

	set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )
	set(LIB_DESTINATION "lib${LIB_SUFFIX}" CACHE STRING "Library directory name")

	## the following are directories where stuff will be installed to
	set(INCLUDE_INSTALL_DIR "include/bullet/" CACHE PATH "The subdirectory to the header prefix")
	set(PKGCONFIG_INSTALL_PREFIX "lib${LIB_SUFFIX}/pkgconfig/" CACHE STRING "Base directory for pkgconfig files")
	if(NOT MSVC)
		configure_file("${CMAKE_CURRENT_SOURCE_DIR}/bullet.pc.cmake" "${CMAKE_CURRENT_BINARY_DIR}/bullet.pc" @ONLY)
		install(
			FILES
			"${CMAKE_CURRENT_BINARY_DIR}/bullet.pc"
			DESTINATION
			"${PKGCONFIG_INSTALL_PREFIX}"
			)
	endif()
endif()

if(BUILD_OPENGL3_DEMOS)
	if(EXISTS "${BULLET_PHYSICS_SOURCE_DIR}/Demos3" AND IS_DIRECTORY "${BULLET_PHYSICS_SOURCE_DIR}/Demos3")
		subdirs(Demos3)
	endif()
else()
	add_definitions(-DNO_OPENGL3)
endif()

option(BUILD_BULLET2_DEMOS "Set when you want to build the Bullet 2 demos" ON)
if(BUILD_BULLET2_DEMOS)
	subdirs(examples)
endif()

option(BUILD_EXTRAS "Set when you want to build the extras" ON)
if(BUILD_EXTRAS)
	subdirs(Extras)
endif()

option(BUILD_UNIT_TESTS "Build Unit Tests" ON)

if(BUILD_UNIT_TESTS)
	enable_testing()
	subdirs(test)
endif()

set(BULLET_CONFIG_CMAKE_PATH lib${LIB_SUFFIX}/cmake/bullet )
list(APPEND BULLET_LIBRARIES LinearMath)
list(APPEND BULLET_LIBRARIES Bullet3Common)
list(APPEND BULLET_LIBRARIES BulletInverseDynamics)
list(APPEND BULLET_LIBRARIES BulletCollision)
list(APPEND BULLET_LIBRARIES BulletDynamics)
list(APPEND BULLET_LIBRARIES BulletSoftBody)
set(BULLET_USE_FILE "${BULLET_CONFIG_CMAKE_PATH}/UseBullet.cmake")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/BulletConfig.cmake.in"
					"${CMAKE_CURRENT_BINARY_DIR}/BulletConfig.cmake"
					@ONLY ESCAPE_QUOTES
	)
option(INSTALL_CMAKE_FILES "Install generated CMake files" ON)

if(INSTALL_CMAKE_FILES)
	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/UseBullet.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/BulletConfig.cmake"
		DESTINATION "${BULLET_CONFIG_CMAKE_PATH}"
		)
endif()
