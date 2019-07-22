/* https://leetcode.com/problems/xxx */

���ݱ�������&����:
0. ����һ��ʹ�õݹ�ʵ��.
1. �������ⶼ���Էֳɶ���׶�(�׶����������Ĳ�), ÿһ�׶�(��)���ж��״̬��ͨ�����ݿ���ö������״̬(���������в��ϵ�״̬). 
   �׶εĻ��֣�1) �����һλ(��)Ϊһ�㣻2) ��ά�����һ��Ϊһ��; 3) ������һ��(��Ӧ�����)Ϊһ��, ����(i+1,j)(i,j+1):б��; 4)һ������ֵ
   ��Ϊһ��״̬��������¥��(¥�ݲ���)������Ǯ��Ŀ��Ǯ����쳲�������(Ŀ����). 
2. һ����Ҫִ�������еĽ׶κ���ܵó����(�����ڴӸ���㵽���е�Ҷ�ӽ��), �����ھ�һЩ��֦��������ִ�й��̱����Ѿ������������Ľ׶�״̬
   ����ִ��, �������ظ�����. ��Щ�������8�ʺ�����еļ�֦������������������������Խ׶ν����ǵ�״̬���ǽ������Щ�����������ƥ������
   ���̼�֦�������׶ε�״̬Ҳ��ҪУ���Ƿ�����������. ��Щʱ���������뵽��֦�������������׶���У��״̬�Ƿ�������,��������ƥ����
   ��ĵ�һ�ֽⷨ.
3. ����¼: ����ʹ�ñ���¼����¼�߹���״̬���Ӷ��ﵽ��֦��Ч���������ظ����㣬���ǱȽ��ʺ�ÿһ���״̬�ô��ݼ�¼�����(���ݹ麯�����÷���
   ֵ����¼������¼��, ״̬һ��һ�㴫�ݵ����׶κ�ᱻ�������У���������¼ֻ��Ҫ��¼:���ʹ�|û�з��ʹ� ����״̬���ɣ�������ս������
   ���Ƿ��з��������Ľ��������true|false ����Ҫ��¼����״̬�����ʹ��н��|���ʹ�û�н��|û�з��ʹ� ����״̬). ���򷵻�ֵ��Ƚ�����ƣ�
   ��Ϊ�з���ֵ�Ļ�һ���һ��״̬���Ӧ���Ҷ�ӽ��״̬����Ҫ����¼����pk��һ�����ӱ���¼�ó�״̬��Ҫ���������ϲ�Ľ���У���Ƚ��鷳.
   һ�㱸��¼�Ͳ��ձ������⼴��(Ҷ��״̬�����һ��ֵ�Ƚ�����¼����ֱ�Ӽ�¼)����Ȼʹ��DP�Ͳ���Ҫ������Щ. 
   ����0-1���������У�items(2,2,2)    f(0,0)
                                   /         \
			       f(1,0)        f(1,2)
			       /   \          /     \
		          f(2,0)  f[2,2]    f[2,2]   f(2,4)
		          /  \    /   \      /   \    /   \
	               (3,0)[3,2][3,2]{3,4}[3,2]{3,4}{3,4}(3,6)     
   ��ʼ����ʱ��(0,0)0λ��ʱ����ѡ+��ѡ����(1,0) (1,2),1λ��ʱ�������֣��������ظ���[2,2]��[2,2]���յõ���
   maxVal��ͬ�������mem��¼�����״̬,״̬��ͬ�ľͲ������ˡ�ע������f[2,2]��ֵ���Ƿ�����f(1,0) f(1,2)��
   �أ�f[2,2]���ն����ͬһ��ֵ, �ݹ����Զ����£������Ҷ�ӽ�㣬��f(1,0) f(1,2)��Ӧ��f[2,2]����Ҷ�ӽ��ֵ
   ��ͬ������һ�ּ�¼״̬��û���ʹ���Ϊ��ʼֵ�����ʹ��ļ�¼Ϊ���ն��Ҷ�ӽ���pk��һ�������������Ҫ�ݹ�
   ��������ֵ�����Ҷ��Ҷ�ӽ���ֵҲ��Ҫpk��һ����һ�㲻�Ƽ����������Ƚϸ��ӡ�
