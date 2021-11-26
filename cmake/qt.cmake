#********************************************
#
# function or macro
#
#********************************************
macro(enable_qt_support)
	set(CMAKE_PREFIX_PATH $ENV{QT_DIR})
	set(Qt5LinguistTools_DIR "$ENV{QT_DIR}/Qt5LinguistTools")

	if(IS_ENABLE_PRECOMPILE)
		set (CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
	endif()
	
	set(CMAKE_AUTOUIC ON)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTORCC ON)
	
	find_package(Qt5 COMPONENTS Widgets WinExtras REQUIRED)
	
	source_group("ui\\moc" REGULAR_EXPRESSION "${CMAKE_CURRENT_BINARY_DIR}/.*\\.cpp")
	source_group("ui\\moc\\rules" REGULAR_EXPRESSION "qrc.*\\.rule")
	
	file(GLOB_RECURSE  FILES ${CMAKE_CURRENT_BINARY_DIR}/*.cpp)
	set_source_files_properties(${FILES} PROPERTIES SKIP_PRECOMPILE_HEADERS "ON")

	string_append(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
endmacro()
