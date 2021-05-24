#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdbool.h>

#define DEFAULT_CAPACITY 3
#define VECTOR(name, type) struct name {    \
    type* _elem;    \
    int _size;    \
    int _capacity;  \
}; \
\
void name##_init(struct name* vector) \
{ \
	vector->_elem = calloc(DEFAULT_CAPACITY, sizeof(type)); \
	vector->_size = 0; \
	vector->_capacity = DEFAULT_CAPACITY;\
}\
\
void name##_expand(struct name* vector) \
{\
	if(vector->_size < vector->_capacity) return;\
	if(vector->_capacity < DEFAULT_CAPACITY) vector->_capacity = DEFAULT_CAPACITY; \
	type* old_elem = vector->_elem; \
	vector->_elem = calloc(vector->_capacity <<= 1, sizeof(type)); \
	for(int i = 0; i < vector->_size; i++) \
		vector->_elem[i] = old_elem[i]; \
	free(old_elem); \
}\
void name##_shrink(struct name* vector) \
{\
	if(vector->_capacity < DEFAULT_CAPACITY << 1) return; \
	if(vector->_size << 2 > vector->_capacity) return; \
	type* old_elem = calloc(vector->_capacity >>= 1, sizeof(type)); \
	for(int i = 0; i < vector->_size; i++) \
		vector->_elem[i] = old_elem[i]; \
	free(old_elem); \
} \
int name##_remove_elements(struct name* vector, int lo, int hi) \
{ \
	if(lo == hi) return 0; \
	while(hi < vector->_size) vector->_elem[lo++] = vector->_elem[hi++]; \
	vector->_size = lo; \
    name##_shrink(vector);\
	return hi - lo; \
} \
\
type name##_remov_element(struct name* vector, int r)\
{\
	type e = vector->_elem[r]; \
	name##_remove_elements(vector, r, r+1); \
	return e;\
}\
type name##_get(struct name* vector,  int r)\
{\
	return vector->_elem[r]; \
}\
type name##_put(struct name* vector, int r, type e)\
{\
	type old_e = vector->_elem[r];\
	vector->_elem[r] = e;\
	return old_e;	\
}\
int name##_insert(struct name* vector, int r, type e)\
{\
	name##_expand(vector);\
	for(int i = vector->_size; i > r; i--) \
		vector->_elem[i] = vector->_elem[i-1];\
	vector->_elem[r] = e;\
	vector->_size ++;\
	return r;\
}\
int name##_find_section(struct name* vector, type* e, int lo, int hi)\
{\
	while((lo < hi--) && (*e != vector->_elem[hi]));\
	return hi;\
}\
int name##_deduplicate(struct name* vector)\
{\
	int old_size = vector->_size;\
	int i = 1;\
	while(i < vector->_size)\
	{\
		(name##_find_section(vector, &vector->_elem[i], 0, i) < 0)?i++:name##_remov_element(vector, i);\
	}\
	return old_size - vector->_size;\
}\
void name##_traverse(struct name* vector, void(*visit)(type* e))\
{\
	for(int i = 0; i < vector->_size; i++)\
		visit(&vector->_elem[i]);\
}\
int name##_disordered(struct name* vector, int (*_cmp)(const void*, const void*))\
{\
    int n = 0;\
    for (int i = 1; i < vector->_size; i++)\
        n += (_cmp(&vector->_elem[i - 1], &vector->_elem[i]));\
    return n;\
}\
int name##_uniquify(struct name* vector)\
{\
    int old_size = vector->_size;\
    int i = 0, j = 0;\
    while(++j < vector->_size)\
        if(vector->_elem[i] != vector->_elem[j])\
            vector->_elem[i++] = vector->_elem[j];\
    vector->_size = ++i;\
    name##_shrink(vector);\
    return old_size - vector->_size;\
}\
void name##_bubble_sort(struct name* vector, int lo, int hi, int (*_cmp)(const void*, const void*))\
{\
    while(lo < --hi)\
        for(int i = lo; i < hi; i++)\
            if(_cmp(&vector->_elem[i], &vector->_elem[i + 1]))\
            { \
                type tmp = vector->_elem[i]; \
                vector->_elem[i] = vector->_elem[i + 1]; \
                vector->_elem[i + 1] = tmp; \
            }\
}\
\
int name##_size(struct name* vector) \
{\
    return vector->_size; \
}\
bool name##_elem(struct name* vector) \
{\
    return vector->_size == 0;\
}\
\
int name##_find(struct name* vector, type *e)\
{\
    return name##_find_section(vector, e, 0, vector->_size); \
}\
int name##_search_section(struct name* vector, type *e, int lo, int hi, int (*_cmp)(const void*, const void*))\
{\
    while(lo < hi)\
    {\
        int mi = (lo + hi) >> 1; \
        int x = _cmp(e, &vector->_elem[mi]);\
        if(x == 0) \
            return mi;\
        else if (x < 0)\
            hi = mi;\
        else if (x > 0)\
            lo = mi;\
    }\
    return -1;\
}\
\
int name##_search(struct name* vector, type *e, int (*_cmp)(const void*, const void*))\
{\
    return name##_search_section(vector, e, 0, vector->_size, _cmp);\
}\

#endif


