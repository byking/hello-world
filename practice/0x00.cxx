/* https://leetcode.com/problems/xxx */

���ݱ�������&����:
1. ����������ʾreturn.
2. balance��������NO.001 checkValid����:������¼.
3. ��:row; ��:col; ��ʼ������:input.
4. checkVaild() �����ڻ��ݹ������жϣ�Ҳ������һ�ֽ�����������ж�.
   ͨ�õķ������ڹ����оͼ����жϣ��������Լ�֦���е��������NO.002
   �ʺ��ڹ������жϣ�������жϣ������е��������NO.001�������жϺ�
   ������ʱҲҪ�жϣ���Ϊ�����е��жϲ�����ȫ�жϲ�����.

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
// ע��:��һ�������������ô�ֵ(����ʹ�����ô���,��DFS�Ƚ�input��res)
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
  return (balance == 0); // ע�⣺��ʾreturn
}


/***************************************
 * ���� NO.002
 * n-queens 
 ***************************************/
vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> res;
  vector<string> input(n,string(n, '.')); // ע��:����'='��ʼ��
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
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // ע��:'&&' not ','
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
