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


template<typename T>
class Array{
private:
	typedef T 								value_type;
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
	/*void* operator new(size_t size, size_t n) {
		std::ofstream out("ff");
		out<<"I'm here";
		void* mem = malloc(size * n);
		memset(mem, 0, size * n);
		return mem;
	}*/


	iterator begin() {
		return m_data;
	}

	iterator end() {
		return (m_data + m_size);
	}

	Array():m_size(0),
			m_data (static_cast<value_type*>(operator new[] (m_capacity * sizeof(value_type)))) 
	{
		DEBUG_INFO("Default constructor", dump();)
	}

	Array(int capacity) {
		ASSERT((m_capacity > 0), "Capacity is less than zero")
		try {
			m_data = static_cast<value_type*>(operator new[] (m_capacity * sizeof(value_type)));
			m_size = 0;
			m_capacity = capacity;
		} catch (std::exception& e) {
			throw array_exception("Bad allocation in capacity constructor");
		}

		DEBUG_INFO("Capacity constructor", dump();)
	}

	Array(const_pointer data, int size) {
		ASSERT((size > 0), "Size is less than zero")
		ASSERT((data != NULL), "Array in parameters is not initialized")
		std::cout<<"Size "<<sizeof(value_type)<<std::endl;
		std::cout<<"Size "<<sizeof(int)<<std::endl;
		std::cout<<"Parameter size  "<<size<<std::endl;

		m_data = static_cast<value_type*>(std::malloc(sizeof(value_type) * size));

		std::cout<<&data[0]<<std::endl;
		std::cout<<&data[size - 1]<<std::endl;
		std::cout<<&m_data[0]<<std::endl;
		std::cout<<&m_data[(size - 1)]<<std::endl;

		for (int i = 0; i < size; i++)
				std::cout<<data[i]<<" ";
		m_size = size;
		m_capacity = m_size;
		pointer data_tmp = new value_type[size];
		for (int i = 0; i < size; i++)
			data_tmp[i] = data[i]; 

		for (int i = 0; i < size; i++) {
			new (m_data + i) value_type(data_tmp[i]);
			for (int i = 0; i < size; i++)
				std::cout<<data[i]<<" ";
			std::cout<<std::endl;
		}
		DEBUG_INFO("Pointer constructor", dump();)
	}

	Array(std::initializer_list<value_type> list) {
		ASSERT((list.size() >0), "List is empty")
		
		m_data = static_cast<value_type*>(operator new[] (list.size() * sizeof(value_type)));
		m_size = list.size();
		m_capacity = m_size;

		int count = 0;
		try {
			for (int i = 0; i < list.size(); i++) {
				new (m_data + i) value_type(list[i]);
				count += 1;
			}
		} catch(std::exception& e) {
			for (int i = 0; i < count; i++) {
				m_data[i].~value_type();
			}
			throw array_exception("Bad allocation in list constructor");
		}
		
		DEBUG_INFO("List constructor", dump();)
	}

	Array(Array&& data) :
	m_size(std::move(data.m_size)),
	m_capacity(std::move(data.m_capacity)),
	m_data (std::move(data.m_data)){
	  DEBUG_INFO("Move constructor, passing data dump", data.dump();)
	
	  data.m_data = nullptr;
	
	  DEBUG_INFO("Move constructor (after moving)", dump();)
	}

	reference at(int index) {
		DEBUG_INFO("At operator", dump();)
		if ( (index > m_size) || (index < 0)) 
			throw std::out_of_range("Out of size range");
		return m_data[index];
	}

	const_reference at(int index) const {
		DEBUG_INFO("Const at operator", dump();)
    	if ( (index > m_size) || (index < 0)) 
        	throw std::out_of_range("Out of size range");
        return m_data[index];
	}

	reference operator[] (int index) {
		DEBUG_INFO("Operator[]", dump();)
		return m_data[index];
	}

	const_reference operator[] (int index) const{
		DEBUG_INFO("Const operator[]", dump();)
		return m_data[index];
	}

	pointer data() noexcept(noexcept(value_type())) {
		DEBUG_INFO("Function data()", dump();)
		return m_data;
	}

	const_pointer data() const noexcept(noexcept(value_type())){
		DEBUG_INFO("Const function data()", dump();)
		return m_data;
	}
	
	reference front() noexcept(noexcept(value_type())) {
		DEBUG_INFO("Function front()", dump();)
		return m_data[0];
	}
	const_reference front() const noexcept(noexcept(value_type())){
		DEBUG_INFO("Const function front()", dump();)
		return m_data[0];
	}

	reference back() noexcept(noexcept(value_type())) {
		DEBUG_INFO("Function back()", dump();)
		return m_data[m_size - 1];
	}
	const_reference back() const noexcept(noexcept(value_type())){
		DEBUG_INFO("Const function back()", dump();)
		return m_data[m_size - 1];
	}

	int size() {
		DEBUG_INFO("Function size()", dump();)
		return m_size;
	}

	int max_size() {
		DEBUG_INFO("Function max_size()", dump();)
		return m_capacity;
	}

