#ifndef MYALLOCATOR_HPP
# define MYALLOCATOR_HPP
# include <iostream>
# include <stddef.h>

template <class T>
class myAllocator
{
	public:
		typedef size_t    size_type;
		typedef ptrdiff_t difference_type;
		typedef T*        pointer;
		typedef const T*  const_pointer;
		typedef T&        reference;
		typedef const T&  const_reference;
		typedef T         value_type;

		myAllocator(void) {}
		myAllocator(myAllocator const &) {}
		~myAllocator(void) {}

		pointer allocate(size_type n, void * const = 0)
		{
			T* t = std::allocator<T>().allocate(n);
			return (t);
		}
		
		void  deallocate(void * p, size_type n)
		{
			if (p)
				std::allocator<T>().deallocate((T*)p, n);
		}

		pointer address(reference x) const {return (&x);}
		const_pointer address(const_reference x) const {return (&x);}
		myAllocator<T>& operator=(myAllocator const &) {return (*this);}
		void construct(pointer p, T const & val) {new(p) T(val);}
		void destroy(pointer p) { p->~T();}

		size_type max_size() const {return size_t(42);}

		template <class U>
		struct rebind {typedef myAllocator<U> other;};

		template <class U>
		myAllocator(myAllocator<U> const &) {}

		template <class U>
		myAllocator& operator=(myAllocator<U> const &) {return *this;}
};

#endif