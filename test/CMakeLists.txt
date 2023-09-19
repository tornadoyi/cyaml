
project(test)


# link
link_directories(
	${CMAKE_BINARY_DIR}/cyaml
)

set(LINK_LIBS -lcyaml)

# sources
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/test_*.cpp)
message(STATUS "TEST_SOURCES: ${SOURCES}")

# add target
foreach(FILE_PATH ${SOURCES})
	file(RELATIVE_PATH REL_FILE_PATH ${PROJECT_SOURCE_DIR} ${FILE_PATH})
	get_filename_component(TARGET ${FILE_PATH} NAME_WE)
	get_filename_component(DIR ${FILE_PATH} DIRECTORY )
	file(RELATIVE_PATH REL_DIR ${PROJECT_SOURCE_DIR} ${DIR})
	string(REPLACE "/" "_" TEST_NAME ${REL_DIR}/${TARGET})

	message(STATUS "TEST_NAME: ${TEST_NAME}" )
	
	add_executable(${TARGET} ${FILE_PATH})
	add_dependencies(${TARGET} cyaml)
	target_link_libraries(${TARGET} ${LINK_LIBS})
	set_target_properties(${TARGET}
		PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${REL_DIR}
		BUILD_WITH_INSTALL_RPATH FALSE
	)
	add_test(${TEST_NAME} ${PROJECT_BINARY_DIR}/${REL_DIR}/${TARGET})
endforeach()
