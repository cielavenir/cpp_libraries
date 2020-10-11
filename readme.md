## cpp_libraries
- Small C++ Libraries (mainly targeted for C++11)

### binarysearch
- easy binarysearch/ternarysearch wrapper
- http://qiita.com/cielavenir/items/852e2458cd327ca73613

#### binary search without numerical error
- https://qiita.com/cielavenir/items/3d2e16ab87d8ddba44b0

### inspect
- multi-purpose object dumper (compatible with C++11 initializer_list)
- http://qiita.com/cielavenir/items/95615185b5ca47d9111d

### range
- boost::irange equivalent
- http://qiita.com/cielavenir/items/94c9abbb7767bd57607b

### rational
- interface is almost compatible with boost::rational.
- http://qiita.com/cielavenir/items/2171327462d2afd98b65

### extension
- bitset comparator (so that it can be put into std::set)
- hasher of STL containers
- derived std::tuple (tpl) with member method get()

#### caveats

Both tpl and **boost::tuple** have the issue that member method get cannot be used in some template context. See tpl_caveat.cpp for detail.

## License
- cpp_rational: 2-clause BSDL (due to operator+= impl)
- others: Boost Software License is applied, where you need to retain the copyright notice only in source distribution.
