#include <catch2/catch.hpp>
#include "../driver.hh"
#include "../precompiled/parser.hh"
// #include "HelperTests.hpp"
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
using namespace Catch::Matchers;

TEST_CASE("Test variable creation"){
    Driver drv;
    yy::parser parser = drv.createParser();

    SECTION("Set and get variables"){
        drv.scan_string("int a = 3");
        parser();

        REQUIRE(drv.getLastValue().getValue<int>() == 3);

    }

}