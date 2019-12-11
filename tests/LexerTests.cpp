#include <catch2/catch.hpp>
#include "../driver.hh"
#include "../precompiled/parser.hh"
#include <iostream>
#include <string>
#include <tuple>
using namespace std;
using namespace Catch::Matchers;
// LEGACY 
/*yy::parser::symbol_type yylex(Driver& drv);
typedef struct yy_buffer_state* YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string (const char * yystr );
void yy_switch_to_buffer ( YY_BUFFER_STATE new_buffer  );


auto generate_string_Driver(Driver& drv){
    return [&](const char* str) {
        auto bp = yy_scan_string(str);
        yy_switch_to_buffer(bp);
        auto sym = yylex(drv);
        return sym;
    };        
} 

auto generate_driver_tokenizer(Driver& drv){
    return [&](){
        return drv.get_token();
    };
}*/



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


TEST_CASE( "testing assingment and datatypes", "[variables]" ) {
    Driver drv;
    const auto& [type_checker, value_checker, t_and_v_check] = generate_type_checks(drv);
    SECTION("A basic lexer"){
        
        drv.scan_string("int asd char jgkl_sdf");
       
        type_checker(3);
        t_and_v_check(4, string("asd"));
        type_checker(3);
        t_and_v_check(4, string("jgkl_sdf"));

        
    }

    SECTION("String test"){
        drv.scan_string("\"Helllo\" int 'Greetings humans' \"goodbye\"");

        t_and_v_check(5, string("\"Helllo\""));
        type_checker(3);
        t_and_v_check(5, string("'Greetings humans'"));
        t_and_v_check(5, string("\"goodbye\""));

    }
}
