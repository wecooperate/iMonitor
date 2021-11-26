macro(git_get_hash hash)
	set(hash "")
	find_package(Git QUIET)
	if(GIT_FOUND)
		execute_process(
		COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
		OUTPUT_VARIABLE ${hash}
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET
		WORKING_DIRECTORY
		${CMAKE_CURRENT_SOURCE_DIR})
	endif()
endmacro()

macro(git_get_branch branch)
	set(branch "")
	find_package(Git QUIET)
	if(GIT_FOUND)
		execute_process(
		COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
		OUTPUT_VARIABLE ${branch}
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET
		WORKING_DIRECTORY
		${CMAKE_CURRENT_SOURCE_DIR})
	endif()
endmacro()
