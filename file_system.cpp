#include<iostream>
#include<fstream>
#include<string>
#include<vector> 
//#include<cstdlib> // for system(), used to execute system commands
#include<cstdio> // To delete file, Syntax: remove("filename.txt");
//#include<filesystem> //unable to integrate, because old compiler to substituted this - using windows API, and also i've tried to avoid the use of it as it has many pre written logics
#include<Windows.h> // For getting Current working directory (problem: makes the app windows specific)(But file system not working because old compiler)
// NOT WORKING WITH PATH !!!!
// MISSING FUNCTION : COPYING DIRECTORY
#define APP_NAME "FILE MANAGEMENT SYSTEM"
using namespace std;
vector<string> split(string , char);
string join(vector<string> , char);

// Class of all the basic operations on FILE
class file_op{
public:
        void create(string fileName) {
            ifstream test(fileName);
            if (test.good()) {
                cout << "File is already present\n";
                return ;
            }
            test.close();
            
            ofstream file(fileName);
            file.close();
        }

        void del(string fileName){
            // remove is in cstdio
            if(remove(fileName.c_str()) != 0)// c_str used to type cast string to const char*, as remove has paramter as const char*

                std::cout << "No such file or directory as '" << fileName << "' found."<< endl; 
        }

        vector<string> copy(string fileName){ 
            // Copies file name and its content in an array (CLIPBOARD)
            vector<string> file_name_arr = split(fileName, '.');
            vector<string> file_det;
            string buff;
            if(file_name_arr.size() == 2)
                file_det.push_back(file_name_arr[0] + "_copy." + file_name_arr[1]);
            else
                file_det.push_back(fileName + "_copy");
            ifstream file(fileName);
            file_det.push_back("");
            while(getline(file, buff))
                file_det[1] += buff + "\n";
            std::cout << "File copied succesfully\n";
            return file_det;
        }

        void cd(string* cwd, vector<string> cmd_arr){ 
            // CHECK FUNCTIONING
            vector<string> temp;
            string temp_cwd = *cwd;
            if(split(cmd_arr[1], '/').size() > 1 || split(cmd_arr[1], '\\').size() > 1){ 
                // To check wether the given path exists or not
                if(split(cmd_arr[1], '\\').size() > 1){
                    temp_cwd = cmd_arr[1];
                    ofstream test_file(temp_cwd + "\\test________test.txt");
                    // Checks if the entered path exists
                    if(test_file.good()){
                        *cwd = cmd_arr[1];
                        test_file.close();
                        del(temp_cwd + "\\test________test.txt");
                    }
                    else{
                        cout << "No such path as '" << cmd_arr[1] << "' found." << endl;
                        test_file.close();
                    }
                }
                else if(split(cmd_arr[1], '/').size() > 1){
                    temp_cwd = cmd_arr[1];
                    ofstream test_file(temp_cwd + "/test________test.txt");
                    // Checks if the entered path exists
                    if(test_file.good()){
                        *cwd = cmd_arr[1];
                        test_file.close();
                        del(temp_cwd + "/test________test.txt");
                    }
                    else{
                        cout << "No such path as '" << cmd_arr[1] << "' found." << endl;
                        test_file.close();
                    }
                }
            }
            else if(cmd_arr[1] == "-"){ // To go back by one directory
                if(split(*cwd, '\\').size() > 1){
                    temp = split(*cwd, '\\');
                    temp.pop_back();
                    *cwd = join(temp, '\\');
                }
                else if(split(*cwd, '/').size() > 1){
                    temp = split(*cwd, '/');
                    temp.pop_back();
                    *cwd = join(temp, '/');
                }
            }
            else{ // This case if user enters only directory name
                if(split(temp_cwd, '\\').size() > 1){
                    cmd_arr.erase(cmd_arr.begin());
                    temp_cwd = temp_cwd + "\\" + join(cmd_arr, ' ');
                    ofstream test_file(temp_cwd + "\\test________test.txt");
                    // Checks if the entered directory exists
                    if(test_file.good()){
                        *cwd = temp_cwd;
                        test_file.close();
                        del(temp_cwd + "\\test________test.txt");
                    }
                    else{
                        cout << "No such directory as '" << join(cmd_arr, ' ') << "' found." << endl;
                        test_file.close();
                    }
                }
                else if(split(temp_cwd, '/').size() > 1){
                    cmd_arr.erase(cmd_arr.begin());
                    temp_cwd = temp_cwd + "/" + join(cmd_arr, ' ');
                    ofstream test_file(temp_cwd + "/test________test.txt");
                    // Checks if the entered directory exists
                    if(test_file.good()){
                        *cwd = temp_cwd;
                        test_file.close();
                        del(temp_cwd + "/test________test.txt");
                    }
                    else{
                        cout << "No such directory as '" << join(cmd_arr, ' ') << "' found." << endl;
                        test_file.close();
                    }
                    test_file.close();
                }                
            }


        }

