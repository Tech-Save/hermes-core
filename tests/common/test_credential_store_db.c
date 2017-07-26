/*
 * Copyright (c) 2017 Cossack Labs Limited
 *
 * This file is part of Hermes.
 *
 * Hermes is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hermes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with Hermes.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "test_credential_store_db.h"
#include "common.h"

#include <hermes/common/errors.h>

#include <themis/themis.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#define __USE_GNU
#include <search.h>

typedef struct hm_test_db_node_type{
  uint8_t id[USER_ID_LENGTH];
  uint8_t pk[256];
  size_t pk_length;
}hm_test_db_node_t;

typedef struct hm_cs_test_db_type{
    void* users;
}hm_cs_test_db_t;

int hm_test_db_node_compare(const void *pa, const void *pb){
  if(!pa){
    if(!pb){
      return 0;
    }
    return -1;
  }
  if(!pb){
    return 1;
  }
  return memcmp(((hm_test_db_node_t*)pa)->id, ((hm_test_db_node_t*)pb)->id, USER_ID_LENGTH);
}

void
action(const void *nodep, const VISIT which, const int depth)
{
  hm_test_db_node_t *datap;
  switch (which) {
  case preorder:
    fprintf(stderr,"3\n");
    break;
  case postorder:
    datap = *(hm_test_db_node_t **) nodep;
    fprintf(stderr,"1\n");
    break;
  case endorder:
    fprintf(stderr,"4\n");
    break;
  case leaf:
    datap = *(hm_test_db_node_t **) nodep;
    fprintf(stderr,"2\n");
    break;
  }
}


uint32_t hm_cs_test_db_get_pub_by_id(void* db, const uint8_t* id, const size_t id_length, uint8_t** key, size_t* key_length){
  if(!db || !id || id_length!=USER_ID_LENGTH || !key){
    return HM_INVALID_PARAMETER;
  }
  hm_test_db_node_t node;
  memcpy(node.id, id, id_length);
  hm_test_db_node_t** searched_node = (hm_test_db_node_t**)tfind(&node, &(((hm_cs_test_db_t*)db)->users), hm_test_db_node_compare);
  if(!searched_node){
    return HM_FAIL;
  }
  *key=malloc((*searched_node)->pk_length);
  assert(*key);
  *key_length=(*searched_node)->pk_length;
  memcpy(*key, (*searched_node)->pk, (*searched_node)->pk_length);
  return HM_SUCCESS;
}

hm_cs_db_t* hm_test_cs_db_create(){
  hm_cs_db_t* db=calloc(1, sizeof(hm_cs_db_t));
  assert(db);
  db->user_data=calloc(1, sizeof(hm_cs_test_db_t));
  assert(db->user_data);
  db->get_pub=hm_cs_test_db_get_pub_by_id;
  //for test purpose only
  int i=0;
  uint8_t sk[256];
  char sk_filename[256];
  while(i<MAX_USERS){
    hm_test_db_node_t* node=malloc(sizeof(hm_test_db_node_t));
    node->pk_length=sizeof(node->pk);
    assert(node);
    size_t sk_length=sizeof(sk);
    assert(THEMIS_SUCCESS==soter_rand(node->id, USER_ID_LENGTH));
    assert(THEMIS_SUCCESS==themis_gen_ec_key_pair(sk, &sk_length, node->pk, &(node->pk_length)) || !(node->pk_length));
    int j=0;
    sprintf(sk_filename, "");
    for(;j<USER_ID_LENGTH;++j){
      sprintf(sk_filename, "%s%02x", sk_filename, node->id[j]);
    }
    sprintf(sk_filename, "%s.priv", sk_filename);
    FILE* sk_file=fopen(sk_filename, "wb");
    assert(sk_file);
    fwrite(sk, 1, sk_length, sk_file);
    fclose(sk_file);
    hm_test_db_node_t* searched_node = *(hm_test_db_node_t**)tsearch(node, &(((hm_cs_test_db_t*)(db->user_data))->users), hm_test_db_node_compare);
    assert(searched_node);
    if(searched_node != node){
      free(node);
      continue;
    }
    ++i;
  }
  //
  return db;
}


uint32_t hm_test_cs_db_destroy(hm_cs_db_t** db){
  if(!db || !(*db) || !((hm_cs_test_db_t*)((*db)->user_data))){
    return HM_INVALID_PARAMETER;
  }
  system("rm *.priv");
  tdestroy(((hm_cs_test_db_t*)((*db)->user_data))->users, free);
  free((*db)->user_data);
  free(*db);
  *db=NULL;
  return HM_SUCCESS;
}

