#pragma once
#include "Data Structures/Tree/Polymorphic/ValuedTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename STORED_TYPE>
		class BinaryTree : public ValuedTree<size_t, STORED_TYPE> {
		public:
			static const size_t LEFT;
			static const size_t RIGHT;

			BinaryTree();
			BinaryTree(BinaryTree<STORED_TYPE>&& other);
			BinaryTree(const BinaryTree<STORED_TYPE>& other);
			BinaryTree<STORED_TYPE>& operator=(BinaryTree<STORED_TYPE>&& other);
			BinaryTree<STORED_TYPE>& operator=(const BinaryTree<STORED_TYPE>& other);
			virtual ~BinaryTree();

			BinaryTree(STORED_TYPE root);

			virtual void add(Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) override;
			virtual void insert(size_t position, Pointer<AbstractTree<size_t, STORED_TYPE>>& subtree) override;
			virtual void remove(const size_t& position) override;

			virtual void children(AbstractDictionary<size_t, AbstractTree<size_t, STORED_TYPE>*>* storage_solution) override;
			virtual void children(AbstractDictionary<size_t, const AbstractTree<size_t, STORED_TYPE>*>* storage_solution) const override;

			virtual AbstractTree<size_t, STORED_TYPE>* child(const size_t& position) override;
			virtual const AbstractTree<size_t, STORED_TYPE>* child(const size_t& position) const override;

			virtual size_t number_of_children() const noexcept override;

			virtual Pointer<AbstractTree<size_t, STORED_TYPE>> clone() const override;

			virtual std::ostream& visualise(std::ostream& os, const String& prefix = "") const override;
		protected:
			inline void _move_(BinaryTree<STORED_TYPE>& other);
			inline void _copy_(const BinaryTree<STORED_TYPE>& other);
			inline void _cleanup_();
		private:
			Pointer<AbstractTree<size_t, STORED_TYPE>> left_child;
			Pointer<AbstractTree<size_t, STORED_TYPE>> right_child;

			inline void _this_move_(BinaryTree<STORED_TYPE>& other);
			inline void _this_copy_(const BinaryTree<STORED_TYPE>& other);

			inline void _super_move_(BinaryTree<STORED_TYPE>& other);
			inline void _super_copy_(const BinaryTree<STORED_TYPE>& other);
			inline void _super_cleanup_();

			inline AbstractTree<size_t, STORED_TYPE>* retrieve_child(const size_t& position) const;
		};

	}

}