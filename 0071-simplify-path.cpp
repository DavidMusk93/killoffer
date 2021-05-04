//
// Created by Steve on 11/24/2020.
//

#include "solver_ex.h"

class Solution {
public:
    string simplifyPath(string path) {
#define DOT '.'
#define DELIMITER '/'
//        if(path.empty()||path[0]!=DELIMITER){ /*never mind*/
//            return "";
//        }
        sun::StringSeparator separator(path,DELIMITER);
        vector<sun::StringView> a;
        for(;;){
            if(!separator.next()){
                break;
            }
            auto sv=separator.getStringView();
            if(path[sv.i]==DOT){
                if(sv.i+1==sv.j){ /*'.'*/
                    continue;
                }
                if(sv.i+2==sv.j&&path[sv.i+1]==DOT){ /*'..'*/
//                    if(a.empty()){ /*'/..' not an error*/
//                        return {DELIMITER};
//                    }
                    if(!a.empty()){a.pop_back();}
                    continue;
                }
            }
            a.push_back(sv); /*'.bashrc','..tag','...' is valid*/
        }
        if(a.empty()){
            return {DELIMITER};
        }
        stringstream ss;
//        string ans;
        for(auto&sv:a){
            ss<<DELIMITER<<path.substr(sv.i,sv.j-sv.i);
//            auto t=DELIMITER+path.substr(sv.i,sv.j-sv.i);
//            ans+=t;
        }
        return ss.str();
    }
};

MAIN(){
    PREREQUISITES(simplifyPath);
    TEST("/home","/home/");
    TEST("/","/../");
    TEST("/home/foo","/home//foo");
    TEST("/c","/a/./b/../../c/");
    TEST("/c","/a/../../b/../c//.//");
    TEST("/a/b/c","/a//b////c/d//././/..");
    TEST("/...","/...");
    TEST("/","/..");
}
