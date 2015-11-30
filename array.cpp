#include <haste/array.hpp>
#include <cstring>

namespace haste {

using namespace std;

static const size_t array_align = 8;

void swap(array& a, array& b) {
	if (&a != &b) {
		std::swap(a._data, b._data);
		std::swap(a._ndim, b._ndim);
		std::swap(a._dtype, b._dtype);
		std::swap(a._shape, b._shape);
		std::swap(a._strides, b._strides);
	
		if (!a._data) {
			a._shape = &a._ndim;
			a._strides = &a._ndim;
		}
		
		if (!b._data) {
			b._shape = &b._ndim;
			b._strides = &b._ndim;
		}
	}
}

array::array() 
	: _data(nullptr)
	, _ndim(0)
	, _dtype(data_t::unorm8x1)
	, _shape(&_ndim)
	, _strides(&_ndim) {
}

array::array(const array& that) 
	: array() {
	if (that._data) {
		ubyte* storage = static_cast<ubyte*>(::malloc(that._storage_size()));

		_ndim = that._ndim;
		_dtype = that._dtype;
		_data = storage + _ndim * 2 * sizeof(size_t);
		_shape = reinterpret_cast<size_t*>(storage);
		_strides = _shape + _ndim;

		::memcpy(_storage(), that._storage(), that._storage_size());
	}
}

array::array(array&& that) 
	: array() {
	swap(*this, that);
}

array::~array() {
	if (_data) {
		::free(_storage());
	}
}

array& array::operator=(const array& that) {
	if (this != &that) {
		array temp(that);
		swap(*this, temp);
	}

	return *this;
}

array& array::operator=(array&& that) {
	swap(*this, that);
	return *this;
}

size_t array::nbytes() const {
	return (_shape[0] * _strides[0] + array_align - 1) / array_align * array_align;
}

array array::empty(size_t ndim, size_t* shape, data_t dtype) {
	if (ndim == 0) {
		auto result = array();
		result._dtype = dtype;
		return result;
	}
	else {
		size_t item = haste::stride(dtype);
		size_t stride = (shape[ndim - 1] * item + array_align - 1) / array_align * array_align;
		size_t nbytes = stride;

		for (size_t i = 0; i < ndim - 1; ++i) {
			nbytes *= shape[i];
		}

		ubyte* storage = static_cast<ubyte*>(::malloc(nbytes + sizeof(size_t) * 2 * ndim));

		array result;
		result._data = storage + sizeof(size_t) * 2 * ndim;
		result._ndim = ndim;
		result._shape = reinterpret_cast<size_t*>(storage);
		result._strides = result._shape + ndim;

		for (size_t i = 0; i < ndim; ++i) {
			result._shape[i] = shape[i];
		}

		result._strides[ndim - 1] = item;
		result._strides[ndim - 2] = stride;

		for (size_t i = 3; i <= ndim; ++i) {
			result._strides[ndim - i] = result._strides[ndim - i + 1] * result._shape[ndim - i];
		}

		result._dtype = dtype;

		return result;
	}
}

array::ubyte* array::_storage() {
	return _shape != &_ndim ? reinterpret_cast<array::ubyte*>(_shape) : nullptr;
}

const array::ubyte* array::_storage() const {
	return _shape != &_ndim ? reinterpret_cast<array::ubyte*>(_shape) : nullptr;
}

size_t array::_storage_size() const {
	return _ndim * 2 * sizeof(size_t) + nbytes();
}

}
