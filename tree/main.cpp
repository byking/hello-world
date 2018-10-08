#include <iostream>
#include <gflags/gflags.h>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>

DEFINE_string(tree1_preorder, "", "tree 1 preorder");
DEFINE_string(tree1_inorder, "", "tree 1 inorder");
DEFINE_string(tree1_postorder, "", "tree 1 postorder");

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct TreeLinkNode {
  TreeLinkNode* left;
  TreeLinkNode* right;
  TreeLinkNode* next;
};

struct InfoNode {
  TreeNode* node;
  int depth; 
  int pos; //position in the depth
  InfoNode(TreeNode* node, int depth, int pos) :
	  node(node), depth(depth), pos(pos) {}
};

/*********************************
 * Binary Tree Preorder Traversal
 *  1   
 * 2 3 ==> 1,2,3 (root,left,right)
 * first is recusive version
 * second is not 
 *********************************/
void recursivePreorderTraversal(TreeNode* root, vector<int>& res) {
  if (nullptr == root) {
    return;
  }
  res.push_back(root->val);
  recursivePreorderTraversal(root->left, res);
  recursivePreorderTraversal(root->right, res);
}

vector<int> preorderTraversal(TreeNode* root) {
  vector<int> res;
  recursivePreorderTraversal(root, res);
  return res;
}

vector<int> preorderTraversalII(TreeNode* root) {
  vector<int> res;
  stack<TreeNode*> st;
  if (nullptr == root) {
    return res;
  }
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    res.push_back(node->val);
    if (nullptr != node->right) {
      st.push(node->right);
    }
    if (nullptr != node->left) {
      st.push(node->left);
    }
  }
  return res;
}

/***********************************
 * Binary Tree InOrder Traversal
 *  1
 * 2 3 ==> 2,1,3(left, root, right)
 ***********************************/
vector<int> inorderTraversal(TreeNode* root) {
  vector<int> res;
  stack<TreeNode*> st;
  
  TreeNode* node = root;
  while (nullptr != node) {
    st.push(node);
    node = node->left;
  }
  while (!st.empty()) {
    TreeNode* cur_node = st.top();
    st.pop();
    res.push_back(cur_node->val);
    TreeNode* cur_root = cur_node->right;
    if (nullptr != cur_root) {
      st.push(cur_root);
      TreeNode* left_node = cur_root->left;
      while(nullptr != left_node) {
        st.push(left_node);
	left_node = left_node->left;
      }
    }
  }
  return res;
}

/***********************************
 * Binary Tree PostOrder Traversal
 *  1
 * 2 3 ==> 2,3,1(left, right, root)
 * use two stack, for output stack
 * we want output left,right,root,
 * so in input stack, the sequence
 * is left, right.
 ***********************************/
vector<int> postorderTraversal(TreeNode* root) {
  stack<TreeNode*> in, out;
  vector<int> res;
  if (nullptr != root) {
    in.push(root);
  }
  while(!in.empty()) {
    TreeNode* node = in.top();
    in.pop();
    out.push(node);
    if (nullptr != node->left) {
      in.push(node->left);
    }
    if (nullptr != node->right) {
      in.push(node->right);
    }
  }
  while(!out.empty()) {
    TreeNode* node = out.top();
    out.pop();
    res.emplace_back(node->val);
  }
  return res;
}

/*************************************
 * Binary Tree Right Side View
 *   1
 *  2 3   ==>  1,3,4
 *   5 4 
 * like level traversal tree, in same
 * level only get the last node
 *************************************/
vector<int> rightSideView(TreeNode* root) {
  queue<TreeNode*> q;
  vector<int> res;
  if (nullptr != root) {
    q.push(root);
  }
  while (!q.empty()) {
    int q_size = q.size();
    for (int i = 0; i < q_size; i++) {
      TreeNode* node = q.front();
      q.pop();
      if (i == (q_size - 1)) {
        res.emplace_back(node->val);
      } 
      if (nullptr != node->left) {
        q.push(node->left);
      }
      if (nullptr != node->right) {
      	q.push(node->right);
      }
    }
  }
  return res;
}

/**************************************
 * Count Complete Tree Nodes
 **************************************/
