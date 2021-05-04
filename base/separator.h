//
// Created by Steve on 11/24/2020.
//

#ifndef KILLOFFER_SEPARATOR_H
#define KILLOFFER_SEPARATOR_H

#include <functional>
#include <string>

namespace sun{
    using Closure=std::function<void()>;
    struct Defer{
        Closure closure;
        Defer(Closure closure):closure(closure){}
        ~Defer(){closure();}
    };
    struct StringView{
        int i{},j{};
//        string&s;
    };
    struct StringSeparator{
        const std::string&s;
        const int N;
        int i;
        char delimiter;
        StringSeparator(const std::string&s,char delimiter=' '):s(s),N(s.size()),i(0),delimiter(delimiter){}
        bool next(){
            if(i<N){
                for(;i<N&&s[i]==delimiter;++i);
            }
            return i!=N;
        }
        StringView getStringView(){
            int j;
            Defer defer([this,&j]{i=j;});
            for(j=i+1;j<N&&s[j]!=delimiter;++j);
            return StringView{i,j};
        }
    };
}

#endif //KILLOFFER_SEPARATOR_H
