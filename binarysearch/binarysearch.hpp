// cpp_binarysearch (C) @cielavenir under Boost Software License.
// returns the smallest value satisfying the predicate.

#include <functional>
template<typename T,typename F=std::function<bool(T)>>
T binarysearch(T lo,T hi,const T eps,const F &predicate){
	T r=hi+eps;
	for(;lo<hi+eps;){
		T mi=eps!=1||(lo<0)==(hi<0) ? lo+(hi-lo)/2 : (lo<-hi) ? -((-lo-hi-1)/2+1) : (lo+hi)/2;
		if(predicate(mi)){
			r=mi;
			hi=mi-eps;
		}else{
			lo=mi+eps;
		}
	}
	return r;
}
template<typename T,typename F=std::function<bool(T)>>
T binarysearch(T lo,T hi,const F &predicate){return binarysearch(lo,hi,(T)1,predicate);}

template<typename F=std::function<bool(double)>>
double binarysearch(double _lo,double _hi,const F &predicate){
	long long lo;
	if(_lo<0)_lo=-_lo,lo=-*(long long*)(&_lo);else lo=*(long long*)(&_lo);
	long long hi;
	if(_hi<0)_hi=-_hi,hi=-*(long long*)(&_hi);else hi=*(long long*)(&_hi);
	long long _r=binarysearch(lo,hi,1LL,[&](long long _mi){
		double mi;
		if(_mi<0)_mi=-_mi,mi=-*(double*)(&_mi);else mi=*(double*)(&_mi);
		return predicate(mi);
	});
	double r;
	if(_r<0)_r=-_r,r=-*(double*)(&_r);else r=*(double*)(&_r);
	return r;
}

template<typename T,typename F>
T ternarysearch(T lo,T hi,const T eps,const F &predicate){
	for(;lo+eps<hi;){
		T mi=(lo+hi)/2;
		if(predicate(mi)>predicate(mi-eps)){
			hi=mi;
		}else{
			lo=mi;
		}
	}
	return lo;
}
template<typename T,typename F>
T ternarysearch(T lo,T hi,const F &predicate){return ternarysearch(lo,hi,(T)1,predicate);}
