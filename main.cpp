#include "organizationTree.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main(void) {
	Tree Organization;
	string command;
	string input[3];
	//input[0] ����� �̸�
	//input[1] �ൿ
	//input[2] ����� �̸�

	while (1) {
		getline(cin, command);
		char* buffer = new char[100];
		strcpy(buffer, command.c_str());
		char* tok = strtok(buffer, " ");
		int Idx = 0;
		while (tok != NULL) {
			input[Idx++] = (string(tok));
			tok = strtok(NULL, " ");
		}
		if (input[0]=="print") {
			Organization.showSub();
		}
		else if (input[1] == "") continue; //boss�̸� �Է� 
		else if (input[1]=="hires") {
			Organization.insert(input[0], input[2]);
		}
		else if (input[0] == "fire") {
			Organization.remove(input[1]);
		}
	}
}