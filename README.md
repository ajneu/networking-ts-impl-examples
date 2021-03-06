# Usage of networking-ts-impl

This repository shows examples of Christopher M. Kohlhoff's implementation [networking-ts-impl](https://github.com/chriskohlhoff/networking-ts-impl)
of the [C++ Technical Specification "Extensions for Networking"](https://github.com/cplusplus/networking-ts)

## Conversion Boost Asio Tutorials to networking-ts-impl

The [Boost Asio Tutorials](http://www.boost.org/doc/libs/release/doc/html/boost_asio/tutorial.html) ([code](https://github.com/boostorg/asio/tree/develop/example/cpp03/tutorial)) will be converted to using the networking-ts-impl implementation instead.

## Compiling

```bash
git clone https://github.com/ajneu/networking-ts-impl-examples.git
cd networking-ts-impl-examples
mkdir build
cd    build
cmake ..
make -j4

# run binaries
./tutorial/timer1/timer1
./tutorial/timer2/timer2
./tutorial/timer3/timer3
./tutorial/timer4/timer4
./tutorial/timer5/timer5

# etc.
```
