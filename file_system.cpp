#include<iostream>
#include<fstream>
#include<string>
#include<vector> 
#include<cstdio> // To delete file, Syntax: remove("filename.txt");
//#include<filesystem> //unable to integrate, because old compiler to substituted this - using windows API
#include<Windows.h> // For getting Current working directory (problem: makes the app windows specific)(But file system not working because old compiler)

#define APP_NAME "FILE MANAGEMENT SYSTEM"

using namespace std;

// Class of all the basic operations on FILE
class file_op{
public:
        void create(string file_path) {
            ofstream file(file_path);
            file.close();
        }

        void del(string file_path){

            if(remove(file_path.c_str()) != 0)// c_str used to type cast string to const char*, as remove has paramter as const char*

                cout << "No such file or directory as '" << file_path << "' found."<< endl; 
        }

        void help(){            
            cout << "\ncreate: To create a file SYNTAX-> create <fileName/Path>\n"
                 << "del: To delete a file SYNTAX-> del <fileName/Path>\n"
                 << "end: To close and Exit the Session\n"
                 << "\n";
        }
};

// To validate the number of arguments of a command
bool validate_args(int arg_inp, int valid_arg, string cmd){
    if(arg_inp > valid_arg){
        cout << "Too many arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
        return false;
    }
    else if(arg_inp < valid_arg){
        cout << "Too few arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
        return false;
    }
    return true;
}


// To get the current working directory
string getCWD(){
    char cwd[MAX_PATH]; // An array of char to store path of var, array of 260 char for windows, MAX_PATH is a constn defined in windows.h 
    GetCurrentDirectoryA(MAX_PATH, cwd);// Function in windows.h  here cwd:A pointer to the buffer where the directory path will be stored
    string path = cwd;
    return path;
}

// Could have gone by displaying the function and assigning a number to them but to make it more natural i've made it linux like
// Though with small number of commands displaying the list and assigning the number is more handy but as we add more and more commands it starts to clutter

// Used to count the number of splitter
// Avoided the use of in built count function in algorithm library
/**
 * number of words = number of splitter + 1
 */
int countChr(string s, char splitter){
    int count = 0;
    for (int i = 0; i < s.length(); i++){
        if (s[i] == splitter){
            count++;
        }
    }
    return count;
}

// Split function to differentiate between the actual command and the arguments
/**
 * s: string to be split
 * splitter: the character to split the string by
 */
vector<string> split(string s, char splitter){
    s += " ";
    vector<string> arr;
    string temp = "";

    for(int i = 0; i < s.length() ; i++){
        if(s[i] == splitter){
            arr.push_back(temp);
            temp = "";
        }
        else
            temp += s[i];
    }
    return arr;
}

// Function to display the heirarchy(PENDING...)
void display_Heirarchy();

// Function to open shell
void openWin() { // Pending...
}

int main(){
    vector<string> cmd;
    cout << "Welcome to " << APP_NAME << "\n";
    string cwdPath = getCWD();

    while(true){
        string cmd;
        vector<string> cmd_arr;
        file_op op;
        bool validity = true; // Flag to check if the command is valid, intoduced this to encounter of printing both invalid arg and cmd not recognised


        cout << "\n" << cwdPath << "> ";
        getline(cin, cmd);
        cmd_arr = split(cmd, ' ');

        if(cmd_arr[0] == "help")
            op.help();
        else if(cmd_arr[0] == "create" && (validity = validate_args(cmd_arr.size() - 1, 1, cmd_arr[0])))          
            op.create(cmd_arr[1]);
        else if(cmd_arr[0] == "del" && (validity = validate_args(cmd_arr.size() - 1, 1, cmd_arr[0])))
            op.del(cmd_arr[1]);
        else if(cmd_arr[0] == "end")
            break;
        else if(validity)
            cout << "Error:'" << cmd_arr[0] << "' is not recognised as a Command,\nuse help for list and of commands.\n";
    }
    cout << "Thank You for using" << APP_NAME << "\nExiting...\n";
    
    return 0;
} 