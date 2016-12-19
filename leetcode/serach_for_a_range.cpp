//
// Created by mark on 16-12-19.
//
class Solution{
public:
    vector<int> searchRange(vector<int> &nums, int target){
        vector<int> result;
        int right = findRight(nums, target, 0, nums.size()-1);
        right = right < nums.size() && nums[right] == target ? right : -1;
        int left = findLeft(nums, target, 0, right);
        left = left < nums.size() && nums[left] == target? left : -1;

        result.push_back(left), result.push_back(right);
        return result;
    }

private:
    int findRight(vector<int> &nums, int target, int start, int end){
        while(start <= end){
            int mid = start + (end - start)/2;
            if(nums[mid] <= target){
                start = mid + 1;
            }
            else
                end = mid - 1;
        }
        return start-1;
    }
    int findLeft(vector<int> &nums, int target, int start, int end){
        while(start <= end){
            int mid = start + (end - start)/2;
            if(nums[mid] >= target){
                end = mid - 1;
            }
            else
                start = mid + 1;
        }
        return end+1;
    }
};
