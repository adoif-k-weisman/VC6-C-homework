#include<iostream>
#include<vector>
using namespace std;
int main()
{
	return 0;
}
 int getMiss_index(vector<int>&nums)
    {
        if(nums.empty()) return 0;
        int left=0,right=nums.size()-1;
        while(left<right){
            int mid=left + (right>>1) ;
            if(nums[mid]!=mid){
                right=mid;
            }
            else{
                left=mid+1; }
        }
        if(nums[right]==right) right++;
        return right;
    }