/* https://leetcode.com/problems/xxx */

回溯编码问题&技巧:
0. 回溯一般使用递归实现.
1. 回溯问题都可以分成多个阶段(阶段类似于树的层), 每一阶段(层)都有多个状态，通过回溯可以枚举所有状态(遍历完所有层上的状态). 
   阶段的划分：1) 数组的一位(步)为一层；2) 二维数组的一行为一层; 3) 棋盘上一步(对应多个点)为一层, 例如(i+1,j)(i,j+1):斜线; 4)一个输入值
   作为一个状态，例如爬楼梯(楼梯层数)、找零钱（目标钱）、斐波那契等(目标数). 
2. 一般需要执行完所有的阶段后才能得出结果(类似于从根结点到所有的叶子结点), 可以挖掘一些剪枝条件，在执行过程避免已经不满足条件的阶段状态
   继续执行, 来减少重复计算. 有些情况例如8皇后过程中的剪枝就是满足最后结果的条件，所以阶段结束是的状态就是结果；有些情况例如括号匹配问题
   过程剪枝但是最后阶段的状态也需要校验是否满足结果条件. 有些时候不能立刻想到剪枝条件可以在最后阶段再校验状态是否满足结果,例如括号匹配问
   题的第一种解法.
3. 备忘录: 可以使用备忘录来记录走过的状态，从而达到剪枝的效果来避免重复计算，但是比较适合每一层的状态好传递记录的情况(即递归函数不用返回
   值来记录到备忘录中, 状态一层一层传递到最后阶段后会被算入结果中，这样备忘录只需要记录:访问过|没有访问过 两种状态即可，如果最终结果是判
   断是否有符合条件的结果即返回true|false 则需要记录三种状态：访问过有结果|访问过没有结果|没有访问过 三种状态). 否则返回值会比较难设计，
   因为有返回值的话一层的一个状态会对应多个叶子结点状态，需要都记录或者pk出一个，从备忘录拿出状态还要继续加入上层的结果中，会比较麻烦.
   一般备忘录就参照背包问题即可(叶子状态都会和一个值比较来记录或者直接记录)，当然使用DP就不需要考虑这些. 
   例如0-1背包问题中，items(2,2,2)    f(0,0)
                                   /         \
			       f(1,0)        f(1,2)
			       /   \          /     \
		          f(2,0)  f[2,2]    f[2,2]   f(2,4)
		          /  \    /   \      /   \    /   \
	               (3,0)[3,2][3,2]{3,4}[3,2]{3,4}{3,4}(3,6)     
   初始化的时候(0,0)0位的时候有选+不选两种(1,0) (1,2),1位的时候有四种，其中有重复的[2,2]，[2,2]最终得到的
   maxVal相同，因此用mem记录算过的状态,状态相同的就不计算了。注意这里f[2,2]的值与是否来自f(1,0) f(1,2)无
   关，f[2,2]最终都算出同一个值, 递归是自顶向下，结果在叶子结点，而f(1,0) f(1,2)对应的f[2,2]最终叶子结点值
   相同。还有一种记录状态：没访问过的为初始值，访问过的记录为最终多个叶子结点的pk的一个结果，这种需要递归
   函数返回值，而且多个叶子结点的值也需要pk出一个，一般不推荐这样做，比较复杂。
4. 步骤：明确结束条件，遍历层，遍历层上不同状态，添加剪枝条件.
5. balance法见回溯NO.001 checkValid函数:遍历记录.
6. 行:row; 列:col; 初始的输入:input.

一、回溯
  NO.001 列举左右括号匹配情况
  NO.002 8皇后
  NO.003 0-1背包
  NO.004 正则匹配

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

// 有剪枝版本
void find(string& input, int pos, int leftP, int rightP, vector<string>& res) {
  if (pos == input.length()) {
    if (leftP == rightP) {
      res.push_back(input);
    }
    return;
  }
  if (leftP < input.length() / 2) {
    input[pos] = '(';
    find(input, pos + 1, leftP + 1, rightP, res);
  }
  if (leftP > rightP) {
    input[pos] = ')';
    find(input, pos + 1, leftP, rightP + 1, res);
  }
}


/***************************************
 * 回溯 NO.002
 * n-queens 
 ***************************************/
vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> res;
  vector<string> input(n, string(n, '.')); // 注意:不用'='初始化
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
  for (int i = row - 1; i >= 0; i--) {
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
 * partition-equal-subset-sum 在数组中能否找到一些数的和正好是数组所有数据和的一半 (0-1背包问题变种) 
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
  sum /= 2; // 找nums中数不超过sum的最大值，如果是sum/2就是true，背包问题变种.
  vector<vector<int>> mem(nums.size(), vector<int>(20000, -1)); // 20000是所有物品重量加起来的最大值
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


/***************************************
 * 回溯 NO.004
 * regular-expression-matching
 * 正则表达式: '*'匹配0-n个字符 '?'匹配0-1个字符
 * bool match = false;
 * rmatch(0, 0, text, pattern, match); // text文本 pattern正则
 * void rmatch(int ti, int pi, string text, string pattern, bool& match) {
 *   if (match == true) return; // 注意这里必须，要不可能会被其他false结果覆盖
 *   if (pi == pattern.length()) { // 正则匹配要以pattern结束作为结束条件
 *     if (ti == text.length()) {
 *       match == true;
 *     }
 *     return;
 *   }
 *   if (pattern[pi] == '*') {
 *     for (int i = 0; i <= text.lenght() - ti; i++) {
 *       rmatch(ti + i, pi + 1, text, pattern, match);
 *     }
 *   }else if (pattern[pi] == '?') {
 *     rmatch(ti, pi + 1, text, pattern, match);
 *     rmatch(ti + 1, pi + 1, text, pattern, match);
 *   }else {
 *     if (ti < text.length() && text[ti] == pattern[pi]) {
 *       rmatch(ti + 1, pi + 1, text, pattern, match);
 *     }  
 *   }
 * }
 *
 * 下面这道题比较麻烦 '*' 表示其在pattern中前一个字符可以出现0-n次
 * '.' 表示可以匹配一个任意字符.
 * 结束条件，text走完pattern没有走完的情况下不一定不匹配，因为pattern
 * 中*会作废前一个字符串. text = a ; pattern = ab*; 遍历pattern，处理
 * 各种状态：这里状态有点多。如果是'.'就都前进一个，但是如果下一pattern
 * 是'*'就需要处理作废当前pattern的情况；如果是字符就看是否相等，也要处理
 * 下一个pattern是'*'的时候作废当前pattern的情况.
 *  如果当前是'*',需要枚举pattern中'*'前一个字符出现1-n的情况,0的情况在
 * '.'和字符的时候单独处理了. 
 ***************************************/
void rMatch(string& text, string& pattern, int ti, int pi, bool& match) {
  if (match == true) { // 注意一定要加，不然会被后面计算的不符合的情况覆盖结果
    return;
  }
  if (pi == pattern.length()) {
    if (ti == text.length()) {
      match = true;
    }
    return;
  }   
  if (pattern[pi] == '.') {
    rMatch(text, pattern, ti + 1, pi + 1, match);
    if (pi < pattern.length() - 1 && pattern[pi + 1]  == '*') {
      rMatch(text, pattern, ti, pi + 2, match);
    }
  }else if (pattern[pi] == '*') {
    rMatch(text, pattern, ti, pi + 1, match);
    if (pi > 0) {
      for (int i = ti; i < text.length(); i++) {
        if (text[i] != pattern[pi - 1] && pattern[pi - 1] != '.') {
	  break;
	}
        rMatch(text, pattern, i + 1, pi + 1, match);
      }
    }
  }else {
    if (ti < text.length() && text[ti] == pattern[pi]) {
      rMatch(text, pattern, ti + 1, pi + 1, match);
    }
    if (pi < pattern.length() - 1 && pattern[pi + 1]  == '*') {
      rMatch(text, pattern, ti, pi + 2, match);
    }
  }
}


二、动态规划
  NO.001 0-1背包 "类型一"
  NO.002 棋盘最短距离[0-1背包类]
  NO.003 找零钱问题 "类型二"
  NO.004 三角形顶到底最小距离[0-1背包类]
  NO.005 最大乘积子数组[0-1背包类]
  NO.006 最长递增子序列[0-1背包类]
  NO.007 最长公共子数组 最长公共子串"类型三" 
  NO.008 两个字符串问最少改动多少两个字符串可以一样 最长公共子序列"类型三"

0. 回溯是递归+备忘录，自顶向下的计算(叶子结点才是结果); DP是for遍历，自底向上的计算(每一步都是结果)，需要定义状态及状态转移方程
1. [背包类问题]根据输入数据(数组)下标递归，动态规划的状态转移方程f(x,y)=...其中x是下标y是状态,例如问题NO.001 NO.002
2. [找零钱类问题]根据目标结果递归，动态规划的状态转移方程f(x)=...其中x是目前结果同时也是状态，例如问题NO.003
3. [最长公共子数组/子序列类问题], 二维的点为每一步,状态为当前点对应的结果.
4. 确定是背包类问题还是找零钱类问题的方法是看结果是否和输入数据的下标有关系,有关系切无后效性(f(i+1)只和f(i)有关系)就是背包类，否则
   是找零钱类。背包类问题回溯备忘录只需要记录是否走过，找零钱类问题需要记录具体的值,递归需要返回值。
5. 找零钱类问题需要用多个值来标记状态：访问过，没有值，有值...
6. 对于f(i)需要通过f(i-1)计算的情况，可以安排哨兵，用于计算结果的res可以申请为input.size()+1，这样res[0]就可以作为哨兵，不担心越界
   或者可以对边界单独计算,如题NO.007 NO.008
7. 对于maxVal minVal的初始化，要根据题目的情况来，例如最长、最大子串、序列等初始为0即可。
8. 子序列:subsequence不连续, subarray子数组、子串是连续的。不连续的情况f(i)的值不满足的条件的时候需要初始化，不能继承f(i-1)的值
/***************************************
 * DP NO.001
 * partition-equal-subset-sum (0-1背包问题变种) 
 * 
 * 0-1背包
 * weight:物品重量 n:物品个数 w:背包可承受重量 求weight中可以装进背包的最大质量
 * 举例: weight: 2, 2, 3  w: 5
 *     质量 0 1 2 3 4 5          0 1 2 3 4 5         0 1 2 3 4 5         0 1 2 3 4 5 
 * 物品0(2) 0 0 0 0 0 0  i=0 0(2)1 0 1 0 0 0 i=1 0(2)1 0 1 0 0 0 i=2 0(2)1 0 1 0 0 0
 *     1(2) 0 0 0 0 0 0  --> 1(2)0 0 0 0 0 0 --> 1(2)1 0 1 0 1 0 --> 1(2)1 0 1 0 1 0 --> return 5
 *     2(3) 0 0 0 0 0 0      2(3)0 0 0 0 0 0     2(3)0 0 0 0 0 0     2(3)1 0 1 1 1 1
 *
 * int knapsack(vector<int> weight, int n, int w) {
 *   vector<vector<bool>> states(n, vector<int>(w + 1, false));
 *   states[0][0] = true;
 *   if (weight[0] <= w) states[0][weight[0]] = true;  
 *   for (int i = 1; i < n; i++) {
 *     for (int k = 0; k <= w; k++) {
 *       if (states[i-1][k]] == true) { 
 *         states[i][k] = true; // 不装第i个物品
 *         if (k <= w - weight[i]) {
 *           states[i][k + weight[i]] == true; // 装第i个物品
 *         }
 *       }
 *     }
 *   }
 *   for (int i = w; i >= 0; i++) { // 输出结果
 *     if (states[n-1][i] == true) return i; 
 *   }
 * }
 * 
 * 状态压缩版本：下一层的状态依赖于上一层而不需要再之前的层的状态，所以可以用一个一维数组存储状态
 * int knapsack(vector<int> weight, int , int w) {
 *   vector<bool> states(w + 1, false);
 *   states[0] = true; 
 *   if (weight[0] <= w) states[weight[0]] = true;
 *   for (int i = 1; i < n; i++) {
 *     for (int j = w - weight[i]; j >= 0; j--) {
 *       if (states[j] == true) states[j + weight[i]] = true;
 *     }    
 *   }
 *   for (int i = w; i >= 0; i++) {
 *     if (states[i] == true)  return i;
 *   }
 * }  
 ***************************************/
bool canPartition(vector<int>& nums) {//和回溯解法略不同
  int sum = 0;
  for (auto n : nums) {
    sum += n;
  }        
  if (sum & 1 != 0) return false; //如果和不是偶数一半是小数，不可能有整数的和是小数
  sum /= 2; 
  vector<bool> states(sum + 1, false);
  states[0] = true;
  if (states[nums[0]] <= sum) states[nums[0]] == true;
  for (int i = 1; i < nums.size(); i++) {
    for (int j = sum - nums[i]; j >= 0; j--) {
      if (states[j] == true) states[j + nums[i]] = true; 
    }
  }
  return states[sum];
}


/***************************************
 * DP NO.002
 * minimum-path-sum 棋盘最短距离：求棋盘起点到终点的最短路径，每次只能往下或者往后走一步。
 *
 * 1, 3, 1
 * 1, 5, 1  --> 7 : 1,3,1,1,1
 * 4, 2, 1  
 * 
 * 回溯或者DP来解(distance[i,j]只和distance[i-1,j],distance[i,j-1]有关,所以可以用DP)
 * 状态转换方程: d[i,j] = min(d[i-1][j], d[i][j-1]) + grid[i][j]; 第一行、第一列单独算 
 ***************************************/
int minPathSum(vector<vector<int>>& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) {
    return 0;
  }
  vector<vector<int>> res(grid.size(), vector<int>(grid[0].size(), 0));
  res[0][0] = grid[0][0]; // 初始化(0,0), 需要加grid.size()判断
  for (int i = 1; i < (int)grid.size(); i++) { //初始化第一行距离
    res[i][0] = res[i-1][0] + grid[i][0]; 
  }
  for (int j = 1; j < (int)grid[0].size(); j++) { //初始化第一列距离
    res[0][j] = res[0][j-1] + grid[0][j];
  }
  for (int i = 1; i < grid.size(); i++) { //DP方程
    for (int j = 1; j < grid[i].size(); j++) {
	res[i][j] = min(res[i-1][j], res[i][j-1]) + grid[i][j];
    }
  }
  return res[grid.size() - 1][grid[0].size() - 1]; //返回注意需要加grid.size()判断在最开始
}
// 回溯解法,下面解法会超时，需要通过备忘录来避免重复状态的计算，但是这里的状态是(i,j,distance),
// distance需要可以枚举才可以，题目没有说明，不过可以将i,j --> id=i*j+j key为id,然后set值存distance,
// 没有访问过的状态不在, id对应的set中，不过比较麻烦，这种优先使用DP来解。
int minPathSum(vector<vector<int>>& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) {
    return 0;
  }
  int minVal = INT_MAX;
  find(grid, 0, 0, minVal, 0);
  return minVal;
}
void find(vector<vector<int>>& grid, int i, int j, int& minVal, int distance) {
  if (i == grid.size() - 1 && j == grid[i].size() - 1) {
    minVal = min(minVal, distance + grid[i][j]);
    return;
  }
  if (i >= grid.size() || j >= grid[i].size()) {
    return;
  }
  find(grid, i+1, j, minVal, distance + grid[i][j]);
  find(grid, i, j+1, minVal, distance + grid[i][j]);
}


