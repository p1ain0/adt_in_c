#ifndef _BST_H_
#define _BST_H_
#ifndef NULL
#define NULL 0
#endif
//binary search tree
//
#define BST_HEAD(name,type) \
typedef struct name {\
    struct type* bst_root;\
}name

#define BST_INIT(root) do {\
    (root)->bst_root = NULL;\
}while(0)

#define BST_ENTRY(type)\
struct {\
    type* parent;\
    type* left;\
    type* right;\
}\

#define BST_PARENT(elm, field) (elm)->field.parent
#define BST_LEFT(elm, field)    (elm)->field.left
#define BST_RIGHT(elm, field)   (elm)->field.right
#define BST_ROOT(head) (head)->root

#define BST_SET(elm, parent, field) \
    do(\
        BST_PARENT(elm, field) = parent;\
        BST_LEFT(elm, filed) = RB_RIGHT(elm, field) = NULL; \
    }while(0)

#define BST_PROTOTYPE(name, type, field, cmp) \
type* name##_bst_insert(name* head, type* elm)\
{\
    type *tmp;\
    type *parent;\
    int comp = 0;\
    tmp = BST_ROOT(head);\
    while(tmp){\
        parent = tmp; \
        comp = (cmp)(elm, parent); \
        if(comp < 0) \
            tmp = BST_LEFT(tmp, field); \
        else if(comp > 0) \
            tmp = BST_RIGHT(tmp, field); \
        else \
            return (tmp);\
    }\
    RB_SET(elm, parent, field) = elm;\
    if(parent != NULL) { \
        if(comp < 0) \
            BST_LEFT(parent, field) = elm;\
        else \
            BST_RIGHT(parent, field) = elm;\
    } else \
        BST_ROOT(head) = elm;\
    return NULL;\
}\
\
type *name##_bst_next(name* head, type *elm)\
{\
    if(BST_RIGHT(elm, field)){\
        elm = BST_RIGHT(elm, field);\
        while(BST_LEFT(elm, field))\
            elm = BST_LEFT(elm, field);\
    } else {\
        if(BST_PARENT(elm, field) && (elm == BST_LEFT(BST_LEFT(BST_PARENT(elm, field), field))))\
            elm = BST_PARENT(elm, field);\
        else{\
            while(BST_PARENT(elm, field) && (elm == BST_RIGHT(BST_PARENT(elm, field), field)))\
                elm = BST_PARENT(elm, field);\
            elm = BST_PARENT(elm, field);\
        }\
    }\
    return (elm);\
}\
\
type * name##_BST_MINMAX(name* head, int val)\
{\
    type *tmp = BST_ROOT(head);\
    type *parent = NULL;\
    while (tmp) { \
        parent = tmp;\
        if(val < 0)\
            tmp = BST_LEFT(tmp, field);\
        else \
            tmp = BST_RIGHT(tmp, field); \
    }\
    return parent;\
}\
\
type* name##_bst_remove(name* head, type* elm)\
{\
    \
}\

#define BST_NEGINF -1
#define BST_INF 1
#define BST_MIN(name, x) name##_BST_MINMAX(x, BST_NEGINF)
#define BST_MAX(name, x) name##_BST_MINMAX(x, BST_INF)

#define BST_FOREACH(x, name, head)\
    for ((x) = BST_MIN(name, head);\
            (x) != NULL;\
            (x) = name##_BST_NEXT(head, x))\

#endif
