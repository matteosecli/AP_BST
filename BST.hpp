#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <memory>
#include <utility>
#include "Node.hpp"
#include "Iterator.hpp"

namespace APbst {

    template <typename KT, typename VT, typename cmp = std::less<KT>>
    class bst{
        cmp op; // operator of comparison
        std::unique_ptr<APutils::Node<std::pair<const KT, VT>>> root;
    public:
        bst() : op{}, root{nullptr} {}
        bst(cmp x) : op{x}, root{nullptr} {}

        using pair_type = std::pair<const KT, VT>;
        using node_type = APutils::Node<pair_type>;
        using iterator = APutils::__iterator<node_type, pair_type>;
        using const_iterator = APutils::__iterator<node_type, const pair_type>;

        std::pair<iterator, bool> insert(const pair_type& x) {
            auto tmp = root.get();
            while(tmp) {
                if(op(x.first,tmp->data.first)) {
                    if(tmp->left) {
                        tmp = tmp->left.get();
                    } else {
                        tmp->left.reset(new node_type{x, tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->left.get()}, true);
                    }
                } else if(op(tmp->data.first, x.first)) {
                    if (tmp->right) {
                        tmp = tmp->right.get();
                    } else {
                        tmp->right.reset(new node_type{x, tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->right.get()}, true);
                    }
                } else{
                    return std::make_pair<iterator, bool>(iterator{tmp}, false);
                }
            }
            root.reset(new node_type{x, nullptr});
            return std::make_pair<iterator, bool>(iterator{tmp}, true);
        }
        
        std::pair<iterator, bool> insert(pair_type&& x) {
            auto tmp = root.get();
            while(tmp) {
                if(op(x.first,tmp->data.first)) {
                    if(tmp->left) {
                        tmp = tmp->left.get();
                    } else {
                        tmp->left.reset(new node_type{std::move(x), tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->left.get()}, true);
                    }
                } else if(op(tmp->data.first, x.first)) {
                    if (tmp->right) {
                        tmp = tmp->right.get();
                    } else {
                        tmp->right.reset(new node_type{std::move(x), tmp});
                        return std::make_pair<iterator, bool>(iterator{tmp->right.get()}, true);
                    }
                } else{
                    return std::make_pair<iterator, bool>(iterator{tmp}, false);
                }
            }
            root.reset(new node_type{std::move(x), nullptr});
            return std::make_pair<iterator, bool>(iterator{tmp}, true);
        }

        //template<class... Types>
        //std::pair<iterator,bool> emplace(Types&&... args);

        //void clear();

        iterator begin() noexcept {
            /* If root is nullptr we return a nullptr iterator */
            if(!root) return end();
            /* I descend in the tree as long as I have a left child */
            auto tmp = root.get();
            while (tmp->left) {
                tmp = tmp->left.get();
            }
            return iterator{tmp};
        }

        // const_iterator begin() const noexcept {
        //     /* If root is nullptr we return a nullptr const_iterator */
        //     if(!root) return end();
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
