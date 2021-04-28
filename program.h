#ifndef PROGRAM_H
#define PROGRAM_H
#include <fstream>
#include <string>
using namespace std;

namespace type_plants
{
	// �������� ������ �������� �����������
	enum month
	{
		JAN,
		FEB,
		MAR,
		APR,
		MAY,
		JUNE,
		JULY,
		AUG,
		SEPT,
		OCT,
		NOV,
		DEC
	};

	// �������� ����� ������
	enum view
	{
		DOMESTIC,
		GARDEN,
		WILD
	};
	// �������� ���� ������������� ��������
	enum place
	{
		TUNDRA,
		DESERT,
		STEPPE,
		TAIGA,
		MIXED_FOREST,
		MOUNTAINS
	};

	struct tree
	{
		long age;
	};

	// ���������, ��������� ��� ��������
	struct plants
	{
		enum type
		{
			TREE,
			BASH,
			FLOWER
		};
		type key;
		string name;
		place place_growth; //����� �������������
		void *plants;
	};

	plants *plants_Input(ifstream &ifst);
	bool plants_Output(struct plants *plants, ofstream &ofst);

	struct bash
	{
		month m;
	};

	// �����
	struct flower
	{
		view flower_view;
	};

	bash *bash_Input(ifstream &ifst);
	void bash_Output(struct bash *bash, ofstream &ofst);

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
	struct node *get_node(struct node *head, int index);

	// ����� ������ ��������
	void Output_only_tree(struct container *list, ofstream &ofst);

} // end type_plants namespace
#endif // PROGRAM_H

// ���������� ��������� ���� � �������� �������� (����� �����)
int number_consonants(struct plants *plants);

// ���������� ����������� ����������
void sort(container *list);
// C�������� ������ ���� ����������� ��������
bool compare(struct plants *first, struct plants *second);

} // end type_plants namespace
#endif // PROGRAM_H
