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
        int h; // current node height
        int l; // subtree left limit
        int r; // subtree right limit
        int val;
        TreeNode* left;
        TreeNode* right;
        Node(int h, int l, int r, int val, TreeNode* left, TreeNode* right) : h(h), l(l), r(r), val(val), left(left), right(right) {}
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

int getHeight(TreeNode* root) {
  if(nullptr == root) return 0;
  return max(getHeight(root->left),getHeight(root->right)) + 1;
}


vector<vector<string> > printTree(TreeNode* root) {
        int height = getHeight(root);
        int row = height;
        int col = (1 << height) - 1; 
        cout << "row:" << row << endl;
        cout << "col:" << col << endl;
	vector<vector<string> > res(row, vector<string>(col, " "));
	queue<Node*> *my_queue = new queue<Node*>();
        Node *node = new Node(0,0,col,root->val,root->left,root->right);
	my_queue->push(node);
        while(!my_queue->empty()) {
            Node *node = my_queue->front();
            my_queue->pop();
            int height = node->h;
            int left = node->l;
            int right = node->r;
            int mid = (left + right) / 2;
            res[height][mid] = to_string(node->val);
            if (nullptr != node->left) {
                Node *node1 = new Node(height+1, left, mid, node->left->val, node->left->left, node->left->right);
                my_queue->push(node1);
            }    
            if (nullptr != node->right) {
                Node *node2 = new Node(height+1, mid+1, right, node->right->val, node->right->left, node->right->right);
                my_queue->push(node2);
            }
	    delete node;
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
