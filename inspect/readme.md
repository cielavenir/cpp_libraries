# cpp_inspect
- Inspects the content of C++ container using C++11 uniform initializer syntax.

## How to use
- Include `inspect.hpp` and you can push the following to **any ostream**:
  - pair
  - array
  - vector
  - deque
  - list
  - forward_list
  - set
  - unordered_set
  - multiset
  - unordered_multiset
  - map
  - unordered_map
  - multimap
  - unordered_multimap

- then you can use the output to initialize the container **during compilation**.

- Please check test.cpp and test.sh for detail.

## Printing char and string
- `inspect.hpp` overrides char/string printing.
- Defining NDEBUG disables this behavior.
  - Or you can use rdbuf()->sputc().

## Note
- tuple is not supported because unitorm initialization is not supported.
  - Also, getting the size looks kind of difficult.

## License
- Boost Software License is applied, where you need to retain the copyright notice only in source distribution.
