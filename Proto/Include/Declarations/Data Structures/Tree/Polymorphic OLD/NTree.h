#pragma once
#include "Data Structures/Tree/Polymorphic/AbstractValuedTree.h"
#include "Memory Management/Pointers/Optional.h"


namespace Proto {

	namespace PolymorphicOLD {

		template <size_t N, typename TYPE>
		class NTree : public AbstractValuedTree<TYPE> {
		public:
			NTree();
			NTree(NTree<N, TYPE>&& other);
			NTree(const NTree<N, TYPE>& other);
			NTree<N, TYPE>& operator=(NTree<N, TYPE>&& other);
			NTree<N, TYPE>& operator=(const NTree<N, TYPE>& other);
			~NTree();

			NTree(TYPE root_value);

			virtual void add(Pointer<AbstractTree<TYPE>>& subtree) override;
			virtual void insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) override;
			virtual void remove(const size_t position) override;

			virtual size_t number_of_children() const noexcept override;

			virtual AbstractTree<TYPE>* child(const size_t index) override;
			virtual const AbstractTree<TYPE>* child(const size_t index) const override;

			virtual Pointer<AbstractTree<TYPE>> clone() const override;
		protected:
			inline void _move_(NTree<N, TYPE>& other);
			inline void _copy_(const NTree<N, TYPE>& other);
			inline void _cleanup_();
			inline void _super_move_(NTree<N, TYPE>& other);
			inline void _super_copy_(const NTree<N, TYPE>& other);
			inline void _super_cleanup_();
		private:
			Pointer<AbstractTree<TYPE>> child_trees[N];
		};

	}

}