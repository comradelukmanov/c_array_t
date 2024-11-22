#include <stdio.h>
#include "./c_array_t.h"
#include <assert.h>


int main()
{
	// Создание массива нулевого размера
	c_array_t *arr1 = c_arr_init(sizeof(int));
	assert(arr1->size_ == 0); // Проверка размера
	c_arr_destroy(arr1);

	// Создание массива из трех элементов
	arr1 = c_arr_init_size(sizeof(int), 3);
	assert(arr1->size_ == 3); // Проверка размера
	c_arr_destroy(arr1);

	// Создание массива заполненного значением x
	int x = 42;
	arr1 = c_arr_init_size_val(sizeof(int), 2, &x);
	assert(arr1->size_ == 2); // Проверка размера
	assert(*(int *) arr1->p_buffer_ == x); // Проверка значения (первого элемента)
	c_arr_destroy(arr1);

	// Создание массива из элементов другого массива
	int arr[] = {1, 2, 3};
	arr1 = c_arr_init_from(sizeof(int), arr, 3);
	assert(arr1->size_ == 3); // Проверка размера
	assert(*(int *) arr1->p_buffer_ == arr[0]); // Проверка значения (первого элемента)
	
	// Копирование массива
	c_array_t *arr2 = c_arr_copy(arr1);
	assert(arr2->size_ == arr1->size_); // Проверка размера
	assert(*(int *) arr1->p_buffer_ == *(int *) arr2->p_buffer_); // Проверка значения (первого элемента)
	c_arr_destroy(arr1);
	c_arr_destroy(arr2);
	
	// Копирование одного массива в другой 
	int a = 4;
	int b = 7;
	arr1 = c_arr_init_size_val(sizeof(int), 2, &a);
	arr2 = c_arr_init_size_val(sizeof(int), 3, &b);
	c_arr_copy_assign(arr1, arr2);
	assert(arr1->size_ == arr2->size_);
	assert(*(int *) arr1->p_buffer_ == *(int *) arr2->p_buffer_); // Проверка значения (первого элемента)
	c_arr_destroy(arr1);
	c_arr_destroy(arr2);

	// Получение элемента по индексу через get
	int c = 5;
	arr1 = c_arr_init_size_val(sizeof(int), 4, &c);
	int d = *(int *) c_arr_get(arr1, 1);
	assert(d == c); // Проверка полученного значения

	// Изменение элемента по индексу
	int e = 9;
	c_arr_set(arr1, 3, &e);
	assert(*(int *) c_arr_get(arr1, 3) == e); // Проверка изменения
	c_arr_destroy(arr1);

	// Получение элемента по индексу через at
	int f = 5;
	arr1 = c_arr_init_size_val(sizeof(int), 7, &f);
	int g = *(int *) c_arr_get(arr1, 1);
	assert(f == g); // Проверка полученного значения

	// Получение и проверка первого элемента
	assert(c_arr_get(arr1, 0) == c_arr_front(arr1));

	// Получение и проверка последнего элемента
	assert(c_arr_get(arr1, arr1->size_ - 1) == c_arr_back(arr1));

	// Получение и проверка адреса массива
	assert(c_arr_data(arr1) == arr1->p_buffer_);

	// Проверка массива на наличие в нём элементов 
	assert(c_arr_empty(arr1) == 0);

	// Получение и проверка количества элементов массива
	assert(c_arr_size(arr1) == arr1->size_);

	// Получение и проверка размера элемента массива
	assert(c_arr_type_size(arr1) == arr1->type_size_);

	// Заполнение существующего массива значением
	int h = 22;
	c_arr_fill(arr1, &h);
	assert(*(int *) c_arr_get(arr1, 2) == h);
	c_arr_destroy(arr1);

	// Обмен значений двух массивов
	int i = 5;
	int j = 2;

	arr1 = c_arr_init_size_val(sizeof(int), 10, &i);
	arr2 = c_arr_init_size_val(sizeof(int), 10, &j);
	
	c_arr_swap(arr1, arr2);

	assert(*(int *) c_arr_get(arr1, 2) == j);
	assert(*(int *) c_arr_get(arr2, 2) == i);

	// Проверка равенства и неравенства двух массивов
	assert(c_arr_equal(arr1, arr2, c_cmp_int) == 0);
	assert(c_arr_not_equal(arr1, arr2, c_cmp_int) != 0);
	
	c_arr_destroy(arr1);
	c_arr_destroy(arr2);
	
	// Вывод значения массива
	int k[5] = {1, 2, 3, 2, 1};
	arr1 = c_arr_init_from(sizeof(int), k, 5);
	c_arr_print(arr1, c_print_int);
	printf("\n");

	c_arr_destroy(arr1);

	return 0;
}
