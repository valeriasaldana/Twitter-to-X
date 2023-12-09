// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	//  Your code here
	tableSize = M;
	table = new XUser*[tableSize];

    // Initialize each bucket to nullptr
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }

    numCollision = 0;  // Initialize the collision counter
}

XUser* HashTable::createUser(string username, string userBio)
{
	//  Your code here
	XUser* newUser = new XUser();  //allocate memory for a new user

    newUser->username = username;
    newUser->userBio = userBio;
    newUser->postCount = 0;  // Initialize post count to 0
    newUser->next = nullptr;  // Initialize the next pointer to nullptr

    // Create a new BST for the user
    newUser->bst = new BST();

    return newUser;
}

unsigned int HashTable::hashFunction(string username)
{
	//  Your code here
	unsigned int hashVal = 0; //initializing variable

	for (char c: username)
	{
		hashVal += static_cast<unsigned int>(c); //adding the ascii value of every character in the username
	}

	hashVal %= tableSize; //taking modulo with respect to table size.

	return hashVal; //returning the value
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{
	//  Your code here
	unsigned int value = hashFunction(username); //to get the hash value
	 XUser* newUser = createUser(username, userBio); //XUser* insertedUser = searchUser(username); //check if the username has already been inserted
	if (table[value] == nullptr)
	{
		table[value] = newUser; // return nullptr if the username already exists
	}
	else
	{
		numCollision++;
		newUser->next = table[value]; // handeling collisions by inserting at the head of the linked list.
		table[value] = newUser;
	}

	return newUser;
}

XUser* HashTable::searchUser(string username)
{
	//  Your code here
	unsigned int value = hashFunction(username); // calculate the value of username

	XUser* currUser = table[value]; //traverse the linked list at the hash value
	while (currUser != nullptr)
	{
		if (currUser->username == username) //check if the current username matches the search user
		{
			return currUser; //return the user node if it is found
		}

		currUser = currUser->next; // move to next user to ll
	}

	return nullptr;
}

void HashTable::printUsers()
{
	//  Your code here
	for (int i = 0; i < tableSize; i++)
    {
        cout << i << "|"; //print index for bucket

        XUser* currUser = table[i]; // traverse the ll in the current index
        
            while( currUser != nullptr )
            {
                cout << currUser->username << "->"; //print the username
                currUser = currUser->next; //go to the next node in ll
            }
			cout << "NULL" << endl;
    }
}

void HashTable::printAllPostByUser(string username) 
{
	//  Your code here
	XUser* user = searchUser(username);

	if (user == nullptr)
	{
		cout << "User does not exit, try again..." << endl;
		return;
	}

	cout << user->username << ":" << endl;
	cout << "| userBio: " << user->userBio << endl;
	cout << "| postCount: " << user->postCount << endl;
	cout << "| Posts: " << endl; 
	cout << endl;

	user->bst->displayPosts();
	cout << endl;

}

void HashTable::printMostLikedPost() 
{
	//  Your code here
	XPost* mostLikedPost = nullptr; //initialize post to store most liked
	XUser* mostLikedUser = nullptr; // to store username

	for (int i = 0; i < tableSize; i++) //traverse each bucket in hash
	{
		XUser* currUser = table [i];

		while(currUser != nullptr) //traverse ll in bucket
		{
			XPost* currPost = currUser->bst->mostPopular(); //traverse posts in users bst
			if (currPost != nullptr && (mostLikedPost == nullptr || currPost->likes > mostLikedPost->likes)) //check if current post has more likes than the current most liked post
			{
				mostLikedPost = currPost;
				mostLikedUser = currUser;
			}
			currUser = currUser->next; //move to the next node in ll
		}
	}

	if(mostLikedPost != nullptr) //check if most liked post was found
	{
		// Display information about the most liked post and its user
        cout << "Most liked post by: " << mostLikedUser->username << endl;
        cout << "| userBio: " << mostLikedUser->userBio << endl;
        cout << "| postCount: " << mostLikedUser->postCount << endl;
        cout << "| Post:" << endl;
		cout << mostLikedPost->postedTime << endl;
        cout << "__| likes: " << mostLikedPost->likes << endl;
        cout << "__|" << mostLikedPost->xContents << endl;
	}
	else
	{
		cout << "No posts found." << endl; //if no posts are found
	}

}

int HashTable::longestChain() 
{
	//  Your code here

	int longestChain = 0; //initialize longest chain variable

	for(int i = 0; i < tableSize; i++) //traverse hash table
	{
		int currLength = 0;
		XUser* currUser = table[i];

		while (currUser != nullptr) //traverse ll in bucket
		{
			currLength++;
			currUser = currUser->next; //move to the next node in ll
		}

		if(currLength > longestChain)//update longest chain
		{
			longestChain = currLength;
		}
	}
	return longestChain;
}
    
