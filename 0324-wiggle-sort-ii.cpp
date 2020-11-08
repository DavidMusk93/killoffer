//
// Created by Steve on 10/27/2020.
//

#include "solver_ex.h"

namespace sun{
    template<typename Iter>
    void nth_element(Iter a,Iter b,Iter c){
        Iter i,j;
        swap(*a,*b);
        for(i=j=a+1;j<c;){
            if(*j>*a){
                ++j;
            }else{
                swap(*i++,*j++);
            }
        }
        if(i==b+1){
            swap(*a,*b);
            return;
        }else if(i>b){
            ::nth_element(a,b,i);
        }else{
            ::nth_element(i,b,c);
        }
    }
}

class Solution {
public:
    void wiggleSort(vector<int>& nums) { /*does not hold the CORE (duplicate medians)*/
        const int N=nums.size(),HALF=N/2;
        if(N==1){
            return;
        }
        nth_element(nums.begin(),nums.begin()+HALF,nums.end());
//        cout<<"divide:"<<nums<<endl;
        if(N&1){
            if(HALF&1){
                for(int i=1,j=i+HALF;j<N;i+=2,j=i+HALF){
                    swap(nums[i],nums[j]);
                }
            }else{
                for(int i=1,j=N-i;i<HALF;i+=2,j=N-i){
                    swap(nums[i],nums[j]);
                }
            }
        }else{
            for(int i=1,j=N-1-i;i<HALF;i+=2,j=N-1-i){
                swap(nums[i],nums[j]);
            }
        }
    }
    /** REAL INDEX:
     * a,the greater boundary;
     * b,the equality boundary;
     * c,the less boundary.
     */
    void v2(vector<int>&nums){
        const int N=nums.size();
        if(N<2){
            return;
        }
        vector<int> I(N,0);
        for(int i=0;i<N;++i){
            I[i]=(i*2+1)%(N|1);
        }
        auto it=nums.begin()+N/2;
        nth_element(nums.begin(),it,nums.end());
        int a,b,c,m;
#define X(i) nums[I[i]]
        for(a=b=0,c=N,m=*it;b<c;){
            if(X(b)>m){
                swap(X(a++),X(b++));
            }else if(X(b)<m){
                swap(X(b),X(--c));
            }else{
                ++b;
            }
        }
    }
};

//MAIN(){
//#define MYTEST \
//INVOKE(nums);\
//cout<<nums<<endl
//    PREREQUISITES(v2);
//    vector<int> nums={6,5,1,4,1,1,7};
//    INVOKE(nums);
//    cout<<nums<<endl;
//    nums={8,7,5,6,1,2,4,3};
//    INVOKE(nums);
//    cout<<nums<<endl;
//    nums={1,5,1,1,6,4};
//    INVOKE(nums);
//    cout<<nums<<endl;
//    nums={1,2,1,2,1,1,2,2,1};
//    INVOKE(nums);
//    cout<<nums<<endl;
//    nums={4,5,5,6};
//    MYTEST;
//}
MAIN(){
#define M (nums.begin()+nums.size()/2)
#define MYTEST \
sun::nth_element(nums.begin(),M,nums.end());\
cout<<nums<<endl
    vector<int> nums;
    nums={8,6,4,5,6,7};
    MYTEST;
    nums={6,5,1,4,1,1,7};
    MYTEST;
    nums={1,2,1,2,1,1,2,2,1};
    MYTEST;
}