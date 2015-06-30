// cpp_rational (C) by @cielavenir under 2-clause BSDL.

static inline long long gcd2(long long x,long long y){return y?gcd2(y,x%y):x;}
static inline long long gcd(long long x,long long y){
	if(x<0)x=-x;
	if(y<0)y=-y;
	return gcd2(x,y);
}
static inline long long lcm(long long x,long long y){return y/gcd(x,y)*x;}

#ifdef BOOST
#include <boost/rational.hpp>
typedef boost::rational<long long> RLL;
#else
#include <ostream>
template<typename I>
class rational{
	I num,den;
public:
	rational(I _num=0,I _den=1){assign(_num,_den);}
	rational& operator=(I n){return assign(n,1);}
	rational& assign(I n,I d){
		if(n==0){
			d=1;
		}else{
			I g=gcd(n,d);
			n/=g;
			d/=g;
			if(d<0){
				n=-n;
				d=-d;
			}
		}
		num=n;
		den=d;
		return *this;
	}

	//utility
	I numerator() const{return num;}
	I denominator() const{return den;}
	rational reverse() const{return rational(den,num);}

	//arithmetic
	//To avoid license issue, we use ruby/rational.c implementation.
	rational& operator+=(const rational<I> &other){
		I g=gcd(den,other.den);
		I a=other.den/g*num;
		I b=den/g*other.num;
		I c=a+b;
		b=den/g;
		g=gcd(c,g);
		num=c/g;
		den=other.den/g*b;
		return *this;
	}
	rational& operator-=(const rational<I> &other){return *this+=-other;}
	rational& operator*=(const rational<I> &other){
		I g1=gcd(num,other.den);
		I g2=gcd(den,other.num);
		num=(num/g1)*(other.num/g2);
		den=(den/g2)*(other.den/g1);
		return *this;
	}
	rational& operator/=(const rational<I> &other){return *this*=other.reverse();}

	//arithmetic with copy
	rational operator+(const rational<I> &other) const{return rational(*this)+=other;}
	rational operator-(const rational<I> &other) const{return rational(*this)-=other;}
	rational operator*(const rational<I> &other) const{return rational(*this)*=other;}
	rational operator/(const rational<I> &other) const{return rational(*this)/=other;}

	//unary
	rational& operator++(){num+=den;return *this;}
	rational& operator--(){num-=den;return *this;}
	operator bool() const{return !!num;}
	bool operator!() const{return !num;}
	rational operator+() const{return *this;}
	rational operator-() const{return rational(-num,den);}

	//comparison
	bool operator==(const rational<I> &other) const{return num==other.num&&den==other.den;}
	bool operator!=(const rational<I> &other) const{return num!=other.num||den!=other.den;}
	bool operator<(const rational<I> &other) const{return num*other.den<other.num*den;}
	bool operator>(const rational<I> &other) const{return num*other.den>other.num*den;}
	bool operator<=(const rational<I> &other) const{return num*other.den<=other.num*den;}
	bool operator>=(const rational<I> &other) const{return num*other.den>=other.num*den;}
};
namespace std{
	//cpp_inspect compat
	template<typename I>
	ostream& operator<<(ostream& out,const rational<I> &r){
    	return out<<r.numerator()<<"/"<<r.denominator();
    }
}
template<typename I>
rational<I> abs(const rational<I> &r){
	if(r.numerator()>=0)return r;
	return rational<I>(-r.numerator(),r.denominator());
}
template<typename T,typename I>
T rational_cast(const rational<I> &r){
	return static_cast<T>(r.numerator())/static_cast<T>(r.denominator());
}
typedef rational<long long> RLL;
#endif
