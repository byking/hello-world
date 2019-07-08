/* https://leetcode.com/problems/xxx */

编码问题&技巧:
1. 函数必须显示return.
2. balance法见回溯NO.001 valid函数:遍历记录.


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
// 注意第一个参数不能引用传值
void find(string input, int pos, vector<string>& res) {
  if (pos == input.length()) {
    if (valid(input)) {
      res.push_back(input);
    }
  }else {
    input[pos] = '(';
    find(input, pos + 1, res);
    input[pos] = ')';
    find(input, pos + 1, res);
  }
}

bool valid(string& input) {
  int balance = 0;
  for (auto c : input) {
    if (c == '(') {
      balance ++;
    }else if (c == ')') {
      balance --;
    }
    if (balance < 0) {
      return false;
    }
  }
  return (balance == 0);
}


