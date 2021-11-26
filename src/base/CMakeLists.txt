enable_precompile()

set(PROJECT_NAME base)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})
