#pragma once
#include "Data Structures/Tree/Polymorphic/AbstractTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		class AbstractValuedTree : public AbstractTree<TYPE>{
		public:
			AbstractValuedTree();
			AbstractValuedTree(AbstractValuedTree<TYPE>&& other);
			AbstractValuedTree(const AbstractValuedTree<TYPE>& other);
			AbstractValuedTree<TYPE>& operator=(AbstractValuedTree<TYPE>&& other);
			AbstractValuedTree<TYPE>& operator=(const AbstractValuedTree<TYPE>& other);
			virtual ~AbstractValuedTree();

			AbstractValuedTree(TYPE root_value);

			virtual TYPE& value() override;
			virtual const TYPE& value() const override;
		protected:
			inline void _move_(AbstractValuedTree<TYPE>& other);
			inline void _copy_(const AbstractValuedTree<TYPE>& other);
			inline void _cleanup_();
		private:
			TYPE root_value;
		};

	}

}