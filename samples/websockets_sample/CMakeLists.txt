#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

compileAsC11()

add_executable(websockets_sample
	main.c
	iothub_certs.h
	iothub_certs.c)
	
#TODO: link to whatever else the platform has (now for windows it is just ws2_32)

include_directories(.)
if(WIN32)
	#windows needs this define
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DGB_MEASURE_MEMORY_FOR_THIS -DGB_DEBUG_ALLOC)

	target_link_libraries(websockets_sample
		uamqp
		ws2_32
		$ENV{OpenSSLDir}/lib/ssleay32.lib $ENV{OpenSSLDir}/lib/libeay32.lib		
		aziotsharedutil.lib
		$ENV{WSDir}/build/lib/Debug/websockets_static.lib
		$ENV{WSDir}/build/lib/Debug/zlib_internal.lib)
	file(COPY $ENV{OpenSSLDir}/bin/libeay32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY $ENV{OpenSSLDir}/bin/ssleay32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
else()
	target_link_libraries(websockets_sample	uamqp aziotsharedutil ssl crypto)
endif()