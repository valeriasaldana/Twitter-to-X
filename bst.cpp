#include "bst.hpp"

BST::BST() {
	// Your code here...
}

BST::~BST() {
	// Your code here...
}

XPost* BST::createPost(float time, string content, int likes) 
{
	// Your code here...
}

void BST::insertPost(float time, string content, int likes) 
{
	// Your code here...
}

XPost* BST::insertHelper(XPost* rt, XPost* pst) 
{
	// Your code here...
}

void BST::displayPosts() 
{
	// Your code here...
}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	// Your code here...
}

XPost* BST::mostPopular() 
{
	// Your code here...
}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	// Your code here...
}
