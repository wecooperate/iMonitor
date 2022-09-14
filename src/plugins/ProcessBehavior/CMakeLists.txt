enable_precompile()

get_current_folder(PROJECT_NAME)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" "*.rc")

include_directories(../Base)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} base PluginBase)
