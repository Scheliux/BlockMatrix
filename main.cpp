#include <iostream>
#include <vector>
#include "BlockMatrix.h"
#include "read.hpp"

using namespace std;

///#define NORMAL_MODE
#ifdef NORMAL_MODE

class Menu
{
public:
    void run();

private:
    vector<BlockMatrix> BM;

    void menuWrite();
    void getElement() const;
    void importMatrix();
    void createMatrix();
    void writeMatrix() const;
    void sum();
    void mul();
};

int main()
{
    Menu m;
    m.run();
    return 0;
}

bool check(int n) { return 0<=n && n<=6; }

void Menu::run()
{
    int n = 0;
    do {
        menuWrite();

        n = read <int> ( "\n>>> ", "integer between 0 and 6 is needed\n", check );
        switch(n)
        {
        case 1:
            getElement();
            break;
        case 2:
            writeMatrix();
            break;
        case 3:
            createMatrix();
            break;
        case 4:
            importMatrix();
            break;
        case 5:
            sum();
            break;
        case 6:
            mul();
            break;
        }
    } while(n!=0);
}

void Menu::menuWrite()
{
    cout << endl;
    cout << " 0. - Quit" << endl;
    cout << " 1. - Get an element from a matrix" << endl;
    cout << " 2. - Write a matrix" << endl;
    cout << " 3. - Create a matrix from console" << endl;
    cout << " 4. - Import a matrix from file" << endl;
    cout << " 5. - Add two matrices (+)" << endl;
    cout << " 6. - Multiply two matrices (*)" << endl;
    cout << "There are " << BM.size() << " matrices stored.\n" ;
}

void Menu::getElement() const
{
    unsigned int a;
    cout << "\nType the index of the matrix that you want to get the element from.\n> ";
    cin >> a;
    if (a > BM.size()-1 || BM.size() == 0)
    {
        cout << "There's no matrix on that index!\n";
        return;
    }

    unsigned int i,j;
    cout << "\nGive the index of the row:\n> ";
    cin >> i;
    cout << "Give the index of the column:\n> ";
    cin >> j;

    try
    {
        cout << endl << BM[a].getElem(i, j) << endl;
    }
    catch (BlockMatrix::Exceptions ex)
    {
        if (ex == BlockMatrix::OVERINDEXED)
            cout << "Overindexing!\n";
    }
}

void Menu::writeMatrix() const
{
    unsigned int a;
    cout << "\nType the index of the matrix that you want to print.\n> ";
    cin >> a;
    if (a > BM.size()-1 || BM.size() == 0)
    {
        cout << "There's no matrix on that index!\n";
        return;
    }
    cout << endl << BM[a] << endl;
}

void Menu::importMatrix()
{
    string filename;
    cout << "Type the name of the file:\n> ";
    getline(cin, filename, '\n');
    try
    {
        BM.push_back(BlockMatrix(filename));
    }
    catch (BlockMatrix::Exceptions ex)
    {
        if (ex == BlockMatrix::OPEN_ERROR)
            cout << "The file doesn't exist.\n";
        if (ex == BlockMatrix::INPUT_ERROR)
            cout << "The data of the matrix is not appropriate.\n";
    }
}

void Menu::createMatrix()
{
    unsigned int b1, b2;
    vector<int> vec1;
    vector<int> vec2;
    int num;
    cout << "\nType the size of the first and second block.\n> ";

    cin >> b1 >> b2;
    cout << "Type the items of the first and second block.\n> ";
    for (unsigned int i = 0; i < b1*b1; ++i)
    {
        cin >> num;
        vec1.push_back(num);
    }
    for (unsigned int i = 0; i < b2*b2; ++i)
    {
        cin >> num;
        vec2.push_back(num);
    }

    BM.push_back(BlockMatrix(vec1, vec2));
}

void Menu::sum()
{
    unsigned int a, b;
    cout << "\nType the index of the first matrix.\n> ";
    cin >> a;
    cout << "Type the index of the second matrix.\n> ";
    cin >> b;
    if (a > BM.size()-1 || b > BM.size()-1 || BM.size() == 0)
    {
        cout << "There's no matrix on that index!\n";
        return;
    }
    try
    {
        BlockMatrix c = BM[a] + BM[b];
        cout << "\nResult:\n";
        cout << c;
    }
    catch (BlockMatrix::Exceptions ex)
    {
        if (ex == BlockMatrix::DIFFERENT_SIZE)
            cout << "Cannot add two different sized matrices!\n";
    }
}

void Menu::mul()
{
    unsigned int a, b;
    cout << "\nType the index of the first matrix.\n> ";
    cin >> a;
    cout << "Type the index of the second matrix.\n> ";
    cin >> b;
    if (a > BM.size()-1 || b > BM.size()-1 || BM.size() == 0)
    {
        cout << "There's no matrix on that index!\n";
        return;
    }
    try
    {
        BlockMatrix c = BM[a] * BM[b];
        cout << "\nResult:\n";
        cout << c;
    }
    catch (BlockMatrix::Exceptions ex)
    {
        if (ex == BlockMatrix::DIFFERENT_SIZE)
            cout << "Cannot multiply two different sized matrices!\n";
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("create matrix") {
    const string file1 = "teszt1.txt";
    const vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    const vector<int> vec2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};

    const vector<int> bad1 = {1, 2, 3, 4, 5, 6, 7, 8};
    const vector<int> bad2 = {9, 8, 7, 6, 5, 4, 3, 2};

    BlockMatrix BM1(file1);
    BlockMatrix BM2(vec1, vec2);

    CHECK_FALSE(!(BM1 == BM2));
    CHECK_THROWS(BlockMatrix("non_existing_file.txt"));
    CHECK_THROWS(BlockMatrix(bad1, bad2));
}

/**
TEST_CASE("remove_max") {
        PrQueue PQ;
        CHECK_THROWS(PQ.remove_max());
        Item item(23, "Csapat1");
        Item item2(69, "Csapat2");
        Item item3(420, "Csapat3");
        PQ.add(item);
        PQ.add(item2);
        PQ.add(item3);
        CHECK(PQ.remove_max()._pr == 420);
        CHECK_FALSE(PQ.is_empty());
}
*/

#endif
