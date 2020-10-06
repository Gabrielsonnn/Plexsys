//clears tree starting at node
template<class T>
void BinaryTree<T>::clear(BTNode<T> *n) {
	if (n != nullptr) {
		if(n->left != nullptr)
			clear(n->left);
		if(n->right != nullptr)
			clear(n->right);
		delete n;
		n = nullptr;
	}
}

//inserts node into tree
template<class T>
void BinaryTree<T>::insertNode(const T& el) {
	
	if (root == nullptr) {//checks for empty tree
		root = new BTNode<T>(el);
	}
	else {

		BTNode<T> *n = root;//starts n at root

		while (n != nullptr) {
			if (el < n->el) {//if el is less than el in n
				if (n->left != nullptr) {//if there is a node to the left move to that node
					n = n->left;
					continue;//restarts loop
				}
				else {//else create node to the left and put el in it
					n->left = new BTNode<T>(el);
					break;
				}
			}
			else if (el > n->el) {//if el is greater than el in n
				if (n->right != nullptr) {//if there is a node to the right move to that node
					n = n->right;
					continue;//restarts loop
				}
				else {//else create node to the left and put el in it
					n->right = new BTNode<T>(el);
					break;
				}
			}
			else if (el == n->el) {//if el is equal to el in n
				//ALERT
				//do something with linked list maybe
				break;
			}
		}
	}
}

//searches tree for a specific element within a node
template<class T>
bool BinaryTree<T>::searchNode(const T& el, BTNode<T>* n) {
	while (n != nullptr) {//contuinues until reaches end of tree
		if (el == n->el) {//if node found return true
			return true;
		}
		else if (el < n->el)//if el is less than element in node n
			n = n->left;//then move left
		else
			n = n->right;//else move right
	}
	return false;//if reaches end of tree return false
}

//preorder prints all elements within tree
template<class T>
void BinaryTree<T>::preorderPrint(BTNode<T> *n) {
	if (n != nullptr) {
		cout << n->el << endl;
		preorderPrint(n->left);
		preorderPrint(n->right);
	}
}