#include <catch2/catch.hpp>
#include "../driver.hh"
#include "../precompiled/parser.hh"
#include "HelperTests.hpp"
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
using namespace Catch::Matchers;






TEST_CASE( "testing assingment and datatypes", "[variables]" ) {
    Driver drv;
    const auto& [type_checker, value_checker, t_and_v_check] = generate_type_checks(drv);
    SECTION("A basic lexer"){
        
        drv.scan_string("int asd char jgkl_sdf");
       
        value_checker(Type::INT);
        t_and_v_check(4, string("asd"));
        value_checker(Type::CHAR);
        t_and_v_check(4, string("jgkl_sdf"));
    }

    SECTION("String test"){
        drv.scan_string("\"Helllo\" int char bool float string 'Greetings humans' \"goodbye\"");

        t_and_v_check(5, string("\"Helllo\""));
        value_checker(Type::INT);
        value_checker(Type::CHAR);
        value_checker(Type::BOOL);
        value_checker(Type::FLOAT);
        value_checker(Type::STRING);
        t_and_v_check(5, string("'Greetings humans'"));
        t_and_v_check(5, string("\"goodbye\""));

    }
}
