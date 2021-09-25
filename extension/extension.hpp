// stdc++ extension
// (C) @cielavenir under Boost Software License.

#include <cstddef>

#include <bitset>

/// bitset comparator (so that it can be put into std::set)
namespace std{
	template<size_t N>
	struct less<bitset<N> > : binary_function <bitset<N>,bitset<N>,bool>{
		bool operator()(const bitset<N> &L, const bitset<N> &R) const{
			for(unsigned int i=0;i<L.size();i++)
				if(L.test(i)){
					if(!R.test(i))return false;
				}else{
					if(R.test(i))return true;
				}
			return false; //same
		}
	};
}

#if __cplusplus>=201103
#include <tuple>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

/// hasher
namespace std{
	template<typename T>
	inline void hash_combine(size_t& seed, const T &v){
		// boost/functional/hash/hash.hpp
		seed ^= hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
	}
	template<typename It>
	inline size_t hash_range(It first, It last){
		size_t seed=0;
		hash_range(seed,first,last);
		return seed;
	}
	template<typename It>
	inline void hash_range(size_t& seed, It first, It last){
		for(;first!=last;++first)hash_combine(seed, *first);
	}
	template<typename A,typename B>
	class hash<pair<A,B>>{
		public:
		size_t operator()(const pair<A,B> &p) const{
			size_t seed=0;
			hash_combine(seed,p.first);
			hash_combine(seed,p.second);
			return seed;
		}
	};
	template<typename... Y>
	class hash<tuple<Y...>>{
		public:
		template<int I,typename... X>
		struct __tuple_hasher__{
			static inline size_t rec(const tuple<X...> &t){
				size_t seed=__tuple_hasher__<I-1,X...>::rec(t);
				hash_combine(seed,get<I-1>(t));
				return seed;
			}
		};
		template<typename... X>
		struct __tuple_hasher__<0,X...>{
			static inline size_t rec(const tuple<X...> &t){
				return 0;
			}
		};
		size_t operator()(const tuple<Y...> &t) const{
			return __tuple_hasher__<sizeof...(Y),Y...>::rec(t);
		}
	};
	template<typename T,size_t N>
	class hash<array<T,N>>{
		public:
		size_t operator()(const array<T,N> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename A>
	class hash<vector<T,A>>{
		public:
		size_t operator()(const vector<T,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename A>
	class hash<deque<T,A>>{
		public:
		size_t operator()(const deque<T,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename A>
	class hash<list<T,A>>{
		public:
		size_t operator()(const list<T,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename A>
	class hash<forward_list<T,A>>{
		public:
		size_t operator()(const forward_list<T,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename C,typename A>
	class hash<set<T,C,A>>{
		public:
		size_t operator()(const set<T,C,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename C,typename A>
	class hash<multiset<T,C,A>>{
		public:
		size_t operator()(const multiset<T,C,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename K,typename T,typename C,typename A>
	class hash<map<K,T,C,A>>{
		public:
		size_t operator()(const map<K,T,C,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename K,typename T,typename C,typename A>
	class hash<multimap<K,T,C,A>>{
		public:
		size_t operator()(const multimap<K,T,C,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename H,typename P,typename A>
	class hash<unordered_set<T,H,P,A>>{
		public:
		size_t operator()(const unordered_set<T,H,P,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename T,typename H,typename P,typename A>
	class hash<unordered_multiset<T,H,P,A>>{
		public:
		size_t operator()(const unordered_multiset<T,H,P,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename K,typename T,typename H,typename P,typename A>
	class hash<unordered_map<K,T,H,P,A>>{
		public:
		size_t operator()(const unordered_map<K,T,H,P,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};
	template<typename K,typename T,typename H,typename P,typename A>
	class hash<unordered_multimap<K,T,H,P,A>>{
		public:
		size_t operator()(const unordered_multimap<K,T,H,P,A> &container) const{
			return hash_range(container.begin(),container.end());
		}
	};

	// it is not possible to calc hash of stack/queue as `container.c` is protected.
	// anyway no one should be making stack/queue as "key" of dictionary.

/*
	template<typename I>
	class hash<pair<I,I>>{
		public:
		size_t operator()(pair<I,I> const &p) const {return hash<long long>() (((long long)(p.first))<<32|p.second);}
	};
*/
}

#endif

#if __cplusplus>=201402
#include <tuple>

template<typename... Y>
class tpl: public std::tuple<Y...>{
	public:
	tpl(const tpl&) = default;
	tpl(tpl&&) = default;
	tpl(): std::tuple<Y...>(){}
	tpl(const std::tuple<Y...> &o): std::tuple<Y...>(o){}
	tpl(std::tuple<Y...> &&o): std::tuple<Y...>(o){}
	tpl(const Y&... elems): std::tuple<Y...>(elems...){}
	tpl(Y&&... elems): std::tuple<Y...>(elems...){}
	tpl& operator=(const std::tuple<Y...> &o){(std::tuple<Y...>&)*this = o;return *this;}
	tpl& operator=(std::tuple<Y...> &&o){(std::tuple<Y...>&)*this = o;return *this;}
	tpl& operator=(const tpl &o){*this = (std::tuple<Y...>&)o;return *this;}
	tpl& operator=(tpl &&o){*this = (std::tuple<Y...>&)o;return *this;}

	template<typename T>
	T& get(){return std::get<T>(*this);}
	template<typename T>
	T& get() const{return std::get<T>(*this);}
	template<int I>
	auto& get(){return std::get<I>(*this);}
	template<int I>
	auto& get() const{return std::get<I>(*this);}

	// handy ordinal wrapper, just for fun
	auto& first(){return std::get<0>(*this);}
	auto& second(){return std::get<1>(*this);}
	auto& third(){return std::get<2>(*this);}
	auto& fourth(){return std::get<3>(*this);}
	auto& fifth(){return std::get<4>(*this);}
	auto& sixth(){return std::get<5>(*this);}
	auto& seventh(){return std::get<6>(*this);}
	auto& eighth(){return std::get<7>(*this);}
	auto& ninth(){return std::get<8>(*this);}
	auto& tenth(){return std::get<9>(*this);}
	auto& eleventh(){return std::get<10>(*this);}
	auto& twelfth(){return std::get<11>(*this);}

	auto& first() const{return std::get<0>(*this);}
	auto& second() const{return std::get<1>(*this);}
	auto& third() const{return std::get<2>(*this);}
	auto& fourth() const{return std::get<3>(*this);}
	auto& fifth() const{return std::get<4>(*this);}
	auto& sixth() const{return std::get<5>(*this);}
	auto& seventh() const{return std::get<6>(*this);}
	auto& eighth() const{return std::get<7>(*this);}
	auto& ninth() const{return std::get<8>(*this);}
	auto& tenth() const{return std::get<9>(*this);}
	auto& eleventh() const{return std::get<10>(*this);}
	auto& twelfth() const{return std::get<11>(*this);}

	// It seems tpl can be casted to std::tuple implicitly.
	// If it does not work, this explicit converter could be used.
	std::tuple<Y...>& to_tuple(){return (std::tuple<Y...>&)*this;}
	std::tuple<Y...>& to_tuple() const{return (std::tuple<Y...>&)*this;}
};

namespace std{
	template<typename... Y>
	class hash<::tpl<Y...>>: public hash<tuple<Y...>>{};
}
#endif
