#include "s.h"
#include <cstdio>

namespace __s
{
    void __s(char const* msg)
    {
        fprintf(stderr, "%s\n", msg);
    }
}
