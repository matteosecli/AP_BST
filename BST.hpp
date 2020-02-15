#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <utility>
#include <vector>
#include "Node.hpp"
#include "Iterator.hpp"

//#ifndef DEBUG
//#define DEBUG false    /**< @brief Whether we are in DEBUG mode or not; DEBUG mode prints much more info (which, though, slows the program down). */
//#endif


/** 
 * @brief Principal namespace
 * 
 * Namespace of the library bst
 */
namespace APbst {

    /**
     * @brief Class that implements a Binary Search Tree.
     */
    template <typename KT, typename VT, typename cmp = std::less<KT>>
    class bst{
        /** @brief Operator of comparison. */
        cmp op;
        /** @brief The root of the tree. */
        std::unique_ptr<APutils::Node<std::pair<const KT, VT>>> root;

        /**
         * @brief Support function for the function @ref balance().
         * @param v The vector.
         * @param a The starting point of the vector.
         * @param b The ending point of the vector.
         */
        void __balance(std::vector<std::pair<const KT, VT>>& v, long long int a, long long int b) {
            if (b < a) {
                return;
            }
            long long int mid{(b + a)/2};
            std::cout << "Inserting " << v[mid].first << " in palce " << mid << std::endl;
            this->emplace(v[mid]);
            __balance(v, a, mid-1);
            __balance(v, mid+1, b);
            return;
        }

        /**
         * @brief Support function for the copy semantic.
         * @param t The tree to be copied.
         */
        void __copy(const bst& t, std::unique_ptr<APutils::Node<std::pair<const KT, VT>>>& a) {
            this->emplace(a.get()->data);
            if (a.get()->left) {
                __copy(t, a.get()->left);
            }
            if (a.get()->right) {
                __copy(t, a.get()->right);
            }
            return;
        }

      public:
        using key_type = KT;
        using mapped_type = VT;
        using pair_type = typename std::pair<const KT, VT>;
        using pair_type_nc = typename std::pair<KT, VT>;
        using node_type = typename APutils::Node<pair_type>;
        using iterator = typename APutils::__iterator<node_type,  pair_type>;
        using const_iterator = typename APutils::__iterator<node_type, const pair_type>;

        /**
         * @brief Empty constructor.
         */
        bst() noexcept : op{}, root{nullptr} {}

        /**
         * @brief Constructor setting the comparison operation.
         * @param x The comparison operator.
         */
        bst(cmp x) noexcept : op{x}, root{nullptr} {}

        /**
         * @brief Copy constructor.
         * @param t The tree to be copied.
         */
        bst(const bst& t) : op{t.op}, root{std::unique_ptr<node_type>(new node_type(t.root.get()->data, nullptr))} {
            if (t.root.get()->left) {
                __copy(t, t.root.get()->left);
            }
            if (t.root.get()->right) {
                __copy(t, t.root.get()->right);
            }
        }

        /**
         * @brief Move constructor.
         * @param t The tree to be moved.
         */
        bst(bst&& t) noexcept = default;

        /**
         * @brief Copy assignment for @ref bst.
         * @param t The tree to be copied.
         *
         * It performs a deep-copy of the tree.
         */
        bst& operator=(const bst& t) {
            this->clear();
            this->emplace(t.root.get()->data);
            if (t.root.get()->left) {
                __copy(t, t.root.get()->left);
            }
            if (t.root.get()->right) {
                __copy(t, t.root.get()->right);
            }
            return *this;
        }

        /**
         * @brief Move assignment for @ref bst.
         * @param t The tree to be moved.
         */
        bst& operator=(bst&& t) noexcept = default;

