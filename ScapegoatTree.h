#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    
    //benim tanimladiklarim
    Node<T>* rebuildTree(Node<T> *u)const;
    int myheight(Node<T>  *r) const;
    Node<T>* make_copy(Node<T> *t1, Node<T> *t2)const;
    void deleteTree(Node<T> *r)const;
    int addwithDepth(Node<T> *u)const;
    Node<T>* searchforparentnode(Node<T>* pRoot, Node<T>* r)const;
    bool ifNodeExists(Node<T>* r, const T& x) const;
    int numberNodes(Node<T> *r) const;
    int storeInArray(Node<T> * r, T* x, int i) const;
    Node<T>* sortedArrayToBST(T* arr, int start, int end) const;
    Node<T> * DeleteNode(Node<T>* r,const T d)const;
    const T& Ceil(Node<T>* r, T input) const;
    const T& Floor(Node<T>* r,  T input) const;
    const T& Next(Node<T>* r,  T input) const;
    


private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    
    root = NULL;
    upperBound = 0;
    /* TODO */
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    
    
    root = NULL;
    *this = obj;
  /* TODO */
}


template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    
    deleteTree(root);
    root = NULL;
    upperBound = 0;
    /* TODO */
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    return (root == NULL)
    /* TODO */
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    if(root == NULL){
        return -1;
    }
    
    Node<T> *r = root;
    
    int x = myheight(r);
    return x-1;

    /* TODO */
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    if(root == NULL){
        return 0;
    } 
    else{
      Node<T> *r = root;
        int x = numberNodes(r);
        return x;  
    }
    
    /* TODO */
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    if(root == NULL){
        Node<T> *current = new Node<T>;
        current->element = element;
        root = current;
        root->left = NULL;
        root->right = NULL;
        upperBound++;
        return true;
    }
    
    Node<T> *r = root;
    T x = element;
    bool alfa = ifNodeExists(r,x);
    if(alfa == true){
        return false;
    }
    
    Node<T> *u = new Node<T>;
    u->element = element;
    u->left  = NULL;
    u->right = NULL;
    int d = addwithDepth(u);
    upperBound++;
    
    if(d > (   (int)ceil(2.4663034623764317 * log(upperBound))     )  ){
        
        Node<T>* temp = u;
        Node<T>* alfam = searchforparentnode(root,temp);
        while(3* numberNodes(temp) <= 2* numberNodes(alfam) ){
            temp = searchforparentnode(root, temp);
            alfam = searchforparentnode(root,alfam);
        }
        temp = searchforparentnode(root, temp);
        if(temp == NULL){
            balance();
        }
        else{
            rebuildTree(temp);
        }
        
    }
    
    return d>=0;
    
    /* TODO */
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    
    if(root == NULL){
        return false;
    } 
    Node<T> *r = root;
    T x = element;
    bool alfa = ifNodeExists(r,x);
    if(alfa == false){
        return false;
    }
    Node<T> *curr = root;
    root = DeleteNode(curr,element);
    if(2*numberNodes(root) < upperBound){
        upperBound = numberNodes(root);
        balance();
    }
    return true;
    
    

    /* TODO */
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    if(root == NULL) return;
    
    deleteTree(root);
    root = NULL;
    upperBound = 0;
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    if(root == NULL){
        throw NoSuchItemException();
        
    }
    
    Node<T> *rr = root;
    T x = element;
    bool alfa = ifNodeExists(rr,x);
    if(alfa == false){
         throw NoSuchItemException();
    }
    
    if(root->element == element){
        return root->element;
    }
    
/*    
    Node<T> *r = root;
    
    while(r->left != NULL || r->right != NULL){
        if(r->element == element){
            return element;
            break;
        }
        else{
            if((r->element < element) && (r->right != NULL)){
                r = r->right;
            }
            else if( (r->element < element) && (r->right == NULL) ){
                throw NoSuchItemException();
                break;
            }
            else if((r->element > element) && (r->left == NULL)){
                throw NoSuchItemException();
                break;
            }
            else{
                r = r->left;
            }
            
        }
    }
*/
    return element;
 
    /* TODO */
}


