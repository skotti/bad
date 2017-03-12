#include <iostream>
#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <fstream>

class array_exception : public std::exception {
public:
	array_exception(std::string m) : msg(m){}
	~array_exception(){}
	const char* what() {return msg.c_str();}

private:
	std::string msg;
};



#ifdef NDEBUG
#define DEBUG_INFO(message, func)
#define DEBUG_PRINT(message)
#else 
#define DEBUG_INFO(message, func) std::cout<<message<<std::endl; func
#define DEBUG_PRINT(message) std::cout<<message<<std::endl;
#endif

#ifdef NDEBUG
#define ASSERT(cond, exp) if (!(cond)) {\
                          std::cout<<"ASSERTION FAILED"<<std::endl; \
                          std::cout<<"FILE : "<<__FILE__<<std::endl;\
                          std::cout<<"LINE : "<<__LINE__<<std::endl;\
                          std::cout<<"MESSAGE : "<<(exp)<<std::endl;\
                          abort();}
 #else
 #define ASSERT(cond, exp)
 #endif

 #ifdef NDEBUG
 #define SOFT_ASSERT(cond, exp)
 #else
 #define SOFT_ASSERT(cond, exp)
 #endif                         


template<typename bool>
class Array{
private:
	typedef bool 							value_type;
	typedef size_t 							size_type;
	typedef std::ptrdiff_t 					difference_type;
	typedef value_type& 					reference;
	typedef const value_type&				const_reference;
	typedef value_type* 					pointer;
	typedef const value_type*				const_pointer;
	typedef value_type*						iterator;
	typedef const value_type*				const_iterator;
	typedef value_type*						input_iterator;

	int m_size;
	int m_capacity = 10; 
	value_type* m_data;
public:

	class reference {
	private:
		int pos;
	public:
		reference() {

		}

		~reference(){
			pos = 0;
		}

		reference& operator=( bool x ) {
			m_data[pos] = x;
		}

		reference& operator=( const reference& x ) {
			m_data[pos] = x;
		}

		
	};









