#pragma once
#include "ProtoString.h"
#include <fstream>


namespace Proto {

	class FileWriter {
	public:
		FileWriter();
		FileWriter(FileWriter&& other);
		FileWriter(const FileWriter& other) = delete;
		FileWriter& operator=(FileWriter&& other);
		FileWriter& operator=(const FileWriter& other) = delete;
		~FileWriter();

		bool open(const String& path);
		bool is_open() const;
		void write_all(const String& content);
		void close();
	protected:
		inline void _move_(FileWriter& other);
		inline void _cleanup_();
	private:
		std::ofstream file_stream;
	};

}