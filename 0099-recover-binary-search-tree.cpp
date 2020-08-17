//
// Created by Steve on 8/9/2020.
//

#include "solver.h"

class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode*pre{},*cur{};
        struct Seq{
//            TreeNode*p1,*p2,*p3,*p4;
            TreeNode*p1,*p2;
            void update(TreeNode*pre,TreeNode*cur){
                if(pre&&cur&&pre->val>cur->val){
                    if(!p1){
                        p1=pre,p2=cur;
                    }else{
//                        p3=pre,p4=cur;
                        p2=cur;
                    }
                }
            }
            void swap() const{
//                if(!p3){
                std::swap(p1->val,p2->val);
//                }else{
//                    std::swap(p1->val,p4->val);
//                }
            }
        } seq{};
//        auto update=[&pre,&cur,&seq](TreeNode*node){
//            pre=cur;
//            cur=node;
//            seq.update(pre,cur);
//        };
        function<void(TreeNode*)> inorder_traverse;
        inorder_traverse=[&inorder_traverse,&pre,&cur,&seq](TreeNode*root){
            if(root){
                inorder_traverse(root->left);
//                update(root);
                pre=cur,cur=root;
                seq.update(pre,cur);
                inorder_traverse(root->right);
            }
        };
        inorder_traverse(root);
        seq.swap();
    }
};

MAIN(){
    void*p{};
    LOG("%d",!!p);
}