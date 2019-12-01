#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>
#include "../example.hpp"
#include "FlexLexer.h"
#include <iostream>
#include <sstream>
#include <iostream>
#include <ostream>
using namespace std;
using namespace Catch::Matchers;


TEST_CASE( "testing types", "[variables]" ) {
    GIVEN("A basic lexer"){
        stringstream i_str;
        ostringstream o_str;
        istream in(i_str.rdbuf());
        ostream out(o_str.rdbuf());
        yyFlexLexer scanner(&in, &out);
    
        SECTION("Basic test"){
            i_str << "int a_sd bool";
            
            REQUIRE(scanner.yylex() == 258);
            REQUIRE(scanner.yylex() == 259);
            REQUIRE(scanner.yylex() == 258);

        }

        SECTION("All types test"){
            i_str << "int bool char float";
            for (int i = 0; i < 4; i++)
            {
                REQUIRE(scanner.yylex() == 258);
            }
            
        }

        SECTION("symbols test"){
            i_str << "asd Hello123 s_d_23_as_d _AsD";
            for (int i = 0; i < 4; i++)
            {
                REQUIRE(scanner.yylex() == 259);
            }

            SECTION("symbols test correctness"){
                i_str << "asd 1Hello123";
                scanner.yyrestart(&in);
                REQUIRE(scanner.yylex() == 259);
                REQUIRE(scanner.yylex() == 0);

                i_str << "s_d_23_as_d ;AsD";
                scanner.yyrestart(&in);
                REQUIRE(scanner.yylex() == 259);
                REQUIRE(scanner.yylex() == 0);

            }
            
        }

        
    }
    //cout << o_str.str() << endl;
}
