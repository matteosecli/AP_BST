#ifndef BST_HPP
#define BST_HPP


/** @mainpage
 *
 * @section sec_description Description
 * A simple Binary Search Tree implementation for the Advanced Programming 2019-2020 course @ SISSA.
 *
 * @section sec_compile How to compile
 * @subsection sec_compilation Compilation
 * We include a standard `Makefile` for convenience, so you can run the usual
 * `make` commands; out-of-source build are not supported.
 *
 * It is also possible to generate the `Makefile` via `qmake` by opening a terminal
 * in the source code folder and running
 *
 *     mkdir build && cd build    # If you'd like to, not compulsory
 *     qmake ..
 *     make
 *
 * In both cases, if everything goes as it should, you now have an executable
 * `AP_BST` in your build folder `$BLD`. You can run it via
 *
 *     ./AP_BST
 *
 * __Notes:__
 *
 * - You can print some debug info by using one of the following:
 *   - `make EXTRA_CXXFLAGS=-D__DEBUG_AP_BST`
 *   - `qmake CONFIG+=debug && make`
 * - You might need to tweak a little bit the `qmake` step, depending on your system configuration. Examples:
 *   - On Linux. Use `qmake -spec linux-g++` if you want to compile with GNU G++, while use `qmake -spec linux-icc` if you want to use Intel's IC(P)C.
 *   - On MacOS. Use `qmake -spec macx-g++ QMAKE_CXX=/path/to/g++ QMAKE_LINK=/path/to/g++` if you want to compile with GNU G++, while use `qmake -spec macx-icc` if you want to use Intel's IC(P)C. Notice that, if you want to compile with GNU G++, you also have to manually specify the two extra variables `QMAKE_CXX` and `QMAKE_LINK`; while in the other cases it's not necessary, in this case it is because otherwise MacOS will pick Apple's LLVM G++ by default (which is basically Clang).
 *   - As said before, you can manually specify `QMAKE_CXX` and `QMAKE_LINK` (e.g. if you want to select a version of G++ different from the default one or in a non-standard location). You can also do this step in the `make` step, but you have to specify the extra variables without the "QMAKE" (e.g. `make CXX=/path/to/g++ LINK=/path/to/g++`).
 *
 * @subsection sec_builddoc Build the documentation
 * You can build the documentation by running
 *
 *     make doc
 *
 * The documentation is built into the folder `$BLD/doc/_build/`, where `$BLD` is
 * your build folder.
 *
 * @subsection sec_runtests Build and running the unit tests
 * You can build the unit tests (written in Catch2) via
 *
 *     make test
 *
 * in the `$SRC` directory, where `$SRC` is the directory that contains `main.cpp`,
 * or via
 *
 *     qmake && make
 *
 * in the `$SRC/test` directory. A binary `test` is generated in the `$SRC/test` directory,
 * and you can run it with
 *
 *     ./test
 *
 * Refer to `./test --help` for a list of all the possible options for the test
 * executable. E.g. the `-s` option lists even the successful tests.
 *
 * @section sec_howtorun How to run the code
 * @subsection sec_running Running
 * The sample program, that shows how to use the library, can be run in the following way:
 *
 *     ./AP_BST
 *
 * The tests, if compiled, can be run via
 *
 *     cd test
 *     ./test
 *
 * @section sec_author Authors
 * - Angela Carraro <[angela_carraro@hotmail.it](email:angela_carraro@hotmail.it)>
 * - Matteo Seclì <[secli.matteo@gmail.com](email:secli.matteo@gmail.com)>
 *
 */


#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>
#include "Iterator.hpp"
#include "Node.hpp"


/** 
 * @brief Namespace for the Binary Search Tree
 * 
 * This namespace hosts the class @ref bst and possibly, in the future, related
 * objects and functions.
 */
namespace APbst {

    /**
     * @brief Class that implements a Binary Search Tree.
     *
     * This class takes two compulsory template parameters, `KT` and `VT`,
     * and an optional one (`cmp`). The compulsory ones are, respectively,
     * the `Key` type and the `Value` type of the Nodes of the tree, while
     * `cmp` is the "less than" operator for the particular `KT` in use.
     *
     * Example:
     *
     *     APbst::bst<std::string,int> personAge{};
     *
     * As this is an exam project, some internal members are documented as well.
     *
     * @see op
     */
    template <typename KT, typename VT, typename cmp = std::less<KT>>
    class bst{
        /** @brief Operator of comparison ("less than") for the `Key` type. */
        cmp op;
        /** @brief The root Node of the tree. */
        std::unique_ptr<APutils::Node<std::pair<const KT, VT>>> root;

