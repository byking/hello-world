#include <iostream>
#include <gflags/gflags.h>
#include <queue>
#include <stack>
#include <deque>

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
 *************************************/

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
