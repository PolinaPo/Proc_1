#include <iostream>
#include <fstream>
#include "program.h"

namespace type_plants
{
	void container_Init(container *list)
	{
		list->size = 0;
		list->head = NULL;
	}

	void container_Clear(struct container *list)
	{
		node *currentNode = list->head;

		while (currentNode != NULL)
		{
			node *temp = currentNode->next;
			delete currentNode;
			currentNode = temp;
		}

		list->head = NULL;
		list->size = 0;
	}

	void container_Fill(struct container *list, ifstream &ifst)
	{
		// Проверка файла на пустоту
		if (ifst.peek() == EOF) 
		{
			cout << "Error, Fail empty!" << endl;
			exit(1);
		}

		while (!ifst.eof())
		{
			if (node_Add(list, ifst))
			{
				(list->size)++;
			}
		}
	}

	void container_Output(struct container *list, ofstream &ofst)
	{
		if (list->size == 0)
		{
			cout << "|List is empty!|" << endl;
			return;
		}
		ofst << "Container contains " << list->size << " elements." << endl;
		cout << "|Container contains " << list->size << " elements.|" << endl;

		for (int i = 0; i < list->size; i++)
		{
			if (!node_Output(list->head, i, ofst))
			{
				cout << "Error in node #" << i << " output" << endl;
			}
		}
	}

	tree *tree_Input(ifstream &ifst)
	{
		tree *newObj = new tree();
		ifst >> newObj->age;
		// Проверка, возраст дерева должен быть положительным числом
		if (newObj < 0) 
		{
			cout << "Error, Age cannot be negative!" << endl;
			exit(1);
		}
		return newObj;
	}

	void tree_Output(struct tree *tree, ofstream &ofst)
	{
		ofst << "Age: " << tree->age << "," << endl;
	}

	bool node_Add(struct container *currentList, ifstream &ifst)
	{
		struct node *newNode = new node;
		newNode->info = plants_Input(ifst);
		if (newNode->info == 0)
		{
			delete (newNode);
			return false;
		}
		if (currentList->head == NULL)
		{
			newNode->next = NULL;
			currentList->head = newNode;
		}
		else
		{
			newNode->next = currentList->head;
			currentList->head = newNode;
		}
		return true;
	}

	bool node_Output(struct node *headNode, int pos, ofstream &ofst)
	{
		node *currentNode = get_Node(headNode, pos);
		if (!plants_Output(currentNode->info, ofst))
		{
			cout << "Cannot to output plants!" << endl;
			return false;
		}
		else
		{
			ofst << "The number of consonants in the name: " << number_Consonants(currentNode->info) << "." << endl;
			return true;
		}
	}

	struct node *get_Node(struct node *head, int index)
	{
		struct node *curNode = head;
		for (int i = 0; i < index; i++)
		{
			curNode = curNode->next;
		}
		return curNode;
	}

	plants *plants_Input(ifstream &ifst)
	{
		plants *newObj;
		int place_plant = 0;
		int k;
		ifst >> k;
		// Проверка на правильно введенный ключ
		if (ifst.eof()) 
		{
			return 0;
		}
		if (k < 1 || k > 3) 
		{
			cout << "Error, the key must be a value between 1 and 3!" << endl;
			exit(1);
		}

		switch (k)
		{
		case 1:
			newObj = new plants;
			newObj->plants = tree_Input(ifst);
			ifst >> newObj->name;
			ifst >> place_plant;
			// Проверка правильно введенного места произрастания (число от 0 до 5)
			if (place_plant < 0 || place_plant > 5) 
			{
				cout << "Error, The place of growth should take a value from 0 to 5!" << endl;
				exit(1);
			}
			newObj->place_growth = place(place_plant);
			newObj->key = plants::type::TREE;
			break;
		case 2:
			newObj = new plants;
			newObj->plants = bash_Input(ifst);
			ifst >> newObj->name;
			ifst >> place_plant;
			// Проверка правильно введенного места произрастания (число от 0 до 5)
			if (place_plant < 0 || place_plant > 5)
			{
				cout << "Error, The place of growth should take a value from 0 to 5!" << endl;
				exit(1);
			}
			newObj->place_growth = place(place_plant);
			newObj->key = plants::type::BASH;
			break;
		case 3:
			newObj = new plants;
			newObj->plants = flower_Input(ifst);
			ifst >> newObj->name;
			ifst >> place_plant;	
			// Проверка правильно введенного места произрастания (число от 0 до 5)
			if (place_plant < 0 || place_plant > 5)
			{
				cout << "Error, The place of growth should take a value from 0 to 5!" << endl;
				exit(1);
			}
			newObj->place_growth = place(place_plant);
			newObj->key = plants::type::FLOWER;
			break;
		default:
			return 0;
		}
		return newObj;
	}

