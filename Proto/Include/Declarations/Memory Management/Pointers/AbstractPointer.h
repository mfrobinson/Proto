#pragma once


namespace Proto {

	template <typename TYPE>
	class AbstractPointer {
	public:
		virtual ~AbstractPointer() = 0;
		virtual operator TYPE* () = 0;
		virtual operator const TYPE* () const = 0;
	protected:
	private:
	};

}