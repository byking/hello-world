/* https://leetcode.com/problems/xxx */

回溯编码问题&技巧:
1. 函数必须显示return.
2. balance法见回溯NO.001 checkValid函数:遍历记录.
3. 行:row; 列:col; 初始的输入:input.
4. checkVaild() 可以在回溯过程中判断，也可以在一种结果出来后再判断.
   通用的方法是在过程中就加上判断，这样可以剪枝，有的问题比如NO.002
   适合在过程中判断，最后不用判断，但是有的问题比如NO.001过程中判断后
   最后结束时也要判断，因为过程中的判断不能完全判断不满足.

/***************************************
 * 回溯 NO.001
 * generate-parentheses
 ***************************************/
vector<string> generateParenthesis(int n) {
  vector<string> res;
  string input(2*n, ' ');
  find(input, 0, res);
  return res;
}

// 枚举所有的情况, 每一位上取值为'('、')'两种情况，并找到满足条件的解
// 注意:第一个参数不能引用传值(可以使用引用传递,是DFS先将input入res)
void find(string& input, int pos, vector<string>& res) {
  if (pos == input.length()) {
    if (checkValid(input)) {
      res.push_back(input);
    }
  } else {
    input[pos] = '(';
    find(input, pos + 1, res);
    input[pos] = ')';
    find(input, pos + 1, res);
  }
}

bool checkValid(string& input) {
  int balance = 0;
  for (auto c : input) {
    if (c == '(') {
      balance ++;
    } else if (c == ')') {
      balance --;
    }
    if (balance < 0) {
      return false;
    }
  }
  return (balance == 0); // 注意：显示return
}


/***************************************
 * 回溯 NO.002
 * n-queens 
 ***************************************/
vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> res;
  vector<string> input(n,string(n, '.')); // 注意:不用'='初始化
  find(input, 0, res);
  return res;
}

void find(vector<string>& input, int row, vector<vector<string>>& res) {
  if (row == (int)input.size()) {
    res.push_back(input);
    return;
  }
  for (int i = 0; i < (int)input.size(); i++) {
    if (checkValid(input, row, i)) {
      input[row][i] = 'Q';
      find(input, row + 1, res);
      input[row][i] = '.';
    }
  }
  return;
}

bool checkValid(vector<string>& input, int row, int col) {
  for (int i = row - 1; i >=0; i--) {
    if (input[i][col] == 'Q') {
      return false;
    }
  }
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // 注意:'&&' not ','
    if (input[i][j] == 'Q') {
      return false;
    }
  }
  for (int i = row - 1, j = col + 1; i >= 0 && j < (int)input.size(); i--, j++) {
    if (input[i][j] == 'Q') {
      return false;
    }
  }
  return true;
}


/***************************************
 * 回溯 NO.003
 * partition-equal-subset-sum (0-1背包问题变种) 
 * 0-1背包问题: 
 * int maxVal = INT_MIN;
 * // vector<vector<int>> mem(item.size(), vector<int>(totalSumOfItems, -1));
 * solve01(vector<int>& items, int pos, int curW, int w, int& maxVal) {
 *   if (pos == (int)items.size() || curW == w) { // 注意: 加上'res == w'剪枝
 *     maxVal = max(maxVal, curW);
 *     return;
 *   }
 *   // if (mem[pos][curw] != -1) return; 
 *   solve01(items, pos + 1, curW, w, maxVal);
 *   if (curW + items[pos] <= w) { // 剪枝
 *     solve01(items, pos + 1, curW + items[pos], w, maxVal);
 *   }
 *   // mem[pos][curW] = 1; // 标记pos位置重量为curW的情况已经计算过maxVal
 * }
 * 
 * solve01(items, 0, 0, w);
 * 
 * 备忘录版本: 上面去掉注释
 *  
 ***************************************/
bool canPartition(vector<int>& nums) {
  double sum = 0;
  for (auto num : nums) {
    sum += num;
  }
  sum /= 2;
  vector<vector<int>> mem(nums.size(), vector<int>(20000, -1));
  double maxVal = LONG_MIN;
  find(nums, 0, 0, sum, mem, maxVal); 
  return (maxVal == sum);
}

void find(vector<int>& nums, int pos, double curSum, double aimSum, vector<vector<int>>& mem, double& maxVal) {
  if (pos == (int)nums.size() || curSum == aimSum) {
    maxVal = max(curSum, maxVal); 
    return;  // 注意结束情况要return 
  }
  if (mem[pos][curSum] != -1) {
    return;
  }
  find(nums, pos + 1, curSum, aimSum, mem, maxVal);
  if (curSum + nums[pos] <= aimSum) {
    find(nums, pos + 1, curSum + nums[pos], aimSum, mem, maxVal);
  }
  mem[pos][curSum] = 1;
}
