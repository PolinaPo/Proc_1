#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants
{
	// Значение месяца цветения кустарников
	enum month { JAN, FEB, MAR, APR, MAY, JUNE, JULY, AUG, SEPT, OCT, NOV, DEC };
	// Значения видов цветов
	enum view { DOMESTIC, GARDEN, WILD };
	// Значения мест произрастания растений
	enum place { TUNDRA, DESERT, STEPPE, TAIGA, MIXED_FOREST, MOUNTAINS };

	struct tree
	{
		long age;
	};

	// структура, обощающая все имеющиеся растения
	struct plants
	{
		enum type { TREE, BUSH, FLOWER };
		type key;
		string name;
		place place_growth; 
		void *plants;
	};

	plants *plants_Input(ifstream &ifst);
	bool plants_Output(struct plants *plants, ofstream &ofst);

	struct bush
	{
		month m;
	};

	struct flower
	{
		view flower_view;
	};

	bush* bush_Input(ifstream &ifst);
	void bush_Output(struct bush* bush, ofstream &ofst);

	tree *tree_Input(ifstream &ifst);
	void tree_Output(struct tree *tree, ofstream &ofst);

	flower *flower_Input(ifstream &ifst);
	void flower_Output(struct flower *flower, ofstream &ofst);

	struct node
	{
		plants *info;
		node *next;
	};

	struct container
	{
		int size;
		node *head;
	};

	void container_Init(container *list);
	void container_Clear(struct container *list);
	void container_Fill(struct container *list, ifstream &ifst);
	void container_Output(struct container *list, ofstream &ofst);

	bool node_Add(struct container *currentList, ifstream &ifst);
	bool node_Output(struct node *headNode, int pos, ofstream &ofst);
	struct node *get_Node(struct node *head, int index);

	// Вывод только деревьев
	void Output_only_tree(struct container *list, ofstream &ofst);

	// Количество согласных букв в названии растения (целое число)
	int number_Consonants(struct plants *plants);

	// Сортировка содержимого контейнера
	void Sort(container *list);
	// Cравнение ключей двух программных объектов
	bool Compare(struct plants *first, struct plants *second);

	void MultiMethod(struct container* list, ofstream& ofst);

} // end type_plants namespace
#endif // PROGRAM_H
