#include "inspect.hpp"
int main(){
	std::map<std::pair<int,std::string>,std::vector<std::array<int,3>>> val=
	/// inspected area ///
	{
		{{1,"2"},{
			{{1,2,3}},
			{{4,5,6}},
		}},
		{{4,"5"},{
			{{4,5,6}},
			{{7,8,9}},
		}},
		{{7,"8"},{
			{{7,8,9}},
			{{1,2,3}},
		}},
	}
	/// inspected area end ///
	;std::cout<<val<<std::endl;
}