//
// Created by Steve on 11/13/2020.
//

// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        int i,j,k;
        for(i=1,j=n;i<j;){
            k=i+(j-i)/2;
            if(isBadVersion(k)){
                j=k-1;
            }else{
                i=k+1;
            }
        }
        return isBadVersion(i)?i:i+1;
    }
};