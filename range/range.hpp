// cpp_range (generic range class, very small equivalent of boost::irange)
// (C) @cielavenir under Boost Software License.
// note: end position is exclusive.

#ifdef BOOST
#include <boost/range.hpp>
#define make_range boost::irange
#else
#include <iterator>
#include <functional>
template<typename I,typename F=std::function<I(I)>>
class range{
public:
	class iterator{
	public:
		const F& key;
		I a,b,p;
		long long d; //because I might be unsigned.
		iterator(I _a,I _b,I _p,long long _d,const F& _key):a(_a),b(_b),p(_p),d(_d),key(_key){}

		typedef I value_type;
		typedef I& reference;
		typedef I* pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;

		//copy
		iterator(const iterator &other):a(other.a),b(other.b),p(other.p),d(other.d),key(other.key){}
		iterator& operator=(const iterator &other){
			a=other.a,b=other.b,p=other.p,d=other.d;
			//key=other.key;
			return *this;
		}

		//advance
		iterator& operator+=(I n){p+=n*d;return *this;}
		iterator& operator-=(I n){return *this+=(-n);}
		iterator& operator++(){return *this+=1;}
		iterator& operator--(){return *this-=1;}
		iterator operator+(I n) const{return iterator(a,b,p,d,key);}
		iterator operator-(I n) const{return *this+(-n);}

		//difference
		I operator-(const iterator& other) const{return p-other.p;}

		//equality
		bool operator==(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p==other.p;}
		bool operator!=(const iterator& other) const{return !(*this==other);}

		//compare
		bool operator<(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p*d<other.p*d;}
		bool operator>(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p*d>other.p*d;}

		//reference
		decltype(auto) operator*() const{return key(p);}
	};

protected:
	const F key;
	const I a,b;
	I siz;
	long long d;
public:
	range(I _a,I _b,long long _d=1):a(_a),b(_b),d(_d),key([](I n){return n;}){
		if(d==0)d=1; //
		siz=( (d>0?(b-a):(a-b)) - 1)  / (d>0?d:-d);
	}
	range(I _a,I _b,const F& _key,long long _d=1):a(_a),b(_b),d(_d),key(_key){
		if(d==0)d=1; //
		siz=( (d>0?(b-a):(a-b)) - 1)  / (d>0?d:-d);
	}

	decltype(auto) operator[](I n){return key(a+n*d);}
	iterator begin(){return iterator(a,a+d*siz,a,d,key);}
	iterator end(){return iterator(a,a+d*siz,a+d*(siz+1),d,key);}
	iterator rbegin(){return iterator(b-d*siz,b,b,-1*d,key);}
	iterator rend(){return iterator(b-d*siz,b,b-d*(siz+1),-1*d,key);}
	I size(){return siz+1;}
};
template<typename I>
range<I> make_range(I a,I b,long long d=1){return range<I>(a,b,d);}
template<typename I,typename F>
range<I,F> makeKeyRange(I a,I b,const F& key,long long d=1){return range<I,F>(a,b,key,d);}

#endif