        /**
         * @brief Internal helper function for @ref begin().
         *
         * This function finds the leftmost Node of the tree and it returns a
         * raw pointer to the leftmost Node itself.
         *
         * @see begin()
         * @see cbegin()
         */
        APutils::Node<std::pair<const KT, VT>>* __begin() const {
            /* If root is nullptr we return a nullptr */
            if (!root) return nullptr;
            /* I descend in the tree as long as I have a left child */
            auto tmp = root.get();
            while (tmp->left) {
                tmp = tmp->left.get();
            }
            return tmp;
        }

        /**
         * @brief Internal helper function for @ref find().
         *
         * This function finds the Node with key @ref x and it returns a
         * raw pointer to the found Node.
         *
         * @see find()
         */
        APutils::Node<std::pair<const KT, VT>>* __find(const KT& x) const {
            auto tmp = root.get();
            while (tmp) {
                if (op(x,tmp->data.first)) {
                    tmp = tmp->left.get();
                } else if (op(tmp->data.first, x)) {
                    tmp = tmp->right.get();
                } else {
                    return tmp;
                }
            }
            // The tree is empty or the key doesn't exist, so I return the end of the tree (a nullptr)
            return nullptr;
        }

        /**
         * @brief Internal helper function for the copy operations.
         *
         * @param t The tree to be copied.
         * @param a The Node to be copied.
         *
         * This function recursively copies a tree by performing a deep copy of
         * all of its Nodes.
         *
         * @see bst()
         * @see bst::operator=
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

        /**
         * @brief Internal helper function for @ref balance().
         *
         * @param v A vector that contains all the tree pairs.
         * @param a The index of the first vector element to insert in the tree.
         * @param b The index of the last vector element to insert in the tree.
         *
         * This function emplaces all the Node pairs contained in @ref v in a
         * balanced fashion, by starting with the middle element and then recursively
         * calling itself.
         *
         * @see balance()
         */
        void __balance(std::vector<std::pair<const KT, VT>>& v, long long int a, long long int b) {
            if (b < a) {
                return;
            }
            long long int mid{(b + a)/2};
            #ifdef __DEBUG_AP_BST
            std::cout << "Inserting " << v[mid].first << " in place " << mid << std::endl;
            #endif
            this->emplace(v[mid]);
            __balance(v, a, mid-1);
            __balance(v, mid+1, b);
            return;
        }

      public:
        /**
         * @brief The `Key` type of the Node of the tree.
         */
        using key_type = KT;
        /**
         * @brief The `Value` type of the Node of the tree.
         */
        using mapped_type = VT;
        /**
         * @brief The `Pair` type of the tree, i.e. `std::pair<const Key,Value>`.
         */
        using pair_type = typename std::pair<const KT, VT>;
        /**
         * @brief The `Node` type of the tree, i.e. `Node<Pair>`.
         */
        using node_type = typename APutils::Node<pair_type>;
        /**
         * @brief The non-const iterator type.
         */
        using iterator = typename APutils::__iterator<node_type,  pair_type>;
        /**
         * @brief The const iterator type.
         */
        using const_iterator = typename APutils::__iterator<node_type, const pair_type>;

        /**
         * @brief Empty constructor.
         *
         * It creates an empty tree with no Nodes and with the default "less than"
         * operation.
         */
        bst() noexcept : op{}, root{nullptr} {}

        /**
         * @brief Empty constructor with an explicit comparison ("less than") operation.
         *
         * @param x The comparison ("less than") operator.
         *
         * It creates an empty tree with no Nodes and with the specified "less than"
         * operation.
         */
        explicit bst(cmp x) noexcept : op{x}, root{nullptr} {}

        /**
         * @brief Copy constructor.
         *
         * @param t The tree to be copied.
         *
         * It creates a new tree by performing a deep copy of the tree @ref t.
         *
         * @see bst::operator=
         */
        explicit bst(const bst& t) : op{t.op}, root{std::unique_ptr<node_type>(new node_type(t.root.get()->data, nullptr))} {
            if (t.root.get()->left) {
                __copy(t, t.root.get()->left);
            }
            if (t.root.get()->right) {
                __copy(t, t.root.get()->right);
            }
        }

        /**
         * @brief Move constructor.
         *
         * @param t The tree to be moved.
         *
         * It creates a new tree by moving the tree @ref t.
         *
         * @see bst::operator=
         */
        bst(bst&& t) noexcept = default;

