#pragma once


namespace Proto {

	template <typename TYPE>
	class Pointer;

	template <typename TYPE>
	class Cloneable {
	public:
		virtual ~Cloneable();

		virtual Pointer<TYPE> clone() const = 0;
	protected:
	private:
	};

}