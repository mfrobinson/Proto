#pragma once
#include "Data Structures/Tree/Polymorphic/AbstractValuedTree.h"


namespace Proto {

	namespace Polymorphic {

		template <template <typename> typename LIST_TYPE, typename TYPE>
		class ListStoredTree : public AbstractValuedTree<TYPE> {
		public:
			ListStoredTree();
			ListStoredTree(ListStoredTree<LIST_TYPE, TYPE>&& other);
			ListStoredTree(const ListStoredTree<LIST_TYPE, TYPE>& other);
			ListStoredTree<LIST_TYPE, TYPE>& operator=(ListStoredTree<LIST_TYPE, TYPE>&& other);
			ListStoredTree<LIST_TYPE, TYPE>& operator=(const ListStoredTree<LIST_TYPE, TYPE>& other);
			~ListStoredTree();

			ListStoredTree(TYPE root_value);

			virtual void add(Pointer<AbstractTree<TYPE>>& subtree) override;
			virtual void insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) override;
			virtual void remove(const size_t position) override;

			virtual size_t number_of_children() const noexcept override;

			virtual AbstractTree<TYPE>* child(const size_t index) override;
			virtual const AbstractTree<TYPE>* child(const size_t index) const override;

			virtual Pointer<AbstractTree<TYPE>> clone() const override;
		protected:
			inline void _move_(ListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _copy_(const ListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _cleanup_();
			inline void _super_move_(ListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _super_copy_(const ListStoredTree<LIST_TYPE, TYPE>& other);
			inline void _super_cleanup_();
		private:
			LIST_TYPE<Pointer<AbstractTree<TYPE>>> subtrees;
		};

	}

}