	void reserve(int size) {
		DEBUG_INFO("Function reserve()", dump();)
		ASSERT(ok(), "Cannot reserve, array is broken")
		if (size > max_size())
			throw std::length_error("Size is greater than max size");
		if (size > m_size) {
			resize(size);
		}
		DEBUG_INFO("Function reserve() (after reserving)", dump();)
		ASSERT(ok(), "Array is broken after resizing");
	}


	void push_back(reference elem) {
		DEBUG_INFO("Function push_back()", dump();)
		ASSERT(ok(), "Cannot push, array is broken")
		if ((m_size + 1) > m_capacity)
			resize(2 * m_size);
		m_data[m_size++] =  elem;
		DEBUG_INFO("Function push_back() ( after pushing)", dump();)
		ASSERT(ok(), "Array is broken after push()")
	}

	void pop_back() {
		DEBUG_INFO("Function pop_back()", dump();)
		ASSERT((m_size > 0), "size is less than zero, cannot pop")
		--m_size;
	}

	Array(const Array<value_type>& data) {
		m_size = data.m_size;
		m_capacity = data.m_capacity;
		m_data = new value_type[m_capacity];
		std::copy(&data.m_data[0], &data.m_data[m_size], &m_data[0]);

		DEBUG_INFO("Copy constructor ", dump();)
	}

	const Array<value_type>& operator=(const Array<value_type>& data) {
		ASSERT(data.ok(), "Invalid input data")

		if (this == &data) { 
			DEBUG_INFO("Operator = (eqaulity was true)", dump();) 
			return *this;
		}
		if (m_size == 0)
			m_data = static_cast<value_type*>(operator new[] (data.m_size * sizeof(value_type)));
		else if (m_size < data.m_size) {
			resize(data.m_size);
		}
		auto a(data);
		a.swap(*this);

		DEBUG_INFO("Operator = (after =)", dump();)
		ASSERT(ok(), "Array is broken after operator = ")
		return *this;
	}

	Array<value_type>& operator=(Array<value_type>&& data) {
		DEBUG_INFO("Move operator =", dump();)
		ASSERT(data.ok(), "Passing array is broken, cannot move")

		m_size = data.m_size;
		m_capacity = data.m_capacity;
		m_data (std::move(data.m_data));
		data.m_data = nullptr;

		DEBUG_INFO("Move operator = (after move)", dump();)
		ASSERT(ok(), "Array is broken after move =")
	}

	void swap(Array<value_type>& data) noexcept{
		DEBUG_INFO("Function swap() ", dump();)

		std::swap(data.m_data, this->m_data);
		std::swap(data.m_size, this->m_size);
		std::swap(data.m_capacity, this->m_capacity);
		
		DEBUG_INFO("Function swap() (after swap)", dump();)
	}

	template <typename ...Args>
	pointer emplace(int pos, Args&&... args) {
		DEBUG_INFO("Function emplace()", dump();)

		if ((m_size + 1) > m_capacity) {
			auto tmp(*this);
			resize(2 * m_size);
			std::copy(&tmp.m_data[0], &tmp.m_data[pos], &m_data[0]);
			m_data[pos] = *(new value_type(std::forward<value_type>(args)...));
			std::copy(&tmp.m_data[pos], &tmp.m_data[m_size], &m_data[pos + 1]);
		} else {
			auto tmp(*this);
			m_data[pos] = *(new value_type(std::forward<value_type>(args)...));
			std::copy(&tmp.m_data[pos], &tmp.m_data[m_size],&m_data[pos + 1]);
		}
		m_size+=1;

		DEBUG_INFO("Function emplace() (after emplace)", dump();)
		ASSERT(ok(), "Array is broken after emplace")
		return &m_data[pos];
	}
			
	void resize(int size) {
		DEBUG_INFO("Function resize()", dump();)
		ASSERT(ok(), "Array is broken, cannot be resized")

		auto tmp(*this);
		delete[] m_data;
		m_data = static_cast<value_type*>(operator new[] (size * sizeof(value_type)));
		m_capacity = size;
		int count = 0;
		try {
			for (int i = 0; i < m_size; i++) {
				new (m_data + i) value_type(tmp.m_data[i]);
				count += 1;
			}
		} catch(std::exception& e) {
			for (int i = 0; i < count; i++) {
				m_data[i].~value_type();
			}
			throw array_exception("Bad allocation in resize");
		}

		DEBUG_INFO("Function resize() (after resize)", dump();)
		ASSERT(ok(), "Array is broken after resizing")
	}

	Array<value_type>& operator+=(const Array<value_type>& other) {
		DEBUG_INFO("Operator += ", dump();)
		ASSERT(ok(), "Current array is broken, cannot add")
		ASSERT(other.ok(), "Another array is broken, cannot add")
		
		auto size = std::min(m_size, other.m_size);
		for (int i = 0; i < size; i++) {m_data[i] += other.m_data[i];}
		
		DEBUG_INFO("Operator +=(after +=) ", dump();)
		ASSERT(ok(), "Current array is broken after add")
		ASSERT(other.ok(), "Another array is broken after add")
		
		return *this;
	}

