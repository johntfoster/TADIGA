# Copyright 2017 John T. Foster

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#    http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
find_program(GCOV_PATH gcov)
find_program(LCOV_PATH lcov)

if(NOT GCOV_PATH)
	message(FATAL_ERROR "gcov not found! Aborting...")
endif() # NOT GCOV_PATH

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
	if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 3)
		message(FATAL_ERROR "Clang version must be 3.0.0 or greater! Aborting...")
	endif()
elseif(NOT CMAKE_COMPILER_IS_GNUCXX)
	message(FATAL_ERROR "Compiler is not GNU gcc! Aborting...")
endif() 

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  message( WARNING "Code coverage results with an optimized (non-Debug) build may be misleading" )
endif() 

function(setup_target_for_coverage _targetname _testrunner _outputname)

	if(NOT LCOV_PATH)
		message(FATAL_ERROR "lcov not found! Aborting...")
	endif() # NOT LCOV_PATH

	set(coverage_info "${CMAKE_BINARY_DIR}/${_outputname}.info")
	set(coverage_cleaned "${coverage_info}.cleaned")

	separate_arguments(test_command UNIX_COMMAND "${_testrunner}")

	# Setup target
	add_custom_target(${_targetname}

		# Cleanup lcov
		${LCOV_PATH} --directory . --zerocounters

		# Run tests
        COMMAND ${test_command} ${ARGV3}

		# Capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} --directory . --capture --output-file ${coverage_info}
        COMMAND ${LCOV_PATH} --remove ${coverage_info} '*/test/*' '*/tests/*' '/usr*' '*trilinos*' '*Trilinos*' '*Xcode*'  --output-file ${coverage_cleaned}
        COMMAND ${CMAKE_COMMAND} -E remove ${coverage_info}

		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
		COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
	)

ENDFUNCTION() 
