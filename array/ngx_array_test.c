#include "ngx_array.h"
#include "ngx_palloc.h"

void dump_pool(ngx_pool_t *pool)
{
    while(pool)
    {
        printf("pool = 0x%x\n", pool);
        printf("    .d\n", pool->d.last);
        printf("      .last = 0x%x\n", pool->d.last);
        printf("      .end = 0x%x\n",pool->d.end);
        printf("      .next = 0x%x\n", pool->d.next);
        printf("      .failed = %d\n", pool->d.failed);
        printf("    .max = %d\n", pool->max);
        printf("    .current = 0x%x\n",pool->current);
        printf("    .chain = 0x%x\n", pool->chain);
        printf("    .large = 0x%x\n",pool->large);
        printf("    .cleanup = 0x%x\n", pool->cleanup);
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
        pool = pool->d.next;
    }
}


void dump_array(ngx_array_t *a)
{
    if (a)
    {
        printf("array = 0x%x\n",a);
        printf("    .elts = 0x%x\n",a->elts);
        printf("    .nelts = %d\n", a->nelts);
        printf("    .size = %d\n", a->size );
        printf("    .nalloc = %d\n",a->nalloc);
        printf("    .pool = 0x%x\n", a->pool);
        printf("elements:");
        int *ptr = (int *)(a->elts);
        for(; ptr < (int *)(a->elts + a->nalloc * a->size);)
        {
            printf("0x%x ", *ptr++);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    ngx_pool_t *pool;
    int i;
    printf("--------------------------------\n");
    printf("create a new pool:\n");
    printf("--------------------------------\n");
    pool = ngx_create_pool(1024);
    dump_pool(pool);

    printf("--------------------------------\n");
    printf("alloc an array from the pool:\n");
    printf("--------------------------------\n");
    ngx_array_t *a = ngx_array_create(pool, 10, sizeof(int));
    dump_pool(pool);

    for( i = 0; i < 10; i++)
    {
        int *pstr = ngx_array_push(a);
        *pstr = i + 1;
    }

    dump_array(a);

    ngx_array_destroy(a);
    ngx_destroy_pool(pool);
    return 0;
}
