#include <haste/list.hpp>
#include <utility>
#include <cstdlib>

namespace haste {

namespace detail {

list::list() 
	: _data(nullptr)
	, _size(0)
	, _capacity(0) {
}

list::list(const list& that) {
	if (that._data) {
		_data = std::malloc(that._capacity * _item_size());
		_size = that._size;
		_capacity = that._capacity;
		_init(_data, that._data, _size);
	}
	else {
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}
}

list::list(list&& that) {
	_data = that._data;
	_size = that._size;
	_capacity = that._capacity;
	that._data = nullptr;
	that._size = 0;
	that._capacity = 0;
}

list::~list() {
	if (_data) {
		std::free(_data);
	}
}

list& list::operator=(const list& that) {
	if (this != &that) {
		if (_data) {
			_del(_data, _size);
			std::free(_data);
		}

		if (that._data) {
		_data = std::malloc(that._capacity * _item_size());
		_size = that._size;
		_capacity = that._capacity;
		_init(_data, that._data, _size);
		}
		else {
			_data = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}

	return *this;
}

list& list::operator=(list&& that) {
	if (this != &that) {
		if (_data) {
			_del(_data, _size);
			std::free(_data);
		}

		_data = that._data;
		_size = that._size;
		_capacity = that._capacity;
		that._data = nullptr;
		that._size = 0;
		that._capacity = 0;
	}

	return *this;
}



}


}