// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdlib.h>
#ifdef _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif
#include <string.h>
#include "sasl_anonymous.h"
#include "amqpalloc.h"
#include "logger.h"

typedef struct SASL_ANONYMOUS_INSTANCE_TAG
{
	unsigned char dummy : 1;
} SASL_ANONYMOUS_INSTANCE;

static const SASL_MECHANISM_INTERFACE_DESCRIPTION saslanonymous_interface =
{
	saslanonymous_create,
	saslanonymous_destroy,
	saslanonymous_get_init_bytes,
	saslanonymous_get_mechanism_name
};

/* Codes_SRS_SASL_ANONYMOUS_01_001: [saslanonymous_create shall return on success a non-NULL handle to a new SASL anonymous mechanism.] */
CONCRETE_SASL_MECHANISM_HANDLE saslanonymous_create(void* config)
{
	/* Codes_SRS_SASL_ANONYMOUS_01_003: [Since this is the ANONYMOUS SASL mechanism, config shall be ignored.] */
	(void)config;

	/* Codes_SRS_SASL_ANONYMOUS_01_002: [If allocating the memory needed for the saslanonymous instance fails then saslanonymous_create shall return NULL.] */
	return amqpalloc_malloc(sizeof(SASL_ANONYMOUS_INSTANCE));
}

void saslanonymous_destroy(CONCRETE_SASL_MECHANISM_HANDLE sasl_mechanism_concrete_handle)
{
	/* Codes_SRS_SASL_ANONYMOUS_01_005: [If the argument concrete_sasl_mechanism is NULL, saslannymous_destroy shall do nothing.] */
	if (sasl_mechanism_concrete_handle != NULL)
	{
		/* Codes_SRS_SASL_ANONYMOUS_01_004: [saslannymous_destroy shall free all resources associated with the SASL mechanism.] */
		amqpalloc_free(sasl_mechanism_concrete_handle);
	}
}

int saslanonymous_get_init_bytes(CONCRETE_SASL_MECHANISM_HANDLE sasl_mechanism_concrete_handle, SASL_MECHANISM_BYTES* init_bytes)
{
	int result;

	/* Codes_SRS_SASL_ANONYMOUS_01_007: [If the any argument is NULL, saslanonymous_get_init_bytes shall return a non-zero value.] */
	if ((sasl_mechanism_concrete_handle == NULL) ||
		(init_bytes == NULL))
	{
		result = __LINE__;
	}
	else
	{
		/* Codes_SRS_SASL_ANONYMOUS_01_012: [The bytes field of init_buffer shall be set to NULL.] */
		init_bytes->bytes = NULL;
		/* Codes_SRS_SASL_ANONYMOUS_01_006: [saslanonymous_get_init_bytes shall validate the concrete_sasl_mechanism argument and set the length of the init_bytes argument to be zero.] */
		init_bytes->length = 0;

		/* Codes_SRS_SASL_ANONYMOUS_01_011: [On success saslanonymous_get_init_bytes shall return zero.] */
		result = 0;
	}

	return result;
}

const char* saslanonymous_get_mechanism_name(CONCRETE_SASL_MECHANISM_HANDLE sasl_mechanism)
{
	const char* result;

	/* Codes_SRS_SASL_ANONYMOUS_01_009: [If the argument concrete_sasl_mechanism is NULL, saslanonymous_get_mechanism_name shall return NULL.] */
	if (sasl_mechanism == NULL)
	{
		result = NULL;
	}
	else
	{
		/* Codes_SRS_SASL_ANONYMOUS_01_008: [saslanonymous_get_mechanism_name shall validate the argument concrete_sasl_mechanism and on success it shall return a pointer to the string �ANONYMOUS�.] */
		result = "ANONYMOUS";
	}

	return result;
}

const SASL_MECHANISM_INTERFACE_DESCRIPTION* saslanonymous_get_interface(void)
{
	return &saslanonymous_interface;
}