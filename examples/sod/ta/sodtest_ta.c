// Copyright (c) 2020, Friedrich Doku


#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <sodtest_ta.h>

TEE_Result
TA_CreateEntryPoint(void)
{
	IMSG("ENTRY POINT CREATED");
	return TEE_SUCCESS;
}

void
TA_DestroyEntryPoint(void)
{
	IMSG("Destory Entry Point");
}

TEE_Result
TA_OpenSessionEntryPoint(uint32_t				  param_types,
						 TEE_Param __maybe_unused params[4],
						 void __maybe_unused ** sess_ctx)
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types) {
		return TEE_ERROR_BAD_PARAMETERS;
	}

	(void)&params;
	(void)&sess_ctx;

	return TEE_SUCCESS;
}

void
TA_CloseSessionEntryPoint(void __maybe_unused * sess_ctx)
{
	(void)&sess_ctx; /* unused parameter*/
	IMSG("Goodbye To A World\n");
}

static TEE_Result
sodtest(uint32_t  param_types,
		TEE_Param params[4])
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types) {
		return TEE_ERROR_BAD_PARAMETERS;
	}


    unsigned char* face_realnet_model_data;
    uint32_t face_realnet_model_size;

    face_realnet_model_data = params[0].memref.buffer;
    face_realnet_model_size = params[0].memref.size;
   
    IMSG("THE TA GOT THE MODEL");

    int ret = 0;
    sod_realnet *pNet = NULL;

    ret = sod_realnet_create(&pNet);
    if(ret != SOD_OK){
        DMSG("Could not create sod realnet.");
        return TEE_ERROR_GENERIC;
    }

    ret = sod_realnet_load_model_from_mem(pNet, face_realnet_model_data, face_realnet_model_size, 0);

    if(ret != SOD_OK){
        DMSG("Could not load model realnet.");
        goto err;
    }

	return TEE_SUCCESS;

err:
    if(pNet != NULL) sod_realnet_destroy(pNet);
    return TEE_ERROR_GENERIC;
}


TEE_Result
TA_InvokeCommandEntryPoint(void __maybe_unused * sess_ctx,
						   uint32_t				 cmd_id,
						   uint32_t				 param_types,
						   TEE_Param			 params[4])
{
	if (cmd_id == TA_SODTEST) {
		return sodtest(param_types, params);
	}
}
