
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#include "ngx_alloc.h"


ngx_uint_t  ngx_pagesize;
ngx_uint_t  ngx_pagesize_shift;
ngx_uint_t  ngx_cacheline_size;


void *
ngx_alloc(size_t size)
{
    void  *p;

    p = malloc(size);
    if (p == NULL) {
        printf("malloc(%uz) failed\n", size);
    }

    printf("malloc: %p:%uz\n", p, size);

    return p;
}


void *
ngx_calloc(size_t size)
{
    void  *p;

    p = ngx_alloc(size);

    if (p) {
        ngx_memzero(p, size);
    }

    return p;
}


#if (NGX_HAVE_POSIX_MEMALIGN)

void *
ngx_memalign(size_t alignment, size_t size)
{
    void  *p;
    int    err;

    err = posix_memalign(&p, alignment, size);

    if (err) {
        printf("posix_memalign(%uz, %uz) failed\n", alignment, size);
        p = NULL;
    }

    printf("posix_memalign: %p:%uz @%uz\n", p, size, alignment);

    return p;
}

#elif (NGX_HAVE_MEMALIGN)

void *
ngx_memalign(size_t alignment, size_t size)
{
    void  *p;

    p = memalign(alignment, size);
    if (p == NULL) {
        printf("memalign(%uz, %uz) failed\n", alignment, size);
    }

    printf("memalign: %p:%uz @%uz\n", p, size, alignment);

    return p;
}

#endif
