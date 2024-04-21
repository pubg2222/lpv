#include<iostream>
#include<stdlib.h>
#include<queue>
#include<omp.h>
//#include <omp.h>
#include <stdio.h>
#include <stack>
double start,stop,start_p,stop_p, startDfs, stopDfs, startDfs_p, stopDfs_p;
using namespace std;

class node
{
	public:
    		node *left, *right;
    		int data;
};    

class Breadthfs
{
	public: 
 	node *insert(node *, int);
 	void bfs(node *);
};

node *insert(node *root, int data)
{
    	if(!root)
    	{   	 
   		root=new node;
   	 	root->left=NULL;
   	 	root->right=NULL;
   	 	root->data=data;
   	 	return root;
    	}
    	queue<node *> q;
    	q.push(root);
    	while(!q.empty())
    	{
   		node *temp=q.front();
   	 	q.pop(); 
   	 	if(temp->left==NULL)
   	 	{		 
   		 	temp->left=new node;
   		 	temp->left->left=NULL;
   		 	temp->left->right=NULL;
   		 	temp->left->data=data;    
   		 	return root;
   	 	}
   	 	else
   	 	{
   	 		q.push(temp->left);
   	 	}
   	 	if(temp->right==NULL)
   	 	{	 		 
   			temp->right=new node;
   		 	temp->right->left=NULL;
   		 	temp->right->right=NULL;
   		 	temp->right->data=data;    
   		 	return root;
   	 	}
   	 	else
   	 	{
   	 		q.push(temp->right);
   	 	}
    	}   
    	return 0;
}

void bfsMP(node *head)
{
	start_p=omp_get_wtime();
   	queue<node*> q;
   	q.push(head);   	 
   	int qSize;
   	while (!q.empty())
   	{
   		qSize = q.size();
   		#pragma omp parallel for
            	//creates parallel threads
   		for (int i = 0; i < qSize; i++)
   		{
   			node* currNode;
   			#pragma omp critical
   			{
   				currNode = q.front();
   			   	q.pop();
   			   	cout<<"->"<<currNode->data;
   			}// prints parent node
   			#pragma omp critical
   			{
   			 	if(currNode->left)// push parent's left node in queue
   					q.push(currNode->left);
   			 	if(currNode->right)
   				 	q.push(currNode->right);
   			 }// push parent's right node in queue   	 
   		}
   	}
	stop_p=omp_get_wtime();	
}
void bfsSeq(node *head)
{
	start=omp_get_wtime();
   	queue<node*> q;
   	q.push(head);   	 
   	//int qSize;
   	while (!q.empty())
   	{
   		int qSize = q.size();
   		for (int i = 0; i < qSize; i++)
   		{
   			node* currNode = currNode = q.front();
   			q.pop();
			cout<<"->"<<currNode->data;
   			if(currNode->left)// push parent's left node in queue
				q.push(currNode->left);
   			if(currNode->right)
				q.push(currNode->right);// push parent's right node in queue   	 
   		}
   	}
	stop=omp_get_wtime();	
}

void dfsSeq(node *head) {
    startDfs = omp_get_wtime();
    stack<node*> st;
    st.push(head);   	 
    while (!st.empty()) {
        node* currNode = st.top();
        st.pop();
        cout << "\t" << currNode->data; // Process the current node
        
        // Push child nodes into the stack
        if (currNode->right)
            st.push(currNode->right);
        if (currNode->left)
            st.push(currNode->left);
    }
    stopDfs = omp_get_wtime();
}

void dfsMP(node *head) {
    startDfs_p = omp_get_wtime();
    stack<node*> st;
    st.push(head);   	 
    while (!st.empty()) {
        #pragma omp parallel num_threads(2)
        {
            node* currNode;
            #pragma omp critical
            {
                currNode = st.top();
                st.pop();
            }
            cout << "\t" << currNode->data; // Process the current node
            
            // Push child nodes into the stack
            if (currNode->right)
                st.push(currNode->right);
            if (currNode->left)
                st.push(currNode->left);
        }
    }
    stopDfs_p = omp_get_wtime();
}

int main()
{
    	node *root=NULL;
    	int data,i, n=7;
   	int ans;
    	int a[n]={1,2,3,4,5,6,7};
	for( i= 0; i<n; i++)
	{
	   	//a[i]=(rand()%25)+1;
	   	root=insert(root,a[i]);
	}
	cout<<"\nBFS traversal (Sequential)";
	bfsSeq(root);
	cout<<"\n****************************************************************";
	cout << "\nTime Sequential  = " << stop-start;\
	cout<<"\n****************************************************************";
	cout<<"\nBFS traversal (parallel)";
    	bfsMP(root);
    	cout<<"\n****************************************************************";
    	cout << "\nTime Parallel  = " << stop_p-start_p;\
    	cout<<"\n****************************************************************\n";
    	

    	return 0;
}
