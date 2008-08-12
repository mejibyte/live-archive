#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
        // An object of type TreeNode represents one node
        // in a binary tree of strings.
   int item;       // The data in this node.
   TreeNode *left;    // Pointer to left subtree.
   TreeNode *right;   // Pointer to right subtree.
   TreeNode(int i = 0) {
          // Constructor, defined for convenience. 
          // Make a node containing the specified string.
      item = i;
      left = NULL;
      right = NULL;
   }
};  // end struct TreeNode



void preorder(TreeNode *node) {
   if ( node != NULL ) {
       cout << " " << node->item; 
       preorder(node->left);  
       preorder(node->right);           
   }
}

int countNodes(TreeNode *node) {
      // Count the nodes in the binary tree to which node 
      // points.  Return the answer.
   if ( node == NULL ) {
           // Tree is empty, so it contains no nodes.
      return 0;
   }
   else {
          // Add up the root node and the nodes in its two subtrees.
      int leftCount = countNodes( node->left );
      int rightCount = countNodes( node->right );
      return  1 + leftCount + rightCount;  
   }
}

void insertIzquierda(TreeNode *node, int item){
     if (node->left == NULL)
        node->left = new TreeNode(item);
}

void insertDerecha(TreeNode *node, int item){
     if (node->right == NULL)                            
        node->right = new TreeNode(item);
}


string partir(string &arbol, bool izquierda){
       //cout << "partir: " << arbol << " " << (izquierda?"izq":"der") << " ";
       int contParentesis = 1, i=1;
       if(arbol.substr(0, 2) == "(,"){
           i = 1;
       }else if(false){
       }else{
             while(true){
             if (arbol[i] == '('){
                  contParentesis++;
             }else if (arbol[i] == ')'){
                  contParentesis--;
             }
             i++;
             if (contParentesis == 1) 
                 break;
             }
       }
       //cout << "i es: " << i << "\n";
              
       if (izquierda){
           //cout << arbol.substr(1, i-1) << endl;
           return (arbol.substr(1, i-1));               
       }else{
           //cout << arbol.substr(i+1, arbol.length()-i-2) << endl; 
           return (arbol.substr(i+1, arbol.length()-i-2));
       }
       return "";
}


void colgar(TreeNode *papa, string arbol, bool izquierda){
     if (arbol != ""){
         if (izquierda){
             //cout << "llamando insert izquierda\n";
             insertIzquierda(papa, 0);
         }else{
             //cout << "llamando insert derecha\n";
             insertDerecha(papa, 0);
         }
         if (arbol != "()"){
            string subizq = partir(arbol, true);                   
            string subder = partir(arbol, false);            
            if (izquierda){
               colgar(papa->left, subizq, true);                          
               colgar(papa->left, subder, false); 
            }else{
               colgar(papa->right, subizq, true);                          
               colgar(papa->right, subder, false); 
            }
         }
     }
}

void asignar(TreeNode *nodo, const vector<int> &nums){
     vector<int> temp;
     if (nodo != NULL){
         int canIzq = countNodes(nodo->left);
         int canDer = countNodes(nodo->right);
         nodo-> item = nums[canIzq];
         if (canIzq > 0){
             temp.assign(nums.begin(), nums.begin()+canIzq);
             asignar(nodo->left, temp);
         }
         if (canDer > 0){
             temp.assign(nums.begin()+canIzq+1, nums.end());
             asignar(nodo->right, temp);       
         }         
     }
}


int main() {

   TreeNode *root;
   
   string line, subizq, subder;
   getline(cin, line);
   vector<int> nums;
   int i;
   while (line != "()"){
         root = new TreeNode(0);
         subizq = partir(line, true);
         subder = partir(line, false);
         colgar(root, subizq, true);
         colgar(root, subder, false);                  
         i = countNodes(root);
         nums.clear();
         for (int j=1; j<=i; j++){
             nums.push_back(j);
         }
         asignar(root, nums);
         cout << root->item;
         preorder(root->left);
         preorder(root->right);
         cout << "\n";
         getline(cin, line);
   }
   return 0;
}

