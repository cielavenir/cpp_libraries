// cpp_binarysearch (C) @cielavenir under Boost Software License.
// type F should be something like std::function<bool(T)>.

template<typename T,typename F>
T binarysearch(T lo,T hi,F checker,T eps=1){
	for(;lo+eps<hi;){
		T mi=(lo+hi)/2;
		if(checker(mi)){
			lo=mi;
		}else{
			hi=mi;
		}
	}
	return lo;
}
