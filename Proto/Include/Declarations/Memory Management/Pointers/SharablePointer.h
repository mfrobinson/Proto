#pragma once
#include "Memory Management/Pointers/AbstractInstancePointer.h"


namespace Proto {

	template <typename TYPE>
	class SharablePointer : public AbstractInstancePointer<TYPE> {
	public:
		SharablePointer();
		SharablePointer(SharablePointer<TYPE>&& other);
		SharablePointer(const SharablePointer<TYPE>& other);
		SharablePointer<TYPE>& operator=(SharablePointer<TYPE>&& other);
		SharablePointer<TYPE>& operator=(const SharablePointer<TYPE>& other);
		~SharablePointer();
		SharablePointer(TYPE instance);
		virtual operator TYPE* () override;
		virtual operator const TYPE* () const override;
		virtual TYPE* operator->() override;
		virtual const TYPE* operator->() const override;
	protected:
		struct InstanceRecord {
			size_t number_of_handles;
			TYPE* instance;
		};
		InstanceRecord* record;
	private:
		inline void _move_(SharablePointer<TYPE>& other);
		inline void _copy_(const SharablePointer<TYPE>& other);
		inline void _cleanup_();
		inline TYPE* access_instance() const;
	};

}