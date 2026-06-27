class Solution {
public:

    // bool dfs(int ans, vector<int>& nums, int start, int s, vector<int>& suffix) {
    //     if(ans == s) return true;
    //     if(start < nums.size() && s + suffix[start] < ans) return false;

    //     for(int i = start; i < nums.size(); i++) {
    //         if(s + nums[i] > ans) break;
    //         if(dfs(ans, nums, i + 1, s + nums[i], suffix)) {
    //             return true;
    //         }
    //     }

    //     return false;
    // }

    bool canPartition(vector<int>& nums) {
        int a = 0;
        for(int n : nums) {
            a += n;
        }
        if(a % 2 == 1) return false;

        int h = a / 2;

        vector<bool> dp(h + 1, false);
        dp[0] = true;
        for(int x : nums) {
            for(int j = h; j >= x; j--) {
                dp[j] = dp[j] || dp[j - x];
            }
        }

        return dp[h];

        // vector<int> suffix(nums.size() + 1, 0);
        // sort(nums.begin(), nums.end());
        // for(int i = nums.size() - 1; i >= 0; i--) {
        //     suffix[i] = suffix[i + 1] + nums[i];
        // }
        
        // return dfs(a / 2, nums, 0, 0, suffix);
    }
};