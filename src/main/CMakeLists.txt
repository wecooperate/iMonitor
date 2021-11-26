enable_precompile()
enable_subsystem_windows()

set(PROJECT_NAME iMonitor)

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" "*.rc")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ui core)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")
