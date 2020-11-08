//
// Created by Steve on 10/2/2020.
// @ref
//   * https://github.com/frontend9/fe9-library/issues/3
//   * https://github.com/frontend9/fe9-library/issues/10
//   * https://python3-cookbook.readthedocs.io/zh_CN/latest/c02/p19_writing_recursive_descent_parser.html
//

#include "solver_ex.h"

class Parser{
public:
    struct Token{
        enum class Type:char{
            NUM,
            PLUS,
            MINUS,
            MUL,
            DIV,
            LP,
            RP,
            NONE,
        };
        Type type;
        int val;
        Token(Type type,int val):type(type),val(val){}
        Token(Type type):Token(type,0){}
        Token():Token(Type::NONE){}
    };
public:
    Parser(string&s):s_(s),i_(0){}
    Token next(){
        Token tok{};
        for(;i_<s_.size();){
            char c=s_[i_++];
            tok.val=c;
            if(isspace(c)){
                continue;
            }else if(c=='+'){
                tok.type=Token::Type::PLUS;
            }else if(c=='-'){
                tok.type=Token::Type::MINUS;
            }else if(c=='*'){
                tok.type=Token::Type::MUL;
            }else if(c=='/'){
                tok.type=Token::Type::DIV;
            }else if(c=='('){
                tok.type=Token::Type::LP;
            }else if(c==')'){
                tok.type=Token::Type::RP;
            }else{
                tok.type=Token::Type::NUM;
                tok.val=c-'0';
                for(;i_<s_.size();++i_){
                    char t=s_[i_];
                    if(isdigit(t)){
                        tok.val*=10;
                        tok.val+=t-'0';
                    }else{
                        break;
                    }
                }
            }
            break;
        }
        return tok;
    }
private:
    string&s_;
    int i_;
};

class Solution {
public:
    using Type=Parser::Token::Type;

    int calculate(string s) {
        parser_=make_unique<Parser>(s);
        Advance();
        return op1();
    }

    int op1(){
        int v=op2();
        while(tok_.type==Type::PLUS||tok_.type==Type::MINUS){
            if(tok_.type==Type::PLUS){
                v+=op2();
            }else if(tok_.type==Type::MINUS){
                v-=op2();
            }
        }
        return v;
    }

    int op2(){
        int v=op3();
        while(tok_.type==Type::MUL||tok_.type==Type::DIV){
            if(tok_.type==Type::MUL){
                v*=op3();
            }else if(tok_.type==Type::DIV){
                v/=op3();
            }
        }
        return v;
    }

    int op3(){
        Advance();
        int v=tok_.val;
        if(tok_.type==Type::LP){
            v=op1();
            Expect(Type::RP);
            return v;
        }
        Expect(Type::NUM);
        return v;
    }

protected:
    void Advance(){
        tok_=nexttok_;
        nexttok_=parser_->next();
    }

    bool Expect(Parser::Token::Type type){
        if(tok_.type==type){
            Advance();
            return true;
        }
        throw invalid_argument("unexpected token");
//        return false;
    }

private:
    unique_ptr<Parser> parser_{};
    Parser::Token tok_{},nexttok_{};
};

MAIN(){
//    string s{" 3+5 / 2 "};
//    Parser parser(s);
//    using Token=Parser::Token;
//    Token tok{};
//    while((tok=parser.next()).type!=Token::Type::NONE){
//        if(tok.type!=Token::Type::NUM){
//            LOG("%c",static_cast<char>(tok.val));
//        }else{
//            LOG("%d",tok.val);
//        }
//    }
    PREREQUISITES(calculate);
    TEST(11,"3+2*2*2");
    TEST(1," 3/2 ");
    TEST(5," 3+5 / 2 ");
    TEST(15,"3*(1+4/(3-2*1))");
}