int countNodes(TreeNode* root) {
  if (nullptr == root) {
    return 0;
  }
  TreeNode* left_node = root;
  int l = 0;
  while (nullptr != left_node) {
    left_node = left_node->left;
    l++;
  }
  int r = 0;
  TreeNode* right_node = root;
  while (nullptr != right_node) {
    right_node = right_node->right;
    r++;
  }
  if (r == l) {
    return (1 << l) - 1;
  }
  return 1 + countNodes(root->left) + countNodes(root->right);
}

/************************************************
 * Populating Next Right Pointers in Each Node II
 *   1           1->NULL
 *  2 3   ==>   2->3->NULL
 * 4 5 7      4->5->7->NULL
 * similar to BFS of tree, process level by level
 ************************************************/
void connect(TreeLinkNode* root) {
  if (nullptr == root) {
    return;
  }
  queue<TreeLinkNode*> q;
  q.push(root);
  while(!q.empty()) {
    int level_size = q.size();
    for(int i = 0; i < level_size; i++) {
      TreeLinkNode* node = q.front();
      q.pop();
      if(nullptr != node->left) {
        q.push(node->left);
      }
      if(nullptr != node->right) {
        q.push(node->right);
      }
      if(i != level_size - 1) {
        node->next = q.front();
      }else {
        node->next = nullptr;
      }
    }
  }  
}

vector<int> split(string str, char a) {
  vector<int> strvec;
  string::size_type pos1, pos2;
  pos2 = str.find(a);
  pos1 = 0;
  while (string::npos != pos2) {
    strvec.push_back(stoi(str.substr(pos1, pos2 - pos1)));
    pos1 = pos2 + 1;
    pos2 = str.find(a, pos1);
  }
  string val = str.substr(pos1);
  if ("" != val) {
    strvec.push_back(stoi(str.substr(pos1)));
  }
  return strvec;
}

/*************************************************************
 * Construct Binary Tree from Preorder and Inorder Traversal
 * preorder: [root, left, right] inorder: [left, root, right]
 * so we can find root node in inorder to get left subtree 
 * and right subtree, and then do same operation to left/right
 * subtree recursivelly.
 *************************************************************/
TreeNode* buildTreeByPreInorder(const vector<int>& preorder, int pre_start,
				const vector<int>& inorder, int in_start, int in_end) {
  if (in_end < in_start) {
    return nullptr;
  } 

  TreeNode* node = new TreeNode(preorder.at(pre_start));
  int left_subtree_size = 0;
  for(int i = in_start; i <= in_end ; i++) {
    if (node->val == inorder.at(i)) {
      break;
    }
    left_subtree_size++;
  }

  node->left = buildTreeByPreInorder(preorder, pre_start + 1, 
		  		     inorder, in_start, in_start + left_subtree_size - 1);
  node->right = buildTreeByPreInorder(preorder, pre_start + left_subtree_size + 1,
		  		     inorder, in_start + left_subtree_size + 1, in_end);
  return node;
}

TreeNode* buildTreeByPreInorder(const vector<int>& preorder, const vector<int>& inorder) {
  int pre_start = 0;
  int in_start = 0;
  int in_end = inorder.size() - 1;
  return buildTreeByPreInorder(preorder, pre_start, inorder, in_start, in_end); 
}


/************************************************************
 * Construct Binary Tree from Inorder and Postorder Traversal
 * inorder: left, root, right; postorder: left, right, root
 * so we can get root node when end to begin traversal post-
 * order, and in inorder we can get left subtree and right
 * subtree.
 ************************************************************/
TreeNode* buildTreeByInPostorder(const vector<int>& inorder, int in_start, int in_end,
				 const vector<int>& postorder, int post_start) {
  if (in_end < in_start) {
    return nullptr;
  }   

  TreeNode* node = new TreeNode(postorder.at(post_start));
  int right_subtree_size = 0;
  for (int i = in_end; i >= in_start; i--) {
    if (node->val == inorder.at(i)) {
      break;
    }
    right_subtree_size++;
  }
  node->left = buildTreeByInPostorder(inorder, in_start, in_end - right_subtree_size - 1,
		  		      postorder, post_start - right_subtree_size - 1);
  node->right = buildTreeByInPostorder(inorder, in_end - right_subtree_size + 1, in_end,
		  		       postorder, post_start - 1);

  return node;
}

