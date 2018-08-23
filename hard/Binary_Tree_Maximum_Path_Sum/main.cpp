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



int ans;
int maxSum(TreeNode *root) {
int maxHere = root->val;
int lsum, rsum, retval;

if (root->left && root->right) {
    lsum = maxSum(root->left);
    rsum = maxSum(root->right);
    retval = max(maxHere, maxHere + max(lsum, rsum));
    maxHere = max(maxHere, maxHere + max(lsum+rsum, max(lsum, rsum)));
} else if (root->left) {
    lsum = maxSum(root->left);
    retval = max(maxHere, maxHere + lsum);
    maxHere = retval;
} else if (root->right) {
    rsum = maxSum(root->right);
    retval = max(maxHere, maxHere + rsum);
    maxHere = retval;
} else {
    retval = maxHere;
}
ans = max(ans, maxHere);
	  
return retval;
}

int maxPathSum1(TreeNode* root) {
ans = root->val;
maxSum(root);
return ans;
}

vector<int> sumlist;
int call_sum(TreeNode* node) {
  if (nullptr == node) {
    return 0;
  }
  int cur_val = node->val;
  int sumleft = 0;
  int sumright = 0;
  if (nullptr != node->left) {
    sumleft = call_sum(node->left);
    sumlist.push_back(sumleft);
  }
  if (nullptr != node->right) {
    sumright = call_sum(node->right);
    sumlist.push_back(sumright);
  }
  int sumnodeleft = cur_val + sumleft;
  int sumnoderight = cur_val + sumright;
  int ret = max(cur_val, cur_val + max(sumleft,sumright));
  int sum = cur_val + sumleft +  sumright;
  sumlist.push_back(sumnodeleft);
  sumlist.push_back(sumnoderight);
  sumlist.push_back(cur_val);
  sumlist.push_back(sum);
  return ret;
}

int maxPathSum(TreeNode* root){
  int sum = call_sum(root);
  if (sumlist.empty()) {
    return -1;
  }
  sort(sumlist.begin(), sumlist.end(), greater<int>());
  return sumlist.at(0); 
}

int main(int argc, char* argv[]) {
  google::ParseCommandLineFlags(&argc, &argv, true);
  cout << "get tree1 preorder: " << FLAGS_tree1_preorder << endl;
  cout << "get tree1 inorder:  " << FLAGS_tree1_inorder << endl;

  vector<string> tree1_preorder_vec = split(FLAGS_tree1_preorder, ',');  
  vector<string> tree1_inorder_vec = split(FLAGS_tree1_inorder, ',');  

  TreeNode *tree1_root = buildTreeByPreIn(&tree1_preorder_vec, &tree1_inorder_vec);

  bfsTree(tree1_root);

  cout << "max tree path sum0: "  << maxPathSum(tree1_root) << endl;
  cout << "max tree path sum1: " << maxPathSum1(tree1_root) << endl;
  return 0;
}
