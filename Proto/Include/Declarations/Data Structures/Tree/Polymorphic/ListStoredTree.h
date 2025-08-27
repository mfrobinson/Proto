#pragma once
#include "Declarations/Data Structures/Tree/Polymorphic/ValuedTree.h"


namespace Proto {

	namespace Polymorphic {

		template <template <typename> typename LIST_TYPE, typename STORED_TYPE>
		class ListStoredTree : public ValuedTree<size_t, STORED_TYPE> {
		public:
			ListStoredTree();
			ListStoredTree(ListStoredTree<LIST_TYPE, STORED_TYPE>&& other);
			ListStoredTree(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			ListStoredTree<LIST_TYPE, STORED_TYPE>& operator=(ListStoredTree<LIST_TYPE, STORED_TYPE>&& other);
			ListStoredTree<LIST_TYPE, STORED_TYPE>& operator=(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			virtual ~ListStoredTree();

			ListStoredTree(STORED_TYPE root);

			virtual void add(Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) override;
			virtual void insert(size_t position, Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) override;
			virtual void remove(const size_t& position) override;

			virtual void children(AbstractDictionary<size_t, AbstractTree<size_t, STORED_TYPE>*>* storage_solution) override;
			virtual void children(AbstractDictionary<size_t, const AbstractTree<size_t, STORED_TYPE>*>* storage_solution) const override;

			virtual AbstractTree<size_t, STORED_TYPE>* child(const size_t& position) override;
			virtual const AbstractTree<size_t, STORED_TYPE>* child(const size_t& position) const override;

			virtual size_t number_of_children() const noexcept override;

			virtual Pointer<AbstractTree<size_t, STORED_TYPE>> clone() const override;
		protected:
			inline void _move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			inline void _copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			inline void _cleanup_();
		private:
			LIST_TYPE<Pointer<AbstractTree<size_t, STORED_TYPE>>> child_trees;

			inline void _this_move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			inline void _this_copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other);

			inline void _super_move_(ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			inline void _super_copy_(const ListStoredTree<LIST_TYPE, STORED_TYPE>& other);
			inline void _super_cleanup_();

			template <typename CHILD_TYPE>
			inline void retrieve_children_to_dictionary(AbstractDictionary<size_t, CHILD_TYPE>* storage_solution) const;
		};

	}

}