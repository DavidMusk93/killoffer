//
// Created by Steve on 9/21/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        enum class element_type:char{
            NUM,
            OP,
        };
        enum class op_type:char{
            PLUS,
            MINUS,
            MUL,
            DIV,
        };
        struct element{
            element_type type;
            op_type op;
            int n;
//            union{
//               int n;
//               op_type op;
//            } data;
        };
        const int N=tokens.size();
        vector<element> elements;
        elements.reserve(N);
        for(auto&token:tokens){
            int i=atoi(token.c_str()); /*error may be useful*/
            if(i){
                elements.push_back({.type=element_type::NUM,.n=i});
            }else{
                op_type op;
                if(token=="+"){
                    op=op_type::PLUS;
                }else if(token=="-"){
                    op=op_type::MINUS;
                }else if(token=="*"){
                    op=op_type::MUL;
                }else if(token=="/"){
                    op=op_type::DIV;
                }else{
                    elements.push_back({.type=element_type::NUM,.n=0});
                    continue;
                }
                elements.push_back({.type=element_type::OP,.op=op});
            }
        }
        vector<int> result;
        for(auto&e:elements){
            if(e.type==element_type::NUM){
                result.push_back(e.n);
            }else{
                auto n2=result.back();
                result.pop_back();
                auto&n1=result.back();
                if(e.op==op_type::PLUS){
                    n1+=n2;
                }else if(e.op==op_type::MINUS){
                    n1-=n2;
                }else if(e.op==op_type::MUL){
                    n1*=n2;
                }else{
                    n1/=n2;
                }
            }
        }
        return result.back();
    }
};