if(MSVC)
	add_compile_options(/permissive- /utf-8 /await)
endif()
set(CMAKE_CXX_STANDARD 20)

add_library("vec.std" SHARED
	${CMAKE_CURRENT_LIST_DIR}/extension.cpp
)

target_include_directories("vec.std" PUBLIC
	./
)

target_link_libraries("vec.std" PUBLIC smcppsdk)

set_target_properties("vec.std" PROPERTIES PREFIX "" SUFFIX ".ext.2.csgo.${HL2SDK_LIB_SHARED_EXT}")
