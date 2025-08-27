#pragma once
#include "Memory Management/Cloneable.h"
#include "ProtoString.h"
#include "Memory Management/Pointers/Pointer.h"
#include "Data Structures/Dictionary/AbstractDictionary.h"
#include <iostream>


namespace Proto {

	namespace Polymorphic {

		template <typename INDEX_TYPE, typename STORED_TYPE>
		class AbstractTree : public Cloneable<AbstractTree<INDEX_TYPE, STORED_TYPE>> {
		public:
			virtual ~AbstractTree();

			virtual void add(Pointer<AbstractTree<INDEX_TYPE, STORED_TYPE>>& subtree) = 0;
			virtual void insert(INDEX_TYPE position, Pointer<AbstractTree<INDEX_TYPE, STORED_TYPE>>& subtree) = 0;
			virtual void remove(const INDEX_TYPE& position) = 0;

			virtual STORED_TYPE& value() = 0;
			virtual const STORED_TYPE& value() const = 0;

			virtual void children(AbstractDictionary<INDEX_TYPE, AbstractTree<INDEX_TYPE, STORED_TYPE>*>* storage_solution) = 0;
			virtual void children(AbstractDictionary<INDEX_TYPE, const AbstractTree<INDEX_TYPE, STORED_TYPE>*>* storage_solution) const = 0;

			virtual AbstractTree<INDEX_TYPE, STORED_TYPE>* child(const INDEX_TYPE& position) = 0;
			virtual const AbstractTree<INDEX_TYPE, STORED_TYPE>* child(const INDEX_TYPE& position) const = 0;

			virtual size_t number_of_children() const noexcept = 0;

			virtual size_t height() const noexcept;

			virtual std::ostream& visualise(std::ostream& os, const String& prefix = "") const;
		protected:
		private:
		};

		template <typename INDEX_TYPE, typename STORED_TYPE>
		std::ostream& operator<<(std::ostream& os, const AbstractTree<INDEX_TYPE, STORED_TYPE>& tree);

	}

}