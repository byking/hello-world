/* https://leetcode.com/problems/xxx */

��������&����:
1. ����������ʾreturn.
2. balance��������NO.001 valid����:������¼.


/***************************************
 * ���� NO.001
 * generate-parentheses
 ***************************************/
vector<string> generateParenthesis(int n) {
  vector<string> res;
  string input(2*n, ' ');
  find(input, 0, res);
  return res;
}

// ö�����е����, ÿһλ��ȡֵΪ'('��')'������������ҵ����������Ľ�
// ע���һ�������������ô�ֵ
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


