//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <chrono>
#include <functional>
#include <thread>
#include <experimental/io_context>
#include <experimental/timer>
#include <experimental/executor>

class printer
{
public:
  printer(std::experimental::net::io_context& io)
    : strand_(io.get_executor()),
      timer1_(io, std::chrono::seconds(1)),
      timer2_(io, std::chrono::seconds(1)),
      count_(0)
  {
    timer1_.async_wait(bind_executor(strand_, std::bind(&printer::print1, this)));
    timer2_.async_wait(bind_executor(strand_, std::bind(&printer::print2, this)));
  }

  ~printer()
  {
    std::cout << "Final count is " << count_ << std::endl;
  }

  void print1()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 1: " << count_ << std::endl;
      ++count_;

      timer1_.expires_at(timer1_.expiry() + std::chrono::seconds(1));
      timer1_.async_wait(bind_executor(strand_, std::bind(&printer::print1, this)));
    }
  }

  void print2()
  {
    if (count_ < 10)
    {
      std::cout << "Timer 2: " << count_ << std::endl;
      ++count_;

      timer2_.expires_at(timer2_.expiry() + std::chrono::seconds(1));
      timer2_.async_wait(bind_executor(strand_, std::bind(&printer::print2, this)));
    }
  }

private:
  std::experimental::net::strand<std::experimental::net::io_context::executor_type> strand_;
  std::experimental::net::steady_timer timer1_;
  std::experimental::net::steady_timer timer2_;
  int count_;
};

int main()
{
  std::experimental::net::io_context io;
  printer p(io);
  std::thread t(std::bind(&std::experimental::net::io_context::run, &io));
  io.run();
  t.join();

  return 0;
}
