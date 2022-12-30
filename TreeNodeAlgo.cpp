vector<int> inorderTraversal(TreeNode* root) {
    if (root == nullptr)
    {
        return vector<int>();
    }
    vector<int> out;
    auto vecL = inorderTraversal(root->left);
    auto vecR = inorderTraversal(root->right);

    for (const auto& c : vecL)
    {
        out.push_back(c);
    }
    out.push_back(root->val);
    for (const auto& c : vecR)
    {
        out.push_back(c);
    }
    return out;
}

vector<int> preorderTraversal(TreeNode* root) {

    if (root == nullptr)
    {
        return vector<int>();
    }
    vector<int> out;
    auto vecL = preorderTraversal(root->left);
    auto vecR = preorderTraversal(root->right);
    out.push_back(root->val);
    for (const auto& c : vecL)
    {
        out.push_back(c);
    }

    for (const auto& c : vecR)
    {
        out.push_back(c);
    }
    return out;
}

vector<int> postorderTraversal(TreeNode* root) {

    if (root == nullptr)
    {
        return vector<int>();
    }
    vector<int> out;
    auto vecL = postorderTraversal(root->left);
    auto vecR = postorderTraversal(root->right);

    for (const auto& c : vecL)
    {
        out.push_back(c);
    }

    for (const auto& c : vecR)
    {
        out.push_back(c);
    }
    out.push_back(root->val);
    return out;
}

//construct-binary-tree-from-inorder-and-postorder-traversal
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    int rootval = *(postorder.end() - 1);
    TreeNode* Root = new TreeNode(rootval);
    if (inorder.size() == 1)
    {
        return Root;
    }
    auto it = find(inorder.begin(), inorder.end(), rootval);
    if (it == inorder.end() - 1)
    {
        vector<int> lefts(inorder.begin(), it);
        vector<int> rights(postorder.begin(), postorder.end() - 1);
        Root->left = buildTree(lefts, rights);
        return Root;
    }
    else if (it == inorder.begin())
    {
        vector<int> lefts(it + 1, inorder.end());
        vector<int> rights(postorder.begin(), postorder.end() - 1);
        Root->right = buildTree(lefts, rights);
        return Root;
    }
    vector<int> leftsideInorder(inorder.begin(), it);
    vector<int> rightsideInorder(it + 1, inorder.end());
    size_t EndLeft = postorder.size() - 1 - rightsideInorder.size();
    auto it2 = postorder.begin() + EndLeft;
    vector<int> leftsidePostorder(postorder.begin(), it2);
    vector<int> rightsidePostorder(it2, postorder.end() - 1);
    Root->left = buildTree(leftsideInorder, leftsidePostorder);
    Root->right = buildTree(rightsideInorder, rightsidePostorder);
    return Root;
}

//construct-binary-tree-from-preorder-and-inorder-traversal
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (inorder.size() == 1)
    {
        return new TreeNode(inorder[0]);
    }
    int root = preorder[0];
    auto Root = new TreeNode(root);
    auto init = find(inorder.begin(), inorder.end(), root);
    if (init == inorder.end() - 1)
    {
        vector<int> preorL(preorder.begin() + 1, preorder.end());
        vector<int> inorderL(inorder.begin(), inorder.end() - 1);
        Root->left = buildTree(preorL, inorderL);
        return Root;
    }
    else if (init == inorder.begin())
    {
        vector<int> preorderl(preorder.begin() + 1, preorder.end());
        vector<int> inorderL(init + 1, inorder.end());
        Root->right = buildTree(preorderl, inorderL);
        return Root;
    }

    vector<int> inorderL(inorder.begin(), init);
    vector<int> inorderR(init + 1, inorder.end());
    size_t endLeft = preorder.size() - inorderR.size();
    auto endit = preorder.begin() + endLeft;
    vector<int> preorderL(preorder.begin() + 1, endit);
    vector<int> preorderR(endit, preorder.end());
    Root->left = buildTree(preorderL, inorderL);
    Root->right = buildTree(preorderR, inorderR);

    return Root;
}

//binary-tree-level-order-traversal-ii
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    queue<TreeNode*> tree;
    tree.push(root);
    tree.push(nullptr);
    vector<int> level;
    vector<vector<int>> out, current;
    if (root == nullptr)
        return out;
    while (!tree.empty())
    {
        auto it = tree.front();
        tree.pop();
        if (it)
        {
            level.push_back(it->val);
            if (it->left)
                tree.push(it->left);
            if (it->right)
                tree.push(it->right);
        }
        else
        {
            current.push_back(level);
            level.resize(0);
            if (tree.size() != 0)
                tree.push(nullptr);
        }
    }
    for (auto it = current.rbegin(); it != current.rend(); ++it)
    {
        out.push_back(*it);
    }
    return out;
}

//median-of-two-sorted-arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    vector<int> sortedArray;
    auto it1 = nums1.begin();
    auto it2 = nums2.begin();

    while (it1 != nums1.end() && it2 != nums2.end())
    {
        if (*it1 < *it2)
        {
            sortedArray.push_back(*it1);

            it1++;
        }
        else
        {
            sortedArray.push_back(*it2);

            ++it2;
        }
    }
    while (it1 != nums1.end())
    {
        sortedArray.push_back(*it1);

        ++it1;
    }
    while (it2 != nums2.end())
    {
        sortedArray.push_back(*it2);

        ++it2;
    }
    double out;
    if (sortedArray.size() % 2)
    {
        out = sortedArray[sortedArray.size() / 2];
    }
    else
    {
        double i = sortedArray[sortedArray.size() / 2];
        double j = sortedArray[(sortedArray.size() - 1) / 2];
        out = (i + j) / 2;

    }
    return out;
}