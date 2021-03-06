#include <iostream>
#include <fstream>
#include "program.h"

using namespace std;
using namespace type_plants;

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect command line!\n"
             << "Waited: command infile outfile" << endl;
        exit(1);
    }

    cout << argv[1] << endl;
    cout << argv[2] << endl;
    ifstream ifst(argv[1]);
    if (!ifst.is_open())
    {
        cout << "File is not open!" << endl;
        exit(1);
    }
    ofstream ofst(argv[2]);

    cout << "Start" << endl;
    container *c = new container;
    container_Init(c);
    container_Fill(c, ifst);
    cout << "Filled container" << endl;
    sort(c);
    cout << "Sorted container" << endl;
    container_Output(c, ofst);
    cout << "Output container" << endl;
    ofst << endl;

    Output_only_tree(c, ofst);
    cout << "Output of trees only" << endl;

    container_Clear(c);
    cout << "Empty container" << endl;
    container_Output(c, ofst);
    cout << "Stop" << endl;

    system("pause");
    return 0;
}