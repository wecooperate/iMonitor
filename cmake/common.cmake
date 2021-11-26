option(GROUP_BY_EXPLORER ON)
#********************************************
#
# function or macro
#
#********************************************
macro(add_subdirectory_all)
	file(GLOB folders RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*)
	foreach(folder ${folders})
		if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${folder})
			if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${folder}/CMakeLists.txt)
				add_subdirectory(${folder})
			endif()
		endif()
	endforeach()
endmacro()

macro(get_current_folder folder) 
	STRING(REGEX REPLACE ".*/(.*)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})
	set(${folder} ${CURRENT_FOLDER})
endmacro()

macro(set_project_folder project folder)
	if(TARGET ${project})
		set_target_properties(${project} PROPERTIES FOLDER ${folder})
	endif()
endmacro()

macro(set_source_folder folder source)
	source_group(${folder} FILES ${source})
endmacro()

macro(set_source_folder_auto)
	foreach(filename IN ITEMS ${ARGN})
		get_filename_component(filepath "${filename}" PATH)
		string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" folderpath "${filepath}")
		string(REPLACE "/" "\\" folderpath "${folderpath}")
		string(REPLACE "\\.\\" "\\" folderpath "${folderpath}")
		#if(folderpath STREQUAL "")
		#	set(folderpath "main")
		#endif()
		source_group("${folderpath}" FILES "${filename}")
		STRING(REGEX MATCH ".*.rc" RC_FILE "${filename}")
		if(RC_FILE STREQUAL ${filename})
			source_group("res" FILES "${filename}")
		endif()
	endforeach()
	set_source_folder("Precompile" "stdafx.h;stdafx.cpp;export.def")
endmacro()

macro(string_append target str)
	set(${target} "${${target}} ${str}")
endmacro()

macro(set_link_flags target flags)
	set_target_properties(${target} PROPERTIES LINK_FLAGS ${flags})
endmacro()

macro(enable_precompile)
if(MSVC)
	string_append(CMAKE_CXX_FLAGS_DEBUG "/Yustdafx.h")
	string_append(CMAKE_CXX_FLAGS_RELEASE "/Yustdafx.h")
	set_source_files_properties(stdafx.cpp PROPERTIES COMPILE_FLAGS "/Ycstdafx.h")
endif()
	set(IS_ENABLE_PRECOMPILE ON)
endmacro()

macro(enable_subsystem_windows)
	set(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
endmacro()
#********************************************
#
# global setting
#
#********************************************
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER cmake)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#********************************************
#
# define
#
#********************************************
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
if(MSVC)
	add_definitions(-DUNICODE)
	add_definitions(-D_UNICODE)
endif()
add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)

if(CMAKE_CL_64)
	set(OS_64 ON)
endif()
#********************************************
#
# output
#
#********************************************
if(OS_64)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/64")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/64")
	set(EXECUTABLE_OUTPUT_PATH_DEBUG "${PROJECT_SOURCE_DIR}/bin/64")
	set(EXECUTABLE_OUTPUT_PATH_RELEASE "${PROJECT_SOURCE_DIR}/bin/64")
	set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/64")
else()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/32")
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/32")
	set(EXECUTABLE_OUTPUT_PATH_DEBUG "${PROJECT_SOURCE_DIR}/bin/32")
	set(EXECUTABLE_OUTPUT_PATH_RELEASE "${PROJECT_SOURCE_DIR}/bin/32")
	set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib/32")
endif()
#********************************************
#
# include
#
#********************************************
set(dir_inc_common
	${PROJECT_BINARY_DIR}
	.
	inc
	inc/core
	inc/third_party
	inc/res
	inc/common
	inc/common/third_party
	inc/common/res
	src/
	src/third_party)	
include_directories(${dir_inc_common})
#********************************************
#
# link library
#
#********************************************
set(dir_lib_common
	lib)
	
if(OS_64)
	list(APPEND dir_lib_common lib/64)
endif()
	
link_directories(${dir_lib_common})
#********************************************
#
# compile
#
#********************************************
if (MSVC)
	set(CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /MP")
	set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS})
	set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS})

if (MSVC_MT)
	string_append(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG /D_DEBUG /Zi /MTd /Od")
	string_append(CMAKE_CXX_FLAGS_RELEASE "/DNODEBUG /D_NODEBUG /Zi /MT /Ob2")
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/NODEFAULTLIB:MSVCRTD ${CMAKE_SHARED_LINKER_FLAGS_DEBUG}")
	set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/NODEFAULTLIB:MSVCRT ${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
else()	
	string_append(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG /D_DEBUG /Zi /MDd /Od")
	string_append(CMAKE_CXX_FLAGS_RELEASE "/DNODEBUG /D_NODEBUG /Zi /MD /Ob2")
endif()
	set(SUPPORT_XP_CFLAGS "/Zc:threadSafeInit-")
	string_append(CMAKE_CXX_FLAGS_DEBUG ${SUPPORT_XP_CFLAGS})
	string_append(CMAKE_CXX_FLAGS_RELEASE ${SUPPORT_XP_CFLAGS})

	set(CMAKE_C_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
	set(CMAKE_C_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
	
	string_append(CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:CONSOLE")
	string_append(CMAKE_SHARED_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")

	string_append(CMAKE_EXE_LINKER_FLAGS_RELEASE "/DEBUG /OPT:REF /OPT:ICF")
	string_append(CMAKE_SHARED_LINKER_FLAGS_RELEASE "/DEBUG /OPT:REF /OPT:ICF")
endif()

macro(enable_msvc_mt)
	string(REPLACE "/MDd" "/MTd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

macro(disable_msvc_mt)
	string(REPLACE "/MTd" "/MDd" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
	string(REPLACE "/MT" "/MD" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
endmacro()

