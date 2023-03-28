#include <iostream>
#include "tasks_rk1.h"
#include <fstream>
#include <map>
#include <cstring>
#include <algorithm>
#include <vector>
#include <time.h>
#include <string>
#include <list>
#include <tuple>
using namespace std;

void WorkWithFile::readFromFile(const char* fileName)
{
    std::wifstream ifs;

    try
    {
        ifs.open(fileName, std::ios_base::in);
    }
    catch (std::exception ex)
    {
        std::cout << "Error: " << ex.what();
        return;
    }


    if (ifs.is_open() == true)
    {
        std::cout << "File is opened." << std::endl;
    }
    else
    {
        std::cout << "File could not be open!" << std::endl;
        return;
    }

    while (ifs)
    {
        wchar_t b;
        //ifs >> b;
        ifs.get(b);


        if (m_mapSymbols.find(b) != m_mapSymbols.end())
            m_mapSymbols[b] += 1;
        else
            m_mapSymbols[b] = 1;
    }
}
void WorkWithFile::writeStatInfoToFile(const char* outFile)
{
    std::wofstream  ofs(outFile);

    for (auto iter : m_mapSymbols)
    {
        ofs << iter.first << "\t" << iter.second << std::endl;
    }
}
void WorkWithFile::prepareTestFile(const char* fileName)
{
    std::wofstream  ofs(fileName);
    ofs << "Test file\n" << "Math operation + = - \n" << "1 2 3 5 6 7 8 222";
}
int task_1()
{
    WorkWithFile wf;
    wf.readFromFile("test.txt");
    wf.writeStatInfoToFile("output.txt");

    WorkWithFile wf1;
    wf1.prepareTestFile("test1.txt");
    wf1.readFromFile("test1.txt");
    wf1.writeStatInfoToFile("output1.txt");
    return 0;
}

char* convertDecToBin(int number) {
    char* result = new char[33];
    int n = number;
    int bit = 1;
    int i = 0;
    while (n > 0) {
        result[i] = (n % 2) + '0';
        n /= 2;
        i++;
        bit *= 10;
    }
    result[i] = '\0';
    std::reverse(result, result + strlen(result));
    return result;
}
void writeToFile(const char* fileName, const char* strNum) {
    std::ofstream file(fileName);
    if (file.is_open()) {
        file << strNum << std::endl;
        file.close();
        std::cout << "The result has been written to the file." << std::endl;
    }
}
int task_2(){
    writeToFile("result_task2.txt",convertDecToBin(16));
    return 0;
}

char* convertBinToHex(const char* binNum) {
    int len = strlen(binNum);
    int pad = len % 4;
    if (pad != 0) {
        len += 4 - pad;
    }
    int hexLen = len / 4;
    char* hexNum = new char[hexLen + 1];
    memset(hexNum, '0', hexLen);
    hexNum[hexLen] = '\0';
    for (int i = 0; i < len; i++) {
        char c = (i < strlen(binNum)) ? binNum[i] : '0';
        hexNum[i / 4] <<= 1;
        hexNum[i / 4] |= (c == '1') ? 1 : 0;
    }
    for (int i = 0; i < hexLen; i++) {
        hexNum[i] = (hexNum[i] < 10) ? hexNum[i] + '0' : hexNum[i] - 10 + 'A';
    }
    return hexNum;
}
int task_3() {
    const char* binNum = "1101110111110001";
    char* hexNum = convertBinToHex(binNum);
    ofstream fout("result_task3.txt");
    fout << hexNum;
    fout.close();
    delete[] hexNum;
    return 0;
}

void buildTree(int height)
{
    for (int i = 0; i < height; i++)
    {
        int space = 0;
        int dots = 0;
        while(space < (height - (i + 1)))
        {
            std::cout << " ";
            space++;
        }
        while(dots < (i + 1))
        {
            std::cout << "*";
            dots++;
        }
        for(int j = 0; j < i; j++)
            std::cout << "*";
        std::cout << std::endl;
    }
}
int task_4()
{
    int h;
    std::cout << "Set the height" << std::endl;
    std::cin >> h;
    buildTree(h);
    return 0;
}

typedef std::vector<std::vector<float>> Matrix;
typedef std::vector<std::pair<int, float >> VecPair;

