#pragma once

struct no_copy {
    no_copy() = default;
    no_copy(no_copy const&) = delete;
};
