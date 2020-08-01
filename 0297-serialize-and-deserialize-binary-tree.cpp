//
// Created by Steve on 7/21/2020.
//

#include <string>
#include <queue>
#include <vector>
#include <stdlib.h>

#include "common.h"

using namespace std;

#define SEP ","
#define EMPTY "null"

struct Parser{
    static int value;
    int *data;
    const char *p;
    Parser(const string&in,int*data):p(in.c_str()),data(data){
        if(!this->data){
            this->data=&value;
        }
    }
    int *next(){
        if(!*p){
            return nullptr;
        }
        if(!(isdigit(*p)||*p=='-'/*for [-1,0,1]*/)){
            p+=sizeof(EMPTY);
            return nullptr;
        }
        char*end;
        *data=(int)strtol(p,&end,10);
        p=end+1;
        return data;
    }
};

int Parser::value=0;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root){
            return EMPTY;
        }
        queue<TreeNode*> q;
        string res;
        q.push(root);
//        auto is_last=[](queue<TreeNode*>q)->bool{ /*for [1,6,2,7,5,null,null,8,null,6,4,7,9,null,null,3,5,null,null,10,8,4,2,null,null,9,11,null,null,1]*/
//            while(!q.empty()){
//                auto p=q.front();
//                if(p->left||p->right){
//                    return true;
//                }
//                q.pop();
//            }
//            return false;
//        };
        res+=to_string(root->val)+SEP;
        while(!q.empty()){
//            int n=q.size();
//            while(n--){ //level by level
                auto p=q.front();
                q.pop();
//                bool is_last=(!q.empty()&&(q.back()->left||q.back()->right));
                if(p->left||p->right/*for [1,null,2] (right matter)*/||!q.empty()){
                    res+=p->left?(q.push(p->left),to_string(p->left->val)+SEP):(EMPTY SEP);
                }
                if(p->right||!q.empty()){
                    res+=p->right?(q.push(p->right),to_string(p->right->val)+SEP):(EMPTY SEP);
                }
//            }
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int val;
        Parser parser(data,&val);
        int *p=parser.next();
        if(!p){
            return nullptr;
        }
        auto root=new TreeNode(*p);
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            auto node=q.front();
            q.pop();
            node->left=(p=parser.next())?(new TreeNode(*p)):nullptr;
            node->right=(p=parser.next())?(new TreeNode(*p)):nullptr;
            if(node->left){
                q.push(node->left);
            }
            if(node->right){
                q.push(node->right);
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

#include "macro.h"

MAIN(){
    TreeNode data[]={{-1},{0},{1},{3},{4},{5},};
    data[0].left=&data[1],data[0].right=&data[2];
//    data[2].left=&data[3],data[2].right=&data[4];
//    data[4].left=&data[5];
//    LOG("%s",Codec().serialize(&data[0]).c_str());
    Codec codec;
    auto s=codec.serialize(&data[0]);
    LOG("%s",s.c_str());
    auto root=codec.deserialize(s);
    auto s2=codec.serialize(root);
    LOG("%s",s2.c_str());
}