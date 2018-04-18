#pragma once

#define                                 \
    STATIC_ASSERT(COND)                 \
        static_assert((COND), #COND)
