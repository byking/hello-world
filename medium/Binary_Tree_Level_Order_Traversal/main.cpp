#include <iostream>
#include <gflags/gflags.h>
#include <queue>

DEFINE_string(tree1_preorder, "", "tree 1 preorder");
DEFINE_string(tree1_inorder, "", "tree 1 inoreder");


using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct Node {
  int level;
  TreeNode* tree_node;
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
  strvec.push_back(str.substr(pos1));
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

vector<vector<int>> levelTransTree(TreeNode *root) {
  vector<vector<int>> res;
  if (nullptr == root) {
    return res;
  }
  queue<Node> *node_queue = new queue<Node>();
  Node node = Node{0, root};
  node_queue->push(node);
  while (!node_queue->empty()) {
    Node node = node_queue->front();
    node_queue->pop();
    int level = node.level;
    if (static_cast<int>(res.size()) <= level) {
      res.push_back(vector<int>());
    }
    res[level].push_back(node.tree_node->val);
    if (nullptr != node.tree_node->left || nullptr != node.tree_node->right) {
      level = level + 1;
    }
    if (nullptr != node.tree_node->left) {
      node_queue->push(Node{node.level+1, node.tree_node->left});
    }    
    if (nullptr != node.tree_node->right) {
      node_queue->push(Node{node.level+1, node.tree_node->right});
    }
  }
  return res;
}

int getHeightOfTree(TreeNode* root) {
  if (nullptr == root) return 0;
  return max(getHeightOfTree(root->left), getHeightOfTree(root->right)) + 1;
}

vector<vector<int>> levelTransTreeII(TreeNode* root) {
  vector<vector<int>> res;
  if (nullptr == root) return res;
  int height = getHeightOfTree(root);
  for(int i = 0; i < height; i++) {
    res.push_back(vector<int>());
  }
  queue<Node> *my_queue = new queue<Node>();
  Node node = Node{0, root};
  my_queue->push(node);
  while (!my_queue->empty()) {
    Node node = my_queue->front();
    my_queue->pop();
    int level = node.level;
    int index = height - level - 1;
    res[index].push_back(node.tree_node->val); 
    if (nullptr != node.tree_node->left) {
      my_queue->push(Node{level+1, node.tree_node->left});    
    }  
    if (nullptr != node.tree_node->right) {
      my_queue->push(Node{level+1, node.tree_node->right}); 
    }
  }
  return res;   
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);

  bfsTree(tree1_root);
  
  vector<vector<int>> res = levelTransTree(tree1_root);
  for (vector<vector<int>>::iterator itr = res.begin(); itr != res.end(); itr++) {
    for (vector<int>::iterator it = (*itr).begin(); it != (*itr).end(); it++) {
      cout << *it << ";";
    }
    cout << endl;
  }

  cout << endl;

  vector<vector<int>> resII = levelTransTreeII(tree1_root);
  for (vector<vector<int>>::iterator itr = resII.begin(); itr != resII.end(); itr++) {
    for (vector<int>::iterator it = (*itr).begin(); it != (*itr).end(); it++) {
      cout << *it << ";";
    }
    cout << endl;
  } 

  return 0;
}
