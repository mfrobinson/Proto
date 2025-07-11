#include "Storage Management/FileReader.h"


namespace Proto {

	FileReader::FileReader() {
		return;
	}

	FileReader::FileReader(FileReader&& other) {
		this->_move_(other);
		return;
	}

	FileReader& FileReader::operator=(FileReader&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	FileReader::~FileReader() {
		this->_cleanup_();
		return;
	}

	bool FileReader::open(const String& path) {
		this->file_stream.open(path, std::fstream::binary | std::fstream::in);
		return this->is_open();
	}

	bool FileReader::is_open() const {
		return this->file_stream.is_open();
	}

	String FileReader::read_all() {
		if (this->is_open()) {
			size_t initial_position = this->file_stream.tellg();
			this->file_stream.seekg(0, std::ios::end);
			size_t total_length = this->file_stream.tellg();
			Array<char> content(total_length);
			this->file_stream.seekg(0, std::ios::beg);
			this->file_stream.read(content, total_length);
			this->file_stream.seekg(initial_position);
			return String(content, total_length);
		}
		return String();
	}

	void FileReader::close() {
		this->file_stream.close();
		return;
	}

	inline void FileReader::_move_(FileReader& other) {
		this->file_stream = (std::ifstream&&)other.file_stream;
		return;
	}

	inline void FileReader::_cleanup_() {
		this->file_stream.close();
		return;
	}


}