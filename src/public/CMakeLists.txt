  
file(RELATIVE_PATH TARGE_NAME "${CMAKE_CURRENT_LIST_DIR}/../" "${CMAKE_CURRENT_LIST_DIR}")
set(TARGET_NAME "${CMAKE_PROJECT_NAME}.${TARGE_NAME}")

add_library("vec.std.public" INTERFACE)

target_sources("vec.std.public" INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/tools.cpp
	${CMAKE_CURRENT_LIST_DIR}/paramparser.cpp
)

target_include_directories("vec.std.public" INTERFACE ${CMAKE_CURRENT_LIST_DIR})
