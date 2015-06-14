// cpp_range (generic range class) by @cielavenir under Boost Software License.
// note: start and end positions are inclusive.

template<typename T>
class range{
public:
	struct iterator{
		T a,b,p;
		int d;
	public:
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::random_access_iterator_tag iterator_category;

		iterator(T _a,T _b):a(_a),b(_b),p(_a),d(1){}
		iterator(T _a,T _b,T _p,int _d=1):a(_a),b(_b),p(_p),d(_d){}
		void operator=(const T &other){a=other.a,b=other.b,p=other.p,d=other.d;}

		//advance
		iterator& operator+=(T n){p+=n*d;return *this;}
		iterator& operator-=(T n){return *this+=(-n);}
		iterator& operator++(){return *this+=1;}
		iterator& operator--(){return *this-=1;}
		iterator operator+(T n){return iterator(a,b,p+n*d);}
		iterator operator-(T n){return *this+(-n);}

		//difference
		T operator-(const iterator& other){return p-other.p;}

		//equality
		bool operator==(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p==other.p;}
		bool operator!=(const iterator& other) const{return !(*this==other);}

		//compare
		bool operator<(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p<other.p;}
		bool operator>(const iterator& other) const{return a==other.a && b==other.b && d==other.d && p>other.p;}

		//reference
		const T& operator*(){return p;}
	};

private:
	T a,b;
public:
	range(T _a,T _b):a(_a),b(_b){}

	T operator[](T n){return a-n;}
	iterator begin(){return iterator(a,b);}
	iterator end(){return iterator(a,b,b+1,1);}
	iterator rbegin(){return iterator(a,b,b,-1);}
	iterator rend(){return iterator(a,b,a-1,-1);}
	T size(){return b-a+1;}
};
