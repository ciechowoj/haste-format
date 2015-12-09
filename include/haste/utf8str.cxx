

namespace haste {

typedef char char8_t;
class str;

char8_t* data(str&);
const char8_t* data(const str&);
size_t nbytes(const str&);
static bool sso(const str&);
static unsigned char sso_nbytes(const str&);
static unsigned char& sso_nbytes(str&);
static size_t sso_capacity(const str&);

void swap(str&, str&);

class str {
public:
	str() {
		::memset(this, 0, sizeof(*this));
	}

	str(const str& that);
	str(str&& that);
	~str();

	str& operator=(const str& that);
	str& operator=(str&& that);

	friend char8_t* data(str& s) {
		return s._data;
	}

	friend const char8_t* data(const str& s) {
		return s._data;
	}

	friend size_t nbytes(const str& s) {
		if (sso(s)) {
			return sso_nbytes(s);
		}
		else {
			return s._size;
		}
	}

	friend bool sso(const str& s) {
		return reinterpret_cast<char*>(_data) == reinterpret_cast<char*>(&_size);
	}

	friend unsigned char sso_nbytes(const str& s) {
		return *(reinterpret_cast<const unsigned char*>(this) + sizeof(*this) - 1);
	}

	friend unsigned char& sso_nbytes(str& s) {
		return *(reinterpret_cast<unsigned char*>(this) + sizeof(*this) - 1);
	}

	friend size_t sso_capacity(const str& s) {
		return sizeof(str) - offsetof(str, _size) - 1;
	}

private:
	char8_t* _data;
	size_t _size;
	size_t _capacity;
	char8_t _[32 - sizeof(data) - sizeof(data) - sizeof(capacity)];
};






}
