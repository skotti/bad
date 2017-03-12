#include <iostream>
#include <initializer_list>
#include <exception>
#include <stdexcept>

#ifdef NDEBUG
#define DEBUG_INFO(exp)
#else 
#define DEBUG_INFO(exp) exp
#endif

#define ASSERT(cond, exp) if (!(cond)) {\
                          std::cout<<"ASSERTION FAILED"<<std::endl; \
                          std::cout<<"FILE : "<<__FILE__<<std::endl;\
                          std::cout<<"LINE : "<<__LINE__<<std::endl;\
                          std::cout<<"MESSAGE : "<<(exp)<<std::endl;\
                          abort();}


template<typename T, std::size_t N>
class FixedArray{
public:
	typedef T										value_type;
	typedef T*										pointer;
	typedef const T*								const_pointer;
	typedef value_type&								reference;
	typedef const value_type&						const_reference;
	typedef value_type*								iterator;
	typedef const value_type*						const_iterator;
	typedef std::size_t								size_type;
	typedef std::reverse_iterator<iterator> 		reverse_iterator;
	typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;

	value_type m_data[N];

	/*FixedArray(std::initializer_list<value_type> list) {
		ASSERT((list.size() > 0), "Invalid initializer list size")
		std::copy_n(list.begin(), N, &m_data[0]);
		ASSERT(ok(), "Array is broken after construction")
		DEBUG_INFO(std::cout<<"List constructor"<<std::endl; dump();)
	}

	FixedArray(const FixedArray<value_type, N>& data) {
		std::copy(data.begin(), data.end(), &m_data[0]);
		ASSERT(ok(), "Array is broken after copy construction")
		DEBUG_INFO(std::cout<<"Copy constructor"<<std::endl; dump();)
	}

	FixedArray<value_type, N>& operator=(const FixedArray<value_type, N>& data) {
		if (this == &data) { return *this;}
		std::copy(data.begin(), data.end(), &m_data[0]);
		ASSERT(ok(), "Array is broken after operator = ")
		DEBUG_INFO(std::cout<<"Function operator ="<<std::endl; dump();)
	}

	FixedArray(FixedArray<value_type, N>&& data) {
		std::copy_n(data.begin(), N, &m_data[0]);
	}*/
	//в чем разница между addressof и operator&
	constexpr iterator begin() noexcept{
		DEBUG_INFO(std::cout<<"Function begin()"<<std::endl; dump();)
		return iterator(std::addressof(m_data[0]));
	}

	constexpr const_iterator begin() const noexcept{
		DEBUG_INFO(std::cout<<"Function const begin()"<<std::endl; dump();)
		return iterator(std::addressof(m_data[0]));
	}

	constexpr iterator end() noexcept{
		DEBUG_INFO(std::cout<<"Function end()"<<std::endl; dump();)
		return iterator(std::addressof(m_data[N]));
	}

	constexpr const_iterator end() const noexcept{
		DEBUG_INFO(std::cout<<"Function const end()"<<std::endl; dump();)
		return iterator(std::addressof(m_data[N]));
	}

	constexpr reference at(int index)  {
		DEBUG_INFO(std::cout<<"Constexpr at operator"<<std::endl; dump();)
		if ( (index > N) || (index < 0)) 
			throw std::out_of_range("Out of size range");
		return m_data[index];
	}

	constexpr const_reference at(int index) const{
		DEBUG_INFO(std::cout<<"Const constexpr at operator"<<std::endl; dump();)
    	if ( (index > N) || (index < 0)) 
        	throw std::out_of_range("Out of size range");
        return m_data[index];
	}

	constexpr reference operator[] (int index) {
		DEBUG_INFO(std::cout<<"Operator[]"<<std::endl; dump();)
		return m_data[index];
	}

	constexpr const_reference operator[] (int index) const{
		DEBUG_INFO(std::cout<<"Const operator[]"<<std::endl; dump();)
		return m_data[index];
	}

	constexpr pointer data() noexcept(value_type()) {
		DEBUG_INFO(std::cout<<"Function data()"<<std::endl; dump();)
		return m_data;
	}

	constexpr const_pointer data() const noexcept(value_type()){
		DEBUG_INFO(std::cout<<"Const function data()"<<std::endl; dump();)
		return m_data;
	}
	
	constexpr reference front() noexcept(value_type()) {
		DEBUG_INFO(std::cout<<"Function front()"<<std::endl; dump();)
		return *begin();
	}
	constexpr const_reference front() const noexcept(value_type()){
		DEBUG_INFO(std::cout<<"Const function front()"<<std::endl; dump();)
		return *begin();
	}

