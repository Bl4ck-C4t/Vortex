#ifndef HELPER_FILE
#define HELPER_FILE

#include <catch2/catch.hpp>
#include "../src/Driver/driver.hh"
#include "../precompiled/parser.hh"
#include "../src/Variables/vars.hpp"
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
using namespace Catch::Matchers;
auto generate_type_checks(Driver& drv){
    auto f1= [&drv](int expected)->void{
        REQUIRE(drv.get_token().type_get() == expected);
    };
    // template<typename T>
    auto f2= [&drv]<typename T>(T expected)->void{
        REQUIRE(drv.get_token().value.as<T>() == expected);
    };

    auto f3 = [&drv]<typename T>(int t_type, T val)->void{
        yy::parser::symbol_type token = drv.get_token();
        // auto s = token.value.as<T>();
        REQUIRE(token.type_get() == t_type);
        REQUIRE(token.value.as<T>() == val);
    };

    return make_tuple(f1, f2, f3);
}


#endif