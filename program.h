#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants {
	// «начение мес€ца цветени€ кустарников
	enum month { JAN, FEB, MAR, APR, MAY, JUNE, JULY, AUG, SEPT, OCT, NOV, DEC };

	struct tree {
		long age;
	};

	// структура, обощающа€ все растени€
	struct plants {
		enum type { TREE, BUSH };
		type key;
		string name;
		void* plants;
	};

	plants* plants_Input(ifstream& ifst);
	bool plants_Output(struct plants* plants, ofstream& ofst);

	struct bush {
		month m;
	};

	bush* bush_Input(ifstream& ifst);
	void bush_Output(struct bush* bush, ofstream& ofst);

	tree* tree_Input(ifstream& ifst);
	void tree_Output(struct tree* tree, ofstream& ofst);

	struct node {
		plants* info;
		node* next;
	};

	struct container { 
		int size;
		node* head;
	};

	void container_Init(container* list);
	void container_Clear(struct container* list);
	void container_Fill(struct container* list, ifstream& ifst);
	void container_Output(struct container* list, ofstream& ofst);

	bool node_Add(struct container* currentList, ifstream& ifst);
	bool node_Output(struct node* headNode, int pos, ofstream& ofst);
	struct node* get_node(struct node* head, int index);

	void MultiMethod(struct container* list, ofstream& ofst);
} // end type_plants namespace
#endif // PROGRAM_H