TreeNode* buildTreeByInPostorder(const vector<int>& inorder, const vector<int>& postorder) {
  int in_start = 0;
  int in_end = inorder.size() - 1;
  int post_start = postorder.size() - 1;
  return buildTreeByInPostorder(inorder, in_start, in_end, postorder, post_start);
}

/*******************************
 * Breadth-first traversal
 *******************************/
void bfsTree(TreeNode* root) {
  cout << "bfsTree: ";
  if (nullptr == root) {
    return;
  }
  queue<TreeNode*> *my_queue = new queue<TreeNode*>();
  my_queue->push(root);
  while(!my_queue->empty()) {
    TreeNode* node = my_queue->front();
    cout << node->val << ",";
    my_queue->pop();
    if (nullptr != node->left) {
      my_queue->push(node->left);
    }
    if (nullptr != node->right) {
      my_queue->push(node->right);
    }
  }
  cout << endl;
  delete my_queue;
  return;
}

/*****************************************
 * Serialize and Deserialize BST
 * serialilze tree use preorder traversal
 * deserialize tree use pivot:
 *   2
 *  1 3
 * 0   4 bfs: 2,1,0,3,4 
 * pivot: 2: 1,0 less than 2 in the left
 *           3,4 greater than 2 in right
 *        ... 
 * time complexity: O(NlogN) worst: O(N^2)
 *****************************************/
string serialize(TreeNode* root) {
  string res = "";
  if (nullptr == root) {
    return res;
  }  
  stack<TreeNode*> st;
  st.push(root);
  while(!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    if ("" == res ) {
      res = to_string(node->val);
    }else {
      res = res + "," + to_string(node->val);
    }
    if (nullptr != node->right) {
      st.push(node->right);
    }
    if (nullptr != node->left) {
      st.push(node->left);
    }
  }
  return res; 
}

TreeNode* deserialize(vector<int>& node_value_list, int begin, int end) {
  if (end < 0 || begin > end) {
    return nullptr;
  }
 
  int cur_val = node_value_list.at(begin);
  TreeNode* node = new TreeNode(cur_val);
  
  if (begin == end) {
     return node;
  }

  int pivot_index = begin + 1;
  int pivot;
  for (int i = begin + 1; i <= end; i++) {
    pivot = node_value_list.at(i);
    if (pivot <= cur_val) {
      pivot_index ++;
    }else {
      break;
    } 
  }

  node->left = deserialize(node_value_list, begin + 1, pivot_index - 1);
  node->right = deserialize(node_value_list, pivot_index, end);
  
  return node;
}

TreeNode* deserialize(string data) {
  vector<int> node_value_list = split(data, ',');
  return deserialize(node_value_list, 0, node_value_list.size() - 1); 
}

/**********************************************
 * Unique Binary Search Trees II 
 * given N, generate all unique BST less than n
 * input: 3, output: [
 *                    [1,null,3,2],
 *                    [3,2,null,1],
 *                    [3,1,null,null,2],
 *                    [2,1,3],
 *                    [1,null,2,null,3]
 *                   ]
 * for every item i, make a recursive call and 
 * get a list of possible values for the left
 * node in range [start,i-1], Since is a BST,
 * right from [i+1, end]. The result is unique,
 * since they have unique roots.  
 **********************************************/
vector<TreeNode*> generateTreeRecursive(int start, int end) {
  vector<TreeNode*> res;
  if (end < start) {
    res.emplace_back(nullptr);
    return res;
  }
  if (end == start) {
    res.emplace_back(new TreeNode(start));
    return res;
  }

  for (int i = start; i <= end; ++i) {
    vector<TreeNode*> left = generateTreeRecursive(start, i-1);
    vector<TreeNode*> right = generateTreeRecursive(i+1, end);
    for(int j = 0; j < (int)left.size(); j++) {
      for(int k=0; k < (int)right.size(); ++k) {
        TreeNode* node = new TreeNode(i);
	node->left = left[j];
	node->right = right[k];
	res.emplace_back(node);
      }
    }
  }
  return res;
}

vector<TreeNode*> generateTrees(int n) {
  if (0 == n) {
    return vector<TreeNode*> ();
  }
  return generateTreeRecursive(1, n);
}

