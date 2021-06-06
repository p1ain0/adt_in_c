#include "bst.h"

typedef struct test_node_t{
    int x;
}test_node_t;
BST_ENTRY(test_node_t) t;
BST_HEAD(test,test_node_t);
int main()
{
    test a;
    BST_INIT(&a);
    return 0;
}
