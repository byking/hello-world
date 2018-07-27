#include <iostream>
#include <gflags/gflags.h>

DEFINE_string(tree1_preorder, "", "tree 1 preorder");
DEFINE_string(tree1_inorder, "", "tree 1 inoreder");
DEFINE_string(tree2_preorder, "", "tree 2 preorder");
DEFINE_string(tree2_inorder, "", "tree 2 inorder");

using namespace std;

struct TreeNode {
  string val;
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
		                 inorder, in_begin + left_size + 1, in_end);
  return root;
}

TreeNode *buildTreeByPreIn(const vector<string> *preorder,
		           const vector<string> *inorder){
  return buildTreeByPreIn(preorder, 0, preorder->size(), inorder, 0, inorder->size());
}

void preorder(TreeNode *root) {
  if (NULL != root) {
    cout << root->val << ";";
    preorder(root->left);
    preorder(root->right);
  }
}

void inorder(TreeNode *root) {
  if (NULL != root) {
    inorder(root->left);
    cout << root->val << ";";
    inorder(root->right);
  }
}

void postorder(TreeNode *root) {
  if (NULL != root) {
    postorder(root->left);
    postorder(root->right);
    cout << root->val << ";";
  }
}

bool isSameTree(TreeNode *p, TreeNode *q) {
  if (nullptr == p && nullptr == q) {
    return true;
  }
  if (nullptr == p || nullptr == q) {
    return false;
  }
  return (
    (p->val == q->val) &&
    (isSameTree(p->left, q->left)) && 
    (isSameTree(p->right, q->right))    
  );
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;
  cout << "get tree2 preorder: " << FLAGS_tree2_preorder << endl;
  cout << "get tree2 inorder:  " << FLAGS_tree2_inorder << endl;

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  
  vector<string> tree2_preorder_vec = split(FLAGS_tree2_preorder, ',');
  vector<string> tree2_inorder_vec = split(FLAGS_tree2_inorder, ',');

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);
  TreeNode *tree2_root = buildTreeByPreIn(&tree2_preorder_vec, &tree2_inorder_vec);
 
  cout << "tree1 preorder: " << endl; 
  preorder(tree1_root);
  cout << endl << "tree1 inorder: " << endl;
  inorder(tree1_root);
  cout << endl << "tree1 postorder: " << endl;
  postorder(tree1_root);
  cout << endl;

  cout << "tree2 preorder: " << endl; 
  preorder(tree2_root);
  cout << endl << "tree2 inorder: " << endl;
  inorder(tree2_root);
  cout << endl << "tree2 postorder: " << endl;
  postorder(tree2_root);
  cout << endl;
 
  cout << "It's " << isSameTree(tree1_root, tree2_root) 
       << " that tree1 and tree2 are the same";  
  return 0;
}
