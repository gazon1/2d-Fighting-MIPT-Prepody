#include "Exception.h"


namespace MyException {
	Exception::Exception() {}
	Exception::~Exception() {}
	Exception::Exception(ExcType l_e, string l_msg):
		e(l_e), msg(l_msg) 
	{}
	
	const char* Exception::what() const noexcept {
		switch (e) {
			case ExcType::fileNotFound:
				return  "Can't open a file or file doesn't exist";
				break;
			case ExcType::elemNotFound:
				return  "Wan't find elem in a container";
				break;
			case ExcType::indexOutOfRange:
				return  "While going through a container we'v gone out of index range";
				break;
			case ExcType::iterOutOfRange:
				return  "While iterating through a container we'v gone out of iter. range";
				break;
			case ExcType::nullPtr:
				return  "nullPtr";
				break;
			case ExcType::overflow:
				return  "overflow";
				break;
			case ExcType::badAlloc:
				return "memory was supposed to be allocated but it didn't do that";
				break;
			default:
				//for ExcType::Uknown
				return "Can't say for sure what happend";
				break;
		}
	}	
	
	string Exception::user_what() {
		string result;
		switch (e) {
			case ExcType::fileNotFound:
				result =  "Can't open a file or file doesn't exist";
				break;
			case ExcType::elemNotFound:
				result =  "Wan't find elem in a container";
				break;
			case ExcType::indexOutOfRange:
				result =  "While going through a container we'v gone out of index range";
				break;
			case ExcType::iterOutOfRange:
				result =  "While iterating through a container we'v gone out of iter. range";
				break;
			case ExcType::nullPtr:
				result =  "nullPtr";
				break;
			case ExcType::overflow:
				result =  "overflow";
				break;
			default:
				//for ExcType::Uknown
				result = "Can't say for sure what happend";
				break;
		}
		if (!msg.empty()) {
			result += "|" + msg;
		}
		msg = result;
		return msg;
	}	
}
