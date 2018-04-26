#include <tuple>
#include <functional>
#include <iostream>
#include <cassert>

using std::move,
      std::get
      ;

namespace execution_context
{
    namespace job
    {
        using name_t = std::string;
        using func_t = std::function<void()>;

        using data_base_t = std::tuple<name_t, func_t>;
        constexpr size_t    name_i = 0,
                            func_i = 1;
        struct data: public data_base_t
        {
            using data_base_t::tuple;
        };

        inline name_t name(data d) { return get<name_i>(d); }
        inline func_t func(data d) { return get<func_i>(d); }
    }
    using job_t = job::data;

    struct sync_t:
        public std::tuple<>
    {
    };

    void initialize(sync_t&);
    void cleanup(sync_t&);
    void dispatch(sync_t, job_t);
}

namespace test
{
    struct spy
    {
        bool called = false;
        void operator () () { called = true; }
    };
}

namespace execution_context_spec
{
    using name_t = std::string;
    using direct_spy_base_t = test::spy;
    using indirect_spy_base_t = test::spy;

    struct direct_spy_t:
        public direct_spy_base_t
    {
        using direct_spy_base_t::spy;
    };

    struct indirect_spy_t:
        public indirect_spy_base_t
    {
        using indirect_spy_base_t::spy;
    };

    using data_base_t = std::tuple<
        direct_spy_t,
        indirect_spy_t,
        execution_context::sync_t,
        name_t
        >;
    constexpr size_t    direct_spy_i = 0,
                        indirect_spy_i = 1,
                        sync_ec_i = 2,
                        name_i = 3;
    struct data:
        public data_base_t
    {
        using data_base_t::tuple;
    };

    inline direct_spy_t& direct_spy(data& d) { return get<direct_spy_i>(static_cast<data_base_t&>(d)); }
    inline indirect_spy_t& indirect_spy(data& d) { return get<indirect_spy_i>(static_cast<data_base_t&>(d)); }
    inline execution_context::sync_t& sync_ec(data& d) { return get<sync_ec_i>(static_cast<data_base_t&>(d)); }
    inline std::string& name(data& d) { return get<name_i>(static_cast<data_base_t&>(d)); }

    void initialize(data&);
    void setup(data&);
    void run(data&);
    bool check(data);
    void cleanup(data&);
}

namespace
{
    template <typename T> void run_test(T = {});
}
int main(int, char**)
{
    run_test<execution_context_spec::data>();
    return 0;
}

///

void execution_context::initialize(sync_t&)
{
}

void execution_context::cleanup(sync_t&)
{
}

void execution_context::dispatch(sync_t, job_t j)
{
    func(j)();
}

///
namespace execution_context_spec
{
    using namespace execution_context;

    void initialize(data& d)
    {
        name(d) = "Execution Context Spec";
    }

    void setup(data& d)
    {
        initialize(sync_ec(d));
    }

    void run(data& d)
    {
        sync_t& ec = sync_ec(d);

        // Enqueue a job that calls the direct spy
        dispatch(ec, {
            "direct spy calling",
            [&d](){ direct_spy(d)(); }
        });

        // Enqueue a job that calls the indirect spy (indirectly)
        dispatch(ec, {
            "indirect spy calling job",
            [&ec, &d]() {
                dispatch(ec, {
                    "indirect spy calling",
                    [&d]() { indirect_spy(d)(); }
                });
            }
        });
    }

    bool check(data d)
    {
        return
            direct_spy(d).called &&
            indirect_spy(d).called;
    }
}

///
namespace
{
    template <
        typename T
        >
    void run_test(T test)
    {
        initialize(test);
        std::cerr << " *** TEST " << name(test) << " ***\n";

        std::cerr << " . . . setting up . . .";
        setup(test);

        std::cerr << " . . . running . . .";
        run(test);

        std::cerr << " . . . success: " << 
            (check(test)? "success" : "FAILURE");

        std::cerr << std::endl;
    }
}