void print(const Matrix& m)
{
    for (auto r : m)
    {
        for (auto c : r)
        {
            std::cout << c << "\t";
        }
        std::cout << std::endl;
    }
}
void randFill(std::vector<float>& ar)
{
    for (auto i = 0; i < ar.size(); i++)
        ar[i] = std::rand();
}
VecPair averStr2DArray(const Matrix& m)
{
    VecPair res;
    int num = 0;
    for (auto r : m)
    {
        float avg = 0.0;

        for (auto c : r)
        {
            avg += c;
        }
        avg /= r.size();
        res.push_back(std::make_pair(num++, avg));
    }

    return res;
}
void print_avg(const VecPair& v)
{
    for (auto i : v)
    {
        std::cout << i.first << "\t" << i.second << std::endl;
    }
}
void save_file(const char* filename, const Matrix& m, const VecPair& avg)
{
    std::ofstream ofs(filename);
    int count = 0;
    for (auto r : m)
    {
        for (auto c : r)
        {
            ofs << c << "\t";
        }
        ofs << ":  " << avg[count++].second << std::endl;
    }
}
int task_5()
{
    auto num = 10;
    std::srand(time(nullptr));
    Matrix  matrix;
    for (int i = 0; i < num; i++)
    {
        std::vector<float> m;
        m.resize(num);
        randFill(m);
        matrix.push_back(m);
    }
    print(matrix);
    VecPair avg_array = averStr2DArray(matrix);
    print_avg(avg_array);
    save_file("result_task5.txt", matrix, avg_array);
    return 0;
}

struct Node {
    Node* next;
    Node* prev;
    int nameNode;
    static int countNodes;
    Node() {
        next = nullptr;
        prev = nullptr;
        nameNode = ++countNodes;
    }
    Node(int _nameNode) {
        next = nullptr;
        prev = nullptr;
        nameNode = _nameNode;
    }
    ~Node() {}
};
int Node::countNodes = 0;
class LinkedList {
private:
    Node* Head;
    Node* Tail;
public:
    LinkedList() {
        Head = nullptr;
        Tail = nullptr;
    }
    ~LinkedList() {}
    void push_back(int nameNode) {
        Node* temp = new Node(nameNode);
        if (Head == nullptr) {
            Head = temp;
            Tail = temp;
            return;
        }
        Tail->next = temp;
        temp->prev = Tail;
        Tail = temp;
    }
    void writeToFileFromTail() {
        ofstream outFile("output_task6.txt");
        if (!outFile.is_open()) {
            cout << "Error: unable to open file" << endl;
            return;
        }
        Node* temp = Tail;
        while (temp != nullptr) {
            outFile << temp->nameNode << " ";
            temp = temp->prev;
        }
        outFile.close();
    }
    void writeToFileFromHead() {
        ofstream outFile("output_task6.txt");
        if (!outFile.is_open()) {
            cout << "Error: unable to open file" << endl;
            return;
        }
        Node* temp = Head;
        while (temp != nullptr) {
            outFile << temp->nameNode << " ";
            temp = temp->next;
        }
        outFile.close();
    }
};
int task_6() {
    LinkedList list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.writeToFileFromHead();
    list.writeToFileFromTail();
    return 0;
}

class StudentInfo {
private:
    tuple<string, string, char*> infoStudent;
    map<string, pair<list<int>, float>> subjMark;
public:
    StudentInfo(string surname, string name, char* studentID) {
        infoStudent = make_tuple(surname, name, studentID);
    }

    int addMark(const string& subjName, int mark, bool addSubj = false) {
        if (subjMark.find(subjName) == subjMark.end()) {
            if (addSubj) {
                subjMark[subjName].first.push_back(mark);
                subjMark[subjName].second = mark;
                return 2;
            }
            else {
                return 1;
            }
        }
        else {
            subjMark[subjName].first.push_back(mark);
            float sum = 0;
            for (auto& i : subjMark[subjName].first) {
                sum += i;
            }
            subjMark[subjName].second = sum / subjMark[subjName].first.size();
            return 0;
        }
    }

    int addSubj(const string& subjName) {
        if (subjMark.find(subjName) == subjMark.end()) {
            subjMark[subjName] = make_pair(list<int>(), 0);
            return 0;
        }
        else {
            return 1;
        }
    }

    float getAverMark(const string& subjName) {
        if (subjMark.find(subjName) == subjMark.end()) {
            return -1;
        }
        else {
            return subjMark[subjName].second;
        }
    }

    void printInfoStudent(bool writeFile = false) {
        ofstream out("student_info.txt");
        if (writeFile && out.is_open()) {
            out << get<0>(infoStudent) << " " << get<1>(infoStudent) << " : " << get<2>(infoStudent) << endl;
            for (auto& i : subjMark) {
                out << "\t" << i.first << " : ";
                for (auto& j : i.second.first) {
                    out << j << ", ";
                }
                out << "-- " << i.second.second << endl;
            }
            out.close();
        }
        else {
            cout << get<0>(infoStudent) << " " << get<1>(infoStudent) << " : " << get<2>(infoStudent) << endl;
            for (auto& i : subjMark) {
                cout << "\t" << i.first << " : ";
                for (auto& j : i.second.first) {
                    cout << j << ", ";
                }
                cout << "-- " << i.second.second << endl;
            }
        }
    }
};
int task_8() {

    StudentInfo student("Ivanov", "Ivan", "1239");

    student.addSubj("math");
    student.addSubj("physic");
    student.addSubj("chemistry");

    student.addMark("math", 5);
    student.addMark("math", 4);
    student.addMark("math", 3);

    student.addMark("physic", 4);
    student.addMark("physic", 4);

    student.addMark("chemistry", 5);

    student.printInfoStudent(true);

    return 0;
}

