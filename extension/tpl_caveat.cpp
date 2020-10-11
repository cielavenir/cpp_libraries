// cf https://stackoverflow.com/questions/3313479/stdtuple-get-member-function
#include <iostream>
#ifdef BOOST
#include <boost/tuple/tuple.hpp>
template<typename... Y>
class Foo{
public:
	static void bar(){
		boost::tuple<Y...> x={1,false};
		// need "template" or this snippet does not compile.
		std::cout << (x.template get<0>()) << std::endl;
		std::cout << (boost::get<0>(x)) << std::endl;
	};
};
#else
#include "extension.hpp"
template<typename... Y>
class Foo{
public:
	static void bar(){
		tpl<Y...> x={1,false};
		// need "template" or this snippet does not compile.
		std::cout << (x.template get<0>()) << std::endl;
		// this does compile :)
		std::cout << (x.first()) << std::endl;
		std::cout << (std::get<0>(x)) << std::endl;
	};
};
#endif

int main(){
	Foo<int,bool>::bar();
}

/*
Not only tpl but also boost::tuple have the issue.
I suppose that is why member get is not available as std. However, such metaprogramming is not used so frequently.
*/
