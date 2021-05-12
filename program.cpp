#include <iostream>
#include <fstream>
#include "program.h"

namespace type_plants {

	void container_Init(container* list) {
		list->size = 0;
		list->head = NULL;
	}

	void container_Clear(struct container* list) {
		node* currentNode = list->head;

		while (currentNode != NULL)
		{
			node* temp = currentNode->next;
			delete currentNode;
			currentNode = temp;
		}

		list->head = NULL;
		list->size = 0;
	}

	void container_Fill(struct container* list, ifstream& ifst) {
		while (!ifst.eof()) {
			if (node_Add(list, ifst)) {
				(list->size)++;
			}
		}
	}

	void container_Output(struct container* list, ofstream& ofst) {
		if (list->size == 0) {
			cout << "|List is empty!|" << endl;
			return;
		}
		ofst << "Container contains " << list->size << " elements." << endl;
		cout << "|Container contains " << list->size << " elements.|" << endl;

		for (int i = 0; i < list->size; i++) {
			if (!node_Output(list->head, i, ofst)) {
				cout << "Error in node #" << i << " output" << endl;
			}
		}
	}

	tree* tree_Input(ifstream& ifst) {
		tree* newObj = new tree();
		ifst >> newObj->age;
		return newObj;
	}

	void tree_Output(struct tree* tree, ofstream& ofst) {
		ofst << "Tree age: " << tree->age << "." << endl;
	}

	bool node_Add(struct container* currentList, ifstream& ifst) {
		struct node* newNode = new node;
		newNode->info = plants_Input(ifst);
		if (newNode->info == 0) {
			delete(newNode);
			return false;
		}
		if (currentList->head == NULL) {
			newNode->next = NULL;
			currentList->head = newNode;
		}
		else {
			newNode->next = currentList->head;
			currentList->head = newNode;
		}
		return true;
	}

	bool node_Output(struct node* headNode, int pos, ofstream& ofst) {
		node* currentNode = get_node(headNode, pos);
		if (!plants_Output(currentNode->info, ofst)) {
			cout << "Cannot to output plants!" << endl;
			return false;
		}
	}

	struct node* get_node(struct node* head, int index) {
		struct node* curNode = head;
		for (int i = 0; i < index; i++) {
			curNode = curNode->next;
		}
		return curNode;
	}

	plants* plants_Input(ifstream& ifst) {
		plants* newObj;
		string k;
		getline(ifst, k);
		switch (atoi(k.c_str()))
		{
		case 1:
			newObj = new plants;
			newObj->plants = tree_Input(ifst);
			ifst >> newObj->name;
			newObj->key = plants::type::TREE;
			break;
		case 2:
			newObj = new plants;
			newObj->plants = bush_Input(ifst);
			ifst >> newObj->name;
			newObj->key = plants::type::BUSH;
			break;
		default:
			return 0;
		}
		return newObj;
	}

	bool plants_Output(struct plants* plants, ofstream& ofst) {
		if (plants->key == plants::type::TREE) {
			ofst << "\nTree name: " << plants->name << "," << "\n";
			tree_Output((tree*)plants->plants, ofst);
			return true;
		}
		else if (plants->key == plants::type::BUSH) {
			ofst << "\nBush name: " << plants->name << "," << "\n";
			bush_Output((bush*)plants->plants, ofst);
			return true;
		}
		else {
			ofst << "Incorrect plants!" << endl;
			return false;
		}
	}

	bush* bush_Input(ifstream& ifst) {
		bush* newObj = new bush();
		int mnth;
		ifst >>  mnth;
		newObj->m = month(mnth);
		return newObj;
	}

	void bush_Output(struct bush* bush, ofstream& ofst) {
		ofst << "Month: " << bush->m << "." << endl;
	}

	void MultiMethod(struct container* list, ofstream& ofst) 
	{
		ofst << "Multimethod." << endl;
		node* currentNode1;
		node* currentNode2;
		for (int i = 0; i < list->size - 1; i++) {
			currentNode1 = list->head;
			for (int p = 0; p < i; p++) {
				currentNode1 = currentNode1->next;
			}
			currentNode2 = currentNode1->next;
			for (int j = i + 1; j < list->size; j++) {
				switch (currentNode1->info->key) {
				case plants::type::TREE:
					switch (currentNode2->info->key) {
					case plants::type::TREE:
						ofst << "--------------" << endl;
						ofst << "Tree and Tree." << endl;
						break;
					case plants::type::BUSH:
						ofst << "--------------" << endl;
						ofst << "Tree and Bush." << endl;
						break;
					default:
						ofst << "Tree and Unknown type." << endl;
						break;
					}
					currentNode2 = currentNode2->next;
					break;
				case plants::type::BUSH:
					switch (currentNode2->info->key) {
					case plants::type::TREE:
						ofst << "--------------" << endl;
						ofst << "Bush and Tree." << endl;
						break;
					case plants::type::BUSH:
						ofst << "--------------" << endl;
						ofst << "Bush and Bush." << endl;
						break;
					default:
						ofst << "--------------" << endl;
						ofst << "Bush and Unknown type." << endl;
						break;
					}
					currentNode2 = currentNode2->next;
					break;
				default:
					ofst << "--------------" << endl;
					ofst << "Unknown type." << endl;
					break;
				}

				node_Output(list->head, i, ofst);
				node_Output(list->head, j, ofst);

			}
		}
	}
}