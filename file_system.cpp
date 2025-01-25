#include<iostream>
#include<fstream>
#include<string>
#include<vector> 
#include<cstdio> // To delete file, Syntax: remove("filename.txt");
//#include<filesystem> unable to integrate, because old compiler to substituted this - using windows API
#include<Windows.h> // For getting Current working directory and opening terminal (problem: makes the app windows specific)
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
                cout << "No such file or directory as " << file_path << " found."<< endl; 
        }
};
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
void display_Heirarchy(){
    // Pending...
};
// Function to open shell
void openWin(){ 
    // Pending...
}
int main(){
    vector<string> cmd;
    cout << "Welcome to file management system\n";
    
    while(true){
        string cmd;
        vector<string> cmd_arr;
        file_op op;
        cout << "\nPath Will Be Here> ";
        getline(cin, cmd);
        cmd_arr = split(cmd, ' ');
        if(cmd_arr[0] == "help"){
            cout << "\ncreate: to create a file SYNTAX-> create <fileName/Path>\n"
                 << "del: to delete a file SYNTAX-> del <fileName/Path>\n"
                 << "\n";
        }
        else if(cmd_arr[0] == "create")
            op.create(cmd_arr[1]);
        else if(cmd_arr[0] == "del")
            op.del(cmd_arr[1]);
        else
            cout << "Command not found, type help to display list of commands";
    }
    return 0;
} 