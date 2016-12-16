//
// Created by mark on 16-12-16.
//
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        vector<vector<int>> res;
        int len = matrix.size();
        res.resize(len);
        for(int i = 0; i < len; ++i){
            res[i].resize(len);
        }
        for(int i = 0; i < len; ++i){
            for(int j = 0; j < len; ++j){
                res[j][len-1-i] = matrix[i][j];
            }
        }
        matrix = res;
    }
};