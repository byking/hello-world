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

bool calcPathSum(TreeNode* root, int sum, int cur_sum) {
  if (nullptr == root) return false;
  cur_sum += root->val;
  if (cur_sum == sum && nullptr == root->left && nullptr == root->right) {
    return true;
  }
  return calcPathSum(root->left, sum, cur_sum) || calcPathSum(root->right, sum, cur_sum);
}

bool hasPathSum(TreeNode* root, int sum) {
  if (nullptr == root) {
    return false;
  }
  int cur_sum = 0;
  return calcPathSum(root, sum, cur_sum);
}

void dfsTraversal(TreeNode* root, int sum, int cur_sum, vector<int>& path_res, vector<vector<int>>& res) {
  if (nullptr == root) return;
  cur_sum += root->val;
  path_res.push_back(root->val);
  if (cur_sum == sum && nullptr == root->left && nullptr == root->right) {
    res.push_back(path_res);
  }
  dfsTraversal(root->left, sum, cur_sum, path_res, res);
  dfsTraversal(root->right, sum, cur_sum, path_res, res);
  path_res.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int sum) {
  vector<vector<int>> res;
  vector<int> path_res;
  dfsTraversal(root, sum, 0, path_res, res);
  return res;
}

void dfsTraversalTree(TreeNode* root, vector<string>& paths, string& path) {
  if (nullptr == root) return;
  string old_path = path;
  if (path.empty()) {
    path = to_string(root->val);
  }else {
    path = path + "->" + to_string(root->val);
  }
  if (nullptr == root->left && nullptr == root->right) {
    paths.push_back(path);
  }
  dfsTraversalTree(root->left, paths, path); 
  dfsTraversalTree(root->right, paths, path);
  path = old_path; 
}

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> paths;
  string path = "";
  dfsTraversalTree(root, paths, path); 
  return paths;
}

int equalSumPathCount = 0;

void dfsCheckTree(TreeNode* root, int sum, int cur_sum) {
  if (nullptr == root) return;
  cur_sum += root->val;
  if (cur_sum == sum) {
    equalSumPathCount++;
  }
  dfsCheckTree(root->left, sum, cur_sum);
  dfsCheckTree(root->right, sum, cur_sum);
}

int pathSumNotOnlyFromRoot(TreeNode* root, int sum) {
  int cur_sum = 0;
  if (nullptr == root) return 0; 
  
  dfsCheckTree(root, sum, cur_sum);
  pathSumNotOnlyFromRoot(root->left, sum);
  pathSumNotOnlyFromRoot(root->right, sum); 
  return equalSumPathCount;
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);

  bfsTree(tree1_root);

  cout << "has sum 22: " << hasPathSum(tree1_root, 22);
  cout << endl;
  cout << "get path sum nodes: ";
  vector<vector<int>> res = pathSum(tree1_root, 22);
  for(vector<vector<int>>::iterator it = res.begin(); it != res.end(); it++) {
    for(vector<int>::iterator i = (*it).begin(); i != (*it).end(); i++) {
      cout << *i << ";";
    }
    cout << endl;
  }

  cout << "get paths of tree:" << endl;
  vector<string> paths = binaryTreePaths(tree1_root);
  for (vector<string>::iterator it = paths.begin(); it != paths.end(); it++) {
    cout << *it << endl;
  }

  cout << "path node equal sum(not only from root or end at leaf): ";
  cout << pathSumNotOnlyFromRoot(tree1_root, 8); 
  cout << endl;
  return 0;
}
