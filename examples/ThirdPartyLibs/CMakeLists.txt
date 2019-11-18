SUBDIRS(
	BussIK
	Gwen
	glad
	optionalX11
	tinyxml2
)

IF(ENABLE_LUA)
	SUBDIRS(lua-5.2.3)
ENDIF()
