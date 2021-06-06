#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>
#include <stdlib.h>
#define LIST(name, type) \
    struct name {\
        struct name* _prev;\
        struct name* _next;\
        type node; \
    };\
\
struct name* name##_alloc_node() \
{\
    return calloc(1, sizeof(struct name));\
}\
\
\
struct name* name##_prev_insert(struct name* next, struct name* node) \
{\
    struct name* prev = next->_prev; \
    next->_prev = node; \
    node->_prev = prev; \
    node->_next = next; \
    if(prev != NULL) \
    {\
        prev->_next = node; \
    }\
    return node; \
}\
\
struct name* name##_next_insert(struct name* prev, struct name* node)\
{\
    struct name* next = prev->_next;\
    prev->_next = node; \
    node->_next = next; \
    node->_prev = prev; \
    if(next != NULL) \
    {\
        next->_prev = node; \
    }\
    return node; \
}\
\
struct name* name##_first(struct name* prev) \
{\
    while (prev->_prev != NULL) \
    {\
        prev = prev->_prev; \
    }\
    return prev; \
}\
\
struct name* name##_last(struct name* next) \
{\
    while (next->_next != NULL) \
    {\
        next = next->_next; \
    }\
    return next;\
}\
\
struct name* name##_remove(struct name* node) \
{\
    struct name* prev = node->_prev;\
    struct name* next = node->_next;\
    \
    if(prev != NULL) \
    {\
        prev->_next = node->_prev; \
    }\
    if(next != NULL) \
    {\
        next->_prev = node->_next; \
    }\
    return node; \
}\
\
void name##_free(struct name* node)\
{\
    free(node);\
}\
void name##_destroy(struct name* list)\
{\
    list = name##_first(list); \
    struct name* next = list->_next; \
    while(list)\
    {\
        name##_free(name##_remove(list));\
        list = next;\
        next = list->_next;\
    }\
\
}\

#endif
