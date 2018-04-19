#include "job_dispatcher.h"

#include <cassert>
#include <thread>
#include "dbg.h"
#include "dbtostr.h"
#include "async.h"
#include "static_assert.h"
#include "functional.h"
#include "logathlon.h"

using functional::compose;
namespace log = logathlon::log::job_dispatcher;


namespace job_dispatcher {

    namespace {

        namespace lock {
            struct running_tag_t { };
            struct pending_tag_t { };
            struct both_tag_t { };
            template <typename tag> struct guard { locks::guard g; };
            guard<pending_tag_t> pending(data& d) { return { locks::block(d.pending_mutex) }; }
            guard<running_tag_t> running(data& d) { return { locks::block(d.running_mutex) }; }

            template <> struct guard<both_tag_t> { locks::guard p, r; };
            guard<both_tag_t> both(data& d) {
                auto& pending = d.pending_mutex;
                auto& running = d.running_mutex;
                using locks::adopt;
                std::lock(pending, running);
                return { locks::adopt(pending), locks::adopt(running) };
            }

            using both_t = guard<both_tag_t>;
        }

        void onTick(data&);

        void enqueue(data& d, joblet_t j) {
            TRACE();
            const auto lock = lock::pending(d);
            d.pending.emplace_back(move(j));
        }

        void cleanup_running(data& d) {
            TRACE();
            const auto lock = lock::running(d);
            auto& running = d.running;
            const auto end_ = end(running);
            for (auto i = begin(running); i != end_; ++i) {
                std::future<void>& future = job::future(*i);
                if (async::is_ready(future)) {
                    TRACE("cleanup_a_running");
                    running.erase(i);
                }
            }
        }

        void dispatch_next(lock::both_t const&, data& d) {
            TRACE();
            auto& pending = d.pending;
            auto& running = d.running;

            joblet_t j = pending.back();
            auto f = functional::seq(j, std::bind(onTick, std::ref(d)));
            pending.pop_back();

            running.emplace_back(std::async(std::launch::async, f));
        }

        void dispatch_enqueued(data& d) {
            TRACE();
            const auto lock = lock::both(d);
            while (!d.pending.empty() && d.running.size() < data::MAX_JOBS)
                dispatch_next(lock, d);
        }

        void onTick(data& d) {
            cleanup_running(d);
            dispatch_enqueued(d);
        }
    }

    void data::initialize(data&) {
        TRACE();
    }

    void data::cleanup(data& d) {
        TRACE();
        while (true) {
            {
                const auto lock = lock::running(d);
                if (d.running.empty())
                    break;
            }
            cleanup_running(d);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void data::run(std::function<void ()> f) {
        TRACE();
        auto& d = *this;
        enqueue(d, move(f));
        onTick(d);
    }
}
