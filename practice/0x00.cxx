/* https://leetcode.com/problems/xxx */

»ØËİ±àÂëÎÊÌâ&¼¼ÇÉ:
1. º¯Êı±ØĞëÏÔÊ¾return.
2. balance·¨¼û»ØËİNO.001 checkValidº¯Êı:±éÀú¼ÇÂ¼.
3. ĞĞ:row; ÁĞ:col; ³õÊ¼µÄÊäÈë:input.
4. »ØËİÎÊÌâ¶¼¿ÉÒÔ·Ö³É¶à¸ö²ã£¬Ã¿Ò»²ã¶¼ÓĞ¶à¸ö×´Ì¬£¬Í¨¹ıµİ¹é+»ØËİ¿ÉÒÔÃ¶¾ÙËùÓĞ×´Ì¬(±éÀúÍêËùÓĞµÄ²ã) 
   ÓĞµÄÊÇ×Ö·û´®µÄÒ»Î»ÎªÒ»²ã£¬ÓĞµÄÊÇ¶şÎ»Êı×éµÄÃ¿Ò»ĞĞÊÇÒ»²ã£¬Ã¿Ò»²ã¶¼ÓĞ¶àÖÖÈ¡Öµ¿ÉÄÜĞÔ¡£
5. ¹ı³ÌÖĞ¿ÉÒÔ·¢¾òÒ»Ğ©Ìõ¼şÀ´¼ôÖ¦ÕâÑù¿ÉÒÔ¼õÉÙÖØ¸´ÅĞ¶Ï£¬ÓĞĞ©Çé¿öÔÚÖĞÍ¾ÅĞ¶Ï×îºóµÄ½á¹û¼´¿ÉÓÃ£¬ÓĞĞ©Çé¿ö
   ÖĞÍ¾µÄÅĞ¶Ï²»ÄÜÍêÈ«¾ö¶¨Âú×ã½âµÄÌõ¼ş£¬»¹ĞèÒª×îºó±éÀúÍêËùÓĞµÄ²ãºóÔÙ´ÎĞ£ÑéÊÇ·ñÂú×ã½âµÄÌõ¼ş¡£
6. ¿ÉÒÔÊ¹ÓÃ±¸ÍüÂ¼À´¼ÇÂ¼×ß¹ıµÄ×´Ì¬£¬ÕâÑù¿ÉÒÔ±ÜÃâ¸ü¶àÖØ¸´¼ÆËã£¬µ«ÊÇ±È½ÏÊÊºÏÃ¿Ò»²ãµÄ×´Ì¬ºÃ´«µİ¼ÇÂ¼µÄÇé¿ö£¬
   ÀıÈç0-1±³°üÎÊÌâÖĞ£¬Ã¿Ò»²ãµÄ×´Ì¬ÊÇµ½µ±Ç°²ã¿ÉÒÔÈ¡µ½µÄÖÊÁ¿(2,0) (2,2) (2,4)£¬µÚ¶ş²ã¼´Êı×éµÚÈıÎ»µÄÊ±ºò
   ¿ÉÒÔÈ¡µ½µÄÖÊÁ¿Îª0,2,4£¬¼ÇÂ¼ÏÂÀ´ÔÙÓĞÖØ¸´×´Ì¬³öÏÖ¾Í¿ÉÒÔ²»ÓÃ¼ÆËã£¬ÒòÎª¼ÆËã¹ıµÄ×´Ì¬×îºóµÄmaxVal¶¼Ëãµ½×îºó
   ½á¹ûÀïÃæÁË¡£
7. ²½Öè£ºÃ÷È·½áÊøÌõ¼ş£¬±éÀú²ã£¬±éÀú²ãÉÏ²»Í¬×´Ì¬£¬Ìí¼Ó¼ôÖ¦Ìõ¼ş.

/***************************************
 * »ØËİ NO.001
 * generate-parentheses
 ***************************************/
vector<string> generateParenthesis(int n) {
  vector<string> res;
  string input(2*n, ' ');
  find(input, 0, res);
  return res;
}

// Ã¶¾ÙËùÓĞµÄÇé¿ö, Ã¿Ò»Î»ÉÏÈ¡ÖµÎª'('¡¢')'Á½ÖÖÇé¿ö£¬²¢ÕÒµ½Âú×ãÌõ¼şµÄ½â
// ×¢Òâ:µÚÒ»¸ö²ÎÊı²»ÄÜÒıÓÃ´«Öµ(¿ÉÒÔÊ¹ÓÃÒıÓÃ´«µİ,ÊÇDFSÏÈ½«inputÈëres)
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
  return (balance == 0); // ×¢Òâ£ºÏÔÊ¾return
}

// ÓĞ¼ôÖ¦°æ±¾
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
 * »ØËİ NO.002
 * n-queens 
 ***************************************/
vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> res;
  vector<string> input(n,string(n, '.')); // ×¢Òâ:²»ÓÃ'='³õÊ¼»¯
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
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) { // ×¢Òâ:'&&' not ','
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
 * »ØËİ NO.003
 * partition-equal-subset-sum (0-1±³°üÎÊÌâ±äÖÖ) 
 * 0-1±³°üÎÊÌâ: 
 * int maxVal = INT_MIN;
 * // vector<vector<int>> mem(item.size(), vector<int>(totalSumOfItems, -1));
 * solve01(vector<int>& items, int pos, int curW, int w, int& maxVal) {
 *   if (pos == (int)items.size() || curW == w) { // ×¢Òâ: ¼ÓÉÏ'res == w'¼ôÖ¦
 *     maxVal = max(maxVal, curW);
 *     return;
 *   }
 *   // if (mem[pos][curw] != -1) return; 
 *   solve01(items, pos + 1, curW, w, maxVal);
 *   if (curW + items[pos] <= w) { // ¼ôÖ¦
 *     solve01(items, pos + 1, curW + items[pos], w, maxVal);
 *   }
 *   // mem[pos][curW] = 1; // ±ê¼ÇposÎ»ÖÃÖØÁ¿ÎªcurWµÄÇé¿öÒÑ¾­¼ÆËã¹ımaxVal
 * }
 * 
 * solve01(items, 0, 0, w);
 * 
 * ±¸ÍüÂ¼°æ±¾: ÉÏÃæÈ¥µô×¢ÊÍ
 *  
 ***************************************/
bool canPartition(vector<int>& nums) {
  double sum = 0;
  for (auto num : nums) {
    sum += num;
  }
  sum /= 2;
  vector<vector<int>> mem(nums.size(), vector<int>(20000, -1)); // 20000ÊÇËùÓĞÎïÆ·ÖØÁ¿¼ÓÆğÀ´µÄ×î´óÖµ
  double maxVal = LONG_MIN;
  find(nums, 0, 0, sum, mem, maxVal); 
  return (maxVal == sum);
}

void find(vector<int>& nums, int pos, double curSum, double aimSum, vector<vector<int>>& mem, double& maxVal) {
  if (pos == (int)nums.size() || curSum == aimSum) {
    maxVal = max(curSum, maxVal); 
    return;  // ×¢Òâ½áÊøÇé¿öÒªreturn 
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
 * »ØËİ NO.004
 * regular-expression-matching
 * ÕıÔò±í´ïÊ½: '*'Æ¥Åä0-n¸ö×Ö·û '?'Æ¥Åä0-1¸ö×Ö·û
 * bool match = false;
 * rmatch(0, 0, text, pattern, match); // textÎÄ±¾ patternÕıÔò
 * void rmatch(int ti, int pi, string text, string pattern, bool& match) {
 *   if (match == true) return; // ×¢ÒâÕâÀï±ØĞë£¬Òª²»¿ÉÄÜ»á±»ÆäËûfalse½á¹û¸²¸Ç
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
 * ÏÂÃæÕâµÀÌâ±È½ÏÂé·³ '*' ±íÊ¾ÆäÔÚpatternÖĞÇ°Ò»¸ö×Ö·û¿ÉÒÔ³öÏÖ0-n´Î
 * '.' ±íÊ¾¿ÉÒÔÆ¥ÅäÒ»¸öÈÎÒâ×Ö·û.
 * ½áÊøÌõ¼ş£¬text×ßÍêpatternÃ»ÓĞ×ßÍêµÄÇé¿öÏÂ²»Ò»¶¨²»Æ¥Åä£¬ÒòÎªpattern
 * ÖĞ*»á×÷·ÏÇ°Ò»¸ö×Ö·û´®. text = a ; pattern = ab*; ±éÀúpattern£¬´¦Àí
 * ¸÷ÖÖ×´Ì¬£ºÕâÀï×´Ì¬ÓĞµã¶à¡£Èç¹ûÊÇ'.'¾Í¶¼Ç°½øÒ»¸ö£¬µ«ÊÇÈç¹ûÏÂÒ»patternÊ
 * ÊÇ'*'¾ÍĞèÒª´¦Àí×÷·Ïµ±Ç°patternµÄÇé¿ö£»Èç¹ûÊÇ×Ö·û¾Í¿´ÊÇ·ñÏàµÈ£¬Ò²Òª´¦Àí
 * ÏÂÒ»¸öpatternÊÇ'*'µÄÊ±ºò×÷·Ïµ±Ç°patternµÄÇé¿ö.
 *  Èç¹ûµ±Ç°ÊÇ'*',ĞèÒªÃ¶¾ÙpatternÖĞ'*'Ç°Ò»¸ö×Ö·û³öÏÖ1-nµÄÇé¿ö,0µÄÇé¿öÔÚ
 * '.'ºÍ×Ö·ûµÄÊ±ºòµ¥¶À´¦ÀíÁË. 
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
