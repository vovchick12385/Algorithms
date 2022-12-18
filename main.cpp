#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if (n == 0)
        return;
    auto it1 = nums1.begin();
    auto it2 = nums2.begin();
    while (it2 != nums2.end())
    {
        if (*it1 <= *it2)
        {
            if (*it1 != 0)
            {
                ++it1;
                continue;
            }
            else
            {
                *it1 = *it2;
                ++it2;
                ++it1;
            }
            
        }
        else if (*it1 > *it2)
        {
            nums1[m] = *it1;
            *it1 = *it2;
            ++it2;
            m++;
        }
    }
    sort(nums1.begin(), nums1.end());
}

bool isPalindrome(string s) {

    if (s.size() == 1)
        return true;
    transform(s.begin(), s.end(), s.begin(), [](unsigned char c) {
        if (!isalnum(c))
            return int(' ');
        return tolower(c);
    });
    string v;
    copy_if(s.begin(), s.end(), back_inserter(v), [](char c) { return c != ' '; });
    if (v.size() == 1 || v.size() == 0)
        return true;
    auto it1 = v.begin();
    auto it2 = v.end();
    --it2;
    auto n = v.size();
    for (int i = 0; i < n - 1; ++i)
    {
        if (*it1 != *it2)
            return false;
        ++it1;
        --it2;
    }
    return true;
}

bool hasCycle(ListNode* head) {
    if (head == nullptr)
        return false;
    ListNode* it1 = head;
    ListNode* it2 = head;
    while (it2->next != nullptr)
    {
        it1 = it1->next;
        if (it2->next->next == nullptr)
            return false;
        it2 = it2->next->next;
        if (it1->next == it2->next)
            return true;
    }
    return false;
}

ListNode* middleNode(ListNode* head) {
    auto it1 = head;
    auto it2 = head;
    while (it2->next != nullptr)
    {
        if (it1->next != nullptr)
        {
            it1 = it1->next;

        }
        else
            break;

        if (it2->next->next != nullptr)
            it2 = it2->next->next;
        else
            break;

    }
    return it1;
}

ListNode* sortList(ListNode* head) {
    if (head->next->next == nullptr)
    {
        auto it1 = head->val;
        auto it2 = head->next;
        if (it1 > it2->val)
        {
            head->val = it2->val;
            it2->val = it1;
        }
        return head;
    }
    else if (head->next == nullptr)
    {
        return head;
    }
    auto it1 = middleNode(head);
    auto it2 = it1->next;
    it1->next = nullptr;
    head = sortList(head);
    it2 = sortList(it2);
    it1->next = it2;
    return head;
}

void reverseString(vector<char>& s) {
    auto it1 = s.begin();
    auto it2 = s.end();
    --it2;
    char c;
    for (int i = 0; i < s.size()/2; ++i)
    {
        c = *it1;
        *it1 = *it2;
        *it2 = c;
        ++it1;
        --it2;
    }
}


void moveZeroes(vector<int>& nums) {
    auto it1 = nums.begin();
    auto it2 = nums.begin();
    for (int i = 0; i < nums.size(); ++i)
    {
        if (*it1 == 0)
        {
            while (*it2 == 0)
            {
                if (it2 != (nums.end() - 1))
                    ++it2;
                else
                    break;
            }
            *it1 = *it2;
            *it2 = 0;
            
            if (it1 == nums.end() || it2==nums.end())
                return;
            
            
        }
        ++it1;
        it2 = it1;
    }
}

int removeElement(vector<int>& nums, int val) {
    auto it1 = nums.begin();
    auto it2 = nums.end();
    --it2;
    int out;
    while (it1 != it2)
    {
        if (*it1 == val)
        {
            if (*it2 != val)
            {
                *it1 = *it2;
                *it2 = val;
                ++it1;
                --it2;
            }
        }
        else
        {
            ++it1;
            --it2;
        }
    }
    out = distance(nums.begin(), it1) - 1;
    return out;
}

vector<int> twoSum(vector<int>& numbers, int target) {
    auto it1 = numbers.begin();
    auto it2 = numbers.end();
    --it2;
    int sum = *it1 + *it2;
    while (sum != target)
    {
        if (sum > target)
        {
            --it2;
        }
        else
        {
            ++it1;
        }
        sum = *it1 + *it2;
        if (it1 == it2)
            continue;
    }
    vector<int> out;
    out.push_back(distance(numbers.begin(), it1) + 1);
    out.push_back(distance(numbers.begin(), it2) + 1);
    return out;
}

int main() {
    
    int n;
    cin >> n;
    int k;
    vector<int> nums;
    int 
    for (int i = 0; i < n; ++i)
    {
        cin >> k;
        nums.push_back(k);
    }
    moveZeroes(nums);
    for (int i = 0; i < n; ++i)
    {
        cout << nums[i] << " ";
    }
   return 0;
}


