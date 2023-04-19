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
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Для нормального считывания русских символов
    fstream file;
    file.open(fileName, ios::in);
    if (!file) {
        throw exception("Ошибка открытия файла");
    }
    //перебираем все елементы массива с событиями
    for (int iterator = 0; !file.eof(); iterator++) {
        Events* tempEvent = new Events; // TODO - не удаляется выделенная память
        //цикл для того что бы пройтись по всем строкам в текстовом файле
        string tempID = "";
        while(!file.eof()){
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
                    // Заходим в один из вариантов что бы его полностью заполнить
                    if (line == "<o>") {
                        getline(file, line);
                        Options* tempOption = new Options; // TODO - не почистил за собой память
                        for (int j = 0; line != "<-o>"; j++) {
                            if (line == "<ot>") {
                                getline(file, line);
                                //считывание всего текста из файла
                                while (line != "<-ot>") {
                                    (*tempOption).text.append(line);
                                    getline(file, line);
                                    if (line == "<P>" || line == "<-o>") {
                                        throw exception("В файле пропущен тэг <-ot>");
                                    }
                                }
                            }
                            if (line == "<P>") { // physical health
                                getline(file, line); // TODO - нет проверки, что считывается после тэга
                                (*tempOption).changePhysical = stoi(line);
                            }// TODO - добавить елз если нет такого тэга и присвоить ноль
                            if (line == "<M>") { // mental helth
                                getline(file, line); // TODO - нет проверки, что считывается после тэга
                                (*tempOption).changeMental = stoi(line);
                            }
                            if (line == "<H>") { // hope 
                                getline(file, line); // TODO - нет проверки, что считывается после тэга
                                (*tempOption).changeHope = stoi(line);
                            }
                            if (line == "<R>") { // resurrection
                                getline(file, line); // TODO - нет проверки, что считывается после тэга
                                (*tempOption).changeResurrection = stoi(line);
                            }
                            if (line == "<t>" || line == "<-e>") {
                                throw exception("В файле пропущен тэг <-o>");
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
