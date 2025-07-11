#pragma once
#include "Data Structures/Tree/Polymorphic/NTree.h"


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		class BinaryTree : public NTree<2, TYPE> {
		public:
			using NTree<2, TYPE>::NTree;
			using NTree<2, TYPE>::operator=;

			virtual Pointer<AbstractTree<TYPE>> clone() const override;

			virtual std::ostream& visualise(std::ostream& os, const String& prefix) const override;

			static const size_t LEFT = 0;
			static const size_t RIGHT = 1;
		protected:
		private:
		};

	}

}