        /**
         * @brief Inserts a @ref Node by copying it in the tree, if not already present.
         * @param x The values of the `Key` and the `Value` to be put in the @ref Node.
         *
         * Used to insert a new @ref Node. The function returns a `pair` of an @ref __iterator (pointing to the @ref Node) and a `bool`.
         * The `bool` is `true` if a new @ref Node has been allocated, `false` otherwise (i.e., the `Key` was already present in the tree). 
         */
        //std::pair<iterator, bool> insert(const pair_type_nc& x) {
        std::pair<iterator, bool> insert(const pair_type& x) {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: COPY_INSERT: APbst::bst::insert(const pair_type& x)" << std::endl;
            #endif
            auto tmp = root.get();
            while (tmp) {
                if (op(x.first,tmp->data.first)) {
                    if (tmp->left) {
                        tmp = tmp->left.get();
                    } else {
                        tmp->left.reset(new node_type{x, tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->left.get()}, true);
                    }
                } else if (op(tmp->data.first, x.first)) {
                    if (tmp->right) {
                        tmp = tmp->right.get();
                    } else {
                        tmp->right.reset(new node_type{x, tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->right.get()}, true);
                    }
                } else {
                    return std::make_pair<iterator, bool>(iterator{tmp}, false);
                }
            }
            // The tree is empty, so I put it in the root
            root.reset(new node_type{x, nullptr});
            return std::make_pair<iterator, bool>(iterator{tmp}, true);
        }

        /**
         * @brief Inserts a @ref Node by moving it in the tree, if not already present.
         * @param x The values of the `Key` and the `Value` to be put in the @ref Node.
         *
         * Used to insert a new node. The function returns a `pair` of an @ref __iterator (pointing to the @ref Node) and a `bool`.
         * The `bool` is `true` if a new @ref Node has been allocated, `false` otherwise (i.e., the `Key` was already present in the tree). 
         */
        //std::pair<iterator, bool> insert(pair_type_nc&& x) {
        std::pair<iterator, bool> insert(pair_type&& x) {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: MOVE_INSERT: APbst::bst::insert(pair_type&& x)" << std::endl;
            #endif
            auto tmp = root.get();
            while (tmp) {
                if (op(x.first,tmp->data.first)) {
                    if (tmp->left) {
                        tmp = tmp->left.get();
                    } else {
                        tmp->left.reset(new node_type{std::move(x), tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->left.get()}, true);
                    }
                } else if (op(tmp->data.first, x.first)) {
                    if (tmp->right) {
                        tmp = tmp->right.get();
                    } else {
                        tmp->right.reset(new node_type{std::move(x), tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->right.get()}, true);
                    }
                } else {
                    return std::make_pair<iterator, bool>(iterator{tmp}, false);
                }
            }
            root.reset(new node_type{std::move(x), nullptr});
            return std::make_pair<iterator, bool>(iterator{tmp}, true);
        }

        // template <typename Args>
        // std::pair<iterator, bool> insert(Args&& args) {
        //     return __insert(std::forward<Args>(args));
        // }

        // /**
        //  * @brief insert
        //  * @param x @ref insert(const pair_type& x)
        //  * @see insert(const pair_type& x)
        //  * @return
        //  *
        //  * This function redirects to @ref insert(const pair_type& x).
        //  * It's provided in order to address use cases in which the user uses e.g.
        //  * `std::pair<int, int>` instead of `std::pair<const int, int>`.
        //  */
        // std::pair<iterator, bool> insert(const pair_type_nc& x) {
        //     std::cout << "CALL: COPY_INSERT_NC: APbst::bst::insert(const pair_type_nc& x)" << std::endl;
        //     return insert((const pair_type)x);
        // }

        // std::pair<iterator, bool> insert(pair_type_nc&& x) {
        //     std::cout << "CALL: MOVE_INSERT_NC: APbst::bst::insert(pair_type_nc&& x)" << std::endl;
        //     return insert((pair_type)x);
        // }

        /**
         * @brief Inserts an element constructed in-place.
         *
         * Inserts a new element into the tree constructed in-place with the given args if there is no element with the
         * `Key` in the tree.
         */
        template<class... Types>  // variadic templates
        std::pair<iterator,bool> emplace(Types&&... args) {
            return insert(pair_type{std::forward<Types>(args)...});
        }

        /** 
         * @brief Clears the content of the tree.
         *
         * Since `reset()` resets @ref root to nullptr and then deletes the previously managed object,
         * the distructor of @ref Node is called on each @ref Node of the tree.
         */
        void clear() noexcept {
            this->root.reset();
        }

