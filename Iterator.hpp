#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

namespace APbst {

    template <typename nodeT, typename T>
    class __iterator{
        nodeT* currentNode;
      public:
        using value_type = T;       // T can be either pair or const pair
        using reference = value_type&;
        using pointer = value_type*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t; // Two iterators are equal if they point to the same node

        explicit __iterator(nodeT* n) noexcept : currentNode{n} {}

        reference operator*() const noexcept { return currentNode->data; }
        pointer operator->() const noexcept { return &(*(*this)); }

        __iterator& operator++() noexcept {  // Iterator ++it (pre-increment)
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

        __iterator operator++(int) noexcept {  // Iterator it++ (post-increment)
            __iterator tmpIterator{currentNode};
            ++(*this);
            return tmpIterator;
        }

        friend inline bool operator==(const __iterator& a, const __iterator& b) { return a.currentNode == b.currentNode; }

        friend inline bool operator!=(const __iterator& a, const __iterator& b) { return !(a == b); }
    };

}


#endif // ITERATOR_HPP