/***************************************
 * DP NO.003
 * coin-change
 * 
 * 找零钱问题 首先是回溯解法 回溯通过结果目标值来递归，即要找的钱数
 * 如果有1,2,3面值的钱，要求找6的最少硬币数：
 * f(6) = min{f(6-c1), f(6-c2), f(6-c3)} + 1
 *      = min{f((6-1)), f(6-2), f(6-3)} + 1
 *      = min{f(5), f(4), f(3)} + 1 = ...
 * f(3) = min{f(2), f(1), f(0)) + 1
 * f(4) = ... f(5) = ...
 * f(2) = min{f(1), f(0), f(-1)} + 1  
 * f(0) = 0 f(小于0) = -1 
 ***************************************/
int coinChange(vector<int>& coins, int amount) {
  // 注意要记录状态：没有访问0  找不开-1  找开了>0
  vector<int> res(amount + 1, 0); //这里存在f(6)，下标从0开始，需要数组大小+1        
  return find(coins, amount, res); 
}
int find(vector<int>& coins, int aim, vector<int>& res) {
  if (aim < 0) { // 找不开
    return -1;
  }
  if (aim == 0) { // 找开了
    return 0;
  }
  if (res[aim] != 0) { // 已经计算过了,直接返回值
    return res[aim]; 
  }
  int minVal = INT_MAX;
  for (auto c : coins) {
    int r = find(coins, aim - c, res);
    if (r != -1) { // 注意找不开回返回-1,不能计入结果
      minVal = min(r, minVal);
    }
  }
  if ( minVal != INT_MAX) { //防止coins空的时候返回INT_MAX 
    res[aim] = minVal + 1;
  }else { // 找不开
    res[aim] = -1;
  }
  return res[aim];
}

