#ifndef OPERATION_HPP
#define OPERATION_HPP
#include "../Variables/vars.hpp"
#include <cmath>
#include <tuple>
#include <string>

class Operation{
    Type type1_;
    Type type2_;
    std::string oper_;
    public:
        Operation(Type tp, Type tp2, std::string op): type1_(tp), type2_(tp2), oper_(op) {}

        Operation(std::string tp): oper_(tp) {}
        virtual bool match(rvalue lhs, rvalue rhs, std::string operation) const
        {
            return lhs.getType() == type1_ && rhs.getType() == type2_ && oper_ == operation;
        }
        virtual rvalue execute(rvalue lhs, rvalue rhs) const = 0;

        std::string getOper() const{
            return oper_;
        }

        static std::tuple<float, float>floatCast(rvalue& lhs, rvalue& rhs){
            float f1,f2;

            if(lhs.getType() == Type::INT){
                f1 = (float)lhs.getValue<int>();
            }
            else{
                f1 = lhs.getValue<float>();
            }

            if(rhs.getType() == Type::INT){
                f2 = (float)rhs.getValue<int>();
            }
            else{
                f2 = rhs.getValue<float>();
            }

            return std::make_tuple(f1, f2);

        }

        static std::tuple<std::string, std::string>stringCast(rvalue& lhs, rvalue& rhs){
            std::string f1,f2;
            if(lhs.getType() == Type::CHAR){
                f1 = lhs.getValue<char>();
            }
            else{
                f1 = lhs.getValue<std::string>();
            }

            if(rhs.getType() == Type::CHAR){
                f2 = rhs.getValue<char>();
            }
            else{
                f2 = rhs.getValue<std::string>();
            }

            return std::make_tuple(f1, f2);
        }
};

#endif