/***********************************************
 * Unique Binary Search Trees
 * dynamic programming:
 * G(n): the number of unique BST for a sequence
 * of length n.
 * F(i, n), 1<=i<=n: the number of unique BST,
 * where the number i is the root of BST, and 
 * the sequence ranges from 1 to n.
 * G(n) = F(1,n) + f(2,n) + ... + f(n,n)
 * G(0) = 0, G(1) = 1.
 * F(i,n) = G(i-1) * G(n-i)  1<=i<=n 
 ***********************************************/
int numTrees(int n) {
  vector<int> res(n+1, 0);
  res.at(0) = 1;  //G(0)
  res.at(1) = 1;  //G(1)
    
  for(int i = 2; i <= n; i++) {
    for(int j = 1; j <= i; j++) {
      res.at(i) += res.at(j-1) * res.at(i-j);  
    }
  }
  return res.at(n);
}

/***********************************************
 * Binary Tree Zigzag Level Order Traversal
 * use deque to record node: first, push root 
 * to deque, while deque not null, we do:  
 * 1.get size of deque, which record node in the 
 *   same level
 * 2.when level % 2 == 0, get/pop node at front,
 *   then push back left/right of the pop node.
 * 3.when level % 2 == 1, get/pop node at back,
 *   then push front right/left of the pop node.
 * 4.push all node in the same level to vector,
 *   then push vector to result.
 ***********************************************/
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
  vector<vector<int>> result;
  if (nullptr == root) {
    return result;
  }  
  deque<TreeNode*> dq;
  dq.push_back(root);
  int level = 0;
  while(!dq.empty()) {
    int level_size = dq.size();
    vector<int> number_same_level;
    for(int i = 0; i < level_size; i++) {
      if (level % 2 == 0) {
        TreeNode* node = dq.front();
        dq.pop_front();
        number_same_level.push_back(node->val);
	if (nullptr != node->left) {
	  dq.push_back(node->left);
	}
	if (nullptr != node->right) {
	  dq.push_back(node->right);
	}
      }else {
        TreeNode* node = dq.back();
	dq.pop_back();
	number_same_level.push_back(node->val);
	if (nullptr != node->right) {
	  dq.push_front(node->right);
	}
	if (nullptr != node->left) {
	  dq.push_front(node->left);
	}
      }
    }
    result.push_back(number_same_level);
    level++;
  }
  return result;
}

/***********************************************
 * House Robber III
 * tips: can't use level traversal tree to solve
 * use recusive
 * first solution is a naive way.
 * second is a optimal way, use map to reduce 
 *   overlap computing
 ***********************************************/
int rob(TreeNode* root) {
  if (nullptr == root) {
    return 0;
  }
  int val = 0;
  if (nullptr != root->left) {
    val += rob(root->left->left) + rob(root->left->right);
  }
  if (nullptr != root->right) {
    val += rob(root->right->left) + rob(root->right->right);
  }
  return max(val+root->val, rob(root->left) + rob(root->right));
}

int robIISub(TreeNode* node, map<TreeNode*,int>& res) {
  if (nullptr == node) {
    return 0;
  }
  if (res.find(node) != res.end()) {
    return res[node];
  }

  int val = 0;
  if (nullptr != node->left) {
    val += robIISub(node->left->left, res) + robIISub(node->left->right, res);
  }
  if (nullptr != node->right) {
    val += robIISub(node->right->left, res) + robIISub(node->right->right, res);
  }
  val = max(val + node->val, robIISub(node->left, res) + robIISub(node->right, res));
  res[node] = val;
  return val;
};

int robII(TreeNode* root) {
  map<TreeNode*, int> res;
  return robIISub(root, res);
}

/***********************************************
 * Validate Binary Search Tree
 * first use recusive
 * second use inorder traversal tree
 ***********************************************/
bool isValidBST(TreeNode* root, long int max, long int min) {
  if (nullptr == root) {
    return true;
  }
  if (root->val >= max || root->val <= min) {
    return false;
  }
  return isValidBST(root->left, root->val, min) 
	  && isValidBST(root->right, max, root->val);
}

bool isValidBST(TreeNode* root) {
  return isValidBST(root, LONG_MAX, LONG_MIN);
}

