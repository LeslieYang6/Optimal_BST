
// Dynamic Programming code for Optimal Binary Search  
// Tree Problem 
#include <stdio.h> 
#include <limits.h> 
//最优二叉树节点
struct Optimal_BST_Node
{
    int key;
    int freq;
    Optimal_BST_Node* right;
    Optimal_BST_Node* left;
    Optimal_BST_Node()
    {
        key=0;
        freq=0;
        right= nullptr;
        left = nullptr;
    }
};

//构造最优二叉树
Optimal_BST_Node* BuildOptimalBST(int **media,Optimal_BST_Node*root,int i,int j,int keys[],int freq[])
{
    if(i>j)
        return root;
    root=new Optimal_BST_Node;
    int k=media[i][j];
    root->key=keys[media[i][j]];
    root->freq=freq[media[i][j]];
    root->right=BuildOptimalBST(media,root->right,media[i][j]+1,j,keys,freq);
    root->left=BuildOptimalBST(media,root->left,i,media[i][j]-1,keys,freq);
    return root;

}
// A utility function to get sum of array elements  
// freq[i] to freq[j] 
int sum(int freq[], int i, int j); 
  
/* A Dynamic Programming based function that calculates 
  minimum cost of a Binary Search Tree. */
int optimalSearchTree(int keys[], int freq[], int n,int **&media)
{ 
    /* Create an auxiliary 2D matrix to store results  
      of subproblems */
    int cost[n][n];
    /* 为二叉树申请空间
     */
        media=new int*[n];
        for(int i=0;i<n;i++)
            media[i]=new int[n];
  
    /* cost[i][j] = Optimal cost of binary search tree 
       that can be  formed from keys[i] to keys[j]. 
       cost[0][n-1] will store the resultant cost */
  
    // For a single key, cost is equal to frequency of the key 
    for (int i = 0; i < n; i++) 
    {
        cost[i][i] = freq[i];
        media[i][i]=i;
    }
  
    // Now we need to consider chains of length 2, 3, ... . 
    // L is chain length. 
    for (int L=2; L<=n; L++) 
    { 
        // i is row number in cost[][] 
        for (int i=0; i<=n-L+1; i++) 
        { 
            // Get column number j from row number i and  
            // chain length L 
            int j = i+L-1; 
            cost[i][j] = INT_MAX; 
            //用于记录最好的二叉树的 root//
            int temp;
            // Try making all keys in interval keys[i..j] as root 
            for (int r=i; r<=j; r++)
            { 
               // c = cost when keys[r] becomes root of this subtree 
               int c = ((r > i)? cost[i][r-1]:0) +  
                       ((r < j)? cost[r+1][j]:0) +  
                       sum(freq, i, j); 
               if (c < cost[i][j]) 
               {
                   cost[i][j] = c;
                   media[i][j]=r;
               }
            } 
        } 
    } 
    return cost[0][n-1]; 
} 
  
// A utility function to get sum of array elements  
// freq[i] to freq[j] 
int sum(int freq[], int i, int j) 
{ 
    int s = 0; 
    for (int k = i; k <=j; k++) 
       s += freq[k]; 
    return s; 
} 
  
// Driver program to test above functions 
int main() 
{ 
    int keys[] = {10, 12, 20}; 
    int freq[] = {34, 8, 50}; 
    int n = sizeof(keys)/sizeof(keys[0]);
    int **media;
    printf("Cost of Optimal BST is %d ",  
                 optimalSearchTree(keys, freq, n,media));
    Optimal_BST_Node *root;
    root=BuildOptimalBST(media,root,0,2,keys,freq);
    return 0; 
} 