#include "vector.h"
#include <stdlib.h>

VECTOR(vector, int);

int main()
{
    struct vector v;
    vector_init(&v);
    vector_expand(&v);
    return 0;
}
