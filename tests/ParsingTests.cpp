#include <catch2/catch.hpp>
#include "../driver.hh"
#include "../precompiled/parser.hh"
// #include "HelperTests.hpp"
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
using namespace Catch::Matchers;

auto generateExecutor(Driver& drv){
    drv.disableReturnPrint();
    return [&drv](string s)->void{
        yy::parser parser = drv.createParser();
        drv.scan_string(s.c_str());
        parser();
    };
}

TEST_CASE("Test variable creation"){
    Driver drv;
    drv.disableReturnPrint();
    yy::parser parser = drv.createParser();
    auto exec = generateExecutor(drv);

    SECTION("Set and get variables"){
        exec("int a = 3");

        CHECK(drv.getLastValue().getValue<int>() == 3);

        exec("b = 6");

        CHECK(drv.getLastValue().getValue<int>() == 6);

        exec("a + b");

        CHECK(drv.getLastValue().getValue<int>() == 9);

    }

    SECTION("Full arithmetics"){
        exec("3.5 + 1.3");
    
        CHECK(drv.getLastValue().getValue<float>() == 4.8f);

        exec("2 + 3*2 - 4/2");

        CHECK(drv.getLastValue().getValue<int>() == 6);

    }

}