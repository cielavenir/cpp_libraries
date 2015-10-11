// stdc++ extension
// (C) @cielavenir under Boost Software License.

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

/// pair<int,int> hasher

#if __cplusplus>=201100
namespace std{
	template<typename I>
	class hash<pair<I,I>>{
		public:
		size_t operator()(const pair<I,I> &p) const {return hash<long long>() (((long long)(p.first))<<32|p.second);}
	};
}
#endif