/***********************************************
 * Lowest Common Ancestor of a Binary Tree
 ***********************************************/ 
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (nullptr == root || nullptr == p || nullptr == q) {
    return NULL;
  } 
  if (root == p || root == q) {
    return root;
  }

  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);

  if (nullptr != left && nullptr != right) {
    return root;
  }

  return left ? left : right; // ac
  //return left == nullptr ? left : right;//wrong answer
}

/***********************************************
 * Lowest Common Ancestor of a Binary Tree(BST)
 * 1. if p, q both less than root, then LCA in 
 *    left tree
 * 2. if p, q both greater than root, then LCA 
 *    in right tree
 * 3. if p or q equal root, then LCA is p or q
 ***********************************************/ 
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (nullptr == root) {
    return NULL;
  }
  if (p->val < root->val && q->val < root->val) {
    return lowestCommonAncestorBST(root->left, p, q);
  }else if (p->val > root->val && q->val > root->val) {
    return lowestCommonAncestorBST(root->right, p, q);
  }else {
    return root;
  }
}

/***********************************************
 * Maximum Depth of Binary Tree
 *    3
 *  9   20    
 *    15  7  => 3  
 ***********************************************/ 
int maxDepth(TreeNode* root) {
  if (nullptr == root) {
    return 0;
  }
  return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

/***********************************************
 * Delete Node in a BST
 * root = [5,3,6,2,4,null,7]
 * key = 3
 *	    5
 *	   / \
 *	  3   6
 *	 / \   \
 *	2   4   7
 *
 * Given key to delete is 3. So we find the node
 * with value 3 and delete it
 *
 * One valid answer is [5,4,6,2,null,null,7], 
 * shown in the following BST.
 *
 *	    5
 *	   / \
 *	  4   6
 *	 /     \
 *	2       7
 *
 * Another valid answer is [5,2,6,null,4,null,7].
 *
 *	    5
 *	   / \
 *	  2   6
 *	   \   \
 *	    4   7
 ***********************************************/
TreeNode* deleteNode(TreeNode* root, int key) {
  if (nullptr == root) {
    return NULL;
  } 
  if (root->val == key) {
    if (nullptr == root->right) {
      TreeNode* left_node = root->left;
      delete root;
      return left_node;
    }else {
      TreeNode* node = root->right;
      while (nullptr !=  node->left) {
        node = node->left;
      }
      swap(node->val, root->val);
    }
  }
  root->left = deleteNode(root->left, key);
  root->right = deleteNode(root->right, key);
  return root;
}

/***********************************************
 * Find Mode in Binary Search Tree
 * Use O(1) extra space
 * find mode means find same val node count in 
 * BST. because of BST, first we use inorder
 * traversal, and record the list of max same val
 * node and the pre node(to judge the mode)
 ***********************************************/
// we need define three global variables:
TreeNode* g_pre = NULL;
int g_count = 0;
int g_max_count = -1;

void inorderFindMode(TreeNode* node, vector<int>& modes){
  if (nullptr == node) {
    return;
  }
  inorderFindMode(node->left, modes);
  if (g_pre != NULL && g_pre->val == node->val) {
    g_count ++;
  }else {
    g_count = 1;
  }

  if (g_count == g_max_count) {
    modes.push_back(node->val);
  }else if (g_count > g_max_count) {
    modes.clear();
    modes.push_back(node->val);
    g_max_count = g_count;
  }

  g_pre = node;
  inorderFindMode(node->right, modes);
}

vector<int> findMode(TreeNode* root) {
  vector<int> modes;
  inorderFindMode(root, modes);
  return modes;
}

/***********************************************
 * Most Frequent Subtree Sum
 * 1. use recursive to traversal tree to calculate
 * sum of node and it's subnodes
 * 2. meanwhile use a map to record the most 
 * frequent sum
 * 3. to save memory of map, use a variable 
 * to record a current max frequent sum, if new
 * frequent of sum is bigger, then clear the map
 * and record new sum and new max frequent.
 ***********************************************/
int sumTree(TreeNode* node, vector<int> &res, map<int, int> &frequents, int& max_frequent) {
  if (nullptr == node) {
    return 0;
  }
  int cur_sum = node->val + sumTree(node->left, res, frequents, max_frequent) 
	  	+ sumTree(node->right, res, frequents, max_frequent);
  frequents[cur_sum]++;
  if (frequents[cur_sum] > max_frequent) {
    res.clear();
    res.push_back(cur_sum);
    max_frequent = frequents[cur_sum];
  }else if (frequents[cur_sum] == max_frequent) {
    res.push_back(cur_sum);
  }
  return cur_sum;
}

vector<int> findFrequentTreeSum(TreeNode* root) {
  vector<int> res;
  int max_frequent = INT_MIN;
  map<int, int> frequents;
  sumTree(root, res, frequents, max_frequent);
  return res;
}

/***********************************************
 * Find Bottom Left Tree Value
 * 1. first we can use bfs to traversal tree, 
 * record the most left node in last node.
 * 2. also can use recursive to dfs travesal tree.
 * traversal left tree first to get the most left
 * node, if new depth greater than max depth then 
 * update most left node.
 ***********************************************/
void dfsFindMostLeftValue(TreeNode* node, int& most_left_value, int cur_depth, int& max_depth) {
  if (nullptr == node) {
    return;
  }
  if (cur_depth > max_depth) {
    most_left_value = node->val;
    max_depth = cur_depth;
  }
  dfsFindMostLeftValue(node->left, most_left_value, cur_depth + 1, max_depth);
  dfsFindMostLeftValue(node->right, most_left_value, cur_depth + 1, max_depth);
}

int findBottomLeftValue(TreeNode* root) {
  int most_left_value = 0;
  int cur_depth = 0;
  int max_depth = -1;
  dfsFindMostLeftValue(root, most_left_value, cur_depth, max_depth);  
  return most_left_value;
}

/***********************************************
 * Find Largest Value in Each Tree Row
 * use BFS the travesal tree, record largest value
 * int each row  
 ***********************************************/
vector<int> largestValues(TreeNode* root) { 
  queue<TreeNode*> q;
  vector<int> res;
  if (nullptr != root) {
    q.push(root);
  }
  while (!q.empty()) {
    int q_size = q.size();
    int level_max_value = INT_MIN;
    for (int i = 0; i < q_size; i++) {
      TreeNode* node = q.front();
      q.pop();
      if (node->val > level_max_value) {
        level_max_value = node->val;
      } 
      if (nullptr != node->left) {
        q.push(node->left);
      }
      if (nullptr != node->right) {
      	q.push(node->right);
      }
    }
    res.push_back(level_max_value);
  }
  return res;
}

/***********************************************
 * Diameter of Binary Tree
 * diameter of binary tree is length of the 
 * longest path between any two nodes in a tree.
 * 1. diameter = depth of left + depth of right
 * 2. every node as root has a diameter, we need
 *    the max diameter;
 * note: count the depth of tree need to judge
 * subnote is null or not.
 ***********************************************/
int dfsGetDepth(TreeNode* node, int& diameter) {
  if (nullptr == node) {
    return 0;
  }
  int left_depth = 0;
  int right_depth = 0;
  if (nullptr != node->left) {
    left_depth = dfsGetDepth(node->left, diameter) + 1;
  }
  if (nullptr != node->right) {
    right_depth = dfsGetDepth(node->right, diameter) + 1;
  }

  int cur_diameter = left_depth + right_depth;
  if (cur_diameter > diameter) {
    diameter = cur_diameter;
  } 

  return max(left_depth, right_depth);
}

int diameterOfBinaryTree(TreeNode* root) {
  int diameter = 0;
  int depth = dfsGetDepth(root, diameter); 
  return diameter;
}

/***********************************************
 * Convert BST to Greater Tree
 * the key solution would be a way to visit nodes
 * in descending order, keeping a sum of all 
 * values that we have already visited and adding 
 * that sum to the node's values as we traverse
 * the tree.
 * example:
 *   5            18
 * 2   13  --> 20    13
 ***********************************************/
TreeNode* convertBSTRecursive(TreeNode* node, int& sum) {
  if (nullptr == node) {
    return node;
  }
  convertBSTRecursive(node->right, sum);
  sum += node->val;
  node->val = sum;
  convertBSTRecursive(node->left, sum);
  return node;
}

TreeNode* convertBST(TreeNode* root) {
  int sum = 0;
  return convertBSTRecursive(root, sum);  
}

/***********************************************
 * Binary Tree Tilt
 * calculate tilt of the whole tree, the tilt of
 * a tree node is defined as the absolute 
 * difference between the sum of all left subtree
 * node values and the sum of all right subtree
 * node values. Null node has tilt 0.
 * Example:
 *   1
 * 2   3 --> 1 
 * tilt of node 2: 0
 *              3: 0
 *              1: |2-3|=1
 *           tree: 0 + 0 + 1 = 1
 ***********************************************/
int calTiltRecursive(TreeNode* node, int& tilt) {
  if (nullptr == node) {
    return 0;
  }
  int left_sum = calTiltRecursive(node->left, tilt);
  int right_sum = calTiltRecursive(node->right, tilt);
   
  tilt += std::abs(left_sum - right_sum);
   
  return left_sum + right_sum + node->val;
}

int findTilt(TreeNode* root) {
  int tilt = 0;
  int sum = calTiltRecursive(root, tilt);
  return tilt;
}

/***********************************************
 * Subtree of Another Tree
 ***********************************************/
bool equals(TreeNode* s, TreeNode* t) {
  if (nullptr == s && nullptr == t) {
    return true;
  }
  if (nullptr == s || nullptr == t) {
    return false;
  }
  return s->val == t->val && equals(s->left, t->left) && equals(s->right, t->right);
}

bool isSubtree(TreeNode* s, TreeNode* t) {
  return (nullptr != s) && (equals(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t));  
}


/***********************************************
 * Construct String from Binary Tree
 ***********************************************/
string tree2str(TreeNode* t) {
  if (nullptr == t) {
    return "";
  }
  if (nullptr == t->left && nullptr == t->right) {
    return to_string(t->val) + "";
  }
  if (nullptr == t->right) {
    return to_string(t->val) + "(" + tree2str(t->left) + ")";
  }
  return to_string(t->val) + "(" + tree2str(t->left) + ")(" + tree2str(t->right) + ")";
}

/***********************************************
 * Merge Two Binary Trees
 ***********************************************/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
  if (nullptr == t1 && nullptr == t2) {
    return nullptr;
  }else if (nullptr != t1 && nullptr == t2) {
    return t1;
  }else if (nullptr == t1 && nullptr != t2) {
    return t2;
  }else {
    t1->val += t2->val;
    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);
    return t1;
  }
}

