/**
 * @file vector.h
 * @brief Minimal, generic dynamic array (vector) data type.
 *
 * Vectors provide type generic, resizable array facilities built on top of
 * regular arrays. Like regular arrays, the don't do any bounds checking. For
 * example usage, see tests/vector_test.cc.
 */
#ifndef __CC_VECTOR_H__
#define __CC_VECTOR_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct vector {
    size_t eltsize;	/* Size of an element. */
    size_t length;	/* Occupied length. */
    size_t capacity;	/* Actual capacity. */
};

/** Initial capacity of the vector. */
#define VECTOR_INIT_SIZE	   (8U)

/** Factor to grow the vector by. */
#define VECTOR_RESIZE_FACTOR	   (2U)

#define DECLARE_VECTOR(type, name)  \
    struct name {		    \
	type *__buffer;		    \
	struct vector __vector;	    \
    }

/**
 * Function-like macros provide type-agnostic wrappers around vector
 * operations. The functions should not be used directly.
 */
#define vector_init(v)			    \
    __vector_init(&(v)->__vector,           \
	         (void**) (&(v)->__buffer), \
	         sizeof(*(v)->__buffer))

#define vector_push(v, pe)		    \
    __vector_push(&(v)->__vector, (void**) (&(v)->__buffer), pe)

#define vector_len(v)		    ((v)->__vector.length)
#define vector_capacity(v)	    ((v)->__vector.capacity)
#define vector_at(v, i)		    ((v)->__buffer[i])
#define vector_free(v)		    free((v)->__buffer);

int __vector_init(struct vector*, void**, size_t);
int __vector_push(struct vector*, void**, void*);

#ifdef __cplusplus
}
#endif
#endif /* __CC_VECTOR_H__ */
