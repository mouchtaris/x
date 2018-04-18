#include "dbg.h"
#ifdef debug_enabled
#   include <iostream>
    namespace {
        enum class level { debug, info, warning, error };

        template <enum level l> struct level_name;
#       define                                              \
            def_level_name(name)                            \
                template <>                                 \
                struct level_name<level::name> {            \
                    static constexpr auto value = #name;    \
                }
        def_level_name(debug);
        def_level_name(info);
        def_level_name(warning);
        def_level_name(error);
        template <enum level l>
        constexpr char const* get_level_name() { return level_name<l>::value; }
    }
    namespace debug {
        template <enum level l>
        void log(char const* msg) {
            std::cerr << '[' << get_level_name<l>() << "] " << msg << '\n';
        }
        void log(char const* msg) {
            log<level::debug>(msg);
        }
    }
#endif
