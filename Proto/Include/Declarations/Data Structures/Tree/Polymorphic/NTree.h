#pragma once
#include "Data Structures/Tree/Polymorphic/ValuedTree.h"
#include "Memory Management/Pointers/StackArray.h"


namespace Proto {

	namespace Polymorphic {

		template <size_t N, typename STORED_TYPE>
		class NTree : public ValuedTree<size_t, STORED_TYPE> {
		public:
			NTree();
			NTree(NTree<N, STORED_TYPE>&& other);
			NTree(const NTree<N, STORED_TYPE>& other);
			NTree<N, STORED_TYPE>& operator=(NTree<N, STORED_TYPE>&& other);
			NTree<N, STORED_TYPE>& operator=(const NTree<N, STORED_TYPE>& other);
			virtual ~NTree();

			NTree(STORED_TYPE root);

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
			inline void _move_(NTree<N, STORED_TYPE>& other);
			inline void _copy_(const NTree<N, STORED_TYPE>& other);
			inline void _cleanup_();
		private:
			StackArray<N, Pointer<AbstractTree<size_t, STORED_TYPE>>> child_trees;

			inline void _this_move_(NTree<N, STORED_TYPE>& other);
			inline void _this_copy_(const NTree<N, STORED_TYPE>& other);

			inline void _super_move_(NTree<N, STORED_TYPE>& other);
			inline void _super_copy_(const NTree<N, STORED_TYPE>& other);
			inline void _super_cleanup_();

			inline AbstractTree<size_t, STORED_TYPE>* retrieve_child(const size_t& position) const;

			template <typename CHILD_TYPE>
			inline void retrieve_children_to_dictionary(AbstractDictionary<size_t, CHILD_TYPE>* storage_solution) const;
		};

	}

}