/* https://leetcode.com/problems/xxx */

���ݱ�������&����:
1. ����������ʾreturn.
2. balance��������NO.001 checkValid����:������¼.
3. ��:row; ��:col; ��ʼ������:input.
4. �������ⶼ���Էֳɶ���㣬ÿһ�㶼�ж��״̬��ͨ���ݹ�+���ݿ���ö������״̬(���������еĲ�) 
   �е����ַ�����һλΪһ�㣬�е��Ƕ�λ�����ÿһ����һ�㣬ÿһ�㶼�ж���ȡֵ�����ԡ�
5. �����п��Է���һЩ��������֦�������Լ����ظ��жϣ���Щ�������;�ж����Ľ�������ã���Щ���
   ��;���жϲ�����ȫ��������������������Ҫ�����������еĲ���ٴ�У���Ƿ�������������
6. ����ʹ�ñ���¼����¼�߹���״̬���������Ա�������ظ����㣬���ǱȽ��ʺ�ÿһ���״̬�ô��ݼ�¼�������
   ����0-1���������У�ÿһ���״̬�ǵ���ǰ�����ȡ��������(2,0) (2,2) (2,4)���ڶ��㼴�������λ��ʱ��
   ����ȡ��������Ϊ0,2,4����¼���������ظ�״̬���־Ϳ��Բ��ü��㣬��Ϊ�������״̬����maxVal���㵽���
   ��������ˡ�
7. ���裺��ȷ���������������㣬�������ϲ�ͬ״̬����Ӽ�֦����.

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

// �м�֦�汾
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


/***************************************
 * ���� NO.003
 * partition-equal-subset-sum (0-1�����������) 
 * 0-1��������: 
 * int maxVal = INT_MIN;
 * // vector<vector<int>> mem(item.size(), vector<int>(totalSumOfItems, -1));
 * solve01(vector<int>& items, int pos, int curW, int w, int& maxVal) {
 *   if (pos == (int)items.size() || curW == w) { // ע��: ����'res == w'��֦
 *     maxVal = max(maxVal, curW);
 *     return;
 *   }
 *   // if (mem[pos][curw] != -1) return; 
 *   solve01(items, pos + 1, curW, w, maxVal);
 *   if (curW + items[pos] <= w) { // ��֦
 *     solve01(items, pos + 1, curW + items[pos], w, maxVal);
 *   }
 *   // mem[pos][curW] = 1; // ���posλ������ΪcurW������Ѿ������maxVal
 * }
 * 
 * solve01(items, 0, 0, w);
 * 
 * ����¼�汾: ����ȥ��ע��
 *  
 ***************************************/
bool canPartition(vector<int>& nums) {
  double sum = 0;
  for (auto num : nums) {
    sum += num;
  }
  sum /= 2;
  vector<vector<int>> mem(nums.size(), vector<int>(20000, -1)); // 20000��������Ʒ���������������ֵ
  double maxVal = LONG_MIN;
  find(nums, 0, 0, sum, mem, maxVal); 
  return (maxVal == sum);
}

void find(vector<int>& nums, int pos, double curSum, double aimSum, vector<vector<int>>& mem, double& maxVal) {
  if (pos == (int)nums.size() || curSum == aimSum) {
    maxVal = max(curSum, maxVal); 
    return;  // ע��������Ҫreturn 
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
 * ���� NO.004
 * regular-expression-matching
 * ������ʽ: '*'ƥ��0-n���ַ� '?'ƥ��0-1���ַ�
 * bool match = false;
 * rmatch(0, 0, text, pattern, match); // text�ı� pattern����
 * void rmatch(int ti, int pi, string text, string pattern, bool& match) {
 *   if (match == true) return; // ע��������룬Ҫ�����ܻᱻ����false�������
 *   if (pi == pattern.length() || ti == text.lenght()) {
 *     match = ((pi == pattern.length()) && ti == text.length());
 *     return match;
 *   }
 *   if (pattern[pi] == '*') {
 *     for (int i = 0; i <= text.lenght() - ti; i++) {
 *       rmatch(ti + i, pi + 1, text, pattern, match);
 *     }
 *   }else if (pattern[pi] == '?') {
 *     rmatch(ti, pi + 1, text, pattern, match);
 *     rmatch(ti + 1, pi + 1, text, pattern, match);
 *   }else {
 *     if (text[ti] == pattern[pi]) {
 *       rmatch(ti + 1, pi + 1, text, pattern, match);
 *     }  
 *   }
 * }
 *
 * ���������Ƚ��鷳 '*' ��ʾ����pattern��ǰһ���ַ����Գ���0-n��
 * '.' ��ʾ����ƥ��һ�������ַ�.
 * ����������text����patternû�����������²�һ����ƥ�䣬��Ϊpattern
 * ��*������ǰһ���ַ���. text = a ; pattern = ab*; ����pattern������
 * ����״̬������״̬�е�ࡣ�����'.'�Ͷ�ǰ��һ�������������һpattern�
 * ��'*'����Ҫ�������ϵ�ǰpattern�������������ַ��Ϳ��Ƿ���ȣ�ҲҪ����
 * ��һ��pattern��'*'��ʱ�����ϵ�ǰpattern�����.
 *  �����ǰ��'*',��Ҫö��pattern��'*'ǰһ���ַ�����1-n�����,0�������
 * '.'���ַ���ʱ�򵥶�������. 
 ***************************************/
void rMatch(string& text, string& pattern, int ti, int pi, bool& match) {
  if (match == true) {
    return;
  }
  if (pi == pattern.length()) {
    if (ti == text.length()) {
      match = true;
      return;
    }
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
