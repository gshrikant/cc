/**
 * @file vector.c
 * @brief Minimal dynamic array (vector) library.
 * @author Shrikant Giridhar
 */
#include <cc/vector.h>

/**
 * @brief Initialize a vector container.
 *
 * @param v		Pointer to embedded vector field.
 * @param buf		Pointer to container array.
 * @param elt_size	Size of an individual element in the vector.
 *
 * @return 0 on success; negative error code on failure.
 */
int __vector_init(struct vector *v, void **buf, size_t elt_size)
{
    *buf = calloc(VECTOR_INIT_SIZE, elt_size);
    if (*buf == NULL)
	return -EFAULT;

    v->length = 0;
    v->capacity = VECTOR_INIT_SIZE;
    v->eltsize = elt_size;
    return 0;
}

/**
 * @brief Push an element at the end of a vector.
 *
 * @param v	Pointer to embedded vector field.
 * @param buf	Pointer to container array. 
 * @param elt	Pointer to the element to be pushed.
 *
 * @return 0 on success; negative error code on failure.
 */
int __vector_push(struct vector *v, void **buf, void *elt)
{
    if (elt == NULL)
	return -EINVAL;

    size_t eltsize = v->eltsize;

    /* Resize container and bail out if we can't. */
    if (v->length >= v->capacity) {
	size_t current_size = (v->capacity)*eltsize; 
	size_t new_size = current_size*VECTOR_RESIZE_FACTOR;

	/* realloc() guarantees that existing elements would be copied. */
	*buf = realloc(*buf, new_size);
	if (*buf == NULL)
	    return -ENOMEM;

	v->capacity *= VECTOR_RESIZE_FACTOR;
    }

    void *dest = (char*) *buf + (v->length)*eltsize;
    memcpy(dest, elt, eltsize);
    v->length++;
    return 0;
}