/***********************************************
 * Add One Row to Tree
 * need to think: 
 * 1. insert before root
 * 2. insert after leaf(when node is subnode of 
 * leaf, but cur_d equal input d-1)
 * 3. input dept equal dept of tree - 1 
 ***********************************************/
TreeNode* recursiveAddOneRow(TreeNode* node , int v, int d, int cur_d, int flag) {
  if ((d - 1) == cur_d) {
    TreeNode* new_node = new TreeNode(v);
    if (0 == flag) {
      new_node->left = node;
    }else if (1 == flag) {
      new_node->left = node;
    }else if (2 == flag) {
      new_node->right = node; 
    }
    return new_node;
  }
  if (nullptr == node) {
    return nullptr;
  }
  node->left = recursiveAddOneRow(node->left, v, d, cur_d + 1, 1);
  node->right = recursiveAddOneRow(node->right, v, d, cur_d + 1, 2);

  return node; 
} 

TreeNode* addOneRow(TreeNode* root, int v, int d) {
  return recursiveAddOneRow(root, v, d, 0, 0);
}

/***********************************************
 * Find Duplicate Subtrees
 ***********************************************/
string findDuplicateRecursive(TreeNode* node, map<string, int> &record, 
		            vector<TreeNode*> &res) {
  if (nullptr == node) {
    return "#";
  }
  string serial = to_string(node->val) + 
	          findDuplicateRecursive(node->left, record, res) +
		  findDuplicateRecursive(node->right, record, res);
  if (record.find(serial) != record.end()) {
    record[serial]++;
    if (record[serial] == 2) {
      res.push_back(node);
    } 
  }else {
    record[serial] = 1;
  }
  return serial;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
  map<string, int> record;
  vector<TreeNode*> res;
  findDuplicateRecursive(root, record, res);
  return res;
}

