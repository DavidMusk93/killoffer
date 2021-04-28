#include "solver_ex.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
// -10,-3,0,5,9
//
//     0
//    / \
//   -3  9
//   /   /
//  -10  5
//
// 3 ways:
//  1) array to tree
//  2) slow&fast pointer
//  3) inorder traversal
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int len = 0;
        ListNode *p = head;
        while (p) {
            ++len;
            p = p->next;
        }
        std::function<TreeNode *(int, int)> buildBST;
        p = head;
        // [0,1]
        // m=1,[0,0],[2,1]
        buildBST = [&buildBST, &p](int s, int e)/*[s,e]*/ -> TreeNode * {
            if (s > e) {
                return nullptr;
            }
            TreeNode *left, *root;
            int m = (s + e + 1) >> 1;
            left = buildBST(s, m - 1);
            root = new TreeNode(p->val, left, nullptr);
            p = p->next;
            root->right = buildBST(m + 1, e);
            return root;
        };
        return buildBST(0, len - 1);
    }
};
