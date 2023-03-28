//
// Created by USER on 28.03.2023.
//

#ifndef TASKS_RK1_TASKS_RK1_H
#define TASKS_RK1_TASKS_RK1_H
#include <map>

class WorkWithFile {
private:
    std::map<wchar_t, int> m_mapSymbols;

public:
    WorkWithFile() {};
    ~WorkWithFile() {};

    void writeStatInfoToFile(const char* outFile);
    void readFromFile(const char* fileName);	//функция чтения из файла
    void prepareTestFile(const char* fileName);	//функция для создания тестового файла
};
int task_1();
int task_2();
int task_3();
int task_4();
int task_5();
int task_6();
int task_7();
int task_8();
#endif //TASKS_RK1_TASKS_RK1_H
