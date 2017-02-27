/*

  Tanner Gower
  11/21/2016
  Project 8: Quick Sort

*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include "Student.h"

using namespace std;

void resolveDuplicateId(Student*);
string* loadNames(string);
void quickSort(vector<Student>&, int, int);
int partition(vector<Student>&, int, int);
void swap(Student&, Student&);


const int kNumStudents = 20;

int main ()
{
  srand(time(0));

  for (int i = 0; i < 3; i++) {
    cout << endl;
    cout << "--------Student Set " << (i + 1) << "--------" << endl;
    vector<Student> list;

    Student students[kNumStudents];
    resolveDuplicateId(students);
    string *firstNames = loadNames("firstnames");
    string *lastNames = loadNames("lastnames");
    for (int i = 0; i < kNumStudents; i++) {
      students[i].setName(firstNames[i] + " " + lastNames[i]);
      list.push_back(students[i]);
    }

    cout << "UNSORTED" << endl;
    for (int p = 0; p < list.size(); p++)
      cout << list[p].toString() << endl;
    cout << endl;

    cout << "SORTED BY GPA" << endl;
    quickSort(list, 0, list.size() - 1);
    for (int p = 0; p < list.size(); p++)
      cout << list[p].toString() << endl;
    cout << endl;
  }

  return 0;
}

void quickSort(vector<Student>& set, int start, int end)
{
  int pivotPoint;
  if (start < end) {
    pivotPoint = partition(set, start, end);
    quickSort(set, start, pivotPoint-1);
    quickSort(set, pivotPoint+1, end);
  }
}

int partition(vector<Student>& set, int start, int end)
{
  int pivot = start;
  while (start != end) {
    if (set[start].getGpa() < set[end].getGpa())
      swap(set[start], set[end]);
    if (set[pivot].getGpa() == set[start].getGpa())
      end--;
    else
      start++;
  }
  return start;
}

void swap(Student& node1, Student& node2)
{
  Student temp = node1;
  node1 = node2;
  node2 = temp;
}

string* loadNames(string filename)
{
  ifstream firstNamesFile;
  vector<string> list;
  firstNamesFile.open(filename.c_str());

  string name = "";
  while(firstNamesFile >> name)
    list.push_back(name);

  vector<string> shuffled;
  int randNum = 0;
  while (list.size() > 0) {
    randNum = rand() % list.size();
    shuffled.push_back(list[randNum]);
    list.erase(list.begin() + randNum);
  }

  string *rlist = new string[shuffled.size()];
  for (int i = 0; i < shuffled.size(); i++)
    rlist[i] = shuffled[i];

  return rlist;
}

void resolveDuplicateId(Student* list)
{
  for (int i = 0; i < kNumStudents; i++) {
    for (int j = i+1; j < kNumStudents; j++) {
      while (list[i].getId() == list[j].getId()) {
        list[i].setId(rand() % 9000 + 1000);
      }
    }
  }
}