4. ���裺��ȷ���������������㣬�������ϲ�ͬ״̬����Ӽ�֦����.
5. balance��������NO.001 checkValid����:������¼.
6. ��:row; ��:col; ��ʼ������:input.

һ������
  NO.001 �о���������ƥ�����
  NO.002 8�ʺ�
  NO.003 0-1����
  NO.004 ����ƥ��

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
  vector<string> input(n, string(n, '.')); // ע��:����'='��ʼ��
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
 * partition-equal-subset-sum ���������ܷ��ҵ�һЩ���ĺ������������������ݺ͵�һ�� (0-1�����������) 
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
  sum /= 2; // ��nums����������sum�����ֵ�������sum/2����true�������������.
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
 *   if (pi == pattern.length()) { // ����ƥ��Ҫ��pattern������Ϊ��������
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
 * ���������Ƚ��鷳 '*' ��ʾ����pattern��ǰһ���ַ����Գ���0-n��
 * '.' ��ʾ����ƥ��һ�������ַ�.
 * ����������text����patternû�����������²�һ����ƥ�䣬��Ϊpattern
 * ��*������ǰһ���ַ���. text = a ; pattern = ab*; ����pattern������
 * ����״̬������״̬�е�ࡣ�����'.'�Ͷ�ǰ��һ�������������һpattern
 * ��'*'����Ҫ�������ϵ�ǰpattern�������������ַ��Ϳ��Ƿ���ȣ�ҲҪ����
 * ��һ��pattern��'*'��ʱ�����ϵ�ǰpattern�����.
 *  �����ǰ��'*',��Ҫö��pattern��'*'ǰһ���ַ�����1-n�����,0�������
 * '.'���ַ���ʱ�򵥶�������. 
 ***************************************/
void rMatch(string& text, string& pattern, int ti, int pi, bool& match) {
  if (match == true) { // ע��һ��Ҫ�ӣ���Ȼ�ᱻ�������Ĳ����ϵ�������ǽ��
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


������̬�滮
  NO.001 0-1���� "����һ"
  NO.002 ������̾���[0-1������]
  NO.003 ����Ǯ���� "���Ͷ�"
  NO.004 �����ζ�������С����[0-1������]
  NO.005 ���˻�������[0-1������]
  NO.006 �����������[0-1������]
  NO.007 ����������� ������Ӵ�"������" 
  NO.008 �����ַ��������ٸĶ����������ַ�������һ�� �����������"������"

0. �����ǵݹ�+����¼���Զ����µļ���(Ҷ�ӽ����ǽ��); DP��for�������Ե����ϵļ���(ÿһ�����ǽ��)����Ҫ����״̬��״̬ת�Ʒ���
1. [����������]������������(����)�±�ݹ飬��̬�滮��״̬ת�Ʒ���f(x,y)=...����x���±�y��״̬,��������NO.001 NO.002
2. [����Ǯ������]����Ŀ�����ݹ飬��̬�滮��״̬ת�Ʒ���f(x)=...����x��Ŀǰ���ͬʱҲ��״̬����������NO.003
3. [�����������/������������], ��ά�ĵ�Ϊÿһ��,״̬Ϊ��ǰ���Ӧ�Ľ��.
4. ȷ���Ǳ��������⻹������Ǯ������ķ����ǿ�����Ƿ���������ݵ��±��й�ϵ,�й�ϵ���޺�Ч��(f(i+1)ֻ��f(i)�й�ϵ)���Ǳ����࣬����
   ������Ǯ�ࡣ������������ݱ���¼ֻ��Ҫ��¼�Ƿ��߹�������Ǯ��������Ҫ��¼�����ֵ,�ݹ���Ҫ����ֵ��
5. ����Ǯ��������Ҫ�ö��ֵ�����״̬�����ʹ���û��ֵ����ֵ...
6. ����f(i)��Ҫͨ��f(i-1)�������������԰����ڱ������ڼ�������res��������Ϊinput.size()+1������res[0]�Ϳ�����Ϊ�ڱ���������Խ��
   ���߿��ԶԱ߽絥������,����NO.007 NO.008
7. ����maxVal minVal�ĳ�ʼ����Ҫ������Ŀ��������������������Ӵ������еȳ�ʼΪ0���ɡ�
8. ������:subsequence������, subarray�����顢�Ӵ��������ġ������������f(i)��ֵ�������������ʱ����Ҫ��ʼ�������ܼ̳�f(i-1)��ֵ
/***************************************
 * DP NO.001
 * partition-equal-subset-sum (0-1�����������) 
 * 
 * 0-1����
 * weight:��Ʒ���� n:��Ʒ���� w:�����ɳ������� ��weight�п���װ���������������
 * ����: weight: 2, 2, 3  w: 5
 *     ���� 0 1 2 3 4 5          0 1 2 3 4 5         0 1 2 3 4 5         0 1 2 3 4 5 
 * ��Ʒ0(2) 0 0 0 0 0 0  i=0 0(2)1 0 1 0 0 0 i=1 0(2)1 0 1 0 0 0 i=2 0(2)1 0 1 0 0 0
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
 *         states[i][k] = true; // ��װ��i����Ʒ
 *         if (k <= w - weight[i]) {
 *           states[i][k + weight[i]] == true; // װ��i����Ʒ
 *         }
 *       }
 *     }
 *   }
 *   for (int i = w; i >= 0; i++) { // ������
 *     if (states[n-1][i] == true) return i; 
 *   }
 * }
 * 
 * ״̬ѹ���汾����һ���״̬��������һ�������Ҫ��֮ǰ�Ĳ��״̬�����Կ�����һ��һά����洢״̬
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
bool canPartition(vector<int>& nums) {//�ͻ��ݽⷨ�Բ�ͬ
  int sum = 0;
  for (auto n : nums) {
    sum += n;
  }        
  if (sum & 1 != 0) return false; //����Ͳ���ż��һ����С�����������������ĺ���С��
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
 * minimum-path-sum ������̾��룺��������㵽�յ�����·����ÿ��ֻ�����»���������һ����
 *
 * 1, 3, 1
 * 1, 5, 1  --> 7 : 1,3,1,1,1
 * 4, 2, 1  
 * 
 * ���ݻ���DP����(distance[i,j]ֻ��distance[i-1,j],distance[i,j-1]�й�,���Կ�����DP)
 * ״̬ת������: d[i,j] = min(d[i-1][j], d[i][j-1]) + grid[i][j]; ��һ�С���һ�е����� 
 ***************************************/
int minPathSum(vector<vector<int>>& grid) {
  if (grid.size() == 0 || grid[0].size() == 0) {
    return 0;
  }
  vector<vector<int>> res(grid.size(), vector<int>(grid[0].size(), 0));
  res[0][0] = grid[0][0]; // ��ʼ��(0,0), ��Ҫ��grid.size()�ж�
  for (int i = 1; i < (int)grid.size(); i++) { //��ʼ����һ�о���
    res[i][0] = res[i-1][0] + grid[i][0]; 
  }
  for (int j = 1; j < (int)grid[0].size(); j++) { //��ʼ����һ�о���
    res[0][j] = res[0][j-1] + grid[0][j];
  }
  for (int i = 1; i < grid.size(); i++) { //DP����
    for (int j = 1; j < grid[i].size(); j++) {
	res[i][j] = min(res[i-1][j], res[i][j-1]) + grid[i][j];
    }
  }
  return res[grid.size() - 1][grid[0].size() - 1]; //����ע����Ҫ��grid.size()�ж����ʼ
}
// ���ݽⷨ,����ⷨ�ᳬʱ����Ҫͨ������¼�������ظ�״̬�ļ��㣬���������״̬��(i,j,distance),
// distance��Ҫ����ö�ٲſ��ԣ���Ŀû��˵�����������Խ�i,j --> id=i*j+j keyΪid,Ȼ��setֵ��distance,
// û�з��ʹ���״̬����, id��Ӧ��set�У������Ƚ��鷳����������ʹ��DP���⡣
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
 * ����Ǯ���� �����ǻ��ݽⷨ ����ͨ�����Ŀ��ֵ���ݹ飬��Ҫ�ҵ�Ǯ��
 * �����1,2,3��ֵ��Ǯ��Ҫ����6������Ӳ������
 * f(6) = min{f(6-c1), f(6-c2), f(6-c3)} + 1
 *      = min{f((6-1)), f(6-2), f(6-3)} + 1
 *      = min{f(5), f(4), f(3)} + 1 = ...
 * f(3) = min{f(2), f(1), f(0)) + 1
 * f(4) = ... f(5) = ...
 * f(2) = min{f(1), f(0), f(-1)} + 1  
 * f(0) = 0 f(С��0) = -1 
 ***************************************/
int coinChange(vector<int>& coins, int amount) {
  // ע��Ҫ��¼״̬��û�з���0  �Ҳ���-1  �ҿ���>0
  vector<int> res(amount + 1, 0); //�������f(6)���±��0��ʼ����Ҫ�����С+1        
  return find(coins, amount, res); 
}
int find(vector<int>& coins, int aim, vector<int>& res) {
  if (aim < 0) { // �Ҳ���
    return -1;
  }
  if (aim == 0) { // �ҿ���
    return 0;
  }
  if (res[aim] != 0) { // �Ѿ��������,ֱ�ӷ���ֵ
    return res[aim]; 
  }
  int minVal = INT_MAX;
  for (auto c : coins) {
    int r = find(coins, aim - c, res);
    if (r != -1) { // ע���Ҳ����ط���-1,���ܼ�����
      minVal = min(r, minVal);
    }
  }
  if ( minVal != INT_MAX) { //��ֹcoins�յ�ʱ�򷵻�INT_MAX 
    res[aim] = minVal + 1;
  }else { // �Ҳ���
    res[aim] = -1;
  }
  return res[aim];
}

int coinChange(vector<int>& coins, int amount) {
  vector<int> res(amount + 1, 0);
  for (int i = 1; i <= amount; i++) {
    int minVal = INT_MAX;
    for (auto c : coins) {
      if ((i - c) >= 0 && res[i-c] != -1) { // �Ҳ����Ͳ�������С�������
        minVal = min(minVal, res[i-c]);   
      }
    }
    if (minVal != INT_MAX) {
      res[i] = minVal + 1;
    }else { // ����һ��Ҫע���Ҳ�����ʱ��ҲҪ��ֵ����Ϊ��ĿҪ��ƥ��Ϊ-1����ʼ������0
      res[i] = -1;
    } 
  }
  return res[amount];
}


/***************************************
 * DP NO.004
 * triangle �����δӶ�������̾���, ÿ��ֻ������һ�����ڽڵ���
 * f(i,j) = min{f(i-1, j), f(i-1, j-1)} + a(i, j) ��������Ҫ���⴦��
 * ��һ��ֻ����һ��״̬��أ����Կ���״̬ѹ����״̬�Ǿ���
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
 * maximum-product-subarray ���˻�������[����subarray]
 * 0-1���������⣬����ͨ���±�ݹ�״̬�����޺�Ч�Եģ���ǰ��������������ǰֵΪǰһ������¼���������ֵ*��ǰ����;
 * ��ǰ��������Ǹ�������ǰ��ֵΪǰһ������¼�ĸ�����Сֵ*��ǰ����:
 * F(i) = f(i-1).positveMax * a[i] if(a[i] >= 0) f(i).positiveMax = f(i-1).positiveMax*a[i] f(i).negativeMin = f(i-1).negativeMin*a[i]
 *      = f(i-1).negativeMin * a[i] if (a[i] <= 0) f(i).posiveMax = f(i-1).negativeMin*a[i] f(i).negativeMin = f(i-1).positiveMax*a[i]
 * ע�⣺int�����Ҫ��double��; ע��ǰһ�����ļ��������СֵΪ0��������������Ե�ǰ�����0�����ֵӦ���ǵ�ǰ��. 
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
      res[i][0] = max((double)nums[i], res[i-1][0] * nums[i]); //ע�����������max ֧�������Ƿ�����������������ǰһ����res==0�����
      res[i][1] = min((double)nums[i], res[i-1][1] * nums[i]); //ע�����������min
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
 * longest-increasing-subsequence ����������� [0-1����������]
 * �����±�ݹ������޺�Ч��, if(a[i] > a[i-1]) f(i) = f(i-1) + 1 else f(i) = f(i-1) | f(i) = 0���Լ�������
 * f(i)����ֵΪ֮ǰԪ��֮�����湫ʽ�����ֵ
 * **************************************/
int lengthOfLIS(vector<int>& nums) {
  if (nums.size() <= 0) {
    return 0;
  } 
  if (nums.size() == 1) {
    return 1;
  } 
  vector<int> res(nums.size(), 1);
  int maxVal = INT_MIN; // ����Ϊ1 �Ϳ���ȥ������nums.size() == 1���ж�
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
 * ״̬ת���Ƕ�ά�ģ���Ҫ��������������
 * f(i,j) = 0 ע�����ﲻ�ܵ���:f(i-1, j-1)������ھͻ�ó��������Ĺ������� if (a[i] != b[j])
 *        = f(i-1, j-1) + 1 if (a[i] == b[j])
 * ��ʼ��һ�С���һ����Ҫ�������� 
 * ������״̬ѹ����ʹ��һά������������һ���״̬,��Ҫj�Ӻ���ǰ�㣬���Ǵ����дӺ���ǰ�ַ������൱�ڱ���. 0111 != 1110
 * ƥ�����󹫹��Ӵ�Ҳ���
 ****************************************/
int findLength(vector<int>& A, vector<int>& B) {
  vector<vector<int>> res(A.size() + 1, vector<int>(B.size() + 1, 0));
  int maxVal = 0; // ����maxVal 0 ����INT_MIN�����ⶼ��ƥ���ʱ�򷵻�INT_MIN
  for (int i = 1; i <= (int)A.size(); i++) { // ע��size()���޷��ţ�-1�����յ�ʱ���Խ��
    for (int j = 1; j <= (int)B.size(); j++) {
      if (A[i-1] == B[j-1]) {
        if (i == 1 || j == 1) {
	  res[i][j] = 1;
	}else {
	  res[i][j] = res[i-1][j-1] + 1; //����i-1,i���ܴ�0��ʼ����1��ʼ��res��Ҫinput.size()+1, input�ķ�����Ҫ-1��Ӧ
	}
        maxVal = max(maxVal, res[i][j]);
      }
    }
  }
  return maxVal;
}

/***************************************
 * DP NO.008
 * delete-operation-for-two-strings (longest common sequence LCS) �����ַ���һ�β�������ɾ��һ���ַ���
 * �ʶ��ٸ���������ʹ�����ַ�����ͬ����ʵ��LCS����
 * ״̬ת���Ƕ�ά�ģ���Ҫ����Ϊ��������������
 * f(i, j) = f(i-1, j-1) + 1 if (a[i] == b[j])
 *         = max(f(i-1,j), f(i, j-1)) if (a[i] != b[j]) 
 ****************************************/
int minDistance(string word1, string word2) {
  vector<vector<int>> res(word1.size() + 1, vector<int>(word2.size() + 1, 0));
  int maxVal = 0; // LCS��С 
  for (int i = 1; i <= (int)word1.size(); i++) {
    for (int j = 1; j <= (int)word2.size(); j++) {
      if (word1[i-1] == word2[j-1]) { // �����ڱ���res[i]��Ӧinput[i-1]
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
  // ���LCS����
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

