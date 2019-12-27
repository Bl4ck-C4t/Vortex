#ifndef PARSERTEST_HH
#define PARSERTEST_HH

#include <catch2/catch.hpp>
#include "../driver.hh"
#include "../precompiled/parser.hh"

// #include "HelperTests.hpp"
#include <iostream>
#include <string>
#include <tuple>
#include <functional>
using namespace std;
using namespace Catch::Matchers;

// function<void(string)> generateExecutor(Driver& drv){
//     drv.disableReturnPrint();
//     return [&drv](string s)->void{
//         drv.evaluate(s.c_str());
//     };
// }
//function<void(Type)>, function<typename T, void(T)>, function<typename T, void(Type, T)>
auto generateExecutor(Driver& drv){
    drv.disableReturnPrint();
    return [&drv](string s)->void{
        drv.evaluate(s.c_str());
    };
}

auto generateValueCheckers(Driver& drv){
    auto f1= [&drv](Type expected)->void{
        CHECK(drv.getLastValue().getType() == expected);
    };

    auto f2= [&drv]<typename T>(T expected)->void{
        CHECK(drv.getLastValue().getValue<T>() == expected);
    };

    auto f3= [&drv]<typename T>(Type expected, T val)->void{
        CHECK(drv.getLastValue().getType() == expected);
        CHECK(drv.getLastValue().getValue<T>() == val);
    };
    
    return make_tuple(f1, f2, f3);

}


TEST_CASE("Test variable creation"){
    Driver drv;
    drv.disableReturnPrint();
    yy::parser parser = drv.createParser();
    auto exec = generateExecutor(drv);
    const auto& [type_checker, value_checker, t_and_v_check] = generateValueCheckers(drv);


    SECTION("Set and get variables"){
        exec("int a = 3;");

        CHECK(drv.getLastValue().getValue<int>() == 3);

        exec("b = 6;");

        CHECK(drv.getLastValue().getValue<int>() == 6);

        exec("a + b");

        CHECK(drv.getLastValue().getValue<int>() == 9);

    }
    

    SECTION("Full arithmetics"){
        exec("float f1 = 3.5;");
        exec("f1 + 1.3");
    
        t_and_v_check(Type::FLOAT, 4.8f);

        exec("2 + 3*2 - 4/2");

        t_and_v_check(Type::INT, 6);

        exec("2**2 - 5 * -1 + 1");
        t_and_v_check(Type::INT, 10);

    }

}

TEST_CASE("Functions"){
    Driver drv;
    auto exec = generateExecutor(drv);
    const auto& [type_checker, value_checker, t_and_v_check] = generateValueCheckers(drv);
    SECTION("Declare and run"){
        drv.executeFile("/home/blackcat/school/Vortex/tests/TestFiles/function_declare.vx");

        exec("f1(3, 2)");

        t_and_v_check(Type::INT, 7);

        exec("f2()");

        t_and_v_check(Type::CHAR, 'c');

        exec("f3(69)");

        type_checker(Type::VOID);

    }
}

#endif