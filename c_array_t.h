#include <stdlib.h>
#include <stdio.h>


typedef struct {
	size_t type_size_;
	size_t size_;
	void *p_buffer_;
} c_array_t;


c_array_t *c_arr_init(size_t type_size);

c_array_t *c_arr_init_size(size_t type_size, size_t size);
	
c_array_t *c_arr_init_size_val(size_t type_size, size_t size, const void *p_data);

c_array_t *c_arr_init_from(size_t type_size, const void *p_src, size_t size);

c_array_t *c_arr_copy(const c_array_t *p_other);

void c_arr_copy_assign(c_array_t *p_self, const c_array_t *p_other);

void c_arr_destroy(c_array_t *p_self);

void *c_arr_get(const c_array_t *p_self, size_t idx);

void c_arr_set(const c_array_t *p_self, size_t idx, const void *p_data);

void *c_arr_at(const c_array_t *p_self, size_t idx);

void *c_arr_front(const c_array_t *p_self);

void *c_arr_back(const c_array_t *p_self);

void *c_arr_data(const c_array_t *p_self);

int c_arr_empty(const c_array_t *p_self);

size_t c_arr_size(const c_array_t *p_self);

size_t c_arr_type_size(const c_array_t *p_self);

void c_arr_fill(c_array_t *p_self, const void *p_data);

void c_arr_swap(c_array_t *p_self, c_array_t *p_other);

typedef int (*c_comparator)(const void *, const void *);

int c_cmp_int(const void *lhs, const void *rhs);

int c_arr_equal(const c_array_t *p_self, const c_array_t *p_other, c_comparator cmp);

int c_arr_not_equal(const c_array_t *p_self, const c_array_t *p_other, c_comparator cmp);

typedef void (*c_print_func)(const void *);

void c_print_int(const void *data);

void c_arr_print(const c_array_t *p_self, c_print_func pf);
