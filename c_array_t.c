#include "./c_array_t.h"


c_array_t *c_arr_init(size_t type_size)
{
	c_array_t *c_array = c_arr_init_size(type_size, 0);
	return c_array;
}


c_array_t *c_arr_init_size(size_t type_size, size_t size)
{
	c_array_t *c_array = malloc(sizeof(c_array_t)); 
	
	c_array->type_size_ = type_size;
	c_array->size_ = size;
	c_array->p_buffer_ = malloc(type_size * size);

	return c_array;
}


c_array_t *c_arr_init_size_val(size_t type_size, size_t size, const void *p_data)
{
	c_array_t *c_array = c_arr_init_size(type_size, size);
	
	for (size_t i = 0; i < size; i++) {
		c_arr_set(c_array, i, p_data);
	}

	return c_array;
}


c_array_t *c_arr_init_from(size_t type_size, const void *p_src, size_t size)
{
	c_array_t *c_array = c_arr_init_size(type_size, size);

	for (size_t i = 0; i < size; i++) {
		c_arr_set(c_array, i, p_src + i * type_size);
	}

	return c_array;
}


c_array_t *c_arr_copy(const c_array_t *p_other)
{
	c_array_t *c_array = c_arr_init_from(p_other->type_size_, p_other->p_buffer_, p_other->size_);
	
	return c_array;
}


void c_arr_copy_assign(c_array_t *p_self, const c_array_t *p_other)
{
	*p_self = *c_arr_copy(p_other); 
}


void c_arr_destroy(c_array_t *p_self)
{
	free(p_self->p_buffer_);
	p_self->type_size_ = 0;
	p_self->size_ = 0;
}


void *c_arr_get(const c_array_t *p_self, size_t idx)
{
	void *arr_elem = (p_self->p_buffer_ + idx * p_self->type_size_);
	return arr_elem;
}


void c_arr_set(const c_array_t *p_self, size_t idx, const void *p_data)
{
	for (size_t i = 0; i < p_self->type_size_; i += sizeof(char)) {
		*(char *) (p_self->p_buffer_ + i + idx * p_self->type_size_) = *(char *) (p_data + i); 
	}
}


void *c_arr_at(const c_array_t *p_self, size_t idx)
{
	void *arr_elem;

	if (idx < p_self->size_) {
		arr_elem = c_arr_get(p_self, idx); 
	} else {
		exit(1);
	}

	return arr_elem;
}


void *c_arr_front(const c_array_t *p_self)
{
	return c_arr_get(p_self, 0); 
}


void *c_arr_back(const c_array_t *p_self)
{
	return c_arr_get(p_self, p_self->size_ - 1);
}


void *c_arr_data(const c_array_t *p_self)
{
	return p_self->p_buffer_;
}


int c_arr_empty(const c_array_t *p_self)
{
	return (p_self->size_ == 0) ? 1 : 0;
}


size_t c_arr_size(const c_array_t *p_self)
{
	return p_self->size_;
}


size_t c_arr_type_size(const c_array_t *p_self)
{
	return p_self->type_size_;
}


void c_arr_fill(c_array_t *p_self, const void *p_data)
{
	for (size_t i = 0; i < p_self->size_; i++) {
		c_arr_set(p_self, i, p_data);
	}
}


void c_arr_swap(c_array_t *p_self, c_array_t *p_other)
{
	c_array_t temp = *p_self;
	*p_self = *p_other;
	*p_other = temp;
}


int c_cmp_int(const void *lhs, const void *rhs)
{
	return *(int *)lhs - *(int *)rhs;
}


int c_arr_equal(const c_array_t *p_self, const c_array_t *p_other, c_comparator cmp)
{
	if (p_self->size_ != p_other->size_ || p_self->type_size_ != p_other->type_size_) {
		return 0;	
	}

	for (size_t i = 0; i < p_self->size_; i++) {
		if (cmp(c_arr_get(p_self, i), c_arr_get(p_other, i)) != 0) {
			return 0;
		} 
	}

	return 1;
}


int c_arr_not_equal(const c_array_t *p_self, const c_array_t *p_other, c_comparator cmp)
{
	return !(c_arr_equal(p_self, p_other, cmp));
}


void c_print_int(const void *data)
{
	printf("%d ", *(int *)data);
}


void c_arr_print(const c_array_t *p_self, c_print_func pf)
{
	for (size_t i = 0; i < p_self->size_; i++) {
		pf(c_arr_get(p_self, i));
	}
}
