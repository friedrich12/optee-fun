/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description: Host code for running sod example in the TA 
 *
 *        Version:  1.0
 *        Created:  12/07/2020 10:21:09 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Friedrich Nii-Laryea Ania Doku, 
 *   Organization:  ,  
 *
 * =====================================================================================
 */

#include <err.h>
#include <stdio.h>
#include <string.h>
/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* To the the UUID (found the the TA's h-file(s)) */
#include <sodtest_ta.h>

#include "incbin.h"
#include "xphoton_util.h"

#define INCBIN_PREFIX 
#define INCBIN_STYLE INCBIN_STYLE_SNAKE


// Load the model into memory
INCBIN(face_realnet_model, "/host/face.realnet.sod");

int 
main(void)
{

    printf("File loaded\n");
    
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = SODTEST_UUID;
	uint32_t err_origin;

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);

	/*
	 * Open a session to the TA */
	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);

	/*
	 * Execute a function in the TA by invoking it, in this case
	 * we're incrementing a number.
	 *
	 * The value of command ID part and how the parameters are
	 * interpreted is part of the interface provided by the TA.
	 */

	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_NONE,
					 TEEC_NONE, TEEC_NONE);
	op.params[0].tmpref.buffer = face_realnet_model_data;
    op.params[0].tmpref.size = face_realnet_model_size;

	/*
	 * TA_HELLO_WORLD_CMD_INC_VALUE is the actual function in the TA to be
	 * called.
	 */
	printf("SENDING MODEL.. \n");
	res = TEEC_InvokeCommand(&sess, TA_SODTEST, &op,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
			res, err_origin);
	printf("IT DIDN'T FAIL!!");

	/*
	 * We're done with the TA, close the session and
	 * destroy the context.
	 *
	 * The TA will print "Goodbye!" in the log when the
	 * session is closed.
	 */

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}

