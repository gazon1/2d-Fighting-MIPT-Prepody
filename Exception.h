#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>
#include <string.h>
using std::string;

namespace MyException {

	enum class ExcType
			{	
				Uknown = -1, //For undefined exceptions
				fileNotFound = 0, //can't open a file or file doesn't exist
				elemNotFound, //can't find elem in a container
				indexOutOfRange, //while going through a container we'v gone out of index range
				iterOutOfRange, //while iterating through a container we'v gone out of iter. range
				nullPtr, //?
				overflow, //?
				badAlloc //memory was supposed to be allocated but it didn't do that
			};	
	
	class Exception: public std::exception {
		public:
		string user_what(); //user_what() вывод расшифровку ошибки и комметарий
		const char* what() const noexcept;//what() - только расшифровка
		
		Exception();
		Exception(ExcType l_e, string l_msg = "");
		~Exception();
		
		private:
		ExcType e = ExcType::Uknown;
		string msg;
	};

}

#endif
