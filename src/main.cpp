#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

void clear_Screen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void load_json_file(ifstream& ifile, json& jsfile){

    if(jsfile.is_array()){
        ifile.open("list.json");
    }
    if(ifile.peek() != EOF){
        ifile >> jsfile;
    }

}

void save_json_file(ofstream& ofile, json& jsfile){

    ofile.open("list.json");
    ofile << jsfile;
    ofile.close();

}

void get_task(string& title, string& descrip){

    cout << "title: ";
    getline(cin, title);
    cout << "description: ";
    getline(cin, descrip);

}

void add_task_to_jsfile(ofstream& ofile, ifstream& ifile, json& jsfile, json& task, string title, string descrip){

    get_task(title, descrip);
    load_json_file(ifile, jsfile);

    ofile.open("list.json");

    task = {
        {"title", title},
        {"description", descrip},
    };
    jsfile.push_back(task);
    ofile << jsfile;

    ofile.close();
}

void view_all_task(ifstream& ifile, json& jsfile){

    load_json_file(ifile, jsfile);

    for(int i = 0;i < jsfile.size();i++){
        cout << i + 1 << " " << jsfile[i]["title"] << endl;
    }

    ifile.close();

}

void view_task_details(ifstream& ifile, json& jsfile, int taskIndex){

    load_json_file(ifile, jsfile);

    cout << " " << jsfile[taskIndex - 1]["title"] << endl;
    cout << "   description: " << jsfile[taskIndex - 1]["description"] << endl;

    ifile.close();

}

void remove_task_from_jsfile(ifstream& ifile, ofstream& ofile, json& jsfile){

    int taskIndex;
    view_all_task(ifile, jsfile);

    cout << endl << "remove: ";
    cin >> taskIndex;
    if(taskIndex >= 1 && taskIndex <= jsfile.size()){
        jsfile.erase(taskIndex - 1);
        save_json_file(ofile, jsfile);
    }
}

void edit_task(ifstream& ifile, ofstream& ofile, json& jsfile, int& taskIndex, string& title, string& descrip, json& task){

    load_json_file(ifile, jsfile);
    view_all_task(ifile, jsfile);

    cout << endl << ": ";
    cin >> taskIndex;
    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

    get_task(title, descrip);
    task = {
        {"title", title},
        {"description", descrip}
    };

    jsfile[taskIndex - 1] = task;
    save_json_file(ofile, jsfile);

}

void main_menu(){
    cout << "{Simple task manager(project)}" << endl << endl;
    cout << "[1] new task" << endl;
    cout << "[2] view taks" << endl;
    cout << "[3] remove task" << endl;
    cout << "[4] edit task" << endl;
    cout << "[5] exit" << endl << endl;;
}

void view_task_menu(){
    cout << endl << "[0] exit" << endl;
    cout << ": ";
}

void handle_view_task(ifstream& ifile, json& jsfile){
    clear_Screen();
    view_all_task(ifile, jsfile);
    view_task_menu();
}


void handle_add_task(ofstream& ofile, ifstream& ifile, json& jsfile, json& task, string title, string descrip){
    clear_Screen();
    add_task_to_jsfile(ofile, ifile, jsfile, task, title, descrip);
    clear_Screen();
}

void handle_remove_task(ifstream& ifile, ofstream& ofile, json& jsfile){
    clear_Screen();
    remove_task_from_jsfile(ifile, ofile, jsfile);
    clear_Screen();
}

void handle_edit_task(ifstream& ifile, ofstream& ofile, json& jsfile, int& taskIndex, string& title, string& descrip, json& task){
    clear_Screen();
    edit_task(ifile, ofile, jsfile, taskIndex, title, descrip, task);
    clear_Screen();
}

int main(){

    ofstream ofile;
    ifstream ifile;

    json jsfile = json::array();
    json task;

    string descrip, title;

    int option;

    while(true){
        main_menu();
        cout << ": ";
        cin >> option;

        while(option != 5){
            switch(option){
                case 1:
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    handle_add_task(ofile, ifile, jsfile, task, title, descrip);
                    goto endloop;
                break;

                case 2:
                int option;
                clear_Screen();
                handle_view_task(ifile, jsfile);
                cin >> option;
                    if(option == 0){
                        clear_Screen();
                        goto endloop;
                    }else if(option != 0){
                        int exitdetails;
                        clear_Screen();
                        view_task_details(ifile, jsfile, option);
                        view_task_menu();
                        cin >> exitdetails;
                        if(exitdetails == 0){
                            continue;
                        }
                    }
                break;

                case 3:
                    handle_remove_task(ifile, ofile, jsfile);
                    goto endloop;
                break;

                case 4:
                    int taskIndex;
                    handle_edit_task(ifile, ofile, jsfile, taskIndex, title, descrip, task);
                    goto endloop;
                break;

                default:
                break;
            }
        }
        endloop:;
        if(option == 5)
            break;
        if(option > 5 || option == 0){clear_Screen; continue;}
    }

}