#include "../api/vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define null NULL; 

struct vector {
        int32_t  *buffer;
        uint32_t items_count;
        float grow_factor;
        uint32_t capacity;
};

struct vector *vector_create(uint32_t initial_size, float grow_factor)
{
        struct vector *vp = null;
        
        if (!initial_size)
                return null;

        vp = (struct vector*)malloc(sizeof(*vp));
        if (!vp)
                return null;
        
        vp->buffer = malloc(sizeof(int32_t) * initial_size);
        if (!vp->buffer) {
                goto out_free_vector;
        } else {
                /* init struct vector before return */
                vp->grow_factor = grow_factor;
                vp->items_count = 0;
                vp->capacity = initial_size;
                srand((unsigned int)time(NULL));   /* Initialization, should only be called once. */
                return vp;
        }

        out_free_vector:
                free(vp);
                return null;
}

void vector_destroy(struct vector **vec)
{
        if (vec && *vec) {
                free((*vec)->buffer);
                free(*vec);
                *vec = null;
        }
}

__bool vector_empty(const struct vector *vec)
{
        if (vec) {
                return (vec->items_count == 0);
        } else {
                return true;
        }
}

uint32_t vector_size(const struct vector *vec)
{
        if (vec) {
                return vec->items_count;
        } else {
                return 0;
        }
}

static enum vector_status grow_if_required(struct vector *vec)
{
        int32_t *new_buf;
        float rem = (float)( (vec->capacity - vec->items_count)/(vec->capacity) );
        
        if (rem < vec->grow_factor) {
                new_buf = realloc(vec->buffer, (uint32_t)( (float)vec->capacity * (1 + vec->grow_factor) )*sizeof(int32_t));
                if (!new_buf) {
                        return VECTOR_INSERT_SUCCEED_BUT_FAILS_TO_GROW;
                } else {
                        vec->buffer = new_buf;
                        vec->capacity = (uint32_t)((float)vec->capacity * (1 + vec->grow_factor));
                }
        }
        return VECTOR_SUCCESS;
}

enum vector_status vector_push_back(struct vector *vec, int32_t item)
{
        enum vector_status e;

        if (!vec)
                return VECTOR_INVALID_VECTOR_POINTER;
        
        /* if there is enough space, push and grow_if_required */
        e = grow_if_required(vec);
        if (vec->items_count < vec->capacity) {
                vec->buffer[vec->items_count] = item;
                ++vec->items_count;
        } else if (0 == vec->grow_factor) {
                e = VECTOR_OVERFLOW;
        }

        return e;
}

enum vector_status shrink_if_required(struct vector *vec)
{
        int32_t *new_buf;
        float rem = (float)( (vec->capacity - vec->items_count)/(vec->capacity) );
        
        if (rem > 2 * vec->grow_factor) {
                new_buf = realloc(vec->buffer, (uint32_t)( (float)vec->capacity * (1 - vec->grow_factor) )*sizeof(int32_t));
                if (!new_buf) {
                        return VECTOR_INSERT_SUCCEED_BUT_FAILS_TO_GROW;
                } else {
                        vec->buffer = new_buf;
                        vec->capacity = (uint32_t)((float)vec->capacity * (1 + vec->grow_factor));
                }
        }
        return VECTOR_SUCCESS;
}

enum vector_status vector_pop_back(struct vector *vec, int32_t *item)
{
        enum vector_status e;

        if (!vec || !item)
                return VECTOR_INVALID_VECTOR_POINTER;
        
        if (vec->grow_factor) {
                e = shrink_if_required(vec);
        }
        
        if(vec->items_count)
        {
                *item = vec->buffer[--vec->items_count];
                e = VECTOR_SUCCESS;
        }
        return e;
}

void vector_for_each(struct vector *vec, void (*action)(int32_t*, void*), void *context)
{
        uint32_t j;

        if (!vec || !action){
                return;
        }

        for (j = 0; j < vec->items_count; ++j) {
                action(&vec->buffer[j], context);
        }
}

enum vector_status vector_get(const struct vector *vec, uint32_t index, int32_t *item)
{
        if (!vec) {
                return VECTOR_INVALID_VECTOR_POINTER;
        }

        if (index >= vec->items_count) {
                return VECTOR_INDEX_OUT_OF_BOUNDS;
        }

        if (!item) {
                return VECTOR_INVALID_INPUT_ARGS;
        }

        *item = vec->buffer[index];
        return VECTOR_SUCCESS;
}

enum vector_status vector_set(struct vector *vec, uint32_t index, int32_t item)
{
        if (!vec) {
                return VECTOR_INVALID_VECTOR_POINTER;
        }

        if (index >= vec->items_count) {
                return VECTOR_INDEX_OUT_OF_BOUNDS;
        }

        vec->buffer[index] = item;
        return VECTOR_SUCCESS;
}

enum vector_status vector_back(const struct vector *vec, int32_t *item)
{
        if (!vec) {
                return VECTOR_INVALID_VECTOR_POINTER;
        }

        if (!vec->items_count) {
                return VECTOR_IS_EMPTY;
        }

        if (!item) {
                return VECTOR_INVALID_INPUT_ARGS;
        }

        *item = vec->buffer[vec->items_count-1];
        return VECTOR_SUCCESS;
}

enum vector_status vector_front(const struct vector *vec, int32_t *item)
{
        return vector_get(vec, 0, item);
}

static void swap_items(int32_t *lhs, int32_t *rhs)
{

}

void vector_shuffle(struct vector *vec)
{

}
