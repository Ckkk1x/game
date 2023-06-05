#include "events.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <locale.h>
using namespace std;

Events::Events() {
	text = "";
}
   map<string, Events> Events::eventsArray = {};

void Events::setUpEvents(string fileName) {
    // ��� ����������� ���������� ������� ��������
    setlocale(LC_ALL, "ru_RU.UTF-8"); 

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
            bool eventIsReadyToSave;
            eventIsReadyToSave = false;
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
                    // ������� � ������� ������� ��� �� ��� ��������� ���������
                    if (line == "<zo>") {
                        getline(file, line);
                        Options* tempOption = new Options; // TODO - �� �������� �� ����� ������ \
                        �������������� ����� �� ����� ���������, ��� ��� �� ������
                        for (int j = 0; line != "<-zo>"; j++) {
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
                        (*tempEvent).zeroOption = (*tempOption);
                        tempOption = NULL;
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
                    if (line == "<N>") {
                        getline(file, line);
                        //���������� ����� ������ �� �����
                        while (line != "<-N>") {
                            int userVariant;
                            string nextEventId;
                            string word;
                            istringstream iss(line);
                            for (int i = 0; getline(iss, word, ' '); i++) {
                                // �������� �� ������� � ������� �����
                                // � ������ ����� ��������� ���������� �������, ��� ������ ������
                                if (i == 0) {
                                    userVariant = stoi(word);
                                }
                                if (i == 1) {
                                    nextEventId = word;
                                }
                            }
                            (*tempEvent).nextEventLine[userVariant] = nextEventId;
                            getline(file, line);
                            if (line == "<-e>") {
                                throw exception("� ����� �������� ��� <-N>");
                            }
                        }
                    }
                } while (line != "<-e>" && !file.eof());
                eventIsReadyToSave = true;
            }
            if (eventIsReadyToSave) {
                Events::eventsArray[tempID] = *tempEvent;
                break;
            }
        }
    }

	file.close();
}


string Events::getText() {
    return this->text;
}