	bool plants_Output(struct plants *plants, ofstream &ofst)
	{
		if (plants->key == plants::type::TREE)
		{
			ofst << "\nTree name: " << plants->name << "," << "\n"
				 << "Place of growth: " << plants->place_growth + 1 << "," << endl;
			tree_Output((tree *)plants->plants, ofst);
			return true;
		}
		else if (plants->key == plants::type::BASH)
		{
			ofst << "\nBash name: " << plants->name << "," << "\n"
				 << "Place of growth: " << plants->place_growth + 1 << "," << endl;
			bash_Output((bash *)plants->plants, ofst);
			return true;
		}
		else if (plants->key == plants::type::FLOWER)
		{
			ofst << "\nFlower name: " << plants->name << "," << "\n" 
				 << "Place of growth: " << plants->place_growth + 1 << "," << endl;
			flower_Output((flower*)plants->plants, ofst);
			return true;
		}
		else
		{
			ofst << "Incorrect plants!" << endl;
			return false;
		}
	}

	bash *bash_Input(ifstream &ifst)
	{
		bash *newObj = new bash();
		int mnth;
		ifst >> mnth;
		// Проверка правильно введенного месяца цветения (число от 0 до 11)
		if (mnth < 0 || mnth > 11) 
		{
			cout << "Error, month must be between 0 and 11!" << endl;
			exit(1);
		}
		newObj->m = month(mnth);
		return newObj;
	}

	void bash_Output(struct bash *bash, ofstream &ofst)
	{
		ofst << "Mounth: " << bash->m + 1 << "," << endl;
	}

	flower *flower_Input(ifstream &ifst)
	{
		flower *newObj = new flower();
		int f_view;
		ifst >> f_view;
		// Проверка правильно введенного значения вида цветка (число от 0 до 2)
		if (f_view < 0 || f_view > 2) 
		{
			cout << "Error, view must be between 0 and 2!" << endl;
			exit(1);
		}
		newObj->flower_view = view(f_view);
		return newObj;
	}
	
	void flower_Output(struct flower* flower, ofstream& ofst)
	{
		ofst << "View: " << flower->flower_view + 1 << "," << endl;
	}

	// Количество согласных букв в названии растения (целое число)
	int number_Consonants(struct plants * plants)
	{
		string consonants = "BbCcDdFfGgHhJjKkLlMmNnPpQqRrSsTtVvWwXxYyZz";
		int sum = 0;
		for (unsigned i = 0; i < plants->name.length(); i++)
		{
			for (unsigned j = 0; j < consonants.length(); j++)
			{
				if (plants->name[i] == consonants[j])
				{
					sum++;
				}
			}
		}
		return sum;
	}

	// Cравнение ключей двух программных объектов
	bool Compare(struct plants * first, struct plants * second)
	{
		return number_Consonants(first) > number_Consonants(second);
	}

	// Сортировка содержимого контейнера
	void Sort(container * list)
	{
		node *left = list->head;
		node *right = list->head->next;

		node *temp = new node;
		for (int i = 0; i < list->size - 1; i++)
		{
			for (int j = i + 1; j < list->size; j++)
			{
				if (Compare(left->info, right->info))
				{
					temp->info = left->info;
					left->info = right->info;
					right->info = temp->info;
				}
				right = right->next;
			}
			left = left->next;
			right = left->next;
		}
	}
	
	// Вывод только деревьев
	void Output_only_tree(struct container *list, ofstream &ofst)
	{
		node *curNode;
		ofst << "Only tree." << endl;
		for (int i = 0; i < list->size; i++)
		{

			curNode = list->head;
			for (int j = 0; j < i; j++)
			{
				curNode = curNode->next;
			}
			if (curNode->info->key == plants::type::TREE)
			{
				if (!node_Output(list->head, i, ofst))
				{
					cout << "|Node #" << i << " is broken!|" << endl;
					ofst << "Node is broken!" << endl;
				}
			}
			else
			{
				ofst << "";
			}
		}
	}
}
