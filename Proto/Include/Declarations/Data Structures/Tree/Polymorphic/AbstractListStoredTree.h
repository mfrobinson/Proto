#pragma once
#include "Data Structures/Tree/Polymorphic/AbstractTree.h"


namespace Proto {

	namespace Polymorphic {

		template <template <typename> typename LIST_TYPE, typename TYPE>
		class AbstractListStoredTree : public AbstractTree<TYPE> {
		public:
			virtual ~AbstractListStoredTree();

			virtual void add(Pointer<AbstractPolymorphicTree<TYPE>> child) override;
			virtual void remove(const size_t index) override;

			virtual TYPE* value() override;
			virtual const TYPE* value() const override;

			virtual size_t number_of_children() const noexcept override;

			virtual AbstractTree<TYPE>* child(const size_t index) override;
			virtual const AbstractTree<TYPE>* child(const size_t index) const override;
		protected:
			inline void _move_(AbstractListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _copy_(const AbstractListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _cleanup_();
		private:
			Pointer<TYPE> root_value;
			LIST_TYPE<Pointer<AbstractPolymorphicTree<TYPE>>> children;
		};

	}

}