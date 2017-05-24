// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef IOTHUBTRANSPORT_GENERIC_AMQP_MESSENGER
#define IOTHUBTRANSPORT_GENERIC_AMQP_MESSENGER

#include "azure_c_shared_utility/umock_c_prod.h"
#include "azure_c_shared_utility/optionhandler.h"
#include "azure_uamqp_c/session.h"
#include "iothub_client_private.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct GMESSENGER_INSTANCE* GMESSENGER_HANDLE;

typedef enum GMESSENGER_SEND_STATUS_TAG
{
	GMESSENGER_SEND_STATUS_IDLE,
	GMESSENGER_SEND_STATUS_BUSY
} GMESSENGER_SEND_STATUS;

typedef enum GMESSENGER_SEND_COMPLETE_RESULT_TAG
{
	GMESSENGER_SEND_COMPLETE_RESULT_OK,
	GMESSENGER_SEND_COMPLETE_RESULT_ERROR_CANNOT_PARSE,
	GMESSENGER_SEND_COMPLETE_RESULT_ERROR_FAIL_SENDING,
	GMESSENGER_SEND_COMPLETE_RESULT_ERROR_TIMEOUT,
	GMESSENGER_SEND_COMPLETE_RESULT_GMESSENGER_DESTROYED
} GMESSENGER_SEND_COMPLETE_RESULT;

typedef enum GMESSENGER_DISPOSITION_RESULT_TAG
{
	GMESSENGER_DISPOSITION_RESULT_NONE,
	GMESSENGER_DISPOSITION_RESULT_ACCEPTED,
	GMESSENGER_DISPOSITION_RESULT_REJECTED,
	GMESSENGER_DISPOSITION_RESULT_RELEASED
} GMESSENGER_DISPOSITION_RESULT;

typedef enum GMESSENGER_STATE_TAG
{
	GMESSENGER_STATE_STARTING,
	GMESSENGER_STATE_STARTED,
	GMESSENGER_STATE_STOPPING,
	GMESSENGER_STATE_STOPPED,
	GMESSENGER_STATE_ERROR
} GMESSENGER_STATE;

typedef struct GMESSENGER_MESSAGE_DISPOSITION_INFO_TAG
{
	delivery_number message_id;
	char* source;
} GMESSENGER_MESSAGE_DISPOSITION_INFO;

typedef void(*ON_GMESSENGER_SEND_COMPLETE)(IOTHUB_MESSAGE_LIST* iothub_message_list, GMESSENGER_SEND_COMPLETE_RESULT gmessenger_event_send_complete_result, void* context);
typedef void(*ON_GMESSENGER_STATE_CHANGED_CALLBACK)(void* context, GMESSENGER_STATE previous_state, GMESSENGER_STATE new_state);
typedef GMESSENGER_DISPOSITION_RESULT(*ON_GMESSENGER_MESSAGE_RECEIVED)(IOTHUB_MESSAGE_HANDLE message, GMESSENGER_MESSAGE_DISPOSITION_INFO* disposition_info, void* context);

typedef struct GMESSENGER_CONFIG_TAG
{
	const char* device_id;
	char* iothub_host_fqdn;
	ON_GMESSENGER_STATE_CHANGED_CALLBACK on_state_changed_callback;
	void* on_state_changed_context;
	char* send_link_relative_path;
	char* receive_link_relative_path;
	MAP_HANDLE send_link_attach_properties;
	MAP_HANDLE receive_link_attach_properties;
} GMESSENGER_CONFIG;

MOCKABLE_FUNCTION(, GMESSENGER_HANDLE, gmessenger_create, const GMESSENGER_CONFIG*, gmessenger_config);
MOCKABLE_FUNCTION(, int, gmessenger_send_async, GMESSENGER_HANDLE, gmessenger_handle, void*, message, ON_GMESSENGER_SEND_COMPLETE, on_gmessenger_event_send_complete_callback, void*, context);
MOCKABLE_FUNCTION(, int, gmessenger_subscribe_for_messages, GMESSENGER_HANDLE, gmessenger_handle, ON_GMESSENGER_MESSAGE_RECEIVED, on_message_received_callback, void*, context);
MOCKABLE_FUNCTION(, int, gmessenger_unsubscribe_for_messages, GMESSENGER_HANDLE, gmessenger_handle);
MOCKABLE_FUNCTION(, int, gmessenger_send_message_disposition, GMESSENGER_HANDLE, gmessenger_handle, GMESSENGER_MESSAGE_DISPOSITION_INFO*, disposition_info, GMESSENGER_DISPOSITION_RESULT, disposition_result);
MOCKABLE_FUNCTION(, int, gmessenger_get_send_status, GMESSENGER_HANDLE, gmessenger_handle, GMESSENGER_SEND_STATUS*, send_status);
MOCKABLE_FUNCTION(, int, gmessenger_start, GMESSENGER_HANDLE, gmessenger_handle, SESSION_HANDLE, session_handle);
MOCKABLE_FUNCTION(, int, gmessenger_stop, GMESSENGER_HANDLE, gmessenger_handle);
MOCKABLE_FUNCTION(, void, gmessenger_do_work, GMESSENGER_HANDLE, gmessenger_handle);
MOCKABLE_FUNCTION(, void, gmessenger_destroy, GMESSENGER_HANDLE, gmessenger_handle);
MOCKABLE_FUNCTION(, int, gmessenger_set_option, GMESSENGER_HANDLE, gmessenger_handle, const char*, name, void*, value);
MOCKABLE_FUNCTION(, OPTIONHANDLER_HANDLE, gmessenger_retrieve_options, GMESSENGER_HANDLE, gmessenger_handle);


#ifdef __cplusplus
}
#endif

#endif /*IOTHUBTRANSPORT_AMQP_MESSENGER*/
