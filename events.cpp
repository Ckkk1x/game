#include "events.h"
#include <fstream>
#include <iostream>
#include <locale.h>
using namespace std;

Events::Events() {
	text = "";
}
   map<string, Events> Events::eventsArray = {};

void Events::setUpEvents(string fileName) {
    setlocale(LC_ALL, "ru_RU.UTF-8"); // ��� ����������� ���������� ������� ��������
    fstream file;
    file.open(fileName, ios::in);
    if (!file) {
        throw exception("������ �������� �����");
    }
    //���������� ��� �������� ������� � ���������
    for (int iterator = 0; !file.eof(); iterator++) {
        Events* tempEvent = new Events; // TODO - �� ��������� ���������� ������
        //���� ��� ���� ��� �� �������� �� ���� ������� � ��������� �����
        string tempID = "";
        while(!file.eof()){
            string line;
            line = "";
            getline(file, line);
            if (line == "<e>") {
                //����������� � ������ ������ ������� (����� ������ <e>)
                do {
                    getline(file, line);
                    if (line == "<id>") { // id
                        getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����, ���� ����������� ��������, �� ��� ����� ���������� �������� ������ ��� ��� �������� ����
                        tempID = line;
                    }
                    if (line == "<t>") {
                        getline(file, line);
                        //���������� ����� ������ �� �����
                        while (line != "<-t>") {
                            (*tempEvent).text.append(line);
                            getline(file, line);
                            if (line == "<o>" || line == "<e>") {
                                throw exception("� ����� �������� ��� <-t>");
                            }
                        }
                    }
                    // ������� � ���� �� ��������� ��� �� ��� ��������� ���������
                    if (line == "<o>") {
                        getline(file, line);
                        Options* tempOption = new Options; // TODO - �� �������� �� ����� ������
                        for (int j = 0; line != "<-o>"; j++) {
                            if (line == "<ot>") {
                                getline(file, line);
                                //���������� ����� ������ �� �����
                                while (line != "<-ot>") {
                                    (*tempOption).text.append(line);
                                    getline(file, line);
                                    if (line == "<P>" || line == "<-o>") {
                                        throw exception("� ����� �������� ��� <-ot>");
                                    }
                                }
                            }
                            if (line == "<P>") { // physical health
                                getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                                (*tempOption).changePhysical = stoi(line);
                            }// TODO - �������� ��� ���� ��� ������ ���� � ��������� ����
                            if (line == "<M>") { // mental helth
                                getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                                (*tempOption).changeMental = stoi(line);
                            }
                            if (line == "<H>") { // hope 
                                getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                                (*tempOption).changeHope = stoi(line);
                            }
                            if (line == "<R>") { // resurrection
                                getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                                (*tempOption).changeResurrection = stoi(line);
                            }
                            if (line == "<t>" || line == "<-e>") {
                                throw exception("� ����� �������� ��� <-o>");
                            }
                            getline(file, line);
                        }
                        (*tempEvent).options.push_back(*tempOption);
                    }
                } while (line != "<-e>" && !file.eof());
            }
        }
        Events::eventsArray[tempID] = *tempEvent;
    }




	file.close();
}


string Events::getText() {
    return this->text;
}
