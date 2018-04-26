#pragma once

void on_eval(char const* name);

template <
    typename T
    >
decltype(auto) __eval_macro_impl(char const* name, T command)
{
    on_eval(name);
    return eval_(command);
}

#define eval(comm) __eval_macro_impl(#comm, comm)
