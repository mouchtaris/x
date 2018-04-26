#pragma once
#include <tuple>
#include "execution_context/job.h"

namespace alias
{
    template <typename _Tag, typename _Base>
    struct alias:
        public _Base
    {
        using Base = _Base;
        using Tag = _Tag;
        using Base::Base;
        Base& as_base() { return *this; }
        Base const& as_base() const { return *this; }
    };
}

namespace execution_context
{
    using job_t = job::data;

    struct sync_tag;
    using sync_t = alias::alias<sync_tag, std::tuple<>>;
    using sync_t_ref = std::reference_wrapper<sync_t>;

    struct initialize_tag;
    using initialize_t = alias::alias<initialize_tag, std::tuple<sync_t_ref>>;
    void eval_(initialize_t);

    struct cleanup_tag;
    using cleanup_t = alias::alias<cleanup_tag, std::tuple<sync_t_ref>>;
    void eval_(cleanup_t);

    struct dispatch_tag;
    using dispatch_t = alias::alias<dispatch_tag, std::tuple<sync_t_ref, job_t>>;
    void eval_(dispatch_t);
}