        /**
         * @brief Copy assignment for @ref bst.
         *
         * @param t The tree to be copied.
         *
         * It creates a new tree by performing a deep copy of the tree @ref t.
         *
         * @see bst()
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
         *
         * @param t The tree to be moved.
         *
         * It creates a new tree by moving the tree @ref t.
         *
         * @see bst()
         */
        bst& operator=(bst&& t) noexcept = default;

        /**
         * @brief Inserts a @ref APutils::Node by copying it in the tree, if not already present.
         *
         * @param x The values of the `Key` and the `Value` to be put in the @ref APutils::Node.
         *
         * This function inserts a new @ref APutils::Node in the current tree, and it returns
         *  a `pair` of an @ref __iterator (pointing to the @ref APutils::Node) and a `bool`.
         * The `bool` is `true` if a new @ref APutils::Node has been allocated,
         * `false` otherwise (i.e., the `Key` was already present in the tree).
         *
         * @see emplace()
         */
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
         * @brief Inserts a @ref APutils::Node by moving it in the tree, if not already present.
         *
         * @param x The values of the `Key` and the `Value` to be put in the @ref APutils::Node.
         *
         * This function inserts a new @ref APutils::Node in the current tree, and it returns
         *  a `pair` of an @ref __iterator (pointing to the @ref APutils::Node) and a `bool`.
         * The `bool` is `true` if a new @ref APutils::Node has been allocated,
         * `false` otherwise (i.e., the `Key` was already present in the tree).
         *
         * @see emplace()
         */
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

        /**
         * @brief Inserts a @ref APutils::Node constructed in-place.
         *
         * @param args The arguments for the `Pair` constructor.
         *
         * Inserts a new @ref APutils::Node into the tree by constructing it in-place.
         *
         * This function forwards the arguments @ref args to the constructor
         * of `Pair`, and if the tree does not contain an element with the same
         * `Key` it inserts the `Pair` itself.
         *
         * @see insert()
         */
        template<class... Types>  // variadic templates
        std::pair<iterator,bool> emplace(Types&&... args) {
            return insert(pair_type{std::forward<Types>(args)...});
        }

        /** 
         * @brief Clears the content of the tree.
         *
         * Since `reset()` resets @ref root to nullptr and then deletes the previously managed object,
         * the distructor of @ref APutils::Node is called on each @ref APutils::Node of the tree.
         */
        void clear() noexcept {
            this->root.reset();
        }

        /**
         * @brief Returns an iterator to the left-most @ref APutils::Node.
         *
         * This function finds the leftmost Node of the tree and it returns an
         * iterator to the leftmost Node itself.
         *
         * @see cbegin()
         * @see end()
         */
        iterator begin() noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_BEGIN" << std::endl;
            #endif
            return iterator{__begin()};
        }

