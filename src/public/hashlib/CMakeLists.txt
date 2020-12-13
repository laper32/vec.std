file(RELATIVE_PATH TARGE_NAME "${CMAKE_CURRENT_LIST_DIR}/../" "${CMAKE_CURRENT_LIST_DIR}")
set(TARGET_NAME "${CMAKE_PROJECT_NAME}.${TARGE_NAME}")

add_library("vec.std.public.hashlib" INTERFACE)

target_sources("vec.std.public.hashlib" INTERFACE
	${CMAKE_CURRENT_LIST_DIR}/md5.h
	${CMAKE_CURRENT_LIST_DIR}/md5.cpp
	${CMAKE_CURRENT_LIST_DIR}/crc32.h
	${CMAKE_CURRENT_LIST_DIR}/crc32.cpp
	${CMAKE_CURRENT_LIST_DIR}/base64.h
	${CMAKE_CURRENT_LIST_DIR}/base64.cpp
	${CMAKE_CURRENT_LIST_DIR}/sha1.h
	${CMAKE_CURRENT_LIST_DIR}/sha256.h
)

target_include_directories("vec.std.public.hashlib" INTERFACE ${CMAKE_CURRENT_LIST_DIR})
