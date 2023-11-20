//Lukas Kelk
//Data Strucutres and Algorithims project
//11/20/2023

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int N, I, Q;

class itemNode
{
public:
  char name[50];
  int count;
  itemNode *left, *right;

  itemNode()
  {
    name[0] = '\0';
    count = 0;
    left = NULL;
    right = NULL;
  }

  itemNode(char itemName[], int population)
  {
    strcpy(name, itemName);
    count = population;
    left = NULL;
    right = NULL;
  }
};

// For Tree Names
class treeNameNode
{
public:
  char treeName[50];
  treeNameNode *left, *right;
  itemNode *theTree;
  treeNameNode()
  {
    treeName[0] = '\0';
    theTree = NULL;
    left = NULL;
    right = NULL;
  }
  treeNameNode(char name[])
  {
    strcpy(treeName, name);
    theTree = NULL;
    left = NULL;
    right = NULL;
  }
};

treeNameNode *searchNameTree(treeNameNode *groot, char name[])
{
  if ((groot == nullptr) || ((strcmp(groot->treeName, name)) == 0))
  {
    return groot; // when found or done return
  }
  if ((strcmp(groot->treeName, name)) > 0)
  {
    return searchNameTree(groot->left, name); // if less go left
  }
  else if ((strcmp(groot->treeName, name)) < 0)
  {
    return searchNameTree(groot->right, name);// if more go right
  }
  else
  {
    return nullptr;
  }
}
itemNode *searchForItem(itemNode *groot, char named[])
{
  if ((groot == nullptr) || ((strcmp(groot->name, named)) == 0))
  {
    return groot;
  }
  if ((strcmp(groot->name, named)) > 0)
  {
    return searchForItem(groot->left, named); //if less go left
  }
  else if ((strcmp(groot->name, named)) < 0)
  {
    return searchForItem(groot->right, named);//if more go right
  }
  else
  {
    return nullptr;
  }
}
itemNode *insertHelperItem(itemNode *root, char name[], int value)
{
  if (root == nullptr)
  {
    return new itemNode(name, value);
  }
  else if ((strcmp(root->name, name)) < 0)
  {
    root->right = insertHelperItem(root->right, name, value); //if greater fo right
  }
  else
  {
    root->left = insertHelperItem(root->left, name, value); //if less go left
  }
  return root;
}

treeNameNode *insertHelper(treeNameNode *groot, char name[])
{
  if (groot == nullptr)
  {
    return new treeNameNode(name);
  }
  else if ((strcmp(groot->treeName, name)) < 0)
  {
    groot->right = insertHelper(groot->right, name); // if greater go right
  }
  else
  {
    groot->left = insertHelper(groot->left, name); //if less go left
  }
  return groot;
}

treeNameNode *buildNameTree(ifstream &input, ofstream &output)
{

  input.open("in-1.txt");

  input >> N >> I >> Q;

  output.open("out.txt"); //input output stuff

  output << N << " " << I << " " << Q << endl;

  cout << N << endl
       << I << endl
       << Q << endl;


  treeNameNode *groot = nullptr;

  for (int i = 0; i < N; i++)
  {
    char name[30];
    input >> name;
    output << name <<" ";
    groot = insertHelper(groot, name); //assign root to new root with updated nodes
  }
  output << endl;
  return groot;
}

