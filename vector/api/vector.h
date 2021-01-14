#pragma once
#include <stdint.h>

typedef uint8_t   __bool;
#define true      ((uint8_t)(0x1))
#define false     ((uint8_t)(0x0))


enum vector_status {
        VECTOR_SUCCESS = 0x0,
        VECTOR_INVALID_VECTOR_POINTER,
        VECTOR_INVALID_INPUT_ARGS,
        VECTOR_INDEX_OUT_OF_BOUNDS,
        VECTOR_OVERFLOW,
        VECTOR_UNDERFLOW,
        VECTOR_OUT_OF_MEMMORY,
        VECTOR_INSERT_SUCCEED_BUT_FAILS_TO_GROW,
        VECTOR_INVALID_ACTION_FUNCTION,
        VECTOR_IS_EMPTY

};



struct vector *vector_create(uint32_t initial_size, float grow_factor);
void vector_destroy(struct vector **vec);
__bool vector_empty(const struct vector *vec);
uint32_t vector_size(const struct vector *vec);
enum vector_status vector_push_back(struct vector *vec, int32_t item);
enum vector_status vector_pop_back(struct vector *vec, int32_t *item);
void vector_for_each(struct vector *vec, void (*action)(int32_t*, void*), void *context);

void vector_sort(struct vector *vec, uint8_t (*equality)(int32_t, int32_t));


enum vector_status vector_back(const struct vector *vec, int32_t *item);
enum vector_status vector_front(const struct vector *vec, int32_t *item);
enum vector_status vector_get(const struct vector *vec, uint32_t index, int32_t *item);
enum vector_status vector_set(struct vector *vec, uint32_t index, int32_t item);

void vector_shuffle(struct vector *vec);




