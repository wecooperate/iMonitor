enable_precompile()
enable_qt_support()

set(PROJECT_NAME ui)

set(TS_FILES "res/language/zh_cn.ts")
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/res/language")

if(QT_ENABLE_TRANSLATION)
	find_package(Qt5LinguistTools REQUIRED)
	qt5_create_translation(QM_FILES  ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES} OPTIONS -source-language en_US -no-obsolete)
endif()

file(GLOB_RECURSE SOURCE_FILES "*.h" "*.cpp" "*.rc" "*.def" "*.qrc" "*.ui")

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${TS_FILES} ${QM_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::WinExtras core)

source_group("language" FILES ${QM_FILES} ${TS_FILES})

file(GLOB_RECURSE AUTO_GEN_FILES ${CMAKE_CURRENT_BINARY_DIR}/*.cpp)

set_source_files_properties(${AUTO_GEN_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS "ON")

#
# 部分qt的生成文件需要移除预处理，在编译前文件还没有生成，导致设置属性失败。
# 如果出现预编译头相关的编译失败，重新编译一次即可。
#
# 硬编码添加未生成的文件。
#
set(MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/ui_autogen/mocs_compilation_Debug.cpp")
list(APPEND MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/ui_autogen/mocs_compilation_Release.cpp")
list(APPEND MOC_FILES "${CMAKE_CURRENT_BINARY_DIR}/ui_autogen/EWIEGA46WW/qrc_res.cpp")
set_source_files_properties(${MOC_FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS "ON")
