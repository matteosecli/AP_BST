#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <iomanip>
#include <memory>
#include <utility>
#include "Node.hpp"
#include "Iterator.hpp"


/** 
 * @brief Principal namespace
 * 
 * Namespace of the library bst
 */
namespace APbst {

    template <typename KT, typename VT, typename cmp = std::less<KT>>
    class bst{
        /** @brief Operator of comparison. */
        cmp op;
        std::unique_ptr<APutils::Node<std::pair<const KT, VT>>> root;
    public:
        bst() : op{}, root{nullptr} {}
        bst(cmp x) : op{x}, root{nullptr} {}

        /**
         * @brief Copy assignment for @ref bst.
         *
         * It performs a deep-copy of the tree.
         */
        bst& operator=(const bst& t) {}

        /**
         * @brief Move assignment for @ref bst.
         */
        bst& operator=(bst&& t) noexcept = default;

        using key_type = KT;
        using mapped_type = VT;
        using pair_type = typename std::pair<const KT, VT>;
        using pair_type_nc = typename std::pair<KT, VT>;
        using node_type = typename APutils::Node<pair_type>;
        using iterator = typename APutils::__iterator<node_type,  pair_type>;
        using const_iterator = typename APutils::__iterator<node_type, const pair_type>;

        //std::pair<iterator, bool> insert(const pair_type_nc& x) {
        std::pair<iterator, bool> insert(const pair_type& x) {
            std::cout << "CALL: COPY_INSERT: APbst::bst::insert(const pair_type& x)" << std::endl;
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
        
        //std::pair<iterator, bool> insert(pair_type_nc&& x) {
        std::pair<iterator, bool> insert(pair_type&& x) {
            std::cout << "CALL: MOVE_INSERT: APbst::bst::insert(pair_type&& x)" << std::endl;
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

        /**
         * @brief insert
         * @param x @ref insert(const pair_type& x)
         * @see insert(const pair_type& x)
         * @return
         *
         * This function redirects to @ref insert(const pair_type& x).
         * It's provided in order to address use cases in which the user uses e.g.
         * `std::pair<int, int>` instead of `std::pair<const int, int>`.
         */
        // std::pair<iterator, bool> insert(const pair_type_nc& x) {
        //     std::cout << "CALL: COPY_INSERT_NC: APbst::bst::insert(const pair_type_nc& x)" << std::endl;
        //     return insert((const pair_type)x);
        // }

        // std::pair<iterator, bool> insert(pair_type_nc&& x) {
        //     std::cout << "CALL: MOVE_INSERT_NC: APbst::bst::insert(pair_type_nc&& x)" << std::endl;
        //     return insert((pair_type)x);
        // }

        // variadic templates
        template<class... Types>
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
         * @brief Return an iterator to the left-most node.
         *
         * It returns the smaller @ref Node according to @ref op; which, likely, is not the root node.
         */
        iterator begin() noexcept {
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

        const_iterator cbegin() const noexcept {
            return begin();
        }

        /* I return one after the last element, so a nullptr*/
        iterator end() noexcept {
            std::cout << "NONCONST_END" << std::endl;
            return iterator{nullptr};
        }

        const_iterator end() const noexcept {
            std::cout << "CONST_END" << std::endl;
            return const_iterator{nullptr};
        }

        const_iterator cend() const noexcept {
            return end();
        }

        /**
         * @brief Finds a node and possibly change its value.
         * @param x The value to be found.
         *
         * Finds a given key. If the key is present, returns an iterator to the proper node, @ref end() otherwise.
         */
        iterator find(const key_type& x) {
            std::cout << "CALL: NONCONST_FIND" << std::endl;
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
         * @brief Finds if a nstd::cout << "CALL: NONCONST_FIND" << std::endl;ode just exists.
         * @param x The value to be found.
         *
         * Finds a given key. If the key is present, returns an iterator to the proper node, @ref end() otherwise.
         */
        const_iterator find(const key_type& x) const {
            std::cout << "CALL: CONST_FIND" << std::endl;
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

        //void balance();

        /**
         * @brief Returns a reference to the value that is mapped to a key equivalent to `x`,
         *  performing an insertion if such key does not already exist.
         */
        mapped_type& operator[](const key_type& x) {  // copy semantic
            std::cout << "COPY_[]" << std::endl;
            return insert(pair_type{x, mapped_type()}).first->second;
        }
        
        /**
         * @brief Returns a reference to the value that is mapped to a key equivalent to `x`,
         *  performing an insertion if such key does not already exist.
         */
        mapped_type& operator[](key_type&& x) {  // move semantic
            std::cout << "MOVE_[]" << std::endl;
            return insert(pair_type{std::move(x), mapped_type()}).first->second;
        }

        /** @brief To print the tree in an easy way. */
        friend std::ostream& operator<<(std::ostream& os, const bst& x) {
            for (const auto& it : x) {
               os << "[Key: " << std::setw(4) << it.first << ", Value: " << std::setw(4) << it.second << "]" << std::endl;
            }
            // for (auto it = x.cbegin(); it != x.cend(); ++it) {
            //     os << "[Key: " << std::setw(4) << it->first << ", Value: " << std::setw(4) << it->second << "]" << std::endl;
            // }

            return os;
        }

        void erase(const key_type& x) {
            
        }
    };

}

#endif // BST_HPP