/***********************************************
 * Two Sum IV - Input is a BST
 ***********************************************/
bool findTargetRecursive(TreeNode* node, int k, set<int> &record) {
  if (nullptr == node) {
    return false;
  }
  if (record.find(k - node->val) != record.end()) {
    return true;
  }
  record.insert(node->val);
  return findTargetRecursive(node->left, k, record) 
	 || findTargetRecursive(node->right, k, record);
}

bool findTarget(TreeNode* root, int k) {
  set<int> record;
  return findTargetRecursive(root, k, record);
}

/***********************************************
 * Maximum Binary Tree
 ***********************************************/
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
  TreeNode* root = nullptr;
  for (vector<int>::iterator it = nums.begin(); it != nums.end(); it++) {
    if (nullptr == root) {
      root = new TreeNode((*it));
      continue;
    }
    TreeNode* cur = root;
    TreeNode* pre = nullptr;
    TreeNode* new_node = new TreeNode((*it));
    while (nullptr != cur) {
      if (cur->val > (*it)) {
	pre = cur;
        cur = cur->right;
      }else {
	if (nullptr == pre) {
	  new_node->left = cur;
	  root = new_node;
	}else {
          new_node->left = cur;
	  pre->right = new_node;
	}
	break;
      }
    }
    if (nullptr == cur && nullptr != pre) {
      pre->right = new_node;
    }
  }
  return root;
}