	Array<value_type>& operator-=(Array<value_type>& other) {
		DEBUG_INFO("Operator -= ", dump();)
		ASSERT(ok(), "Current array is broken, cannot sub")
		ASSERT(other.ok(), "Another array is broken, cannot sub")
		
		auto size = std::min(m_size, other.m_size);
		for (int i = 0; i < size; i++) {m_data[i] -= other.m_data[i];}
		
		DEBUG_INFO("Operator -=(after -=)", dump();)
		ASSERT(ok(), "Current array is broken, cannot sub")
		ASSERT(other.ok(), "Another array is broken, cannot sub")
		
		return *this;
	}

	void clear() {
		DEBUG_INFO("Function clear() ", dump();)
		ASSERT(ok(), "Current array is broken, cannot clear")

		delete[] m_data;
		m_size = 0;
		m_data = static_cast<value_type*>(operator new[] (m_capacity * sizeof(value_type)));

		DEBUG_INFO("Function clear() (after clearing)", dump();)
		ASSERT(ok(), "Array is broken after clear")
	}

	void raw_resize(int size) {
		delete[] m_data;
		m_data = static_cast<value_type*>(operator new[] (size * sizeof(value_type)));
	}

//если сделать через emplace то как будто зря объект создается
	iterator insert(const_iterator it, const value_type& elem) {
		DEBUG_INFO("Function insert() ", dump();)
		ASSERT(std::addressof(it) <= std::addressof(m_data + m_size), "Invalid position for insertion")
		
		if ((m_size + 1) > m_capacity) {
			auto tmp(*this);
			raw_resize(2 * m_size);
			int i = 0;
			while (tmp[i] != *it) {
				new (m_data + i) value_type(tmp[i]);
				i+=1;
			}
			new (m_data + i) value_type(elem); i+=1;
			while (i != m_size) {
				new (m_data + i) value_type(tmp[i]);
				i+=1;
			}
		} else {
			auto tmp(*this);
			int i = 0;
			while(tmp[i] != *it) {
				i+=1;
			}
			m_data[i] = elem;
			std::copy(&tmp.m_data[i], &tmp.m_data[m_size],&m_data[i + 1]);
		}
		m_size+=1;

		DEBUG_INFO("Function insert() (after insertion)", dump();)
		return begin();
	}

	iterator insert( const_iterator pos, T&& value ) {
		return nullptr;
	}

	iterator insert( const_iterator pos, size_type count, const T& value ) {
		return nullptr;
	}

	void dump() const{
		if (ok()) {std::cout<<"ARRAY IS IN OK STATE. PRINTING INFO ..."<<std::endl;}
		else { 
			std::cout<<" ARRAY IS BROKEN. PRINTING INFO..."<<std::endl;
			std::cout<<"Address of broken array : "<<std::addressof(m_data)<<std::endl;
		};
		std::cout<<"ARRAY SIZE : "<<m_size<<std::endl;
		std::cout<<"ARRAY CAPACITY : "<<m_capacity<<std::endl;
		std::cout<<"DATA TYPE : "<<typeid(T).name()<<std::endl;
		std::cout<<"ARRAY ELEMENTS : "<<std::endl;
		std::cout<<"-----------------------------------------"<<std::endl;
		for (int i = 0; i < m_size ; i++)
			std::cout <<"Element ["<<i<<"] : "<<m_data[i]<<std::endl;
		std::cout<<std::endl;
		std::cout<<"-----------------------------------------"<<std::endl;
		std::cout<<std::endl;
	}

	bool ok() const{
		return (m_data!= NULL) && (m_size >= 0) && (m_capacity >= 0) && (m_size <= m_capacity);
	}

	~Array() {
		DEBUG_PRINT("DESTRUCTOR is called")
		m_data = 0;
		m_capacity = 0;
		delete[] m_data;
		m_data = nullptr;
	}
};

template <typename T>
Array<T> operator+(Array<T> a1, Array<T>& a2) {
	DEBUG_INFO("Operator + with move", a1.dump(); a2.dump();)
	std::cout<<"After copy construction"<<std::endl;
	a1+=a2;
	DEBUG_INFO("Operator + with move (after add)", a1.dump(); a2.dump();)
	return a1;
}

template <typename T>
Array<T> operator-(Array<T> a1, Array<T>& a2) {
	DEBUG_INFO("Operator + with move", a1.dump(); a2.dump();)
	std::cout<<"After copy construction"<<std::endl;
	a1-=a2;
	DEBUG_INFO("Operator + with move (after add)", a1.dump(); a2.dump();)
	return a1;
}




//make own exception (конструктор big exception)
//пользовательские ассерты превращаются в exception
//std clog
//soft assert

//код ошибки возвращать,  завимсимости от этого throw или что то еще
//ok с разным уровнем жесткости - типа ok с ассертом и ok с throw
//писать адрес объекта ( типа delete был вызван или нет)