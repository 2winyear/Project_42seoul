// #ifndef VECTOR_HPP
// #define VECTOR_HPP

// #include <iostream>
// #include <memory>
// #include <string>
// //index of
// //robots.txt

// namespace ft {
// 	template <class Type, class Allocator = std::allocator<Type>>
// 	// template <class Allocator = allocator<bool>>
// 	// class vector<bool, Allocator>
// 	class vector {
// 		private:
// 			allocator_type  _alloc;
// 			pointer         _start;
// 			pointer         _end;
// 			pointer         _end_capacity;
		
// 		public:

// 			typedef Type value_type;
// 			typedef Type value_type;
// 			typedef Type const const_value_type;
// 			typedef Allocator allocator_type;
			
// 			typedef typename allocator_type::pointer			pointer;
// 			typedef typename allocator_type::const_pointer		const_pointer;
// 			typedef typename allocator_type::reference			reference;
// 			typedef typename allocator_type::const_reference	const_reference;

// 			size_type max_size() const { return (this->_alloc.max_size()); };

// 			/*
// 			typedef VectorIterator<T> iterator;
// 			typedef VectorIterator<const T> const_iterator;
// 			typedef VectorReverseIterator<T> reverse_iterator;
// 			typedef VectorReverseIterator<const T> const_reverse_iterator;
// 			*/
// 			template<typename _T>
// 			VectorIterator(VectorIterator<_T> const &ve) : ptr((_T*)ve.getPtr()) {}
			
			
// 			size_type capacity() const { return (this->_end_capacity - this->_start); };

// 			void reserve (size_type n)
// 			{
// 				if (n > this->max_size())
// 					throw out_of_range("length_error");	
// 				if (n <= this->capacity())
// 					return ;
// 			}
			
// 			reference operator[] (size_type n);
// 			const_reference operator[] (size_type n) const;

// 			reference at (size_type n);
// 			const_reference at (size_type n) const;
// 	}; // class

// 	// 
// 	// void assign(size_type count, const Type& value);
// 	// void assign(initializer_list<Type> init_list);
// 	// template <class InputIterator>
// 	// void assign(InputIterator first, InputIterator last);

// };	//namespace ft

// /*
// operator!=
// operator==
// operator<
// operator<=
// operator>
// operator>=
// */

// #endif

#include <iostream>
#include <string>

template <typename T>
class Vector {
  T* data;
  int capacity;
  int length;

 public:
  // ?????? ????????? ???????????????

  typedef T value_type;

  // ?????????
  Vector(int n = 1) : data(new T[n]), capacity(n), length(0) {}

  // ??? ?????? ????????? ????????? ????????????.
  void push_back(T s) {
    if (capacity <= length) {
      T* temp = new T[capacity * 2];
      for (int i = 0; i < length; i++) {
        temp[i] = data[i];
      }
      delete[] data;
      data = temp;
      capacity *= 2;
    }

    data[length] = s;
    length++;
  }

  // ????????? ????????? ????????? ????????????.
  T operator[](int i) { return data[i]; }

  // x ?????? ????????? ????????? ????????????.
  void remove(int x) {
    for (int i = x + 1; i < length; i++) {
      data[i - 1] = data[i];
    }
    length--;
  }

  // ?????? ????????? ????????? ?????????.
  int size() { return length; }

  ~Vector() {
    if (data) {
      delete[] data;
    }
  }
};

template <>
class Vector<bool> {
  unsigned int* data;
  int capacity;
  int length;

 public:
  typedef bool value_type;

  // ?????????
  Vector(int n = 1)
      : data(new unsigned int[n / 32 + 1]), capacity(n / 32 + 1), length(0) {
    for (int i = 0; i < capacity; i++) {
      data[i] = 0;
    }
  }

  // ??? ?????? ????????? ????????? ????????????.
  void push_back(bool s) {
    if (capacity * 32 <= length) {
      unsigned int* temp = new unsigned int[capacity * 2];
      for (int i = 0; i < capacity; i++) {
        temp[i] = data[i];
      }
      for (int i = capacity; i < 2 * capacity; i++) {
        temp[i] = 0;
      }

      delete[] data;
      data = temp;
      capacity *= 2;
    }

    if (s) {
      data[length / 32] |= (1 << (length % 32));
    }

    length++;
  }

  // ????????? ????????? ????????? ????????????.
  bool operator[](int i) { return (data[i / 32] & (1 << (i % 32))) != 0; }

  // x ?????? ????????? ????????? ????????????.
  void remove(int x) {
    for (int i = x + 1; i < length; i++) {
      int prev = i - 1;
      int curr = i;

      // ?????? curr ????????? ?????? ????????? 1 ?????????
      // prev ????????? ?????? ????????? 1 ??? ?????????.
      if (data[curr / 32] & (1 << (curr % 32))) {
        data[prev / 32] |= (1 << (prev % 32));
      }
      // ????????? prev ????????? ?????? ????????? 0 ?????? ?????????.
      else {
        unsigned int all_ones_except_prev = 0xFFFFFFFF;
        all_ones_except_prev ^= (1 << (prev % 32));
        data[prev / 32] &= all_ones_except_prev;
      }
    }
    length--;
  }

  // ?????? ????????? ????????? ?????????.
  int size() { return length; }
  ~Vector() {
    if (data) {
      delete[] data;
    }
  }
};

int main() {
  // int ??? ???????????? ????????? ?????????.
  Vector<int> int_vec;
  int_vec.push_back(3);
  int_vec.push_back(2);

  std::cout << "-------- int vector ----------" << std::endl;
  std::cout << "????????? ?????? : " << int_vec[0] << std::endl;
  std::cout << "????????? ?????? : " << int_vec[1] << std::endl;

  Vector<std::string> str_vec;
  str_vec.push_back("hello");
  str_vec.push_back("world");
  std::cout << "-------- std::string vector -------" << std::endl;
  std::cout << "????????? ?????? : " << str_vec[0] << std::endl;
  std::cout << "????????? ?????? : " << str_vec[1] << std::endl;

  Vector<bool> bool_vec;
  bool_vec.push_back(true);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(false);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);
  bool_vec.push_back(true);
  bool_vec.push_back(false);

  std::cout << "-------- bool vector ---------" << std::endl;
  for (int i = 0; i < bool_vec.size(); i++) {
    std::cout << bool_vec[i];
  }
  std::cout << std::endl;
}