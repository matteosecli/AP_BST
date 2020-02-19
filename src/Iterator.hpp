#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>  /* For std::forward_iterator_tag */


namespace APbst {
    template<typename KT, typename VT, typename cmp>
    class bst;
}


namespace APutils {

    /**
     * @brief Class that implements an iterator of a tree.
     */
    template <typename nodeT, typename T>
    class __iterator {
        /** @brief @ref Node referred to by the iterator. */
        nodeT* currentNode;
      public:
        /* Standard members of the class Iterator. You could also derive them directly from the class std::iterator,
         * but since c++17 is deprecated our is the right way. */
        /**
         * @brief Type of the data stored by @ref Node
         *
         * E.g. `std::<const Key, Value>` for APbst::bst.
         */
        using value_type = T;       // T can be either pair or const pair
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        /**
         * @brief Constructor.
         *
         * @param n Raw pointer to a @ref Node.
         *
         * Creates a new @ref __iterator that refers to @ref Node @ref n.
         */
        explicit __iterator(nodeT* n) noexcept : currentNode{n} {}

        /*
         * @brief Operator of re-cast.
         *
         * For the cast at const_iterator.
         */
        //operator __iterator<nodeT, const T>() { return __iterator<nodeT, const T>{currentNode}; }

        /**
         * @brief Dereference operator.
         *
         * Dereferences an @ref __iterator by returning the data stored by the
         * @ref Node it refers to.
         *
         * @see __iterator::operator->
         */
        reference operator*() const noexcept { return currentNode->data; }
        
        /**
         * @brief Arrow operator.
         *
         * Class member access operator; it returns a pointer to the data
         * stored by the @ref Node the @ref __iterator refers to.
         *
         * @see __iterator::operator*
         */
        pointer operator->() const noexcept { return &(*(*this)); }

        /**
         * @brief Pre-increment operator.
         *
         * @see __iterator::operator++(int)
         */
        __iterator& operator++() noexcept {
            /* If we are a nullptr, we return ourselves.
             */
            if (!currentNode) { // equivalent to if (currentNode == nullptr)
                return *this;
            /* If we have a right child, we descend the tree always right until
             * we only have a left child.
             */
            } else if (currentNode->right) {
                currentNode = currentNode->right.get();
                while (currentNode->left) {
                    currentNode = currentNode->left.get();
                } // end while
            /* We go up in the tree while we are the right child of our parent;
             * when we are no more the right child and we are then the left child,
             * we go up one last time to the parent.
             */
            } else {
                nodeT* tmpNode = currentNode->parent;
                while (tmpNode && currentNode == tmpNode->right.get()) {
                    currentNode = tmpNode;
                    tmpNode = currentNode->parent;
                } // end while
                currentNode = tmpNode;
            } // end if
            return *this;
        } // end ++it

        /**
         * @brief Post-increment operator.
         *
         * @see __iterator::operator++()
         */
        __iterator operator++(int) noexcept {
            /* The following line calls our 1-element constructor by giving an
             * argument of type nodeT*. An almost equivalent statement would be
             *     __iterator tmpIterator{*this};
             * that instead calls the copy constructor, since the argument is of
             * type *(__iterator&) == __iterator. Is one better than the other? =)
             */
            __iterator tmpIterator{currentNode};
            ++(*this);
            return tmpIterator;
        } // end it++

        /**
         * @brief Equality operator.
         *
         * Two iterators are defined equal if they point to the same node.
         *
         * @see __iterator::operator!=
         */
        friend inline bool operator==(const __iterator& a, const __iterator& b) { return a.currentNode == b.currentNode; }

        /**
         * @brief Inequality operator.
         *
         * The logical negation of @ref __iterator::operator==.
         *
         * @see __iterator::operator==
         */
        friend inline bool operator!=(const __iterator& a, const __iterator& b) { return !(a == b); }

        /**
         * The class @ref APbst::bst is declared to be `friend` in order to make
         * it able to access our private member ( @ref currentNode).
         */
        template<typename KT, typename VT, typename cmp>
        friend class APbst::bst;

        /**
         * @brief Prints a tree @ref Node.
         *
         * Forwards to @ref Node.printNode().
         */
        template<class... Types>
        void printNode(Types&&... args) {
            return currentNode->printNode(std::forward<Types>(args)...);
        }
    };

}


#endif // ITERATOR_HPP
