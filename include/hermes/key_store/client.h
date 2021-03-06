/*
* Copyright (c) 2017 Cossack Labs Limited
*
* This file is a part of Hermes-core.
*
* Hermes-core is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Hermes-core is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with Hermes-core.  If not, see <http://www.gnu.org/licenses/>.
*
*/



#ifndef HERMES_KEY_STORE_CLIENT_H
#define HERMES_KEY_STORE_CLIENT_H

#include <hermes/rpc/transport.h>

#include <stdint.h>
#include <stdlib.h>

#define HM_KEY_STORE_READ_ACCESS_MASK 1
#define HM_KEY_STORE_WRITE_ACCESS_MASK 2


typedef struct hm_key_store_client_sync_type hm_key_store_client_sync_t;

hm_key_store_client_sync_t *hm_key_store_client_sync_create(hm_rpc_transport_t *transport);

uint32_t hm_key_store_client_sync_destroy(hm_key_store_client_sync_t **client);

uint32_t hm_key_store_client_sync_call_set_rtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        const uint8_t *owner_id, const size_t owner_id_length,
        const uint8_t *read_token, const size_t read_token_length);

uint32_t hm_key_store_client_sync_call_set_wtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        const uint8_t *owner_id, const size_t owner_id_length,
        const uint8_t *write_token, const size_t write_token_length);

uint32_t hm_key_store_client_sync_call_get_rtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        uint8_t **read_token, size_t *read_token_length,
        uint8_t **owner_id, size_t *owner_id_length);

uint32_t hm_key_store_client_sync_call_get_wtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        uint8_t **write_token, size_t *write_token_length,
        uint8_t **owner_id, size_t *owner_id_length);

uint32_t hm_key_store_client_sync_call_del_rtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        const uint8_t *owner_id, const size_t owner_id_length);

uint32_t hm_key_store_client_sync_call_del_wtoken(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const uint8_t *user_id, const size_t user_id_length,
        const uint8_t *owner_id, const size_t owner_id_length);

uint32_t hm_key_store_client_sync_call_get_indexed_rights(
        hm_key_store_client_sync_t *client, const uint8_t *block_id, const size_t block_id_length,
        const size_t index, uint8_t **user_id,
        size_t *user_id_length, uint32_t *rights_mask);

#endif //HERMES_KEY_STORE_CLIENT_H
