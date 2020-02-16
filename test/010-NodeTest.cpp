// 010-NodeTest.cpp

// main() provided in 000-CatchMain.cpp

#include "catch.hpp"

#include <memory>
#include <string>
#include <utility>
#include "Node.hpp"


TEST_CASE( "Create Nodes", "[node_create]" ) {


    SECTION( "Empty Node with default constructor via `Node c`" ) {

        APutils::Node<std::pair<int, int>> c;

        REQUIRE( c.data.first  == 0 );
        REQUIRE( c.data.second == 0 );
        REQUIRE( c.parent == nullptr );
        REQUIRE( c.left .get() == nullptr );
        REQUIRE( c.right.get() == nullptr );

    }

    SECTION( "Empty Node with default constructor via `Node c{}`" ) {

        APutils::Node<std::pair<int, int>> c{};

        REQUIRE( c.data.first  == 0 );
        REQUIRE( c.data.second == 0 );
        REQUIRE( c.parent == nullptr );
        REQUIRE( c.left .get() == nullptr );
        REQUIRE( c.right.get() == nullptr );

    }

}


TEST_CASE( "Insert Pairs into Nodes", "[node_insert]" ) {


    SECTION( "Node with `int` Data" ) {

        std::pair<int, int> testPair(3,4);
        APutils::Node<std::pair<int,int>> testNode(testPair, nullptr);

        REQUIRE( testNode.data.first  == 3 );
        REQUIRE( testNode.data.second == 4 );
        REQUIRE( testNode.parent == nullptr );
        REQUIRE( testNode.left .get() == nullptr );
        REQUIRE( testNode.right.get() == nullptr );

    }

    SECTION( "Node with `string : int` Data" ) {

        std::pair<std::string, int> testPair("Angela",24);
        APutils::Node<std::pair<std::string,int>> testNode(testPair, nullptr);

        REQUIRE( testNode.data.first  == "Angela" );
        REQUIRE( testNode.data.second == 24 );
        REQUIRE( testNode.parent == nullptr );
        REQUIRE( testNode.left .get() == nullptr );
        REQUIRE( testNode.right.get() == nullptr );

    }

}


TEST_CASE( "Link Nodes", "[node_link]" ) {

    SECTION( "Node with Data and Parent" ) {

        std::pair<int, int> testPair(3,4);
        APutils::Node<std::pair<int, int>> c;
        APutils::Node<std::pair<int,int>> testNode(testPair, &c);

        REQUIRE( testNode.data.first  == 3 );
        REQUIRE( testNode.data.second == 4 );
        REQUIRE( testNode.parent == &c );
        REQUIRE( testNode.left .get() == nullptr );
        REQUIRE( testNode.right.get() == nullptr );

    }

    SECTION( "Node with Data, Parent and Children" ) {

        std::pair<int, int> rootPair(1,1);
        std::pair<const int, int> leftPair(0,0);
        const std::pair<const int, int> rightPair(2,2);

        APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
        nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
        nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

        REQUIRE( nodeRoot.data.first  == 1 );
        REQUIRE( nodeRoot.data.second == 1 );
        REQUIRE( nodeRoot.left .get()->data.first  == 0 );
        REQUIRE( nodeRoot.left .get()->data.second == 0 );
        REQUIRE( nodeRoot.right.get()->data.first  == 2 );
        REQUIRE( nodeRoot.right.get()->data.second == 2 );
        REQUIRE( nodeRoot.parent == nullptr );
        REQUIRE( nodeRoot.left .get()->parent == &nodeRoot );
        REQUIRE( nodeRoot.right.get()->parent == &nodeRoot );
        REQUIRE( nodeRoot.left .get()->left  == nullptr );
        REQUIRE( nodeRoot.left .get()->right == nullptr );
        REQUIRE( nodeRoot.right.get()->left  == nullptr );
        REQUIRE( nodeRoot.right.get()->right == nullptr );

        nodeRoot.printNode();
        nodeRoot.left->printNode();
        nodeRoot.right->printNode();

    }

}
