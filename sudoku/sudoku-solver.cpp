#include<bits/stdc++.h>
using namespace std;
bool rh[9][10],ch[9][10],bh[9][10];
// rh stores hash values for rows in range (0-9)
// if rh[x][y] is true then element y is present in row x
// ch stores hash values for columns in range (0-9)
// bh stores hash values for 3X3 boxes numbered in range (0-9)
// there are 9 boxes (3X3) in (9X9) matrix as follows
// 0 1 2
// 3 4 5
// 6 7 8
bool find(int board[][9],int &r,int &c)// finds the unassigned elements
{
    for(r=0;r<9;r++)
    {
        for(c=0;c<9;c++)
            if(board[r][c]==0)// returns true for the first unassigned element found
                return true;
    }
    return false;// return false if no unassigned element found
}
bool allowed(int board[][9],int r,int c,int i)// checks if i can be assigned to board[r][c]
{
    int p=r/3,q=c/3;
    if(rh[r][i]==true || ch[c][i]==true || bh[3*p+q][i]==true)
        return false;
    return true;
}
bool SudokuSolver(int board[][9])
{
    int r,c,i;
    if(!find(board,r,c)) // If no element present that is unassigned
        return true;
    for(i=1;i<=9;i++)//try assign values from (1-9) to board[r][c] which is unassigned initially
    {
        if(allowed(board,r,c,i)) // checks if i can be assigned to board[r][c]
        {
            board[r][c]=i; // assign the value and make hash of row,column,box true
            rh[r][i]=true;
            ch[c][i]=true;
            int p=r/3,q=c/3;
            bh[3*p+q][i]=true;
            if(SudokuSolver(board))
                return true;
            board[r][c]=0; // unassign the value and remove hash
            rh[r][i]=false;
            ch[c][i]=false;
            bh[3*p+q][i]=false;
        }
    }
    return false;
}
int main()
{
    int board[9][9],f=0;
    for(int i=0;i<9;i++)  // Provide a 9X9 Matrix as input
    {
        for(int j=0;j<9;j++)
        {
        int p=i/3,q=j/3;
        cin>>board[i][j];  // Enter values in range (1 to 9)
        if(board[i][j]>0)  // Checks if initial matrix is possible and stores hash values
        {
        if(rh[i][board[i][j]]==true || ch[j][board[i][j]]==true || bh[3*p+q][board[i][j]]==true)
        {
            f=1;  // Means initial matrix is not possible
            break;
        }
        rh[i][board[i][j]]=true;
        ch[j][board[i][j]]=true;
        bh[3*p+q][board[i][j]]=true;
        }
        }
        if(f==1)
        break;
    }
    cout<<endl;
    if(f==1)
        cout<<"Not Possible !";
    else
    {
      if(SudokuSolver(board)) // if answer found then print the solution matrix
      {
        cout<<"The answer is : "<<endl;
        cout<<endl;
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
                cout<<board[i][j]<<" ";
            cout<<endl;
        }
      }
      else
      cout<<"Not Possible !";
    }
    cout<<endl;
}