	constexpr reference back() noexcept(value_type()) {
		DEBUG_INFO(std::cout<<"Function back()"<<std::endl; dump();)
		return *(end() - 1);
	}
	constexpr const_reference back() const noexcept(value_type()){
		DEBUG_INFO(std::cout<<"Const function back()"<<std::endl; dump();)
		return *(end() - 1);
	}

	constexpr size_type size() {
		DEBUG_INFO(std::cout<<"Function size()"<<std::endl; dump();)
		return N;
	}

	constexpr size_type size() const{
		DEBUG_INFO(std::cout<<"Function size()"<<std::endl; dump();)
		return N;
	}

	constexpr size_type max_size() {
		DEBUG_INFO(std::cout<<"Function max_size()"<<std::endl; dump();)
		return N;
	}

	constexpr bool empty() {
		DEBUG_INFO(std::cout<<"Function empty()"<<std::endl; dump();)
		return (N == 0);
	}

	void fill(const value_type& value) {
		DEBUG_INFO(std::cout<<"Function fill()"<<std::endl; dump();)
		ASSERT(ok(), "FixedArray is broken, cannot fill");
		std::fill(&m_data[0], &m_data[N], value);
		DEBUG_INFO(std::cout<<"Function fill()"<<std::endl; dump();)
		ASSERT(ok(), "FixedArray is broken after filling");
	}

	void swap(FixedArray<value_type, N>& data) noexcept(std::swap(std::declval<T&>(), std::declval<T&>())){
		DEBUG_INFO(std::cout<<"Function swap() "<<std::endl; dump();)
		std::swap(data.m_data, this->m_data);
		DEBUG_INFO(std::cout<<"Function swap() (after swap)"<<std::endl; dump();)
	}

	//можно ли переопределить для разных размеров?
	FixedArray<value_type, N>& operator+=(const FixedArray<value_type, N>& other) {
		DEBUG_INFO(std::cout<<"Operator += "<<std::endl; dump();)
		ASSERT(ok(), "Current array is broken, cannot add")
		ASSERT(other.ok(), "Another array is broken, cannot add")
		for (int i = 0; i < N; i++) {m_data[i] += other.m_data[i];}
		DEBUG_INFO(std::cout<<"Operator +=(after +=) "<<std::endl; dump();)
		ASSERT(ok(), "Current array is broken after add")
		ASSERT(other.ok(), "Another array is broken after add")
		return *this;
	}

	FixedArray<value_type, N>& operator-=(FixedArray<value_type, N>& other) {
		DEBUG_INFO(std::cout<<"Operator -= "<<std::endl; dump();)
		ASSERT(ok(), "Current array is broken, cannot sub")
		ASSERT(other.ok(), "Another array is broken, cannot sub")
		for (int i = 0; i < N; i++) {m_data[i] -= other.m_data[i];}
		DEBUG_INFO(std::cout<<"Operator -=(after -=)"<<std::endl; dump();)
		ASSERT(ok(), "Current array is broken, cannot sub")
		ASSERT(other.ok(), "Another array is broken, cannot sub")
		return *this;
	}

	void dump() const{
		if (ok()) {std::cout<<"FIXED_ARRAY IS IN OK STATE. PRINTING INFO ..."<<std::endl;}
		else { std::cout<<"FIXED_ARRAY IS BROKEN. PRINTING INFO..."<<std::endl;};
		std::cout<<"FIXED_ARRAY SIZE : "<<N<<std::endl;
		std::cout<<"DATA TYPE : "<<typeid(T).name()<<std::endl;
		std::cout<<"FIXED_ARRAY ELEMENTS : "<<std::endl;
		std::cout<<"-----------------------------------------"<<std::endl;
		for (int i = 0; i < N; i++)
			std::cout <<"Element ["<<i<<"] : "<<m_data[i]<<std::endl;
		std::cout<<std::endl;
		std::cout<<"-----------------------------------------"<<std::endl;
		std::cout<<std::endl;
	}

	bool ok() const{
		return (m_data!= NULL) && (N >= 0);
	}

	//delete каждого элемента если не знаем тип элемента
	/*~FixedArray() {
	}*/

};

template <typename T, std::size_t N>
FixedArray<T1, min (N1, N2)> operator+(FixedArray<T1, N1> a1, FixedArray<T2, N2>& a2) {
	DEBUG_INFO(std::cout<<"Operator + with move"<<std::endl; a1.dump(); a2.dump();)
	std::cout<<"After copy construction"<<std::endl;
	

	FA <T1, min (N1, N2)> res;

	a1+=a2;
	
	DEBUG_INFO(std::cout<<"Operator + with move (after add)"<<std::endl; a1.dump(); a2.dump();)
	return a1;
}
