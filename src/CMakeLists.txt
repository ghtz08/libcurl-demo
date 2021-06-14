file(GLOB_RECURSE sources "*.cpp")

add_executable(${PROJECT_NAME} ${sources})
target_compile_definitions(${PROJECT_NAME} PRIVATE -Dlet=auto\ const)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
