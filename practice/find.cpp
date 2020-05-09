#include <iostream>
#include <vector>
using namespace std;

// 返回数组下标方便处理找不到的情况。-1就是没有找到
int binary_find(vector<int>& nums, int aim) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
	if (nums[mid] < aim) {
            left = mid + 1;
        }else if (nums[mid] > aim) {
            right = mid - 1;
        }else {
            return mid;
        }
    }
    return -1;
}

//假如有重复值 找等于给定值的第一个元素
int binary_find_first(vector<int>& nums, int aim) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
	if (nums[mid] < aim) {
            left = mid + 1;
        }else if (nums[mid] > aim) {
            right = mid - 1;
        }else{
	    if ((mid - 1) >= 0 && nums[mid-1] == aim) { //等于的再往前看一个
                right = mid - 1;	 
            }else{
                return mid;
            }
        }
    }
    return -1;
}

//假如有重复值 找等于给定值的最后一个元素
int binary_find_last(vector<int>& nums, int aim) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
	if (nums[mid] < aim) {
            left = mid + 1;
        }else if (nums[mid] > aim) {
            right = mid - 1;
        }else{
	    if ((mid + 1) <= right && nums[mid + 1] == aim) { //等于的再往后看一个
                left = mid + 1;	 
            }else{
                return mid;
            }
        }
    }
    return -1;
}

//查找第一个大于等于的元素
int binary_find_first_greater_than(vector<int>& nums, int aim) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
	if (nums[mid] < aim) {
            left = mid + 1;
        }else if (nums[mid] >= aim) {
	    if ((mid - 1) >= left && nums[mid - 1] >= aim) { //等于的再往后看一个
                right = mid - 1;	 
            }else{
                return mid;
            }
        }
    }
    return -1;
}

//查找最后一个小于等于的元素
int binary_find_last_less_than(vector<int>& nums, int aim) {
    int left = 0;
    int right = nums.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (nums[mid] > aim) {
            right = mid - 1;
        }else {
            if ((mid + 1) <= right && nums[mid+1] <= aim) {
                left = mid + 1;
            }
	    return mid;
        }
    }
    return -1;
}

/* 找出现一次的数，其他数都是俩俩相邻出现
   1,2,2,3,3 -> 1  5,5,1,2,2,3,3 -> 1 */
int binary_find_once(vector<int>& nums) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right) {
       int mid = left + ((right - left) >> 1);
       if ((mid - 1) >= 0 && nums[mid] == nums[mid-1]) {
           if ((mid - left + 1) % 2 == 1) {
	       right = mid;
           }else {
               left = mid + 1;
           }
       }else if((mid + 1) <= right && nums[mid] == nums[mid+1]) {
	   if ((right - mid + 1) % 2 == 1) {
               left = mid;
           }else {
	       right = mid - 1;
           }
       }else {
	   return mid;
       }  
    } 
    return -1; 
}

int main() { 
    vector<int> nums = {1, 2, 3, 4, 5};
    int index = binary_find(nums, 2);
    cout << "index=" << index << endl;
    
    vector<int> nums1 = {1, 2, 2, 3, 4, 5};
    int index1 = binary_find_first(nums1, 2);
    cout << "index_first=" << index1 << endl;
    int index2 = binary_find_last(nums1, 2);
    cout << "index_last=" << index2 << endl;
    int index3 = binary_find_first_greater_than(nums1, 2);
    cout << "index_first_greater_than=" << index3 << endl;
    int index4 = binary_find_last_less_than(nums1, 2);
    cout << "index_last_less_than=" << index4 << endl;
   
    vector<int> nums2 = {1,2,2,3,3};
    cout << "index_once=" << binary_find_once(nums2) << endl;
    vector<int> nums4 = {5,5,1,2,2,3,3};
    cout << "index_once=" << binary_find_once(nums4) << endl;
	 
    return 0;
}
