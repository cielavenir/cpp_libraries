// cpp_inspect (C) @cielavenir under Boost Software License.

#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
namespace std{
#ifndef NDEBUG
	ostream& operator<<(ostream &out,const char &c){
		out.rdbuf()->sputc('\'');
		out.rdbuf()->sputc(c);
		out.rdbuf()->sputc('\'');
		return out;
	}
	ostream& operator<<(ostream &out,const string &s){
		out.rdbuf()->sputc('"');
		for(auto &c:s)out.rdbuf()->sputc(c);
		out.rdbuf()->sputc('"');
		return out;
	}
#endif
	template<typename T, typename S>
	ostream& operator<<(ostream &out,const pair<T,S> &e){
		return out<<"{"<<e.first<<","<<e.second<<"}";
	}
	template<int I,typename... X>
	struct __tuple_inspect__{
		static inline ostream& rec(ostream &out,const tuple<X...> &t){
			__tuple_inspect__<I-1,X...>::rec(out,t);
			cout<<",";
			return out<<get<I-1>(t);
		}
	};
	template<typename... X>
	struct __tuple_inspect__<1,X...>{
		static inline ostream& rec(ostream &out,const tuple<X...> &t){
			return out<<get<0>(t);
		}
	};
	template<typename... X>
	struct __tuple_inspect__<0,X...>{
		static inline ostream& rec(ostream &out,const tuple<X...> &t){
			return out;
		}
	};
	template<typename... X>
	ostream& operator<<(ostream &out,const tuple<X...> &t){
		out<<"{";
		return __tuple_inspect__<sizeof...(X),X...>::rec(out,t)<<"}";
	}
	template<typename T, size_t N>
	ostream& operator<<(ostream &out,const array<T,N> &v){
		out<<"{{";
		for(auto &e:v)out<<e<<",";
		out<<"}}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const vector<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const deque<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const list<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const forward_list<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const set<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const unordered_set<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const multiset<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T>
	ostream& operator<<(ostream &out,const unordered_multiset<T> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T,typename S>
	ostream& operator<<(ostream &out,const map<T,S> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T,typename S>
	ostream& operator<<(ostream &out,const unordered_map<T,S> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T,typename S>
	ostream& operator<<(ostream &out,const multimap<T,S> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
	template<typename T,typename S>
	ostream& operator<<(ostream &out,const unordered_multimap<T,S> &v){
		out<<"{";
		for(auto &e:v)out<<e<<",";
		out<<"}";
		return out;
	}
}
template<typename T>
std::string inspect(const T &e){
	std::ostringstream ss;
	ss<<e;
	return ss.str();
}