int coinChange(vector<int>& coins, int amount) {
  vector<int> res(amount + 1, 0);
  for (int i = 1; i <= amount; i++) {
    int minVal = INT_MAX;
    for (auto c : coins) {
      if ((i - c) >= 0 && res[i-c] != -1) { // 找不开就不计入最小结果计算
        minVal = min(minVal, res[i-c]);   
      }
    }
    if (minVal != INT_MAX) {
      res[i] = minVal + 1;
    }else { // 这里一定要注意找不开的时候也要赋值，因为题目要求不匹配为-1，初始化的是0
      res[i] = -1;
    } 
  }
  return res[amount];
}


/***************************************
 * DP NO.004
 * triangle 三角形从顶到底最短距离, 每次只能往下一层相邻节点走
 * f(i,j) = min{f(i-1, j), f(i-1, j-1)} + a(i, j) 所以两边要特殊处理
 * 下一层只和上一层状态相关，所以可以状态压缩，状态是距离
 ***************************************/
int minimumTotal(vector<vector<int>>& triangle) {
  if (triangle.size() <= 0 || triangle[triangle.size() - 1].size() <= 0) {
    return 0;
  }
  vector<int> res(triangle[triangle.size()-1].size(), 0);
  res[0] = triangle[0][0];
  for (int i = 1; i < triangle.size(); i++) {
    for (int j = triangle[i].size() - 1; j >= 0; j--) {
      if (j == triangle[i].size() - 1) {
        res[j] = res[j-1] + triangle[i][j];
      }else if (j > 0 && j < triangle[i].size() - 1) {
        res[j] = min(res[j-1], res[j]) + triangle[i][j]; 
      }else {
        res[j] = res[j] + triangle[i][j];
      } 
    }
  }
  int minVal = INT_MAX;
  for (auto v : res) {
    minVal = min(minVal, v);
  }  
  return minVal;
}

