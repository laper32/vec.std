file(RELATIVE_PATH TARGE_NAME "${CMAKE_CURRENT_LIST_DIR}/../" "${CMAKE_CURRENT_LIST_DIR}")
set(TARGET_NAME "${CMAKE_PROJECT_NAME}.${TARGE_NAME}")

add_library("vec.std.public" INTERFACE)

target_sources("vec.std.public" INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/engine.h
	${CMAKE_CURRENT_LIST_DIR}/engine.cpp
	${CMAKE_CURRENT_LIST_DIR}/utils.h
	${CMAKE_CURRENT_LIST_DIR}/utils.cpp
	${CMAKE_CURRENT_LIST_DIR}/tools.h
	${CMAKE_CURRENT_LIST_DIR}/tools.cpp
	${CMAKE_CURRENT_LIST_DIR}/hashlib.h
	${CMAKE_CURRENT_LIST_DIR}/hashlib.cpp
	${CMAKE_CURRENT_LIST_DIR}/playermgr.h
	${CMAKE_CURRENT_LIST_DIR}/playermgr.cpp
	${CMAKE_CURRENT_LIST_DIR}/paramparser.cpp
	${CMAKE_CURRENT_LIST_DIR}/fileparser.h
	${CMAKE_CURRENT_LIST_DIR}/fileparser.cpp
)

target_include_directories("vec.std.public" INTERFACE ${CMAKE_CURRENT_LIST_DIR})
