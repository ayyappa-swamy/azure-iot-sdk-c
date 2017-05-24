#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#this is CMakeLists.txt for devicemethod_simplesample sample

if(NOT ${use_mqtt} AND NOT ${use_amqp})
	message(FATAL_ERROR "devicemethod_simplesample being generated without mqtt or amqp support")
endif()

if(${use_mqtt})
	add_definitions(-DUSE_MQTT)
endif()

if(${use_amqp})
	add_definitions(-DUSE_AMQP)
endif()

compileAsC99()

set(devicemethod_simplesample_c_files
	devicemethod_simplesample.c
)

if(WIN32)
	set(devicemethod_simplesample_c_files ${devicemethod_simplesample_c_files} ./windows/main.c)
else()
	set(devicemethod_simplesample_c_files ${devicemethod_simplesample_c_files} ./linux/main.c)
endif()

set(devicemethod_simplesample_h_files
	devicemethod_simplesample.h
)

IF(WIN32)
	#windows needs this define
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

include_directories(. ${SHARED_UTIL_INC_FOLDER} ${IOTHUB_CLIENT_INC_FOLDER})

add_executable(devicemethod_simplesample ${devicemethod_simplesample_c_files} ${devicemethod_simplesample_h_files})

if(${use_mqtt})
	include_directories(. ${IOTHUB_CLIENT_MQTT_TRANSPORT_INC_FOLDER})

	target_link_libraries(devicemethod_simplesample
		iothub_client_mqtt_transport
		)
endif()

if(${use_amqp})
	include_directories(. ${IOTHUB_CLIENT_AMQP_TRANSPORT_INC_FOLDER})

	target_link_libraries(devicemethod_simplesample
		iothub_client_amqp_transport
		)
endif()

if (${use_amqp})
	linkUAMQP(devicemethod_simplesample)
endif()

target_link_libraries(devicemethod_simplesample
	serializer 
	iothub_client
	)