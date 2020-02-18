// 030-TreeTest.cpp

// main() provided in 000-CatchMain.cpp

#include "catch.hpp"

#include <memory>
#include <string>
#include <utility>

/* In order to print a vector via 'cout << v' */
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[";
    auto itStop = v.cend();
    for (auto it = v.cbegin(); it != itStop; ++it) {
        os << *it;
        if (it != itStop - 1) os << ", ";
    }
    os << "]";
    return os;
}

#include "Node.hpp"
#include "Iterator.hpp"
#include "BST.hpp"


TEST_CASE( "Inserting Nodes in a Tree", "[insert]" ) {

    APbst::bst<int, int, std::less<int>> tree{};

    SECTION( "Using `insert()`" ) {
    
        std::pair<int, int> APair(1,1);
        auto ins1 = tree.insert(APair);
        REQUIRE(ins1.second == true);

        std::pair<const int, int> BPair(2,2);
        auto ins2 = tree.insert(BPair);
        REQUIRE(ins2.second == true);
        
        auto ins3 = tree.insert(std::pair<int, int>(3,3));  /* NOTE: it has NOT a const Key! */
        REQUIRE(ins3.second == true);
        
        auto ins8 = tree.insert(std::pair<const int, int>(8,8));
        REQUIRE(ins8.second == true);
        
        auto ins8_2 = tree.insert(std::pair<const int, int>(8,8));
        REQUIRE(ins8_2.second == false);
        
        auto ins4 = tree.insert({4, 4});
        REQUIRE(ins4.second == true);

    }

    SECTION( "Using `emplace()`") {

        auto empl7 = tree.emplace(7, 7);
        REQUIRE(empl7.second == true);

        auto empl11 = tree.emplace(11, 11);
        REQUIRE(empl11.second == true);

        auto empl11_2 = tree.emplace(11, 11);
        REQUIRE(empl11_2.second == false);

    }

    SECTION("Tree of <string, vector>") {

        APbst::bst<std::string, std::vector<double>> playerStats{};
        //playerStats.insert(std::pair<const std::string,std::vector<double>>("Bruce Lee",std::vector<double>{170,70,47}));
        //playerStats.insert({"Bruce Lee",std::vector<double>{170,70,47}});
        playerStats.emplace("Bruce Lee",std::vector<double>{170,70,47});
        REQUIRE(playerStats.find("Bruce Lee") != playerStats.end());
        REQUIRE(playerStats["Bruce Lee"][0] == 170);
        REQUIRE(playerStats["Bruce Lee"][1] == 70);
        REQUIRE(playerStats["Bruce Lee"][2] == 47);

        playerStats.emplace("Michael Jackson",std::vector<double>{210,90,50});
        REQUIRE(playerStats.find("Michael Jackson") != playerStats.end());
        REQUIRE(playerStats["Michael Jackson"][0] == 210);
        REQUIRE(playerStats["Michael Jackson"][1] == 90);
        REQUIRE(playerStats["Michael Jackson"][2] == 50);

        playerStats.emplace("Arnold Schwarznegger",std::vector<double>{190,80,60});
        REQUIRE(playerStats.find("Arnold Schwarznegger") != playerStats.end());
        REQUIRE(playerStats["Arnold Schwarznegger"][0] == 190);
        REQUIRE(playerStats["Arnold Schwarznegger"][1] == 80);
        REQUIRE(playerStats["Arnold Schwarznegger"][2] == 60);

        std::cout << playerStats << std::endl;

    }

}


