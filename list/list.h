#ifndef _LIST_H_
#define _LIST_H_
typedef struct list_header_t {
    void* prev;
    void* next;
}list_header_t;
void *node_alloc();
void *insert_prev();
void *insert_next();
void* first();
void* 

#endif
