/*
 * Copyright (c) 2015 Cossack Labs Limited
 */

#ifndef PROTOCOLS_RECORD_SET_H_
#define PROTOCOLS_RECORD_SET_H_

#include "srpc.h"
#include "functions_collection.h"
#include "protocols.h"
#include "stubs_generator.h"

typedef struct{
  srpc_ctx_t* srpc_ctx_;
  uint8_t* tmp_buf_;
  size_t tmp_buf_length_;
}record_set_t;

record_set_t* record_set_create();
protocol_status_t record_set_bind(record_set_t* ctx, const char* endpoint, void* call_ctx);
protocol_status_t record_set_connect(record_set_t* ctx, const char* endpoint, const char* id);
protocol_status_t record_set_call(record_set_t* ctx, const char* func_name, const uint8_t* param_buf, const size_t param_buf_length, void (*proxy_handler)(void* ctx, const uint8_t* res_buf, const size_t res_buf_length), void* call_ctx);
protocol_status_t record_set_sync_call(record_set_t* ctx, const char* func_name, const uint8_t* param_buf, const size_t param_buf_length, uint8_t** res_buf, size_t* res_buf_length);
protocol_status_t record_set_destroy(record_set_t* ctx);

HERMES_FUNCTION_DEFINITIONS(record_set, get_doc_breaf);
HERMES_FUNCTION_DEFINITIONS(record_set, get_doc);
HERMES_FUNCTION_DEFINITIONS(record_set, get_doc_data);
HERMES_FUNCTION_DEFINITIONS(record_set, get_public_block);
HERMES_FUNCTION_DEFINITIONS(record_set, get_private_block);
HERMES_FUNCTION_DEFINITIONS(record_set, add_document);
HERMES_FUNCTION_DEFINITIONS(record_set, update_document);
HERMES_FUNCTION_DEFINITIONS(record_set, update_public_block);
HERMES_FUNCTION_DEFINITIONS(record_set, update_private_block);
HERMES_FUNCTION_DEFINITIONS(record_set, add_public_block);
HERMES_FUNCTION_DEFINITIONS(record_set, add_private_block);
HERMES_FUNCTION_DEFINITIONS(record_set, delete_public_block);
HERMES_FUNCTION_DEFINITIONS(record_set, delete_private_block);
HERMES_FUNCTION_DEFINITIONS(record_set, delete_document);
HERMES_FUNCTION_DEFINITIONS(record_set, get_docs);
HERMES_FUNCTION_DEFINITIONS(record_set, add_access);
HERMES_FUNCTION_DEFINITIONS(record_set, rm_access);

extern functions_collection_t record_set_functions_collection;


#endif /* PROTOCOLS_RECORD_SET_H_ */