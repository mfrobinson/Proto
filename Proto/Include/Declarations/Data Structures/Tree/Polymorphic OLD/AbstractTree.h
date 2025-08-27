#pragma once
#include "Memory Management/Pointers/Pointer.h"
#include "Memory Management/Cloneable.h"
#include "ProtoString.h"
#include <iostream>


namespace Proto {

	namespace PolymorphicOLD {

		template <typename TYPE>
		class AbstractTree : public Cloneable<AbstractTree<TYPE>> {
		public:
			/**
			* The virtual destructor of the interface.
			*
			* This insures that any deallocation of a Tree instance being treated
			* as an AbstractTree will have the appropriate derived destructor called.
			*
			* @exceptsafe Shall not throw any exceptions.
			*/
			virtual ~AbstractTree();
			/**
			* Add a subtree to this tree without a specified position. The Tree implementation
			* should decide where to add the subtree based on its functionality.
			*
			* @param[in] subtree The subtree to add to this tree.
			*/
			virtual void add(Pointer<AbstractTree<TYPE>>& subtree) = 0;
			/**
			* Insert a subtree into the specified position. If a subtree already exists at the position,
			* then the subtree passed to the method will be added to the already existing subtree. The Tree
			* implementation should decide what position values are valid.
			*
			* @param[in] subtree The subtree to add to this tree.
			*/
			virtual void insert(const size_t position, Pointer<AbstractTree<TYPE>>& subtree) = 0;
			/**
			* Remove a subtree from the specified position. If a subtree does not already exist at the 
			* specified position, then no changes are made to the tree. The Tree implementation should decide
			* what position values are valid.
			*
			* @param position The position of the subtree to remove.
			*/
			virtual void remove(const size_t position) = 0;
			/**
			* Retrieve the value of the root node of this tree via a reference.
			* 
			* @return A reference to the value stored at the root node of this tree.
			*/
			virtual TYPE& value() = 0;
			/**
			* Retrieve the value of the root node of this tree via a constant reference.
			*
			* @return A constant reference to the value stored at the root node of this tree.
			*/
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