TEST_CASE( "Iterating on the Nodes in a for loop", "[forloop]" ) {

    APbst::bst<int, int> tree{};
    tree.insert(std::pair<const int, int>(8,8));
    tree.insert(std::pair<const int, int>(3,3));
    tree.insert(std::pair<const int, int>(10,10));
    tree.insert(std::pair<const int, int>(1,1));
    tree.insert(std::pair<const int, int>(6,6));
    tree.insert(std::pair<const int, int>(14,14));
    tree.insert(std::pair<const int, int>(4,4));
    tree.insert(std::pair<const int, int>(7,7));
    tree.insert(std::pair<const int, int>(13,13));

    SECTION("Using a `for` with begin() and end()") {

        auto stop = tree.end();
        for (auto it = tree.begin(); it != stop; ++it) {
            std::cout << "[" << &(*it) << "]    ";
            std::cout << "Key: " << it->first << std::endl;
        }

        std::cout << std::endl;

    }

    SECTION("Using a `for` with cbegin() and cend()") {

        auto stop = tree.cend();
        for (APbst::bst<int,int>::const_iterator it = tree.cbegin(); it != stop; ++it) {
        std::cout << "[" << &(*it) << "]    ";
        std::cout << "Key: " << it->first << std::endl;
        }

        std::cout << std::endl;

    }
    
    SECTION("Using a `for` with const auto&") {

        for (const auto& it : tree) {
            std::cout << "[" << &(it) << "]    ";
            std::cout << "Key: " << it.first << std::endl;
        }

        std::cout << std::endl;

    }

}


TEST_CASE("Subscripting operator", "[subscrpting_op]") {

    APbst::bst<int, int> tree{};
    tree.insert(std::pair<const int, int>(8,8));
    tree.insert(std::pair<const int, int>(3,3));
    tree.insert(std::pair<const int, int>(10,10));
    tree.insert(std::pair<const int, int>(1,1));
    tree.insert(std::pair<const int, int>(6,6));
    tree.insert(std::pair<const int, int>(14,14));
    tree.insert(std::pair<const int, int>(4,4));
    tree.insert(std::pair<const int, int>(7,7));
    tree.insert(std::pair<const int, int>(13,13));

    SECTION("[] move assignment") {

        tree[1] = 11;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (1, 11) with the pair move constructor
        REQUIRE(tree[1] == 11);

        tree[10] = 10;  // insert a new value
        REQUIRE(tree[10] == 10);

        tree[9] = 9;  // insert a new value
        REQUIRE(tree[9] == 9);

    }
    
    SECTION("[] copy assignment") {

        const int i = 2;
        tree[i] = 22;  // update an existing value: calls the MOVE_INSERT since it creates a new pair using (i, 22) with the pair copy constructor
        REQUIRE(tree[2] == 22);

        const int j = 12;
        tree[j] = 12;  // insert a new value
        REQUIRE(tree[12] == 12);
    
        tree[4] = tree[5];
        REQUIRE(tree[4] == tree[5]);

    }

}


TEST_CASE("Finding Nodes in a Tree", "[find]") {

    APbst::bst<int, int> tree{};
    tree.insert(std::pair<const int, int>(8,8));
    tree.insert(std::pair<const int, int>(3,3));
    tree.insert(std::pair<const int, int>(10,10));
    tree.insert(std::pair<const int, int>(1,1));
    tree.insert(std::pair<const int, int>(6,6));
    tree.insert(std::pair<const int, int>(14,14));
    tree.insert(std::pair<const int, int>(4,4));
    tree.insert(std::pair<const int, int>(7,7));
    tree.insert(std::pair<const int, int>(13,13));
    tree.insert(std::pair<const int, int>(5,5));

    SECTION("Print using the put-to operator `<<`") {

        std::cout << tree << std::endl;

    }

    SECTION("Find") {

        /* Show that we can recast the tree as a const tree and then store the iterator in a const_iterator type. */
        APbst::bst<int,int>::const_iterator it_1 = ((const APbst::bst<int,int>)tree).find(5);
        //it_1->second = 78;  // NOT allowed
        REQUIRE(it_1 != tree.cend());

        auto it_2 = tree.find(6);
        it_2->second = 78;  // ALLOWED
        REQUIRE(it_2 != tree.end());

        auto it_3 = tree.find(55);
        REQUIRE(it_3 == tree.end());

        tree.find(5)->second = 78;
        std::cout << tree[5] << std::endl;

        const APbst::bst<int,int> const_tree{tree};
        auto it_const_1 = const_tree.find(1);
        REQUIRE(it_const_1 != const_tree.end());

    }

}


