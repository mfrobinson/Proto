#pragma once
#include "ProtoString.h"
#include <fstream>


namespace Proto {

	class FileReader {
	public:
		FileReader();
		FileReader(FileReader&& other);
		FileReader(const FileReader& other) = delete;
		FileReader& operator=(FileReader&& other);
		FileReader& operator=(const FileReader& other) = delete;
		~FileReader();

		bool open(const String& path);
		bool is_open() const;
		String read_all();
		void close();
	protected:
		inline void _move_(FileReader& other);
		inline void _cleanup_();
	private:
		std::ifstream file_stream;
	};

}