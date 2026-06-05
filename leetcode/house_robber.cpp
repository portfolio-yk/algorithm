class Solution {
public:
    int rob(vector<int>& nums) {
        int dp[105];

        if(nums.size() == 1) {
            return nums[0];
        } else if(nums.size() == 2) {
            return max(nums[1], nums[0]);
        }

        dp[0] = nums[0];
        dp[1] = nums[1];
        dp[2] = nums[0] + nums[2];
        
        for(int i = 3; i < nums.size(); i++) {
            dp[i] = max(nums[i] + dp[i - 3], nums[i] + dp[i - 2]);
        }

        int answer = 0;
        for(int i = 0; i < nums.size(); i++) {
            if(answer < dp[i]) {
                answer = dp[i];
            }
        }

        return answer;
    }
};