TEST_CASE("Erase", "[erase]") {

    APbst::bst<int, int> treeAP{};
    treeAP.emplace(8,8);
    treeAP.emplace(3,3);
    treeAP.emplace(10,10);
    treeAP.emplace(1,1);
    treeAP.emplace(4,4);
    treeAP.emplace(7,7);
    treeAP.emplace(14,14);
    treeAP.emplace(13,13);

    SECTION("Erase some Nodes") {

        treeAP.emplace(6,6);
        std::cout << "Before erasing: " << std::endl;
        std::cout << treeAP << std::endl;
        treeAP.erase(4);
        std::cout << "After erasing 4 (is leaf): " << std::endl;
        std::cout << treeAP << std::endl;

        std::stringstream ssAP{};
        treeAP.printRawTree(ssAP);
        std::stringstream ssAP_exp{};
        ssAP_exp << "1 : 1\n3 : 3\n6 : 6\n7 : 7\n8 : 8\n10 : 10\n13 : 13\n14 : 14\n";
    //    std::cout << ssAP.str() << std::endl;
    //    std::cout << ssAP_exp.str() << std::endl;
        REQUIRE( ssAP.str() == ssAP_exp.str() );

    }

    SECTION("Erase a node with a child") {
        treeAP.erase(10);
        std::cout << "After erasing 10 (has 14 as right child, which has 13 as left child): " << std::endl;
        std::cout << treeAP << std::endl;

        std::stringstream ssAP{};
        treeAP.printRawTree(ssAP);
        std::stringstream ssAP_exp{};
        ssAP_exp << "1 : 1\n3 : 3\n4 : 4\n7 : 7\n8 : 8\n13 : 13\n14 : 14\n";
        REQUIRE( ssAP.str() == ssAP_exp.str() );

    }

    SECTION("Erase a node with a full subtree") {

        treeAP.emplace(6,6);
        treeAP.emplace(5,5);
        treeAP.erase(3);
        std::cout << "After erasing 3 (has a full subtree): " << std::endl;
        std::cout << treeAP << std::endl;

        std::stringstream ssAP{};
        treeAP.printRawTree(ssAP);
        std::stringstream ssAP_exp{};
        ssAP_exp << "1 : 1\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n8 : 8\n10 : 10\n13 : 13\n14 : 14\n";
        REQUIRE( ssAP.str() == ssAP_exp.str() );

    }

    SECTION("Erase root") {

        treeAP.emplace(6,6);
        treeAP.emplace(5,5);
        treeAP.emplace(9,9);
        treeAP.erase(8);
        std::cout << "After erasing 8 (the root): " << std::endl;
        std::cout << treeAP << std::endl;

        std::stringstream ssAP{};
        treeAP.printRawTree(ssAP);
        std::stringstream ssAP_exp{};
        ssAP_exp << "1 : 1\n3 : 3\n4 : 4\n5 : 5\n6 : 6\n7 : 7\n9 : 9\n10 : 10\n13 : 13\n14 : 14\n";
        REQUIRE( ssAP.str() == ssAP_exp.str() );

    }

}


TEST_CASE("Testing `balance()`, Copy Assignment & `clear()`", "[funcs]") {

    APbst::bst<int, int> tree{};
    tree.emplace(8,8);
    tree.emplace(3,3);
    tree.emplace(10,10);
    tree.emplace(1,1);
    tree.emplace(4,4);
    tree.emplace(7,7);
    tree.emplace(14,14);
    tree.emplace(13,13);

    SECTION("Balance the tree") {

        tree.balance();
        std::cout << tree << std::endl;

    }

    SECTION("Copy the tree") {

        APbst::bst<int, int> tree2{};
        tree2 = tree;
        std::cout << tree2 << std::endl;

        APbst::bst<int, int> tree3{tree};
        std::cout << tree3 << std::endl;

    }

    SECTION("Clear the tree") {

        tree.clear();
        
        std::stringstream ss{};
        tree.printRawTree(ss);
        std::stringstream ss_exp{};
        ss_exp << "";
        REQUIRE( ss.str() == ss_exp.str() );

    }

}