/***************************************
 * DP NO.005
 * maximum-product-subarray 最大乘积子数组[连续subarray]
 * 0-1背包类问题，可以通过下标递归状态且是无后效性的：当前的数是正数，当前值为前一个数记录的正的最大值*当前的数;
 * 当前的数如果是负数，当前的值为前一个数记录的负的最小值*当前的数:
 * F(i) = f(i-1).positveMax * a[i] if(a[i] >= 0) f(i).positiveMax = f(i-1).positiveMax*a[i] f(i).negativeMin = f(i-1).negativeMin*a[i]
 *      = f(i-1).negativeMin * a[i] if (a[i] <= 0) f(i).posiveMax = f(i-1).negativeMin*a[i] f(i).negativeMin = f(i-1).positiveMax*a[i]
 * 注意：int相乘需要用double存; 注意前一个数的计算最大最小值为0的情况，这样乘以当前数会变0，最大值应该是当前数. 
 * **************************************/
int maxProduct(vector<int>& nums) {
  if (nums.size() <= 0) {
    return 0;
  }
  if (nums.size() == 1) {
    return nums[0];
  }  
  vector<vector<double>> res(nums.size(), vector<double>(2, 0));
  if (nums[0] >= 0) {
    res[0][0] = nums[0];
    res[0][1] = 0;
  }
  if (nums[0] <= 0) {
    res[0][0] = 0;
    res[0][1] = nums[0]; 
  }
  for (int i = 1; i < nums.size();  i++) {
    if (nums[i] >= 0) {
      res[i][0] = max((double)nums[i], res[i-1][0] * nums[i]); //注意这里最好用max 支持输入是分数的情况，另外就是前一个数res==0的情况
      res[i][1] = min((double)nums[i], res[i-1][1] * nums[i]); //注意这里最好用min
    }
    if (nums[i] <= 0) {
      res[i][0] = max((double)nums[i], res[i-1][1] * nums[i]);
      res[i][1] = min((double)nums[i], res[i-1][0] * nums[i]);
    }
  }
  double maxVal = LONG_MIN;
  for (auto r : res) {
    maxVal = max(r[0], maxVal);
  }
  return maxVal;
}

