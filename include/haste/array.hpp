#pragma once
#include <string>
#include <haste/data_t.hpp>

namespace haste {

using std::string;

class array;

void swap(array&, array&);

class array {
public:
	typedef unsigned char ubyte;

	array();
	array(const array&);
	array(array&&);
	~array();

	array& operator=(const array&);
	array& operator=(array&&);

	ubyte* data();
	const ubyte* data() const;
	size_t ndim() const;
	size_t nbytes() const;
	size_t shape(size_t i) const;
	size_t stride(size_t i) const;
	data_t dtype() const;

	static array empty(size_t ndim, size_t* shape, data_t dtype);

	friend void swap(array&, array&);
private:
	ubyte* _storage();
	const ubyte* _storage() const;
	size_t _storage_size() const;

	ubyte* _data;
	size_t _ndim;
	data_t _dtype;
	size_t* _shape;
	size_t* _strides;
};

inline array::ubyte* array::data() {
	return _data;
}

inline const array::ubyte* array::data() const {
	return _data;
}

inline size_t array::ndim() const {
	return _ndim;
}

inline size_t array::shape(size_t i) const {
	return _shape[i];
}

inline size_t array::stride(size_t i) const {
	return _strides[i];
}

inline data_t array::dtype() const {
	return _dtype;
}

}
