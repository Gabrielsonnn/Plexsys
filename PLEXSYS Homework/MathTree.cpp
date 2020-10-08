//Developer: Gabriel Johnson

template<class T>
int MathTree<T>::buildTree(int index, string mathInput, MNode<T>* node)
{
	//loop through math input
	while (index < mathInput.length()) {
		//if characters is a left parenthesis, add new node and move down to it
		if (charInString(mathInput[index], leftParenthesis)) {

			//check if left node is filled
			if (node->leftFilled == 0) {
				//if not filled, then add new node to left

				//create new node to left of current node
				node->left = new MNode<T>(-1);

				//change flag for left node
				node->leftFilled = -1;

				//recursive call to continue building tree
				index = buildTree(++index, mathInput, node->left);
			}
			//if it is, check if right is filled.
			else if (node->rightFilled == 0) {
				//if not filled, then add new node to right

				//create new node to right of current node
				node->right = new MNode<T>(-1);

				//change flag for right node
				node->rightFilled = -1;

				//recursive call to continue building tree
				index = buildTree(++index, mathInput, node->right);
			}
		}

		//if character is a number or a decimal
		else if (charInString(mathInput[index], listOfNumbers + ".")) {
			//determine if it is the first or second number
			//then add to node

			//value that holds where numbers starts in string
			int startOfNumberIndex = index;

			//move index to next value
			index++;

			//if a number is hit keep checking for numbers until no more numbers
			while (index < mathInput.length()) {

				//check if current index is part of number string
				if (!charInString(mathInput[index], listOfNumbers + ".")) {
					break;
				}

				//keep going until no more numbers are found
				index++;
			}

			//move index back one, since it was not part of the number string
			index--;

			//variable to hold value of number
			double number;

			//convert string to double
			string temp = mathInput.substr(startOfNumberIndex, (index + 1) - startOfNumberIndex);
			number = stod(temp);

			//check if left node is filled
			if (node->leftFilled == 0) {

				//create new node to left of current node with number as the element
				node->left = new MNode<T>(number);

				//change flag for left node
				node->leftFilled = 1;
			}
			//if it is, check if right is filled.
			else if (node->rightFilled == 0) {

				//create new node to right of current node with number as the element
				node->right = new MNode<T>(number);

				//change flag for right node
				node->rightFilled = 1;
			}
		}

		//if character is an operation, set it to current nodes operation
		else if (charInString(mathInput[index], listOfOperations)) {
			//change value of operation in current node
			node->middle = mathInput[index];

			//change flag for operation
			node->middleFilled = 1;

		}
		//if character is a right parenthesis, this node is finished, move back up tree to previous node
		else if (charInString(mathInput[index], rightParenthesis)) {
			return index;
		}
		
		//increment index to move to next char
		index++;
	}
}

template<class T>
double MathTree<T>::calculateNodes(MNode<T>* node)
{
	if (node->el == -1) {
		double left = 0;
		double right = 0;

		//if both left and right have values, do operation
		if ((node->leftFilled == 1 && node->rightFilled == 1) || (node->leftFilled == -1 && node->rightFilled == 1) || (node->leftFilled == 1 && node->rightFilled == -1) || (node->leftFilled == -1 && node->rightFilled == -1)) {

			//get value for left node
			left = calculateNodes(node->left);

			//get value for right node
			right = calculateNodes(node->right);

			//variable for holding operation
			char operation;

			//if no operation, then assume multiplication
			if (node->middleFilled == 0) {
				operation = '*';
			}
			//there is operation listed, get
			else {
				operation = node->middle;
			}

			//now do operation, using switch and return corresponding value
			switch (operation)
			{
			case '^':
				return pow(left, right);
			case '*':
				return left * right;
			case '/':
				return left / right;
			case '%':
				return (int)left % (int)right;
			case '+':
				return left + right;
			case '-':
				return left - right;
			}
		}
		//if only left node filled, return left
		else if (node->leftFilled != 0 && node->rightFilled == 0) {
			
			//get value for left node
			left = calculateNodes(node->left);
			
			//retrun left node value
			return left;
		}
		//if only right node filled return right
		else if (node->leftFilled == 0 && node->rightFilled != 0) {
			
			//get value for right node
			right = calculateNodes(node->right);

			//return right node value
			return right;
		}
	}
	//if node doensn't have value of -1, return el.
	else {
		return node->el;
	}

}

template<class T>
double MathTree<T>::calculate(string mathInput)
{
	//builds the tree for calculating the math
	buildTree(0, mathInput, root);

	//calculates the values for all the nodes, by stepping through tree and returns value
	return calculateNodes(root);
}


//function to test wethere there is a specific char within a string
template<class T>
bool MathTree<T>::charInString(char inchar, string instring) {

	//iterate through all chars in string
	for (int i = 0; i < instring.length(); i++) {
		//check all chars agains in char
		if (inchar == instring[i]) {
			//if found return true
			return true;
		}
	}

	//if not found return false
	return false;
}

//clears tree starting at node
template<class T>
void MathTree<T>::clear(MNode<T>* n) {
	if (n != nullptr) {
		if (n->left != nullptr)
			clear(n->left);
		if (n->right != nullptr)
			clear(n->right);
		delete n;
		n = nullptr;
	}
}