// stdc++ extension
// (C) @cielavenir under Boost Software License.

#include <cstddef>

#include <bitset>

/// bitset comparator
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

#if __cplusplus>=201100
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>

/// hasher
namespace std{
	template<typename T>
	inline void hash_combine(size_t& seed, const T &v){
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
}

/*
	template<typename I>
	class hash<pair<I,I>>{
		public:
		size_t operator()(pair<I,I> const &p) const {return hash<long long>() (((long long)(p.first))<<32|p.second);}
	};
*/
#endif
