// 020-IteratorTest.cpp

// main() provided in 000-CatchMain.cpp

#include "catch.hpp"

#include <memory>
#include <string>
#include <utility>
#include "Node.hpp"
#include "Iterator.hpp"


TEST_CASE( "Use iterators", "[iterators]" ) {

    std::pair<int, int> rootPair(1,1);
    std::pair<const int, int> leftPair(0,0);
    const std::pair<const int, int> rightPair(2,2);

    APutils::Node<std::pair<int, int>> nodeRoot(rootPair, nullptr);
    nodeRoot.left  = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(leftPair, &nodeRoot));
    nodeRoot.right = std::unique_ptr<APutils::Node<std::pair<int, int>>>(new APutils::Node<std::pair<int, int>>(rightPair, &nodeRoot));

    APutils::__iterator<APutils::Node<std::pair<int, int>>,std::pair<int, int>> it(&nodeRoot);

    SECTION( "Change `Value` via non-const iterator" ) {

        REQUIRE( it->first  == 1 );
        REQUIRE( it->second == 1 );
        it->second = 66;   /* Changing the `Value` of a `Node` through an iterator */
        REQUIRE( it->first  == 1 );
        REQUIRE( it->second == 66 );

    }

    SECTION( "Go to the next node via `it++` and `*` access" ) {

        auto itData = (*(it++));

        REQUIRE( itData.first  == 1 );
        REQUIRE( itData.second == 1 );

        REQUIRE( (*(it)).first   == 2 );
        REQUIRE( (*(it)).second  == 2 );

    }

    SECTION( "Go to the next node via `++it` and `->` access" ) {

        auto itDataPtr = (++it);

        REQUIRE( itDataPtr->first  == 2 );
        REQUIRE( itDataPtr->second == 2 );

        REQUIRE( (it)->first  == 2);
        REQUIRE( (it)->second == 2);

    }

}
