#include <iostream>
#include <gflags/gflags.h>
#include <queue>
#include <stack>

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

void preorder_traversal(TreeNode* root) {
  cout << "preorder_traversal: ";
  if (nullptr == root) return;
  stack<TreeNode*> node_stack;
  node_stack.push(root);
  while (!node_stack.empty()) {
    TreeNode* node = node_stack.top();
    node_stack.pop();
    cout << node->val << ";";
    if (nullptr != node->right) {
      node_stack.push(node->right);
    }
    if (nullptr != node->left) {
      node_stack.push(node->left);
    }
  }  
}

void getLeaves(TreeNode* root, vector<int>& leaves) {
  if (nullptr == root) return;
  stack<TreeNode*> node_stack;
  node_stack.push(root);
  while (!node_stack.empty()) {
    TreeNode* node = node_stack.top();
    node_stack.pop();
    if (nullptr == node->right && nullptr == node->left) {
      leaves.push_back(node->val);
    }
    if (nullptr != node->right) {
      node_stack.push(node->right);
    }
    if (nullptr != node->left) {
      node_stack.push(node->left);
    }
  }
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
  vector<int> leaves1;
  vector<int> leaves2;
  getLeaves(root1, leaves1);
  getLeaves(root2, leaves2);
  return leaves1 == leaves2;
}

void flatten(TreeNode* root) {
  if (nullptr == root) return;
  stack<TreeNode*> node_stack;
  node_stack.push(root);
  TreeNode* pre = nullptr;
  TreeNode* cur = nullptr;
  while (!node_stack.empty()) {
    cur = node_stack.top();
    node_stack.pop();
    if (nullptr != cur->right) {
      node_stack.push(cur->right);
    }
    if (nullptr != cur->left) {
      node_stack.push(cur->left);
    }
    cur->left = nullptr;
    if (nullptr != pre) {
      pre->right = cur;
    }
    pre = cur;
  }
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);

  bfsTree(tree1_root);
  preorder_traversal(tree1_root);
  cout << endl;

  cout << "leafSimilar: " << leafSimilar(tree1_root, tree1_root) << endl;

  flatten(tree1_root);
  TreeNode node = *tree1_root;
  while (nullptr != node.right) {
    cout << node.val << ";";
    node = *node.right;
  }
  cout << node.val << ";" << endl;

  return 0;
}
