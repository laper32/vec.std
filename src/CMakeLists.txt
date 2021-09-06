set(ENABLE_JSON ON)
if(MSVC)
	add_compile_options(/permissive- /utf-8)
endif()
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

add_subdirectory("public")

add_library("vec.std" SHARED
	${CMAKE_CURRENT_LIST_DIR}/extension.cpp
	${CMAKE_CURRENT_LIST_DIR}/functions.cpp
	${CMAKE_CURRENT_LIST_DIR}/command.cpp
	${CMAKE_CURRENT_LIST_DIR}/events.cpp
	${CMAKE_CURRENT_LIST_DIR}/client.cpp
)

target_include_directories("vec.std" PUBLIC
	./
)

target_link_libraries("vec.std" PUBLIC smcppsdk)
target_link_libraries("vec.std" PUBLIC "vec.std.public")

set_target_properties("vec.std" PROPERTIES PREFIX "" SUFFIX ".ext.2.csgo${HL2SDK_LIB_SHARED_EXT}")
target_precompile_headers("vec.std" PRIVATE ${CMAKE_CURRENT_LIST_DIR}/stdafx.h)