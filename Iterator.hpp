#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>  /* For std::forward_iterator_tag */


namespace APbst {
    template<typename KT, typename VT, typename cmp>
    class bst;
}

namespace APutils {

    template <typename nodeT, typename T>
    class __iterator {
        /** @brief @ref Node pointed by the iterator. */
        nodeT* currentNode;
      public:
        /* Standard members of the class Iterator. You could also derive them directly from the class std::iterator,
         * but since c++17 is deprecated our is the right way. */
        using value_type = T;       // T can be either pair or const pair
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;

        /**
         * @brief Constructor.
         * @param n a @ref Node.
         *
         * To instantiate an @ref __iterator.
         */
        explicit __iterator(nodeT* n) noexcept : currentNode{n} {}

        /**
         * @brief Operator of re-cast.
         * @param n a @ref Node.
         *
         * For the cast at const_iterator.
         */
        operator __iterator<nodeT, const T>() { return __iterator<nodeT, const T>{currentNode}; }

        /**
         * @brief Operator of de-reference.
         *
         * To de-refrence an @ref __iterator.
         */
        reference operator*() const noexcept { return currentNode->data; }
        pointer operator->() const noexcept { return &(*(*this)); }

        /**
         * @brief Pre-increment function (iterator ++it).
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
         * @brief Post-increment function (iterator it++).
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
        }

        /**
         * @brief Comparison operator for equality.
         *
         * Two iterators are equal if they point to the same node.
         */
        friend inline bool operator==(const __iterator& a, const __iterator& b) { return a.currentNode == b.currentNode; }

        /**
         * @brief Comparison operator for inequality.
         */
        friend inline bool operator!=(const __iterator& a, const __iterator& b) { return !(a == b); }

        /**
         * The function is declared to be `friend` in order to make it able to
         * access our private member (@ref currentNode).
         */
        template<typename KT, typename VT, typename cmp>
        friend class APbst::bst;
//        template<typename KT, typename VT, typename cmp>
//        friend void APbst::bst<KT,VT,cmp>::erase(const KT&);

        void printNode(std::ostream& os = std::cout, const bool& printChildren = false) {
            currentNode->printNode(os, printChildren);
        }
    };

}


#endif // ITERATOR_HPP
