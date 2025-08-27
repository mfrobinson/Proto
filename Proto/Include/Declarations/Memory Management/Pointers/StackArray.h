#pragma once
#include "Memory Management/Pointers/AbstractArrayPointer.h"


namespace Proto {

	template <size_t N, typename TYPE>
	class StackArray : public AbstractArrayPointer<TYPE> {
	public:
		StackArray();
		StackArray(StackArray<N, TYPE>&& other);
		StackArray(const StackArray<N, TYPE>& other);
		StackArray<N, TYPE>& operator=(StackArray<N, TYPE>&& other);
		StackArray<N, TYPE>& operator=(const StackArray<N, TYPE>& other);
		~StackArray();

		virtual TYPE& operator[](const size_t index) override;
		virtual const TYPE& operator[](const size_t index) const override;
		virtual operator TYPE* () override;
		virtual operator const TYPE* () const override;
	protected:
		inline void _move_(StackArray<N, TYPE>& other);
		inline void _copy_(const StackArray<N, TYPE>& other);
		inline void _cleanup_();
	private:
		TYPE internal_array[N];

		inline TYPE* access_pointer() const;
		inline TYPE& access_index(const size_t index) const;
	};

}