/*
 * jcr.cpp
 *
 *  Created on: Feb 15, 2012
 *      Author: fumin
 */

#include "jcr.h"

Jcr* new_write_jcr() {
	Jcr *jcr = (Jcr*) malloc(sizeof(Jcr));
	jcr->job_id = 0;
	jcr->file_num = 0;
	jcr->job_size = 0;
	jcr->dedup_size= 0;
	jcr->chunk_num= 0;
	jcr->number_of_dup_chunks = 0;
    jcr->zero_chunk_amount = 0;
    jcr->zero_chunk_count = 0;
    jcr->rewritten_chunk_amount = 0;
    jcr->rewritten_chunk_count = 0;
    jcr->time = 0;

    jcr->total_container_num = 0;
    jcr->sparse_container_num = 0;
    jcr->inherited_sparse_num = 0;

	jcr->read_time = 0;
	jcr->chunk_time = 0;
	jcr->name_time = 0;
	jcr->filter_time = 0;
	jcr->write_time = 0;
	jcr->test_time = 0;

	jcr->read_chunk_time = 0;
	jcr->write_file_time = 0;

	jcr->completed_files_queue = sync_queue_new(-1);
	jcr->waiting_files_queue = sync_queue_new(-1);
    jcr->fingerchunk_queue = sync_queue_new(-1);

	jcr->write_buffer = 0;
	jcr->read_cache = 0;

	return jcr;
}

Jcr* new_read_jcr(int32_t rcs, BOOL edc) {
	Jcr* jcr = new_write_jcr();
	jcr->enable_data_cache = edc;
	jcr->read_cache_size = rcs;
    jcr->read_cache = 0;
    jcr->read_opt_cache = 0;
	return jcr;
}

void free_jcr(Jcr* jcr) {
	if (jcr->write_buffer)
		container_free_full(jcr->write_buffer);
	sync_queue_free(jcr->completed_files_queue, 0);
    sync_queue_free(jcr->waiting_files_queue, 0);
    sync_queue_free(jcr->fingerchunk_queue, 0);
	free(jcr);
}