/***********************************************
 * Maximum Width of Binary Tree
 * The width of one level is defined as the 
 * length between the end-nodes (the leftmost 
 * and right most non-null nodes in the level, 
 * where the null nodes between the end-nodes 
 * are also counted into the length calculation.
 * example:
 *   1               1                1
 * 3   2 => 2      2   4   => 4     2   3 => 2
 *               3       5        4
 *
 * as the defination of width of tree, we can use
 * the bfs to traverse the tree, meanwhile record
 * the leftmost node, the width equal the max (no
 * null right node - left most node + 1).  
 ***********************************************/
int widthOfBinaryTree(TreeNode* root) {
  if (nullptr == root) {
    return 0;
  }
  queue<TreeNode*> q;
  q.push(new InfoNode(root, 0, 0));
  int curDepth = 0;
  int left = 0;
  int res = 0;
  while (!q.empty()) {
    Info  
  }
}

/***********************************************
 * print two dimensional vector
 ***********************************************/ 
void printTwoDimensionalVector(vector<vector<int>> vectors) {
  for(vector<vector<int>>::iterator it = vectors.begin(); it != vectors.end(); it++) {
    for(vector<int>::iterator i = (*it).begin(); i != (*it).end(); i++) {
      cout << *i << ";";
    }
    cout << endl;
  }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;
  cout << "get tree1 postorder:  " << FLAGS_tree1_postorder << endl;

  vector<int> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<int> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  
  vector<int> tree1_postorder_vec = split(FLAGS_tree1_postorder, ',');  

  /***Construct Binary Tree from Preorder and Inorder Traversal***/
  TreeNode *tree1_root = buildTreeByPreInorder(tree1_preorder_vec, tree1_inorder_vec);
  cout << "***buildTreeByPreInorder***" << endl;
  bfsTree(tree1_root);
  
  /***Construct Binary Tree from Inorder and Postorder Traversal***/
  TreeNode *tree1_root_post = buildTreeByInPostorder(tree1_inorder_vec, tree1_postorder_vec);
  cout << endl << "***buildTreeByInPostorder***" << endl;
  bfsTree(tree1_root_post);
  

  cout << endl << "***Serialize and Deserialize BST***" << endl;
  string s = serialize(tree1_root);
  cout << "serialize BST use preorder traversal: " << s << endl;
  TreeNode* deserialize_tree = deserialize(s);
  cout << "deserialize BST: " << endl;
  bfsTree(deserialize_tree);


  cout << endl << "***unique Binary Search Trees II***" << endl; 
  vector<TreeNode*> trees = generateTrees(3);
  for(int i = 0; i < (int)trees.size(); i++ ) {
    TreeNode* root = trees.at(i);
    bfsTree(root);
  }
  
  cout << endl << "***unique Binary Search Trees***" << endl; 
  cout << "unique BST num is " << numTrees(3) << " when sequence length is 3." << endl;
 
  cout << endl << "***Binary Tree Zigzag Level Order Traversal***" << endl;
  vector<vector<int>> zigzag_result = zigzagLevelOrder(tree1_root);
  printTwoDimensionalVector(zigzag_result);
  
  return 0;
}
