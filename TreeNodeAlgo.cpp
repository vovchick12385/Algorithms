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