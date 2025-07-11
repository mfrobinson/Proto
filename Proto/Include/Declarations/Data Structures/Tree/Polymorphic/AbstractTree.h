#pragma once
#include "Memory Management/Pointers/Pointer.h"
#include "Memory Management/Cloneable.h"
#include "ProtoString.h"
#include <iostream>


namespace Proto {

	namespace Polymorphic {

		template <typename TYPE>
		class AbstractTree : public Cloneable<AbstractTree<TYPE>> {
		public:
			virtual ~AbstractTree();

			// Different Tree structures simply have too much variance in functionality to include a polymorphic "add child" method.
			// However, all other functionality is fairly consistent, and can be modelled in an interface.

			virtual void add(Pointer<AbstractTree<TYPE>>& subtree) = 0;
			virtual void insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) = 0;
			virtual void remove(const size_t position) = 0;

			virtual TYPE& value() = 0;
			virtual const TYPE& value() const = 0;

			virtual size_t number_of_children() const noexcept = 0;

			virtual AbstractTree<TYPE>* child(const size_t index) = 0;
			virtual const AbstractTree<TYPE>* child(const size_t index) const = 0;

			virtual size_t height() const noexcept;

			virtual Pointer<AbstractTree<TYPE>> clone() const = 0;

			virtual std::ostream& visualise(std::ostream& os, const String& prefix = "") const;
		protected:
		private:
		};

		template <typename TYPE>
		std::ostream& operator<<(std::ostream& os, const AbstractTree<TYPE>& tree);

	}

}