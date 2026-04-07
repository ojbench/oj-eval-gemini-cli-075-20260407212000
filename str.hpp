#ifndef STR_HPP
#define STR_HPP

#include <algorithm>
#include <cstring>
#include <vector>

class str
{
private:
	char* data;
	size_t length;

public:
	str() : data(new char[1]), length(0) {
		data[0] = '\0';
	}

	str(const char &c) : data(new char[2]), length(1) {
		data[0] = c;
		data[1] = '\0';
	}

	str(const char *&& s_) {
		if (s_) {
			length = std::strlen(s_);
			data = new char[length + 1];
			std::strcpy(data, s_);
		} else {
			length = 0;
			data = new char[1];
			data[0] = '\0';
		}
	}

	str(const char * const & s_) {
		if (s_) {
			length = std::strlen(s_);
			data = new char[length + 1];
			std::strcpy(data, s_);
		} else {
			length = 0;
			data = new char[1];
			data[0] = '\0';
		}
	}

	str &operator=(const char *&& s_) {
		if (s_ == data) return *this;
		char* new_data = nullptr;
		size_t new_length = 0;
		if (s_) {
			new_length = std::strlen(s_);
			new_data = new char[new_length + 1];
			std::strcpy(new_data, s_);
		} else {
			new_data = new char[1];
			new_data[0] = '\0';
		}
		delete[] data;
		data = new_data;
		length = new_length;
		return *this;
	}

	str &operator=(const char * const & s_) {
		if (s_ == data) return *this;
		char* new_data = nullptr;
		size_t new_length = 0;
		if (s_) {
			new_length = std::strlen(s_);
			new_data = new char[new_length + 1];
			std::strcpy(new_data, s_);
		} else {
			new_data = new char[1];
			new_data[0] = '\0';
		}
		delete[] data;
		data = new_data;
		length = new_length;
		return *this;
	}

	str(const str &other) {
		length = other.length;
		data = new char[length + 1];
		std::strcpy(data, other.data);
	}

	str &operator=(const str &other) {
		if (this != &other) {
			char* new_data = new char[other.length + 1];
			std::strcpy(new_data, other.data);
			delete[] data;
			length = other.length;
			data = new_data;
		}
		return *this;
	}

	char &operator[](size_t pos) {
		return data[pos];
	}

	const char &operator[](size_t pos) const {
		return data[pos];
	}

	size_t len() const {
		return length;
	}

	str join(const std::vector<str> &strs) const {
		if (strs.empty()) return str();
		size_t total_len = 0;
		for (size_t i = 0; i < strs.size(); ++i) {
			total_len += strs[i].len();
		}
		total_len += length * (strs.size() - 1);

		str result;
		delete[] result.data;
		result.length = total_len;
		result.data = new char[total_len + 1];
		
		size_t current_pos = 0;
		for (size_t i = 0; i < strs.size(); ++i) {
			std::memcpy(result.data + current_pos, strs[i].data, strs[i].length);
			current_pos += strs[i].length;
			if (i + 1 < strs.size()) {
				std::memcpy(result.data + current_pos, data, length);
				current_pos += length;
			}
		}
		result.data[total_len] = '\0';
		return result;
	}

	str slice(size_t l, size_t r) const {
		if (l >= r || l >= length) return str();
		if (r > length) r = length;
		size_t new_len = r - l;
		str result;
		delete[] result.data;
		result.length = new_len;
		result.data = new char[new_len + 1];
		std::memcpy(result.data, data + l, new_len);
		result.data[new_len] = '\0';
		return result;
	}

	~str() {
		delete[] data;
	}
};

#endif
