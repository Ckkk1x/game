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
        throw exception("Ошибка открытия файла");
    }
    //перебираем все елементы массива с событиями
    for (int iterator = 0; file.eof(); iterator++) {
        Events* tempEvent = new Events;
        //цикл для того что бы пройтись по всем строкам в текстовом файле
        string tempID = "";
        for (;;) {
            string line;
            line = "";
            getline(file, line);
            if (line == "<e>") {
                //перемещение в рамках одного события (между тэгами <e>)
                do {
                    getline(file, line);
                    if (line == "<id>") { // id
                        getline(file, line); // TODO - нет проверки, что считывается после тэга, если отсутствует значение, то оно может попытаться записать другой тэг как значение айди
                        tempID = line;
                    }
                    if (line == "<t>") {
                        getline(file, line);
                        //считывание всего текста из файла
                        while (line != "<-t>") {
                            (*tempEvent).text.append(line);
                            getline(file, line);
                            if (line == "<o>" || line == "<e>") {
                                throw exception("В файле пропущен тэг <-t>");
                            }
                        }
                    }
                    //if (line == "<o>") {
                    //    getline(file, line);
                    //    for (int j = 0; line != "<-o>"; j++) {
                    //        (*tempEvent).options[j].text.append(line);
                    //        getline(file, line);
                    //        if (line == "<P>") { // physical health
                    //            getline(file, line); // TODO - нет проверки, что считывается после тэга
                    //            (*tempEvent).options[j].changePhysical = stoi(line);
                    //        }
                    //        if (line == "<M>") { // mental helth
                    //            getline(file, line); // TODO - нет проверки, что считывается после тэга
                    //            (*tempEvent).options[j].changeMental = stoi(line);
                    //        }
                    //        if (line == "<H>") { // hope 
                    //            getline(file, line); // TODO - нет проверки, что считывается после тэга
                    //            (*tempEvent).options[j].changeHope = stoi(line);
                    //        }
                    //        if (line == "<R>") { // resurrection
                    //            getline(file, line); // TODO - нет проверки, что считывается после тэга
                    //            (*tempEvent).options[j].changeResurrection = stoi(line);
                    //        }
                    //        if (line == "<t>" || line == "<-e>") {
                    //            throw exception("В файле пропущен тэг <-o>");
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

