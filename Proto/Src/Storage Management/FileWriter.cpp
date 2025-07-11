#include "Storage Management/FileWriter.h"


namespace Proto {

	FileWriter::FileWriter() {
		return;
	}

	FileWriter::FileWriter(FileWriter&& other) {
		this->_move_(other);
		return;
	}

	FileWriter& FileWriter::operator=(FileWriter&& other) {
		if (&other != this) {
			this->_cleanup_();
			this->_move_(other);
		}
		return *this;
	}

	FileWriter::~FileWriter() {
		this->_cleanup_();
		return;
	}

	bool FileWriter::open(const String& path) {
		this->file_stream.open(path, std::fstream::binary | std::fstream::out | std::fstream::ate);
		return this->is_open();
	}

	bool FileWriter::is_open() const {
		return this->file_stream.is_open();
	}

	void FileWriter::close() {
		this->file_stream.close();
		return;
	}

	void FileWriter::write_all(const String& content) {
		if (this->is_open()) {
			this->file_stream.write(content, content.length() - 1);
		}
		return;
	}

	inline void FileWriter::_move_(FileWriter& other) {
		this->file_stream = (std::ofstream&&)other.file_stream;
		return;
	}

	inline void FileWriter::_cleanup_() {
		this->file_stream.close();
		return;
	}


}