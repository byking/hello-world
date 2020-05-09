#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (nums[j] < pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    swap(nums[i], nums[right]); //pay attention
    return i;
}

void quick_sort(vector<int>& nums, int left, int right) {
    if (left >= right) {
        return;
    }
    int p = partition(nums, left, right); // p+1==k [0,p] 为前k小/大数
    quick_sort(nums, left, p-1);
    quick_sort(nums, p+1, right);
}

void quick_sort(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    stack<pair<int, int>> records;
    records.push(make_pair(left, right));
    while(!records.empty()) {
        pair<int, int> record = records.top();
        records.pop();
 	if (record.first >= record.second) continue;
        int p = partition(nums, record.first, record.second);
        records.push(make_pair(record.first, p-1));
        records.push(make_pair(p+1, record.second));
    }
}

void merge(vector<int>& nums, int left, int mid, int right) {
    vector<int> tmp = vector<int>(right - left + 1, 0);
    int i = left;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
	    tmp[k++] = nums[i];
	    i++;
        }else {
            tmp[k++] = nums[j];
	    j++;
	    //num += (mid - i + 1) 逆序对个数 
        }
    }
    while (i <= mid) {
        tmp[k++] = nums[i];
        i++;
    }
    while (j <= right) {
        tmp[k++] = nums[j];
        j++;
    }
    for (int s = 0; s < tmp.size(); s++) {
        nums[left + s] = tmp[s];  //pay attention
    }
}

void merge_sort(vector<int>& nums, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + ((right - left) >> 1);
    merge_sort(nums, left, mid);
    merge_sort(nums, mid+1, right);
    merge(nums, left, mid, right);
}

/* heap sort
   1. 完全二叉树用数组存储，首位空，从1开始，方便*2操作
   2. 建堆: 
   3. 堆排序
*/
void heapfiy(vector<int>& nums, int n, int i) {
    while (true) {
        int maxPos = i;
        if (i*2 <= n && nums[i*2] > nums[maxPos]) {
            maxPos = i * 2;
        }
        if ((i*2 + 1) <= n && nums[i*2+1] > nums[maxPos]) {
            maxPos = i * 2 + 1;
        }
        if (i == maxPos) {
            break;
        }
        std::swap(nums[maxPos], nums[i]);
        i = maxPos;
    } 
}

void build_heap(vector<int>& nums, int n) {
    for (int i = n/2; i >= 1; i--) {
        heapfiy(nums, n, i);
    }
}

void heap_sort(vector<int>& nums, int n) {
    build_heap(nums, n);
    int k = n;
    while (k > 1) {
        swap(nums[k], nums[1]);
        k--;
        heapfiy(nums, k, 1);
    }
}

int remove_heap_top_item(vector<int>& nums, int n) {
    swap(nums[1], nums[n]);
    n--;
    heapfiy(nums, n, 1);
    return n;
}

int main() {
    vector<int> nums = {-1, 5, 4, 3, 2, 1};
    //quick_sort(nums, 0, nums.size() - 1);
    //quick_sort(nums);
    //merge_sort(nums, 0, nums.size() - 1);
    heap_sort(nums, nums.size() - 1);
    for (auto num : nums) {
	cout << num << " ";
    }
    int n = remove_heap_top_item(nums, nums.size() - 1);
    cout << n << endl;
    for (auto num : nums) {
        cout << num << " ";
    } 
    cout << endl;
    return 0;
}
