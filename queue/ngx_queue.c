
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */

#include "ngx_queue.h"

/*
 * find the middle queue element if the queue has odd number of elements
 * or the first element of the queue's second part otherwise
 */

ngx_queue_t *
ngx_queue_middle(ngx_queue_t *queue)
{
    ngx_queue_t  *middle, *next;

    middle = ngx_queue_head(queue);

    if (middle == ngx_queue_last(queue)) {
        return middle;
    }

    next = ngx_queue_head(queue);

    for ( ;; ) {
        middle = ngx_queue_next(middle);

        next = ngx_queue_next(next);

        if (next == ngx_queue_last(queue)) {
            return middle;
        }

        next = ngx_queue_next(next);

        if (next == ngx_queue_last(queue)) {
            return middle;
        }
    }
}


/* the stable insertion sort */

void
ngx_queue_sort(ngx_queue_t *queue,
    ngx_int_t (*cmp)(const ngx_queue_t *, const ngx_queue_t *))
{
    ngx_queue_t  *q, *prev, *next;

    q = ngx_queue_head(queue);

    if (q == ngx_queue_last(queue)) {
        return;
    }

    for (q = ngx_queue_next(q); q != ngx_queue_sentinel(queue); q = next) {

        prev = ngx_queue_prev(q);
        next = ngx_queue_next(q);

        ngx_queue_remove(q);

        do {
            if (cmp(prev, q) <= 0) {
                break;
            }

            prev = ngx_queue_prev(prev);

        } while (prev != ngx_queue_sentinel(queue));

        ngx_queue_insert_after(prev, q);
    }
}

#if 0
void dump_pool(ngx_pool_t* pool)  
{  
    while (pool)  
    {  
        printf("pool = 0x%x\n", pool);  
        printf("  .d\n");  
        printf("    .last = 0x%x\n", pool->d.last);  
        printf("    .end = 0x%x\n", pool->d.end);  
        printf("    .next = 0x%x\n", pool->d.next);  
        printf("    .failed = %d\n", pool->d.failed);  
        printf("  .max = %d\n", pool->max);  
        printf("  .current = 0x%x\n", pool->current);  
        printf("  .chain = 0x%x\n", pool->chain);  
        printf("  .large = 0x%x\n", pool->large);  
        printf("  .cleanup = 0x%x\n", pool->cleanup);  
        //printf("  .log = 0x%x\n", pool->log);  
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);  
        pool = pool->d.next;  
    }  
}  

int main(int argc, char *argv[])
{
	ngx_pool_t *pool;
	ngx_queue_t *myQueue;

	printf("--------------------------------\n");  
    printf("create a new pool:\n");  
    printf("--------------------------------\n");  
    pool = ngx_create_pool(1024);  

	dump_pool(pool); 

 	printf("--------------------------------\n");  
    printf("alloc a queue head and nodes :\n");  
    printf("--------------------------------\n");  
    myQueue = ngx_palloc(pool, sizeof(ngx_queue_t));  //alloc a queue head  
    ngx_queue_init(myQueue);  //init the queue 
	
	
	return 0;
}
#endif
