#pragma once
#include "Data Structures/Tree/Polymorphic/AbstractTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename INDEX_TYPE, typename STORED_TYPE>
		class ValuedTree : public AbstractTree<INDEX_TYPE, STORED_TYPE> {
		public:
			ValuedTree();
			ValuedTree(ValuedTree<INDEX_TYPE, STORED_TYPE>&& other);
			ValuedTree(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other);
			ValuedTree<INDEX_TYPE, STORED_TYPE>& operator=(ValuedTree<INDEX_TYPE, STORED_TYPE>&& other);
			ValuedTree<INDEX_TYPE, STORED_TYPE>& operator=(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other);
			virtual ~ValuedTree();

			ValuedTree(STORED_TYPE root);

			virtual STORED_TYPE& value() override;
			virtual const STORED_TYPE& value() const override;
		protected:
			inline void _move_(ValuedTree<INDEX_TYPE, STORED_TYPE>& other);
			inline void _copy_(const ValuedTree<INDEX_TYPE, STORED_TYPE>& other);
			inline void _cleanup_();
		private:
			STORED_TYPE root_value;
		};

	}

}