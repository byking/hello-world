#include <iostream>
#include <gflags/gflags.h>
#include <queue>

DEFINE_string(tree1_preorder, "", "tree 1 preorder");
DEFINE_string(tree1_inorder, "", "tree 1 inoreder");

using namespace std;

struct TreeNode {
  string val;
  int h; // current node height
  int l; // subtree left limit
  int r; // subtree right limit
  TreeNode *left;
  TreeNode *right;
  TreeNode(string x) : val(x), left(NULL), right(NULL) {}
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

  TreeNode *root = new TreeNode(preorder->at(pre_begin));
  
  auto left_size = find(inorder->begin() + in_begin, 
		         inorder->begin() + in_end, 
			 preorder->at(pre_begin)) - inorder->begin() - in_begin;
  
  //printf("pre_begin:%d;pre_end:%d;in_begin:%d;in_end:%d;left_size:%d\n",
  //       pre_begin,pre_end,in_begin,in_end,left_size);

  root->left = buildTreeByPreIn(preorder, pre_begin + 1, pre_begin + left_size + 1, 
		                inorder, in_begin, in_begin + left_size);
  root->right = buildTreeByPreIn(preorder, pre_begin + left_size + 1, pre_end, 
		                 inorder, in_begin+left_size + 1, in_end);
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

int getHeight(TreeNode* root) {
  int height = 0;
  queue<TreeNode*> *my_queue = new queue<TreeNode*>();
  my_queue->push(root);
  while (!my_queue->empty()) {
    TreeNode *node = my_queue->front();
    my_queue->pop();
    if (nullptr != node->left) {
      my_queue->push(node->left);
    } 
    if (nullptr != node->right) {
       my_queue->push(node->right);
    }
    if (nullptr != node->left && nullptr != node->right) {
       height = height - 1;
    }
    height = height + 1;
  }
  delete my_queue;
  return height;
}

vector<vector<string> > printTree(TreeNode *root) {
  int height = getHeight(root);
  int row = height;
  int col = (1 << height) - 1; 
  vector<vector<string> > res(row, vector<string>(col, " "));
  queue<TreeNode*> *my_queue = new queue<TreeNode*>();
  root->l = 0;
  root->r = col;
  root->h = 0;
  my_queue->push(root);
  while(!my_queue->empty()) {
    TreeNode *node = my_queue->front();
    my_queue->pop();
    int height = node->h;
    int left = node->l;
    int right = node->r;
    int mid = (left + right) / 2;
    res[height][mid] = node->val;
    if (nullptr != node->left) {
      node->left->l = left;
      node->left->r = mid - 1;
      node->left->h = height + 1;
      my_queue->push(node->left);
    }    
    if (nullptr != node->right) {
      node->right->l = mid + 1;
      node->right->r = right;
      node->right->h = height + 1;
      my_queue->push(node->right);
    }
  }
  delete my_queue;
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

  vector<vector<string> > res = printTree(tree1_root);
  for(vector<vector<string> >::iterator it = res.begin() ; it != res.end(); it++) {
    for(vector<string>::iterator i = (*it).begin(); i != (*it).end(); i++) {
      cout << *i;
    } 
    cout << endl;
  } 

  return 0;
}
