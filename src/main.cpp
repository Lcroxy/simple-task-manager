#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void addtask(ofstream& ofile, ifstream& ifile, json& jsfile, json& task, string title, string descrip){
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    cout << "title: ";
    getline(cin, title);
    cout << "description: ";
    getline(cin, descrip);

    ifile.open("list.json");
    if(ifile.peek() != EOF){
        ifile >> jsfile;
    }
    ifile.close();

    if(jsfile.is_array()){
        ofile.open("list.json");

        task = {
            {"title:", title},
            {"description:", descrip}
        };

        jsfile.push_back(task);
        ofile << jsfile;
    }
    ofile.close();
}

void showtasks(ifstream& ifile, json& jsfile){
    ifile.open("list.json");
    if(ifile.peek() != EOF){
        ifile >> jsfile;
    }

    for(int i = 0;i < jsfile.size();i++){
        cout << i + 1 << " title: " << jsfile[i]["title:"] << endl;
        cout << "     details: " << jsfile[i]["description:"] << endl << endl;
    }
    ifile.close();
}


void remove(ifstream& ifile, ofstream& ofile, json& jsfile){
    int remv;
    showtasks(ifile, jsfile);

    cout << endl << "which task u want to remove: ";
    cin >> remv;
    if(remv >= 1 && remv <= jsfile.size()){
        jsfile.erase(remv - 1);

        ofile.open("list.json");
        ofile << jsfile;
        ofile.close();
    }else{
        cout << "no found task" << endl;
    }

}

void menu(){
    cout << "{Simple task manager(project)}" << endl << endl;
    cout << "[1] new task" << endl;
    cout << "[2] show taks" << endl;
    cout << "[3] remove task" << endl;
    cout << "[4] exit" << endl << endl;;
}

void showtask_menu(){
    cout << endl << "[0] exit" << endl;
    cout << "pick: ";
}

int main(){
    ofstream ofile;
    ifstream ifile;

    json jsfile = json::array();
    json task;

    string title = "", descrip = "";

    int cursor;

    while(true){
        menu();
        cout << "pick: ";
        cin >> cursor;
        while(cursor != 4){
            if(cursor == 1){
                clear();
                addtask(ofile, ifile, jsfile, task, title, descrip);
                clear();
                break;
            }else if(cursor == 2){
                clear();
                int exit;
                showtasks(ifile, jsfile);
                showtask_menu();
                cin >> exit;
                if(exit == 0){
                    clear();
                    break;
                }
            }else if(cursor == 3){
                clear();
                remove(ifile, ofile, jsfile);
                clear();
                break;
            }else if(cursor > 4 || cursor == 0){
                break;
            }
        }
        if(cursor == 4){
            break;
        }if(cursor > 4 || cursor == 0){
            clear();
            continue;
        }
    }
}