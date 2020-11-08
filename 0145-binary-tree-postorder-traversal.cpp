//
// Created by Steve on 9/29/2020.
//

#include "solver_ex.h"

SOLUTION{
public:
    vector<int> postorderTraversal(TreeNode*root){
        vector<int> res;
        vector<TreeNode*> stack;
        unordered_set<TreeNode*> us;
        if(root){
            stack.push_back(root);
            do{
                auto t=stack.back();
                if(us.count(t)||(!t->right&&!t->left)){
                    res.push_back(t->val);
                    stack.pop_back();
                }else{
                    if(t->right){
                        stack.push_back(t->right);
                    }
                    if(t->left){
                        stack.push_back(t->left);
                    }
                    us.insert(t);
                }
            }while(!stack.empty());
        }
        return res;
    }
    vector<int> v2(TreeNode*root){
#define LPUSH(x) if(x){lv.push_back(x);}
#define GBACK(v) ({auto t=v.back();v.pop_back();t;})
        if(!root){
            return {};
        }
        vector<int> ans;
        vector<TreeNode*> lv{root},rv;
        while(!lv.empty()){
            root=GBACK(lv);
            if(!root->left&&!root->right){
                ans.push_back(root->val);
                if(lv.empty()){
                    break;
                }
                while(lv.back()!=rv.back()->right){ans.push_back(GBACK(rv)->val);}
            }else{
                rv.push_back(root);
                LPUSH(root->right);
                LPUSH(root->left);
            }
        }
        while(!rv.empty()){ans.push_back(GBACK(rv)->val);}
        return ans;
    }
};