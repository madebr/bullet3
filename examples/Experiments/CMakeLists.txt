add_library(ImplicitClothExperiment STATIC EXCLUDE_FROM_ALL
	ImplicitCloth/ImplicitClothExample.h
	ImplicitCloth/ImplicitClothExample.cpp

	ImplicitCloth/stan/array.h
	ImplicitCloth/stan/Cloth.h
	ImplicitCloth/stan/Cloth.cpp
	ImplicitCloth/stan/SpringNetwork.h
	ImplicitCloth/stan/SpringNetwork.cpp
	ImplicitCloth/stan/vec3n.h
	ImplicitCloth/stan/vec3n.cpp
	ImplicitCloth/stan/vecmath.h
	ImplicitCloth/stan/vecmath.cpp
)

target_include_directories(ImplicitClothExperiment
	PRIVATE
		"${CMAKE_CURRENT_LIST_DIR}"
)

target_link_libraries(ImplicitClothExperiment
	PUBLIC
		Bullet3Common
)

set_target_properties(ImplicitClothExperiment
	PROPERTIES
		POSITION_INDEPENDENT_CODE ${PIC_DEFAULT}
)