        /**
         * @brief Returns an iterator to the left-most node.
         *
         * It returns the smaller @ref Node according to @ref op; which, likely, is not the root node.
         */
        iterator begin() noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_BEGIN" << std::endl;
            #endif
            /* If root is nullptr we return a nullptr iterator */
            if (!root) return end();
            /* I descend in the tree as long as I have a left child */
            auto tmp = root.get();
            while (tmp->left) {
                tmp = tmp->left.get();
            }
            return iterator{tmp};
        }

        /**
         * @brief `const` version of @ref begin().
         * @see begin().
         */
        const_iterator begin() const noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_BEGIN" << std::endl;
            #endif
            /* If root is nullptr we return a nullptr const_iterator */
            if (!root) return end();
            /* I descend in the tree as long as I have a left child */
            auto tmp = root.get();
            while (tmp->left) {
                tmp = tmp->left.get();
            }
            return const_iterator{tmp};
        }
        // const_iterator begin() const noexcept {
        //     return const_cast<pair_type*> (this)->begin();
        // }

        /**
         * @brief `const` version of @ref begin(), to be used when a const_iterator is needed.
         * @see begin().
         */
        const_iterator cbegin() const noexcept {
            return begin();
        }

        /**
         * @brief Returns an iterator to one-past the last element (so a nullptr).
         */
        iterator end() noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_END" << std::endl;
            #endif
            return iterator{nullptr};
        }

        /**
         * @brief `const` version of @ref end().
         * @see end().
         */
        const_iterator end() const noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_END" << std::endl;
            #endif
            return const_iterator{nullptr};
        }

        /**
         * @brief `const` version of @ref end(), to be used when a const_iterator is needed.
         * @see end().
         */
        const_iterator cend() const noexcept {
            return end();
        }

        /**
         * @brief Finds a node and possibly change its value.
         * @param x The value to be found.
         *
         * Finds a given `Key`. If the `Key` is present, returns an @ref __iterator to the proper @ref Node, @ref end() otherwise.
         */
        iterator find(const key_type& x) {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_FIND" << std::endl;
            #endif
            auto tmp = root.get();
            while (tmp) {
                if (op(x,tmp->data.first)) {
                    tmp = tmp->left.get();
                } else if (op(tmp->data.first, x)) {
                    tmp = tmp->right.get();
                } else {
                    return iterator{tmp};
                }
            }
            // The tree is empty or the key doesn't exist, so I return the end of the tree (a nullptr)
            return end();
        }

        /**
         * @brief Finds if a node just exists.
         * @param x The value to be found.
         *
         * Finds a given `Key`. If the `Key` is present, returns an @ref __iterator to the proper @ref Node, @ref end() otherwise.
         */
        const_iterator find(const key_type& x) const {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_FIND" << std::endl;
            #endif
            return (const_iterator) find(x);
            // auto tmp = root.get();
            // while (tmp) {
            //     if (op(x,tmp->data.first)) {
            //         tmp = tmp->left.get();
            //     } else if (op(tmp->data.first, x)) {
            //         tmp = tmp->right.get();
            //     } else {
            //         return const_iterator{tmp};
            //     }
            // }
            // // The tree is empty or the key doesn't exist, so I return the end of the tree (a nullptr)
            // return end();
        }

        /**
         * @brief Balances the tree.
         */
        void balance() {
            std::vector<pair_type> v{};
            std::cout << "Vector:" << std::endl;
            for (const auto& it : *this) {
                v.push_back(it);
                std::cout << " " << it.first << std::endl;
            }
            this->clear();
            long long int mid{(static_cast<long long int> (v.size()))/2};
            std::cout << "Inserting " << v[mid].first << " in palce " << mid << std::endl;
            this->emplace(v[mid]);
            __balance(v, 0, mid-1);
            __balance(v, mid+1, v.size()-1);
            return;
        }

        /**
         * @brief Subscripting operator performing a copy.
         * @param x The `Key` to which access.
         *
         * Returns a reference to the value that is mapped to a `Key` equivalent to `x`,
         *  performing an insertion if such key does not already exist.
         */
        mapped_type& operator[](const key_type& x) {  // copy semantic
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: COPY_[]" << std::endl;
            #endif
            return insert(pair_type{x, mapped_type()}).first->second;
        }
        
        /**
         * @brief Subscripting operator performing a move.
         * @param x The `Key` to which access.
         * 
         * Returns a reference to the value that is mapped to a `Key` equivalent to `x`,
         *  performing an insertion if such key does not already exist.
         */
        mapped_type& operator[](key_type&& x) {  // move semantic
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: MOVE_[]" << std::endl;
            #endif
            return insert(pair_type{std::move(x), mapped_type()}).first->second;
        }

        /**
         * @brief Put-to operator the prints the tree.
         * @param os The stream on which the print has to be made.
         * @param x The tree to be printed.
         */
        friend std::ostream& operator<<(std::ostream& os, const bst& x) {
//            for (const auto& it : x) {
//               os << "[Key: " << std::setw(4) << it.first << ", Value: " << std::setw(4) << it.second << "]" << std::endl;
//            }
            for (auto it = x.cbegin(); it != x.cend(); ++it) {
//                os << "[" << it.currentNode << "]    "
//                   << "[Key: " << std::setw(4) << it->first << ", Value: " << std::setw(4) << it->second << "]" << std::endl;
                it.printNode(os, true);
            }

            return os;
        }

        /**
         * @brief Prints the tree in an easy way.
         * @param ss The string stream.
         */
        void printRawTree(std::stringstream& ss) {
            for (const auto& it : *this) {
               ss << it.first << " : " << it.second << std::endl;
            }
            return;
        }

        /**
         * @brief Removes the element (if one exists) with the `Key` equivalent to @ref x.
         * @param x The `Key` to be removed.
         */
        void erase(const key_type& x) noexcept {
            auto __nodeToDeleteIt = find(x);

            auto __nodeToDelete = __nodeToDeleteIt.currentNode;

            /* If I am deleting a nullptr. */
            if (!__nodeToDelete) return;

            /* If I'm deleting the root. */
            if (__nodeToDelete == root.get()) {
                if ((!__nodeToDelete->left) && (!__nodeToDelete->right)) {             // If node has no children
                    root.reset();
                } else if ( !(!__nodeToDelete->left) != !(!__nodeToDelete->right) ) {  // If node has one child
                    if (__nodeToDelete->left) {                                        // If the child is the left one
                        root.reset(__nodeToDelete->left.release());
                        __nodeToDelete->left->parent = nullptr;
                    } else {                                                           // If the child is the right one
                        root.reset(__nodeToDelete->right.release());
                        __nodeToDelete->right->parent = nullptr;
                    }
                } else {                                                               // If node has two children
                    /* We find the successor 'S' (which, for sure, has NO left child)
                     * and copy the successor 'S' in place of the deleted node 'D'.
                     * If the successor 'S' has a right child 'R', we copy 'R'
                     * in place of 'S' and remove 'R'.
                     */
                    auto __nodeSuccessor = (++__nodeToDeleteIt).currentNode;           // Find in-order successor
                    /* Create a new node with the data of 'S' and that points, to
                     * the left and to the right, to the left/right children of 'D',
                     * and that has nullptr as its parent.
                     */
                    //auto dummyNode = std::make_unique<node_type>(__nodeSuccessor->data, nullptr);
                    auto dummyNode = std::unique_ptr<node_type>(new node_type(__nodeSuccessor->data, nullptr));
                    dummyNode.get()->left .reset(__nodeToDelete->left .release());
                    dummyNode.get()->left .get()->parent = dummyNode.get();

                    /* If successor 'S' is right child of 'D', special case */
                    if (__nodeToDelete->right.get() == __nodeSuccessor) {
                        dummyNode.get()->right.reset(__nodeSuccessor->right.release());
                        dummyNode.get()->right.get()->parent = dummyNode.get();
                    } else {
                        dummyNode.get()->right.reset(__nodeToDelete->right.release());
                        dummyNode.get()->right.get()->parent = dummyNode.get();
                        if (__nodeSuccessor->right) {
                            /* Extra case: 'S' has 'R'. */
                            __nodeSuccessor->right->parent = __nodeSuccessor->parent;
                            __nodeSuccessor->parent->left.reset(__nodeSuccessor->right.release());
                        } else {
                            __nodeSuccessor->parent->left.reset();
                        }
                    }

                    root.reset(dummyNode.release());
                }

                return;
            }

            /* If I'm deleting any other node, that has in this case a parent. */
            auto __nodeParent = __nodeToDelete->parent;

            if ((!__nodeToDelete->left) && (!__nodeToDelete->right)) {  // If node has no children
                if (__nodeParent->left.get() == __nodeToDelete) {       // If node is left child of parent
                    __nodeParent->left.reset();
                } else {                                                // If node is right child of parent
                    __nodeParent->right.reset();
                }
            } else if ( !(!__nodeToDelete->left) != !(!__nodeToDelete->right) ) {  // If node has one child
                if (__nodeToDelete->left) {                              // If the child is the left one
                    __nodeToDelete->left.get()->parent = __nodeParent;
                    if (__nodeParent->left.get() == __nodeToDelete) {    // If node is left child of parent
                        __nodeParent->left.reset(__nodeToDelete->left.release());
                    } else {                                             // If node is right child of parent
                        __nodeParent->right.reset(__nodeToDelete->left.release());
                    }
                } else {                                                 // If the child is the right one
                    __nodeToDelete->right.get()->parent = __nodeParent;
                    if (__nodeParent->left.get() == __nodeToDelete) {    // If node is left child of parent
                        __nodeParent->left.reset(__nodeToDelete->right.release());
                    } else {                                             // If node is right child of parent
                        __nodeParent->right.reset(__nodeToDelete->right.release());
                    }
                }
            } else {                                                     // If node has two children
                /* We find the successor 'S' (which, for sure, has NO left child)
                 * and copy the successor 'S' in place of the deleted node 'D'.
                 * If the successor 'S' has a right child 'R', we copy 'R'
                 * in place of 'S' and remove 'R'.
                 */
                auto __nodeSuccessor = (++__nodeToDeleteIt).currentNode; // Find in-order successor

                /* Create a new node with the data of 'S' and that points, to
                 * the left and to the right, to the left/right children of 'D',
                 * and that has __nodeParent as its parent.
                 */
                //auto dummyNode = std::make_unique<node_type>(__nodeSuccessor->data, __nodeParent);
                auto dummyNode = std::unique_ptr<node_type>(new node_type(__nodeSuccessor->data, __nodeParent));
                dummyNode.get()->left .reset(__nodeToDelete->left .release());
                dummyNode.get()->left .get()->parent = dummyNode.get();

                /* If successor 'S' is right child of 'D', special case */
                if (__nodeToDelete->right.get() == __nodeSuccessor) {
                    dummyNode.get()->right.reset(__nodeSuccessor->right.release());
                    dummyNode.get()->right.get()->parent = dummyNode.get();
                    /* Let __nodeParent to point to dummyNode as well. */
                    if (__nodeParent->left.get() == __nodeToDelete) {
                        __nodeParent->left .reset(dummyNode.release());
                    } else {
                        __nodeParent->right.reset(dummyNode.release());
                    }
                } else {
                    dummyNode.get()->right.reset(__nodeToDelete->right.release());
                    dummyNode.get()->right.get()->parent = dummyNode.get();
                    /* Let __nodeParent to point to dummyNode as well. */
                    if (__nodeParent->left.get() == __nodeToDelete) {
                        __nodeParent->left .reset(dummyNode.release());
                    } else {
                        __nodeParent->right.reset(dummyNode.release());
                    }
                    if (__nodeSuccessor->right) {
                        /* Extra case: 'S' has 'R'. */
                        __nodeSuccessor->right->parent = __nodeSuccessor->parent;
                        __nodeSuccessor->parent->left.reset(__nodeSuccessor->right.release());
                    } else {
                        __nodeSuccessor->parent->left.reset();
                    }
                }

            }
            // The tree is empty or the key doesn't exist, so I return.
            return;
        }

    };

}

#endif // BST_HPP
