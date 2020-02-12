#ifndef BST_HPP
#define BST_HPP

#include <iostream>
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

        using pair_type = std::pair<const KT, VT>;
        using pair_type_nc = std::pair<KT, VT>;
        using node_type = APutils::Node<pair_type>;
        using iterator = APutils::__iterator<node_type, pair_type>;
        using const_iterator = APutils::__iterator<node_type, const pair_type>;

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
            root.reset(new node_type{x, nullptr});
            return std::make_pair<iterator, bool>(iterator{tmp}, true);
        }
        
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
        std::pair<iterator, bool> insert(const pair_type_nc& x) {
            std::cout << "CALL: COPY_INSERT_NC: APbst::bst::insert(const pair_type_nc& x)" << std::endl;
            return insert((const pair_type)x);
        }

        std::pair<iterator, bool> insert(pair_type_nc&& x) {
            std::cout << "CALL: MOVE_INSERT_NC: APbst::bst::insert(pair_type_nc&& x)" << std::endl;
            return insert((pair_type)x);
        }

        //template<class... Types>
        //std::pair<iterator,bool> emplace(Types&&... args);

        //void clear();

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

        // const_iterator begin() const noexcept {
        //     /* If root is nullptr we return a nullptr const_iterator */
        //     if (!root) return end();
        //     /* I descend in the tree as long as I have a left child */
        //     auto tmp = root.get();
        //     while (tmp->left) {
        //         tmp = tmp->left.get();
        //     }
        //     return const_iterator{tmp};
        // }

        const_iterator begin() const noexcept {
            return const_cast<pair_type*> (this)->begin();
        }

        const_iterator cbegin() const noexcept {
            return begin();
        }

        /* I return one after the last element, so a nullptr*/
        iterator end() noexcept {
            return iterator{nullptr};
        }

        const_iterator end() const noexcept {
            return const_iterator{nullptr};
        }

        const_iterator cend() const noexcept {
            return end();
        }

        /** @brief Finds a node and eventually change the value */
        //iterator find(const key_type& x);

        /** @brief Finds if a node just exists */
        //const_iterator find(const key_type& x) const;

        //void balance();

        //value_type& operator[](const key_type& x);  // copy semantic
        //value_type& operator[](key_type&& x);  // move semantic

        //insert({x, VT{}}) // default constructor of type VT

    //friend
        //std::ostream& operator<<(std::ostream& os, const bst& x);

        //void erase(const key_type& x);
    };

}

#endif // BST_HPP
