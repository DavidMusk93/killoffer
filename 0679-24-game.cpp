//
// Created by Steve on 8/22/2020.
//

#include "solver.h"

class Val{
public:
    Val(int i):f_(i){}
    Val(Val&&other)noexcept:Val(0){
        swap(f_,other.f_);
    }
    Val(const Val&other)=default;
//    Val&operator=(Val&&other)noexcept{
//        swap(f_,other.f_);
//        return *this;
//    }
    Val&operator=(const Val&other)=default;
    Val&&move(){
        return static_cast<Val&&>(*this);
    }
    [[nodiscard]] float f() const{
        return f_;
    }
    [[nodiscard]] bool is_zero() const{
        return fabs(f_)<kLimit;
    }
    Val&operator+(const Val&other){
        f_+=other.f_;
        return *this;
    }
    Val&operator-(const Val&other){
        f_-=other.f_;
        return *this;
    }
    Val&operator*(const Val&other){
        f_*=other.f_;
        return *this;
    }
    Val&operator/(const Val&other){
        f_/=other.f_;
        return *this;
    }
private:
    float f_;

    static constexpr const double kLimit=1e-6;
};

static ostream&operator<<(ostream&os,const Val&val){
    os<<val.f();
    return os;
}

class Solution {
public:
    enum /*class Op:int*/{
        PLUS,
        MINUS,
        RMINUS,
        MUL,
        DIV,
        RDIV,
    };

    bool judgePoint24_v1(vector<int>& nums) {
        function<bool(vector<Val>)> dfs;
        dfs=[&dfs](vector<Val> list)->bool{
            if(list.empty()){
                return false;
            }
            int n=list.size();
            if(n==1){
                return (list[0]-kTarget).is_zero();
            }
//            cout<<list;
            for(int i=0;i<n;++i){
                for(int j=i+1;j<n;++j){
                    vector<Val> rest;
                    for(int k=0;k<n;++k){
                        if(k!=i&&k!=j){
                            rest.push_back(list[k]);
                        }
                    }
                    for(int k=0;k<kOpType;++k){
                        auto a=list[i]; //copy constructor
                        auto b=list[j];
                        if(k==PLUS){
                            rest.push_back((a+b).move());
                        }else if(k==MINUS){
                            rest.push_back((a-b).move());
                        }else if(k==RMINUS){
                            rest.push_back((b-a).move());
                        }else if(k==MUL){
                            rest.push_back((a*b).move());
                        }
                        else if(k==DIV){
                            a/b;
                            if(!a.is_zero()){ //avoid zero
                                rest.push_back(a.move());
                            }
                        }else{
                            b/a;
                            if(!b.is_zero()){
                                rest.push_back(b.move());
                            }
                        }
                        if(dfs(rest)){
                            return true;
                        }
                        if(!rest.empty()){
                            rest.pop_back();
                        }
                    }
                }
            }
            return false;
        };
        vector<Val> list;
        list.reserve(4);
        for(auto i:nums){
            list.emplace_back(i);
        }
        return dfs(move(list));
    }

    bool judgePoint24_v2(vector<int>&nums){
#define ISZERO(x) (fabs(x)<1e-4)
        struct Pusher{
            Pusher(vector<float>&v,float f):v(v){
                if(!(zero=ISZERO(f))){v.push_back(f);}
            }
            ~Pusher(){
                if(!zero){v.pop_back();}
            }
            vector<float>&v;
            bool zero;
        };
        function<bool(const vector<float>&)> dfs;
        dfs=[&dfs](const vector<float>&v)->bool{
            if(v.empty()){
                return false;
            }
            int n=v.size();
            if(n==1){
                return ISZERO(v[0]-kTarget);
            }
//            cout<<v;
            for(int i=0;i<n;++i){
                for(int j=i+1;j<n;++j){
                    vector<float> left=v;
                    left.erase(left.begin()+i),left.erase(left.begin()+j-1);
//                    for(int k=0;k<n;++k){
//                        if(k!=i&&k!=j){
//                            left.push_back(v[k]);
//                        }
//                    }
                    auto a=v[i],b=v[j];
                    for(auto f:{a+b,a-b,b-a,a*b,a/b,b/a}/*initializer list*/){
                        Pusher pusher(left,f);
                        if(dfs(left)){
                            return true;
                        }
                    }
                }
            }
            return false;
        };
        vector<float> v;
        v.reserve(4);
        for(auto i:nums){v.push_back(i);}
        return dfs(v);
    }

    bool judgePoint24(vector<int>&nums){
        return judgePoint24_v2(nums);
    }

private:
    static constexpr const int kTarget=24;
    static constexpr const int kOpType=6;
};

MAIN(){
    Solution solver;
    vector<int> data{4,1,8,7};
    LOG("%d",solver.judgePoint24(data));
//    Val val(3);
//    cout<<(Val(1)+val)<<","<<(Val(1)-val)<<","<<(Val(1)*val)<<","<<(Val(1)/val)<<endl;
}