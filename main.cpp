#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <algorithm>
#include <unordered_map>

using namespace std;


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
    while (it2 && it2->next)
    {
        it1 = it1->next;
        it2 = it2->next->next;
    }
    return it1;
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
    vector<int> outvec;
    for (const auto& c : nums)
    {
        if (c != val)
        {
            outvec.push_back(c);
        }
    }
    int out = outvec.size();
    swap(nums, outvec);
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

int removeDuplicates(vector<int>& nums) {
    auto it1 = nums.begin();
    vector<int> copy;
    copy.push_back(*it1);
    auto it2 = copy.begin();
    for (it1; it1 != nums.end(); ++it1)
    {
        if (*it1 != *it2)
        {
            copy.push_back(*it1);
            it2 = copy.end();
            it2--;
        }
    }
    int t = copy.size();
    swap(nums, copy);
    return t;

}

ListNode* reverseList(ListNode* head) {
    auto prev = head;
    if (head == nullptr || head->next == nullptr)
        return head;
    auto next = head->next;
    if (head->next->next)
        head = head->next->next;
    else
    {
        prev->next = nullptr;
        next->next = prev;
        return next;
    }
    prev->next = nullptr;
    next->next = prev;
    while (head->next)
    {

        auto it = prev;
        prev = next;
        prev->next = it;
        next = head;
        head = head->next;
        next->next = prev;
    }
    prev = next;
    next = head;
    next->next = prev;
    return next;
}

bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return true;
    if (head->next->next == nullptr)
    {
        if (head->val != head->next->val)
            return false;
        return true;
    }
    auto it1 = middleNode(head);
    it1 = reverseList(it1);


    do
    {
        if (head->val != it1->val)
            return false;
        head = head->next;
        it1 = it1->next;
    } while (it1->next);
    if (head->val != it1->val)
        return false;
    return true;
}

string reverseWords(string s) {
    string str = "";
    vector<char> str_vec;
    for (const auto& c : s)
    {
        if (c != ' ')
            str_vec.push_back(c);
        else
        {
            reverseString(str_vec);
            for (const auto& c : str_vec)
            {
                str += c;
            }
            str_vec.clear();
            str += " ";
        }
    }
    reverseString(str_vec);
    for (const auto& c : str_vec)
    {
        str += c;
    }
    return str;

}

vector<int> sortArrayByParity(vector<int>& nums) {
    auto it1 = nums.begin();
    auto it2 = nums.begin();
    vector<int> even, odd;
    for (auto it = nums.begin(); it != nums.end(); ++it)
    {
        if (*it % 2 == 0)
        {
            even.push_back(*it);
        }
        else
            odd.push_back(*it);
    }
    for (auto it = odd.begin(); it != odd.end(); ++it)
    {
        even.push_back(*it);
    }
    return even;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head->val == n && head->next == nullptr)
    {
        head = nullptr;
        return head;
    }
    head = reverseList(head);
    auto it1 = head;
    auto it2 = head;
    if (n != 1)
    {
        for (int i = 0; i < n - 1; ++i)
        {

            it1 = it2;
            it2 = it2->next;

        }

        it1->next = it2->next;
        it2 = it2->next;
    }
    else
    {
        head = head->next;
    }
    head = reverseList(head);
    return head;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr && list2 != nullptr)
        return list2;
    else if (list2 == nullptr && list1 != nullptr)
        return list1;
    else if (list1 == nullptr && list2 == nullptr)
        return nullptr;
    ListNode* dummy = new ListNode();
    ListNode* temp = dummy;
    while (list1 && list2)
    {
        if (list1->val <= list2->val)
        {
            temp->next = new ListNode(list1->val);
            temp = temp->next;
            list1 = list1->next;
        }
        else
        {
            temp->next = new ListNode(list2->val);
            temp = temp->next;
            list2 = list2->next;
        }
    }
    while (list1)
    {
        temp->next = new ListNode(list1->val);
        temp = temp->next;
        list1 = list1->next;
    }
    while (list2)
    {
        temp->next = new ListNode(list2->val);
        temp = temp->next;
        list2 = list2->next;
    }
    dummy = dummy->next;
    return dummy;
}

ListNode* sortList(ListNode* head) {
    if (head == nullptr || head->next == nullptr)
        return head;
    if (head->next->next == nullptr)
    {
        if (head->val >= head->next->val)
        {
            auto temp = new ListNode(head->next->val, head);
            temp->next->next = nullptr;
            return temp;
        }
        else
            return head;
    }
    auto it1 = middleNode(head);
    auto it2 = head;
    auto dummy = new ListNode(head->val);
    auto temp = dummy;
    while (it2->next != it1)
    {
        it2 = it2->next;
        temp->next = new ListNode(it2->val);
        temp = temp->next;
    }

    dummy = sortList(dummy);
    it1 = sortList(it1);
    dummy = mergeTwoLists(dummy, it1);
    return dummy;
}

int main() {
    
    int n;
    cin >> n;
    int k;
    vector<int> nums;
    for (int i = 0; i < n; ++i)
    {
        cin >> k;
        nums.push_back(k);
    }
    removeDuplicates(nums);
    for (int i = 0; i < n; ++i)
    {
        cout << nums[i] << " ";
    }
   return 0;
}


