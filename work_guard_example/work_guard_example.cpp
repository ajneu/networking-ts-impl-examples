#include <iostream>
#include <chrono>
#include <thread>
#include <type_traits>
#include <cassert>

#include <experimental/optional>

#include <experimental/io_context>
#include <experimental/timer>
#include <experimental/executor>

// similar to http://think-async.com/Asio/TipsAndTricks?skin=clean.nat%2casio%2cpattern#Stopping_the_io_service_from_run

class Work_Guard {
public:
    Work_Guard(std::experimental::net::io_context &io, std::true_type /*guard_on*/ = std::true_type{})
        : io_{io},
          w_guard_{std::experimental::in_place, io.get_executor()
                                              /*std::experimental::net::make_work_guard(io)*/ }
    {
    }

    Work_Guard(std::experimental::net::io_context &io, std::false_type /*guard_off*/)
        : io_{io}
    {
    }

    void guard_on()
    {
        if (!w_guard_ || !w_guard_->owns_work()) {
            w_guard_.emplace(std::experimental::net::make_work_guard(io_));
        }
    }

    void guard_off()
    {
        if (w_guard_ && w_guard_->owns_work()) {
            w_guard_ = std::experimental::nullopt;
            if (io_.stopped()) { // handle the case where this point is reached (early),
                // before run() is called: need to call reset(), or later
                // run() will not run

                io_.restart();
                assert(!io_.stopped());
            }
        }
    }

private:
    std::experimental::net::io_context &io_;
    std::experimental::optional<std::experimental::net::executor_work_guard<std::experimental::net::io_context::executor_type>> w_guard_;
};



int main()
{
    std::experimental::net::io_context io;
    Work_Guard wg(io); // equiv to:     Work_Guard wg(io, std::true_type());

    wg.guard_off();
    wg.guard_on();
    
    std::thread th([&io]() {
            io.run();
        });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::experimental::net::steady_timer t(io, std::chrono::milliseconds(500));
    t.async_wait([](const std::error_code& /*e*/) {
            std::cout << "hello" << std::endl;
        });

    wg.guard_off();

    th.join();
    return 0;
}
