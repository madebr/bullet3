FILE(GLOB gwen_SRCS "*.cpp" "Controls/*.cpp" "Controls/Dialog/*.cpp" "Controls/Dialogs/*.cpp" "Controls/Layout/*.cpp" "Controls/Property/*.cpp" "Input/*.cpp" "Platforms/*.cpp" "Renderers/*.cpp" "Skins/*.cpp")
FILE(GLOB gwen_HDRS "*.h" "Controls/*.h" "Controls/Dialog/*.h" "Controls/Dialogs/*.h" "Controls/Layout/*.h" "Controls/Property/*.h" "Input/*.h" "Platforms/*.h" "Renderers/*.h" "Skins/*.h")

ADD_LIBRARY(gwen ${gwen_SRCS} ${gwen_HDRS})
IF(NOT APPLE)
	TARGET_LINK_LIBRARIES(gwen PUBLIC glad_gl)
ENDIF()
TARGET_INCLUDE_DIRECTORIES(gwen PUBLIC
	"$<BUILD_INTERFACE:${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs>"
	"$<INSTALL_INTERFACE:${BULLET_INSTALL_INLUDEDDIR}>")

BULLET3_INSTALL(TARGETS gwen
        RUNTIME DESTINATION ${BULLET_INSTALL_BINDIR}
        LIBRARY DESTINATION ${BULLET_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${BULLET_INSTALL_LIBDIR})
