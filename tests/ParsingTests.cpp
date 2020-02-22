#ifndef PARSERTEST_HH
#define PARSERTEST_HH

#include <catch2/catch.hpp>
#include "../src/Driver/driver.hpp"
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

        exec("5.5 - 4**0.5");
        t_and_v_check(Type::FLOAT, 3.5f);

         exec("2 * 0.5");
        t_and_v_check(Type::FLOAT, 1.0f);

         exec("3 + 3");
        t_and_v_check(Type::INT, 6);

         exec("1.2 - 0.2");
        t_and_v_check(Type::FLOAT, 1.0f);

         exec("\"help \" + \"me\"");
        t_and_v_check(Type::STRING, std::string("help me"));

         exec("\" i luv \" + 'u'");
        t_and_v_check(Type::STRING, std::string(" i luv u"));

    }

}

TEST_CASE("Conditionals"){
    Driver drv;
    auto exec = generateExecutor(drv);
    const auto& [type_checker, value_checker, t_and_v_check] = generateValueCheckers(drv);
    SECTION("Basic tests"){
        exec("int res = 5;");
        exec("if(2 > 1) { res = 10; }");

        t_and_v_check(Type::BOOL, true);

        exec("res");
        t_and_v_check(Type::INT, 10);

        exec("15 if (2**2 - 3 > 5) { res = 20; } else { res = 35; }");

        t_and_v_check(Type::BOOL, false);

        exec("res");
        t_and_v_check(Type::INT, 35);
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

    SECTION("Recursion and ifs"){
        drv.executeFile("/home/blackcat/school/Vortex/tests/TestFiles/function_declare.vx");

        exec("max(3, 5)");

        t_and_v_check(Type::INT, 5);


        exec("fact(1)");

        t_and_v_check(Type::INT, 1);

        exec("fact(2)");

        t_and_v_check(Type::INT, 2);

        exec("fact(4)");

        t_and_v_check(Type::INT, 24);
    }
}



#endif