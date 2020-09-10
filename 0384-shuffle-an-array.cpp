//
// Created by Steve on 9/9/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int factorial(int n){ /*@FLAW-1 easy to overflow*/
        if(n==1){
            return 1;
        }
        return n*factorial(n-1);
    }
    struct Node{
        int val;
        Node*next;
        Node():Node(-1){}
        Node(int val):val(val),next{}{}
        static Node*Remove(Node*&head,int i);
        static void Iterate(Node*head,const std::function<void(Node*)>&op/*why not reference?*/);
    };
    Solution(vector<int>& nums) {
        if(nums.empty()){
            return;
        }
        ori_.swap(nums);
        n_=factorial(ori_.size());
        data_.resize(ori_.size());
        srand(time(nullptr));
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
        return ori_;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        if(ori_.empty()){
            return {};
        }
        vector<int> ans;
        int k=rand()%n_+1;
        if(k==1){
            return ori_;
        }
        int N=ori_.size();
        for(int i=0;i<N;++i){
            new(&data_[i])Node(ori_[i]);
            if(i){
                data_[i-1].next=&data_[i];
            }
        }
        auto head=&data_[0];
        auto m=n_;
        auto op=[&ans](Node*p){ans.push_back(p->val);};
        while(k>1){
            m/=N--;
            auto i=(k-1)/m;
            k-=i*m;
            ans.push_back(Node::Remove(head,i)->val);
        }
        Node::Iterate(head,op);
        return ans;
    }
    //probability calculation: (for N-0 stay on its original position)
    // for N-0, 1
    // for N-1, 1/2
    // for N-2, (1/2)*(2/3)=1/3
    // for N-3, (1/3)*(3/4)=1/4
    // ...
    // for N-x, (1/x)*(x/(x+1))=1/(x+1),
    vector<int> v2(){
        auto ans=ori_;
        const int N=ori_.size();
        for(int i=1;i<N;++i){
            auto j=rand()%(i+1);
            swap(ans[i],ans[j]);
        }
        return ans;
    }

private:
    int n_{}; /*tailing underscore to avoid naming conflicts*/
    vector<int> ori_;
    vector<Node> data_;
};

#define NODE Solution::Node
NODE*Solution::Node::Remove(Node *&head, int i) {
//    assert(i>=0);
    if(head){
        NODE*p{head};
        if(i==0){
            head=head->next;
            return p;
        }
        for(;--i&&p;p=p->next);
        if(!p||!p->next){
            return nullptr;
        }
        auto r=p->next;
        p->next=r->next;
        r->next=nullptr;
        return r;
    }
    return nullptr;
}

void Solution::Node::Iterate(Node *head, const std::function<void(Node *)> &op) {
    while(head){
        op(head);
        head=head->next;
    }
}

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */

MAIN(){
    vector<int> nums{1,2,3,4};
    Solution solver(nums);
    cout<<solver.shuffle()<<endl;
    cout<<solver.shuffle()<<endl;
    cout<<solver.shuffle()<<endl;
    cout<<solver.shuffle()<<endl;
    cout<<solver.reset()<<endl;
}