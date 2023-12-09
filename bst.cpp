#include "bst.hpp"

BST::BST() {
	// Your code here...
	root = nullptr;
	XPost* createPost = new XPost();
	size = 0;
}

void _destructpost(XPost *rt) {
    if (rt == nullptr) 
	{
		return;
	}
    else {
        _destructpost(rt->left);
        _destructpost(rt->right);
        delete rt;
    }
}

BST::~BST() {
	// Your code here...
	_destructpost(root);
}

XPost* BST::createPost(float time, string content, int likes) 
{
	// Your code here...

	XPost* newPost = new XPost();
	newPost ->left = nullptr;
	newPost ->right = nullptr;
	newPost ->likes = likes;
	newPost ->postedTime = time;
	newPost ->xContents = content;
	size = 0;

	return newPost;
}

void BST::insertPost(float time, string content, int likes) 
{
	// Your code here...
	XPost* Post = createPost(time, content, likes); // create the post with the parameters
	root = insertHelper(root, Post); //insert post into bst
}

XPost* BST::insertHelper(XPost* rt, XPost* pst) 
{
	// Your code here...
	if (rt == nullptr) // if tree is empty, insert new post at root
	{
		return pst;
	}

	if (pst->postedTime < rt->postedTime)// if the posted time of new post is less than the time of the previous post, go left
	{
		rt->left = insertHelper(rt->left, pst);
	}
	else //go right if greater
	{
		rt->right = insertHelper(rt->right, pst);
	}

	return rt;
}

void BST::displayPosts() 
{
	// Your code here...
	displayHelper(root);
	
}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	// Your code here...
	if (rt == nullptr)
	{
		return;
	}

	displayHelper(rt->left); //fisrt recurse left

	cout << rt->postedTime << endl;
	cout << "__| likes: " << rt->likes << endl;
	cout << "__| " << rt->xContents << endl;
	
	displayHelper(rt->right); 
}

XPost* BST::mostPopular() 
{
	// Your code here...
	XPost* mostLikedPost = nullptr;  // To store the most liked post
    mostPopularHelper(root, mostLikedPost);
    return mostLikedPost;
}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	// Your code here...
	if (rt == nullptr)
	{
		return;
	}

	mostPopularHelper(rt->left, mostLiked);

	if (mostLiked == nullptr || rt->likes > mostLiked->likes) 
	{
        mostLiked = rt;
    }
	mostPopularHelper(rt->right, mostLiked);
}