void buildItemTree(treeNameNode *groot, ifstream &input)
{
  char nameTree[30];
  char nameItem[30];
  int quantity = 0;

  for (int i = 0; i < I; i++)
  {
    input >> nameTree >> nameItem >> quantity;
    // cout << nameTree << nameItem << quantity << endl;
    treeNameNode *temp = searchNameTree(groot, nameTree);
    // cout << temp->treeName << endl;
    temp->theTree = insertHelperItem(temp->theTree, nameItem, quantity);
  }
}
void inorderTraversalPrintItem(itemNode *groot,ofstream &output)
{
  if (groot == nullptr)
  {
    return;
  }
  inorderTraversalPrintItem(groot->left,output); //visit left first
  cout << groot->name << " ";
  output << groot->name << " "; //output
  inorderTraversalPrintItem(groot->right,output); //then visit right
}
void inorderTraversalPrint(treeNameNode *groot, ofstream &output)
{
  if (groot == nullptr)
  {
    return;
  }

  inorderTraversalPrint(groot->left,output); // visit left side
  cout  << "|" << groot->treeName << "|" << endl;
  output << "|" << groot->treeName << "|" << endl; //output
  inorderTraversalPrintItem(groot->theTree,output); // visit sub tree
  cout << endl;
  output << endl;
  inorderTraversalPrint(groot->right,output); //visit right
}
int inorderCountItem(itemNode *groot)
{
  if (groot == nullptr)
  {
    return 0;
  }
  return groot->count + inorderCountItem(groot->left) + inorderCountItem(groot->right); // return the sum of left and right until reaching null
}
int item_before(itemNode *groot, char named[])
{
  // basically an inorder traversal that adds one when it goes through
  if ((groot == nullptr))
  {
    return 0; // returning a zero when we are done cause thats not before
  }
  else if ((strcmp(groot->name, named)) < 0)
  {
    return item_before(groot->right, named) + item_before(groot->left, named) + 1; // the search term is greater so we can keep
  }                                                                                // searching the tree and add one for beofore
  else
  {
    return 0 + item_before(groot->left, named); // when the current term is greater then the search term then it wont be
                                                // in the path so we can continue and return zero
  }
}
int treeHeight(itemNode *root)
{
  if (root == nullptr)
  {
    return 0; // empty :)
  }
  return 1 + max(treeHeight(root->right), treeHeight(root->left)); // we did this in class
  // if the tree is not empty it adds left hight to right hight.
  // at the end of the reccursion it return zero then adds the ones together
}
void balanceCheck(itemNode *groot, treeNameNode *otherRoot, ofstream &output)
{
  int left, right; // obvious

  if (groot == nullptr)
  {
    cout << "Tree is Empty so Its Balanced!" << endl;
    output << "Tree is Empty so Its Balanced!" << endl;
  }

  left = treeHeight(groot->left);   // left hieght
  right = treeHeight(groot->right); // and right height
 
  cout << otherRoot->treeName << ": left Height " << left << ", Right Height " << right << ", Difference " << abs(left - right);
  output << otherRoot->treeName << ": left Height " << left << ", Right Height " << right << ", Difference " << abs(left - right);
  // printing
  if (abs(left - right) <= 1)
  { // balance check, abs is abosulte value
    cout << " Balanced" << endl;
    output << " Balanced" << endl;
  }
  else
  {
    cout << " Not Balanced" << endl;
    output << "Not Balanced" << endl;
  }
}
void queryDoing(ifstream &input, treeNameNode *groot, ofstream &output)
{
  char query[20];

  for (int i = 0; i < Q; i++)
  {

    input >> query;
  //basically were going to check each query and then assign it to the one it matches
    if (strcmp(query, "search") == 0)
    {

      char nameTree[20];
      char subName[20];
      input >> nameTree >> subName;
      treeNameNode *temp = (searchNameTree(groot, nameTree));

      if (temp == nullptr)
      {
        cout << nameTree << " is not a thing" << endl;
        output << nameTree << " is not a thing" << endl;
        continue; //if not a thing we just continue
      }

      itemNode *found = searchForItem(temp->theTree, subName);

      if ((found) == nullptr)
      {
        cout << subName << " is not found in " << temp->treeName << ":(" << endl;
        output << subName << " is not found in " << temp->treeName << ":(" << endl;
      }
      else
      {
        cout << "There are " << (found->count) << " " << found->name << " found in " << temp->treeName << endl;
        output << "There are " << (found->count) << " " << found->name << " found in " << temp->treeName << endl;
      }
    }

    if (strcmp(query, "item_before") == 0)
    {
      char nameTree[20];
      char subName[20];
      input >> nameTree >> subName;
      treeNameNode *temp = (searchNameTree(groot, nameTree)); // doing function
      cout << "items before deer: " << item_before(temp->theTree, subName) << endl;
      output << "items before deer: " << item_before(temp->theTree, subName) << endl;
    }

    if (strcmp(query, "height_balance") == 0)
    {
      char nameTree[20];
      input >> nameTree;
      treeNameNode *temp = (searchNameTree(groot, nameTree));
      balanceCheck(temp->theTree, temp, output); //balance check print stuff
    }

    if (strcmp(query, "count") == 0)
    {
      char nameTree[20];
      input >> nameTree;

      treeNameNode *temp = (searchNameTree(groot, nameTree));
      //search function
      cout << "There are " << inorderCountItem(temp->theTree) << " " << nameTree << "s in the tree" << endl;
      output << "There are " << inorderCountItem(temp->theTree) << " " << nameTree << "s in the tree" << endl;
    }
  }
}
void traverse_in_traverse(treeNameNode *groot, ifstream& input, ofstream &output){
  buildItemTree(groot, input);
  treeNameNode* temp = groot;
  inorderTraversalPrint(groot,output);
  queryDoing(input, groot ,output);
  //all the other functions
}
int main()
{

  ifstream input;
  ofstream output;
  treeNameNode *groot = buildNameTree(input,output);
  traverse_in_traverse(groot,input,output);
 
}
