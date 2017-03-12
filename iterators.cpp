template <typename value_type>
	class Iterator : public std::iterator<std::random_access_iterator_tag, value_type>{
		private:
			pointer m_a;
			int m_pos = 0;
		public:
			Iterator() {}
			Iterator(pointer a, int pos) :m_a(a), m_pos(pos) {}

			Iterator& operator++(int i) {
				m_pos++;
				return *this;
			}

			Iterator& operator--(int i) {
				m_pos--;
				return *this;
			}

			Iterator& operator++() {
				++m_pos;
				return *this;
			}

			Iterator& operator--() {
				--m_pos;
				return *this;
			}
			reference operator*() {return *(m_a + m_pos);}

			int at() {return m_pos;}

			value_type& operator[](int index) {return *(m_a + index);}
	};

	template <typename value_type>
	class Const_Iterator : public std::iterator<std::random_access_iterator_tag, value_type>{
		private:
			pointer m_a;
			int m_pos = 0;
		public:
			Const_Iterator() {}
			Const_Iterator(pointer a, int pos) :m_a(a), m_pos(pos) {}

			Const_Iterator& operator++(int i) {
				m_pos++;
				return *this;
			}

			Const_Iterator& operator--(int i) {
				m_pos--;
				return *this;
			}

			Const_Iterator& operator++() {
				++m_pos;
				return *this;
			}

			Const_Iterator& operator--() {
				--m_pos;
				return *this;
			}
			const_reference operator*() {return *(m_a + m_pos);}

			int at() {return m_pos;}
	};