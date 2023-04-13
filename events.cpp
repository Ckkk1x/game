#include "events.h"

#include <fstream>
#include <iostream>
using namespace std;

Events::Events() {
	text = "";
    id = "";
}
   map<string, Events> Events::eventsArray = {};

void Events::setUpEvents(string fileName) {
    fstream file;
    file.open(fileName, ios::in);
    if (!file) {
        throw exception("������ �������� �����");
    }
    //���������� ��� �������� ������� � ���������
    for (int iterator = 0; file.eof(); iterator++) {
        Events* tempEvent = new Events;
        //���� ��� ���� ��� �� �������� �� ���� ������� � ��������� �����
        string tempID = "";
        for (;;) {
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
                    //if (line == "<o>") {
                    //    getline(file, line);
                    //    for (int j = 0; line != "<-o>"; j++) {
                    //        (*tempEvent).options[j].text.append(line);
                    //        getline(file, line);
                    //        if (line == "<P>") { // physical health
                    //            getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                    //            (*tempEvent).options[j].changePhysical = stoi(line);
                    //        }
                    //        if (line == "<M>") { // mental helth
                    //            getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                    //            (*tempEvent).options[j].changeMental = stoi(line);
                    //        }
                    //        if (line == "<H>") { // hope 
                    //            getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                    //            (*tempEvent).options[j].changeHope = stoi(line);
                    //        }
                    //        if (line == "<R>") { // resurrection
                    //            getline(file, line); // TODO - ��� ��������, ��� ����������� ����� ����
                    //            (*tempEvent).options[j].changeResurrection = stoi(line);
                    //        }
                    //        if (line == "<t>" || line == "<-e>") {
                    //            throw exception("� ����� �������� ��� <-o>");
                    //        }
                    //    }
                    //}
                } while (line != "<-e>");
            }
        }
        Events::eventsArray[tempID] = *tempEvent;
    }
    file.close();



	file.close();
}