        void help(){            
            std::cout << "\nCREATE: To create a file SYNTAX-> create <fileName/Path>\n"
                 << "DEL: To delete a file SYNTAX-> del <fileName/Path>\n"
                 << "COPY: To copy content from one file to another SYNTAX-> cnp <sourceFile>\n"
                 << "PASTE: To paste the clipboard content\n"
                 << "END: To close and Exit the Session\n"
                 << "CD: To change directory SYNTAX:\n\t cd <directoryName/Path>\n\t cd - : To go back by one directory\n"
                 << "\n";
        }

        
};

// To join words in a string by a specific joinerz
string join(vector<string> arr, char joiner){
    string str = "";
    for(int  i = 0; i < arr.size(); i++){
        str += arr[i];
        str += joiner;
    }
    str.pop_back();
    return str;
}
// To validate the number of arguments of a command
/**
 * arg_inp = number of arguments present
 * min_arg = min args possible
 * max_arg= max args possible
 * cmd = name of the command
 */
bool validate_args(int arg_inp, int min_arg,int max_arg, string cmd){
    if(arg_inp > max_arg){
        std::cout << "Too many arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
        return false;
    }
    else if(arg_inp < min_arg){
        std::cout << "Too few arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
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
    s += splitter;
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

// This algo handles the splitting of path if directory name has space in it
vector<string> split_cmd(string s){
    vector<string> temp1, temp2, temp3;
    
    if(split(s, '/').size() > 1){ // Taking care of user input path can be of form / or "\"        
        temp1 = split(s, '/');
        temp3 = split(temp1[0], ' ');        
        temp2.push_back(temp3[0]);
        temp1.erase(temp1.begin());
        temp1.insert(temp1.begin(), temp3[1]);
        temp2.push_back(join(temp1, '/'));
        return temp2;
    }    
    else if( split(s, '\\').size() > 1){ // Taking care of user input path can be of form / or "\"
        temp1 = split(s, '\\');
        temp3 = split(temp1[0], ' ');        
        temp2.push_back(temp3[0]);
        temp1.erase(temp1.begin());
        temp1.insert(temp1.begin(), temp3[1]);
        temp2.push_back(join(temp1, '\\'));
        return temp2;
    }
    else
        return split(s, ' ');
}

// Function to display the heirarchy
void display_Heirarchy(){ // Pending...

}

// Function to open shell (OPTIONAL)
void openWin() { // Pending...
}

int main(){
//     std::cout << "Welcome to " << APP_NAME << "\n";
    string cwdPath = getCWD();
    string cwd = cwdPath;
    vector<string> clipboard;
    vector<string> cwd_arr;
    while(true){
        string cmd;
        vector<string> cmd_arr;
        file_op op;
        bool validity = true; // Flag to check if the command is valid, intoduced this to encounter of printing both invalid arg and cmd not recognised

        std::cout << "\n" << cwd << "> ";
        getline(cin, cmd);
        cmd_arr = split_cmd(cmd);

        if(cmd_arr[0] == "help")
            op.help();
        else if(cmd_arr[0] == "create" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))          
            op.create(cwd + "\\" + cmd_arr[1]);
        else if(cmd_arr[0] == "del" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))
            op.del(cwd + "\\" + cmd_arr[1]);
        else if(cmd_arr[0] == "copy" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))
            clipboard = op.copy(cwd + "\\" + cmd_arr[1]);
        else if(cmd_arr[0] == "paste" && (validity = validate_args(cmd_arr.size() - 1, 0, 0, cmd_arr[0]))){
            if(clipboard.size() == 0)
                std::cout << "Nothing to paste, please copy a file first\n";
            else{
                ofstream copied_file(clipboard[0]);
                copied_file << clipboard[1];
                clipboard.clear();
                copied_file.close();
            }
        }
        else if(cmd_arr[0] == "cd")
            op.cd(&cwd, cmd_arr);
        else if(cmd_arr[0] == "end")
            break;
        else if(validity)
            std::cout << "Error:'" << cmd_arr[0] << "' is not recognised as a Command,\nuse help for list and of commands.\n";
    }
    std::cout << "Thank You for using" << APP_NAME << "\n Exiting...\n"; 
    
    return 0;
}   