/***************************************
 * DP NO.006
 * longest-increasing-subsequence 最长递增子序列 [0-1背包类问题]
 * 根据下标递归满足无后效性, if(a[i] > a[i-1]) f(i) = f(i-1) + 1 else f(i) = f(i-1) | f(i) = 0可以计算连续
 * f(i)最终值为之前元素之行上面公式的最大值
 * **************************************/
int lengthOfLIS(vector<int>& nums) {
  if (nums.size() <= 0) {
    return 0;
  } 
  if (nums.size() == 1) {
    return 1;
  } 
  vector<int> res(nums.size(), 1);
  int maxVal = INT_MIN; // 设置为1 就可以去掉上面nums.size() == 1的判断
  for (int i = 1; i < nums.size(); i++) {
    int maxV = INT_MIN;
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        maxV = max(res[j] + 1, maxV);
      }else {
        maxV = max(res[j], maxV);
      }
    }
    res[i] = maxV;
    maxVal = max(res[i], maxVal);
  }
  return maxVal; 
}

/***************************************
 * DP NO.007
 * maximum-length-of-repeated-subarray (max common subarray)
 * 状态转移是二维的，主要输入是两个数组
 * f(i,j) = 0 注意这里不能等于:f(i-1, j-1)如果等于就会得出不连续的公共长度 if (a[i] != b[j])
 *        = f(i-1, j-1) + 1 if (a[i] == b[j])
 * 初始第一行、第一列需要单独计算 
 * 不可以状态压缩，使用一维数组来保存上一层的状态,需要j从后往前算，但是此题中从后往前字符串就相当于变了. 0111 != 1110
 * 匹配的最大公共子串也会变
 ****************************************/
int findLength(vector<int>& A, vector<int>& B) {
  vector<vector<int>> res(A.size() + 1, vector<int>(B.size() + 1, 0));
  int maxVal = 0; // 这里maxVal 0 不是INT_MIN，避免都不匹配的时候返回INT_MIN
  for (int i = 1; i <= (int)A.size(); i++) { // 注意size()是无符号，-1操作空的时候会越界
    for (int j = 1; j <= (int)B.size(); j++) {
      if (A[i-1] == B[j-1]) {
        if (i == 1 || j == 1) {
	  res[i][j] = 1;
	}else {
	  res[i][j] = res[i-1][j-1] + 1; //这有i-1,i不能从0开始，从1开始，res需要input.size()+1, input的访问需要-1对应
	}
        maxVal = max(maxVal, res[i][j]);
      }
    }
  }
  return maxVal;
}

/***************************************
 * DP NO.008
 * delete-operation-for-two-strings (longest common sequence LCS) 两个字符串一次操作可以删除一个字符，
 * 问多少个操作可以使两个字符串相同，其实是LCS问题
 * 状态转移是二维的，主要是因为输入是两个数组
 * f(i, j) = f(i-1, j-1) + 1 if (a[i] == b[j])
 *         = max(f(i-1,j), f(i, j-1)) if (a[i] != b[j]) 
 ****************************************/
int minDistance(string word1, string word2) {
  vector<vector<int>> res(word1.size() + 1, vector<int>(word2.size() + 1, 0));
  int maxVal = 0; // LCS大小 
  for (int i = 1; i <= (int)word1.size(); i++) {
    for (int j = 1; j <= (int)word2.size(); j++) {
      if (word1[i-1] == word2[j-1]) { // 加入哨兵后res[i]对应input[i-1]
        res[i][j] = res[i-1][j-1] + 1;
      }else {
	res[i][j] = max(res[i-1][j], res[i][j-1]);
      }
    }
  }
  if (word1.size() == 0 || word2.size() == 0) {
    return word1.size() + word2.size();
  }
  maxVal = res[word1.size()][word2.size()];
  // 输出LCS内容
  //int i = word1.size(); 
  //int j = word2.size();
  //while (i >= 1 && j >= 1) {
  //  if (word1[i-1] == word2[j-1]) {
  //    lcs.push(word1[i-1]);
  //    i--;
  //    j--;
  //  }else if (res[i-1][j] >= res[i][j-1]) {
  //    i--;
  //  }else {
  //    j--;
  //  }
  // }
  //while (!lcs.empty()) {
  //  cout << lcs.top();
  //  lcs.pop();
  //}  
  return (word1.size() - maxVal + word2.size() - maxVal); 
}

