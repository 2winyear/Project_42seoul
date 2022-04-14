template <class Type>
class allocator
//example
std::vector<int, cAlloc<int>> v;
template <class T>
class allocator
{
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
  typedef T*        pointer;
  typedef const T*  const_pointer;
  typedef T&        reference;
  typedef const T&  const_reference;
  typedef T         value_type;

  template <class U> 
  struct rebind { typedef allocator<U> other; };

public:
	T* allocate(size_t);
  void deallocate(T*, size_t);
  void construct(T*, const T&);
  void destory(T*);
   
   ....
};

template <class In, class For>
For uninitialized_copy(In, In, For);

template <class For, class T>
void uninitialized_fill(For, For, const T&);