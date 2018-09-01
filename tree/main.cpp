#include <iostream>
#include <gflags/gflags.h>
#include <queue>
#include <stack>
#include <deque>

DEFINE_string(tree1_preorder, "", "tree 1 preorder");
DEFINE_string(tree1_inorder, "", "tree 1 inoreder");

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<string> split(string str, char a) {
  vector<string> strvec;
  string::size_type pos1, pos2;
  pos2 = str.find(a);
  pos1 = 0;
  while (string::npos != pos2) {
    strvec.push_back(str.substr(pos1, pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = str.find(a, pos1);
  }
  string val = str.substr(pos1);
  if ("" != val) {
    strvec.push_back(str.substr(pos1));
  }
  return strvec;
}

TreeNode *buildTreeByPreIn(const vector<string> *preorder, int pre_begin, int pre_end, 
		           const vector<string> *inorder, int in_begin, int in_end) {
  if (pre_begin == pre_end) return NULL;
  if (in_begin == in_end) return NULL;

  TreeNode *root = new TreeNode(stoi(preorder->at(pre_begin)));
  
  auto left_size = find(inorder->begin() + in_begin, 
		         inorder->begin() + in_end, 
			 preorder->at(pre_begin)) - inorder->begin() - in_begin;
  
  //printf("pre_begin:%d;pre_end:%d;in_begin:%d;in_end:%d;left_size:%d\n",
  //       pre_begin,pre_end,in_begin,in_end,left_size);

  root->left = buildTreeByPreIn(preorder, pre_begin + 1, pre_begin + left_size + 1, 
		                inorder, in_begin, in_begin + left_size);
  root->right = buildTreeByPreIn(preorder, pre_begin + left_size + 1, pre_end, 
		                 inorder, in_begin + left_size + 1, in_end);
  return root;
}

TreeNode *buildTreeByPreIn(const vector<string> *preorder,
		           const vector<string> *inorder){
  return buildTreeByPreIn(preorder, 0, preorder->size(), inorder, 0, inorder->size());
}

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

TreeNode* deserialize(vector<string>& node_value_list, int begin, int end) {
  if (end < 0 || begin > end) {
    return nullptr;
  }
 
  int cur_val = stoi(node_value_list.at(begin));
  TreeNode* node = new TreeNode(cur_val);
  
  if (begin == end) {
     return node;
  }

  int pivot_index = begin + 1;
  int pivot;
  for (int i = begin + 1; i <= end; i++) {
    pivot = stoi(node_value_list.at(i));
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
  vector<string> node_value_list = split(data, ',');
  return deserialize(node_value_list, 0, node_value_list.size() - 1); 
}
/***Serialize and Deserialize BST END***/

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
    auto level_size = dq.size();
    vector<int> number_same_level;
    for(auto i = 0; i < level_size; i++) {
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

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);

  cout << endl << "***Serialize and Deserialize BST***" << endl;
  bfsTree(tree1_root);
  string s = serialize(tree1_root);
  cout << "serialize BST use preorder traversal: " << s << endl;
  TreeNode* deserialize_tree = deserialize(s);
  cout << "deserialize BST: " << endl;
  bfsTree(deserialize_tree);
  cout << "***Serialize and Deserialize BST***" << endl;


  cout << endl << "***unique Binary Search Trees II***" << endl; 
  vector<TreeNode*> trees = generateTrees(3);
  for(int i = 0; i < (int)trees.size(); i++ ) {
    TreeNode* root = trees.at(i);
    bfsTree(root);
  }
  

  cout << endl << "***unique Binary Search Trees***" << endl; 
  cout << "unique BST num is " << numTrees(3) << " when sequence length is 3.";
  cout << endl << "***unique Binary Search Trees ***" << endl; 
  cout << "***unique Binary Search Trees***" << endl; 
 
  cout << "***Binary Tree Zigzag Level Order Traversal***" << endl;
  vector<vector<int>> zigzag_result = zigzagLevelOrder(tree1_root);
  printTwoDimensionalVector(zigzag_result);
  cout << "***Binary Tree Zigzag Level Order Traversal***" << endl;


  return 0;
}