        /**
         * @brief Returns a const_iterator to the left-most @ref APutils::Node.
         *
         * This function finds the leftmost Node of the tree and it returns a
         * const_iterator to the leftmost Node itself.
         *
         * @see cbegin()
         * @see end()
         */
        const_iterator begin() const noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_BEGIN" << std::endl;
            #endif
            return const_iterator{__begin()};
        }

        /**
         * @brief The `const` version of @ref begin(), to be used when a const_iterator is needed.
         *
         * @see begin()
         * @see cend()
         */
        const_iterator cbegin() const noexcept {
            return const_iterator{__begin()};
        }

        /**
         * @brief Returns an iterator to one-past the last element.
         *
         * It returns an interator to `nullptr`.
         *
         * @see cend()
         * @see begin()
         */
        iterator end() noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_END" << std::endl;
            #endif
            return iterator{nullptr};
        }

        /**
         * @brief Returns a const_iterator to one-past the last element.
         *
         * It returns a const_interator to `nullptr`.
         *
         * @see cend()
         * @see begin()
         */
        const_iterator end() const noexcept {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_END" << std::endl;
            #endif
            return const_iterator{nullptr};
        }

        /**
         * @brief The `const` version of @ref end(), to be used when a const_iterator is needed.
         *
         * @see end()
         * @see cbegin()
         */
        const_iterator cend() const noexcept {
            return const_iterator{nullptr};
        }

        /**
         * @brief Finds a @ref APutils::Node and possibly change its value.
         *
         * @param x The `Key` to look for.
         *
         * Finds a given `Key`. If the `Key` is present, returns an
         * @ref APutils::__iterator to the proper @ref APutils::Node, @ref end() otherwise.
         */
        iterator find(const key_type& x) {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: NONCONST_FIND" << std::endl;
            #endif
            return iterator{__find(x)};
        }

        /**
         * @brief Finds if a node just exists.
         *
         * @param x The `Key` to look for.
         *
         * Finds a given `Key`. If the `Key` is present, returns an
         * @ref APutils::__iterator to the proper @ref APutils::Node, @ref end() otherwise.
         */
        const_iterator find(const key_type& x) const {
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: CONST_FIND" << std::endl;
            #endif
            return const_iterator{__find(x)};
        }

        /**
         * @brief Balances the tree.
         *
         * Reshuffles the nodes in the tree by trying to minimize its
         * [depth](https://en.wikipedia.org/wiki/Binary_tree).
         */
        void balance() {
            std::vector<pair_type> v{};
            for (const auto& it : *this) {
                v.push_back(it);
            }
            this->clear();
            long long int mid{(static_cast<long long int> (v.size()))/2};
            #ifdef __DEBUG_AP_BST
            std::cout << "Inserting " << v[mid].first << " in palce " << mid << std::endl;
            #endif
            this->emplace(v[mid]);
            __balance(v, 0, mid-1);
            __balance(v, mid+1, v.size()-1);
            return;
        }

        /**
         * @brief Subscripting operator performing a copy.
         *
         * @param x The `Key` to look for.
         *
         * Returns a reference to the value corresponding to the `Key` @ref x,
         * performing an insertion if such `Key` does not already exist.
         */
        mapped_type& operator[](const key_type& x) {  // copy semantic
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: COPY_[]" << std::endl;
            #endif
            return insert(pair_type{x, mapped_type()}).first->second;
        }
        
        /**
         * @brief Subscripting operator performing a move.
         *
         * @param x The `Key` to look for.
         * 
         * Returns a reference to the value corresponding to the `Key` @ref x,
         * performing an insertion if such `Key` does not already exist.
         */
        mapped_type& operator[](key_type&& x) {  // move semantic
            #ifdef __DEBUG_AP_BST
            std::cout << "CALL: MOVE_[]" << std::endl;
            #endif
            return insert(pair_type{std::move(x), mapped_type()}).first->second;
        }

        /**
         * @brief Put-to operator that prints the tree.
         *
         * @param os The stream on which the print has to be made.
         * @param x The tree to be printed.
         *
         * This function assumes that the `Key` and the `Value` have a corresponding
         * overloaded put-to operator; if this is not the case, it is a user's task
         * to implement it **before** including @ref BST.hpp.
         *
         * E.g., in order to print a `std::vector` `Value`, one could write
         *
         *     template <typename T>
         *     std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
         *         os << "[";
         *         auto itStop = v.cend();
         *         for (auto it = v.cbegin(); it != itStop; ++it) {
         *             os << *it;
         *             if (it != itStop - 1) os << ", ";
         *         }
         *         os << "]";
         *         return os;
         *     }
         *
         */
        friend std::ostream& operator<<(std::ostream& os, const bst& x) {
            //for (const auto& it : x) {
            //   os << "[Key: " << std::setw(4) << it.first << ", Value: " << std::setw(4) << it.second << "]" << std::endl;
            //}
            auto itStop = x.cend();
            for (auto it = x.cbegin(); it != itStop; ++it) {
            //    os << "[" << it.currentNode << "]    "
            //       << "[Key: " << std::setw(4) << it->first << ", Value: " << std::setw(4) << it->second << "]" << std::endl;
                it.printNode(os, true);
            }
            return os;
        }

        /**
         * @brief Prints the tree in an easy way.
         *
         * @param ss The string stream.
         *
         * This function is mainly used for tests only, as it prints the tree
         * in a format that is easier to check in automatic tests.
         *
         * E.g., if a tree contains `Key:Value` pairs `1:1`, `2:2`, `3:3`, etc.,
         * `tree.printRawTree(ss)` will fill `ss` with a string that looks like
         *
         *     1 : 1
         *     2 : 2
         *     3 : 3
         *     ...
         *
         */
        void printRawTree(std::stringstream& ss) {
            for (const auto& it : *this) {
               ss << it.first << " : " << it.second << std::endl;
            }
            return;
        }

        /**
         * @brief Removes the element (if it exists) with `Key` @ref x.
         *
         * @param x The `Key` to be removed.
         *
         * If the `Key` does not exist in the tree, this function does nothing.
         */
        void erase(const key_type& x) {
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
