#pragma once

namespace haste {

using size_t = unsigned long long;

namespace detail {

struct list {
	list();
	list(const list&);
	list(list&&);
	~list();

	list& operator=(const list&);
	list& operator=(list&&);

	void _reserve(size_t n);

	virtual size_t _item_size() const = 0;
	virtual void _init(void*, const void*, size_t) const = 0;
	virtual void _del(void*, size_t) const = 0;

	void* _data;
	size_t _size;
	size_t _capacity;
};

}

template <class T> class list;

template <class T> void reserve(list<T>&, size_t);
template <class T> void append(list<T>&, const T& x);
template <class T> size_t xsize(const list<T>&);

template <class T> class list : private detail::list {
public:
	list() = default;
	list(const list<T>&) = default;
	list(list<T>&&) = default;

	template <class... L> list(const L&...);

	~list() {
		_del(_data, _size);
	}

	list<T>& operator=(const list<T>&) = default;
	list<T>& operator=(list<T>&&) = default;
		
	T& operator[](size_t i) {
		return reinterpret_cast<T*>(_data)[i];
	}

	const T& operator[](size_t i) const {
		return reinterpret_cast<const T*>(_data)[i];
	}

	template <class U> friend void reserve(list<U>& l, size_t n) {
		l._reserve(n);
	}
	template <class T> friend void append(list<T>&, const T& x);

	template <class U> friend size_t xsize(const list<U>& l) {
	    return l._size;
	}
private:
	int _append(const T& x) {
		append(*this, x);
		return 0;
	}

	virtual size_t _item_size() const {
		return sizeof(T);
	}

	virtual void _init(void* d, const void* s, size_t n) const {
		for (size_t i = 0; i < n; ++i) {
			new (static_cast<T*>(d) + i) T(static_cast<const T*>(s)[i]);
		}
	}

	virtual void _del(void* d, size_t n) const {
		for (size_t i = 0; i < n; ++i) {
			static_cast<T*>(d)[i].~T();
		}
	}
};

template <class T> template <class... L> inline list<T>::list(const L&... l) 
	: list() {
	reserve(*this, sizeof...(l));
	int x[] = { _append(l)... };
}

template <class T> inline bool operator==(const list<T>& a, const list<T>& b) {
	size_t s = xsize(a);
	
	if (s == xsize(b)) {
		for (size_t i = 0; i < s; ++i) {
			if (a[i] != b[i]) {
				return false;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

template <class T> inline bool operator!=(const list<T>& a, const list<T>& b) {
	return !(a == b);
}

}
