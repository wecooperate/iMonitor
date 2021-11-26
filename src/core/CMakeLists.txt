enable_precompile()

set(PROJECT_NAME core)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} base ws2_32)