template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        if (isEmpty()) {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    } else if (tp == inorder) {

        if (isEmpty()) {
           
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {

        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}


template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        if (node == NULL)
            return;

        std::cout << "\t" << node->element;

        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } 
    
    
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    
    
    else if (tp == postorder) {
        /* TODO */
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the right subtree.
        print(node->right, postorder);

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;

    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}



template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    if(this == &rhs) return *this;
    else{
        removeAllNodes();
        root = make_copy(root,rhs.root);
        upperBound = rhs.upperBound;
        return *this;
    }
    
    /* TODO */
}




template<class T>
void ScapegoatTree<T>::balance() {
    root = rebuildTree(root);
    Node<T> *r = root;
    upperBound = numberNodes(r);
    
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    
    
    if(root == NULL){
        throw NoSuchItemException();
    }
    
    
    T maxi = getMax();
    if(element >maxi){
        throw NoSuchItemException();
    }
    
    if(getSize() == 1){
        return root->element;
    }
    
    
    return Ceil(root,element);
    


    
        
    
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    
    if(root == NULL){
        throw NoSuchItemException();
    }
    
    T mini = getMin();
    if(element < mini){
        throw NoSuchItemException();
    }
    
    if(getSize() == 1){
        return root->element;
    }
    
     return Floor(root,element);
    
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {
    if(root == NULL){
        throw NoSuchItemException();
    }
    if(root->left == NULL) return root->element;
    Node<T> *current = root;
    while(current->left != NULL){
        current = current ->left;
    }
    return current->element;
        
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    if(root == NULL){
        throw NoSuchItemException();
    }
    if(root->right == NULL) return root->element;
    Node<T> *current = root;
    while(current->right != NULL){
        current = current ->right;
    }
    return current->element;
    /* TODO */
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    
    if(root == NULL){
        throw NoSuchItemException();
    }
    Node<T> *r = root;
    while(r->right !=NULL){
        r = r->right;
    }
    T x = r->element;
    if(x == element || x < element){
        throw NoSuchItemException();
    }

    return  Next(root,element);

}




                                // my helpers


template<class T>
int ScapegoatTree<T>::myheight(Node<T> *r)const {
        
    if (r == NULL)
        return 0;
    else {
        int lDepth = myheight(r->left);
        int rDepth = myheight(r->right);
  
        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}
    


template<class T>
int ScapegoatTree<T>::numberNodes(Node<T> *r) const{
    if(r == NULL){
        return 0;
    }
    
    int lns = numberNodes(r->left);
    int rns = numberNodes(r->right);
    return rns +1 + lns ;
}
   


template<class T>
Node<T>* ScapegoatTree<T>::make_copy(Node<T> *target, Node<T>* source)const {
    
    if(source == NULL){
        return NULL;
    }
    else{
        target = new Node<T>(source->element,NULL,NULL);
        target->left = make_copy(target->left,source->left);
        target->right = make_copy(target->right,source->right);
        return target;
    }
    
	
}


template<class T>
void ScapegoatTree<T>::deleteTree(Node<T> *r)const{
    
    if(r == NULL){
        return;
    }
    deleteTree(r->right);
    deleteTree(r->left);
    delete r;

}





template<class T>
int ScapegoatTree<T>::addwithDepth(Node<T> *u)const{
    
    if(u == NULL || root == u) return 0;
    
    
    Node<T> *w = root;
    
    bool done = false;
    int d = 0;
    
    do{
        if(u->element < w->element){
            if(w->left != NULL){
                w = w->left;
                
    
            }
            else{
                w->left = u;
                d++;
                done = true;
            }
        }
            
        else if(u->element > w->element){
            if(w->right != NULL){
                 w = w->right;
            }
            else{
               w->right = u;
               d++;
               done = true;
            }
        }

        d++;
    }
    while(!done);
    return d;
    
}




template<class T>
Node<T>* ScapegoatTree<T>::searchforparentnode(Node<T>* pRoot, Node<T> *r)const{
    if (pRoot == NULL){
        return NULL;
    }
    
    if(r== NULL){
        return NULL;
    }
    
    if(pRoot == r){
        return NULL;
    }

    Node<T> *current = pRoot;
    bool done = true;
    while(done){
        
        if(current->element < r->element){

            if(current->right == r){
                done = false;
            } 

            else{
                current = current->right;
            }
        }
        
        else if(current->element > r->element){

            if(current->left == r){
                done = false;
            } 

            else{
                current = current->left;
            }
        }
    }
    return current;
}


template<class T>   
bool ScapegoatTree<T>::ifNodeExists(Node<T>* r, const T& x)const{
    if (r == NULL)
        return false;
 
    if (r->element == x)
        return true;
    
    Node<T>* curr = r;
    while(curr != NULL){
        if(curr->element == x){
            return true;
        }
        else{
            if(curr->element >x){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
    }
    
    return false;
}




template<class T>
Node<T> * ScapegoatTree<T>::DeleteNode(Node<T>* r, const T d)const
{
    if(r == NULL){
        return NULL;
    }
    
	Node<T>* curr = r;
	
    if(curr->element != d){
        if(curr->element > d){
            curr->left = DeleteNode(curr->left,d);
        }
        else{
            curr->right = DeleteNode(curr->right,d);
        }
    }

    
    else
    {
    if((curr->left == NULL && curr->right != NULL) || (curr->left != NULL && curr->right == NULL)) 
    {
        if(curr->left == NULL && curr->right != NULL)
        {
            Node<T>* temp = curr->right;
            delete r;
            return temp;
        }
        else
        {
            Node<T>* temp = r->left;
            delete r;
            return temp;
        }
    }

    if( curr->left == NULL && curr->right == NULL)
    {
        delete curr;
        return NULL;
    }


    if (curr->left != NULL && curr->right != NULL)
    {

        Node<T>* maxleft = curr->left;;
        while (maxleft->right != NULL)
            maxleft = maxleft->right;

        T alfa = curr->element;
        curr->element = maxleft->element;
        maxleft->element = alfa;
        curr->left = DeleteNode(curr->left, d);
        
    }
    }
    return curr;
}


template<class T>
const T& ScapegoatTree<T>::Floor(Node<T>* r,  T input)const{
 
    
    
    Node<T>* temp = r;
    Node<T>* current = r;
    while(current){
        
        if(input > current->element){
            temp = current;
            current = current->right;
        }
        else if(input < current->element){
            current = current->left;
        }
        else{
            temp = current;
            return temp->element;
        }

    }
    
    return temp->element;
    
    
    
}

template<class T>
const T& ScapegoatTree<T>::Ceil(Node<T>* r, T input)const{
    
    Node<T>* temp = r;
    Node<T>* current = r;
    while(current){
        
        if(input < current->element){
            temp = current;
            current = current->left;
        }
        else if(input > current->element){
            current = current->right;
        }
        else{
            temp = current;
            return temp->element;
        }

    }
    
    return temp->element;

}


template<class T>
const T& ScapegoatTree<T>::Next(Node<T>* r, T input)const{
    
    Node<T>* temp = r;
    Node<T>* current = r;
    while(current){
        
        if(input < current->element){
            temp = current;
            current = current->left;
        }
        else if(input > current->element){
            current = current->right;
        }
        else{
            current = current->right;
        }

    }
    
    return temp->element;

}



template<class T>
int ScapegoatTree<T>::storeInArray(Node<T> * r, T* x, int i) const{
    
    if (r == NULL)
        return i;
    
    else{
       i = storeInArray(r->left, x, i);
        x[i++] = r->element;
        return storeInArray(r->right, x, i); 
    }
    
    
}


template<class T>
Node<T>* ScapegoatTree<T>::sortedArrayToBST(T * arr,int start, int end) const{

    if (start > end)
        return NULL;

    int mid = (start + end)/2;
    Node<T> *r = new Node<T>(arr[mid], NULL, NULL);

    r->left = sortedArrayToBST(arr, start, mid - 1);

    r->right = sortedArrayToBST(arr, mid + 1, end);
 
    return r;
}



template<class T>
Node<T>* ScapegoatTree<T>::rebuildTree(Node<T> *u)const{
    if(u == NULL) return NULL;
    if(u->left == NULL && u->right == NULL) return u;
    int n = numberNodes(u);
    T *a = new T [n];
    Node<T> *p = searchforparentnode(root,u);
    storeInArray(u, a, 0);
    if (!p){
        deleteTree(u);
        u = sortedArrayToBST(a,0,n-1);
        delete [] a;
        return u;
    }
    else if (p->right == u){
        deleteTree(u);
        p->right =  sortedArrayToBST(a,0,n-1);
    }
    else if(p->left == u){
        deleteTree(u);
        p->left =  sortedArrayToBST(a,0,n-1);
    }
    delete [] a;
    
}
