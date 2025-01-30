#include<iostream>
#include<fstream>
#include<string>
#include<vector> 
//#include<cstdlib> // for system(), used to execute system commands, // Could have used this to directly use ccommand propmt function but opt to do it myself
#include<cstdio> // To delete file, Syntax: remove("filename.txt");
//#include<filesystem> //unable to integrate, because old compiler to substituted this - using windows API, and also i've tried to avoid the use of it as it has many pre written logics
#include<Windows.h> // For getting Current working directory (problem: makes the app windows specific)(But file system not working because old compiler)
// WE CAN ALSO USE THE UP ARROW TO GET THE PREVIOUS COMMAND
#define APP_NAME "FILE MANAGEMENT SYSTEM"
using namespace std;
bool hier_status = false; // To not re-display hierarchy view if there is an error message
vector<string> split(string , char);
string join(vector<string> , char);
// Class of all the basic operations on FILE
class file_op{
public:
        void create(string fileName){
            ifstream test(fileName);
            if (test.good()){
                cout << "File is already present\n";
                hier_status = false;
                return ;
            }
            test.close();
            hier_status = true;
            ofstream file(fileName);
            file.close();
        }

        void del(string fileName){
            // remove is in cstdio
            if(remove(fileName.c_str()) != 0){ // c_str used to type cast string to const char*, as remove has paramter as const char*
                cout << "No such file as '" << fileName << "' found."<< endl; 
                hier_status = false;
                return ;
            }
            hier_status = true;
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
            cout << "File copied succesfully\n";
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

        void list(string path){
            path += "\\*";
            WIN32_FIND_DATA findFileData; // WIN32_FIND_DATA is a struct that stores information about any file or folder 
            HANDLE hFind = FindFirstFile(path.c_str(), &findFileData);// HANDLE is a data type  in the Windows API that represents a reference (or pointer) to an object managed by the Windows operating system It is used to interact with system resources like files and foldrs, HANDLE is like an ID that Windows gives you when you open or create a system resource
            // if there are no files in the directory then FindFirstFile resturns INVALID_HANDLE_VALUE
            if (hFind == INVALID_HANDLE_VALUE){
                cout << "No files found.\n";
                return;
            }    
            while (FindNextFile(hFind, &findFileData) != 0){ // findnextfile return non zero if there are more files else it returns 0
                string fileName = findFileData.cFileName;

                if (fileName == "." || fileName == "..") // . and .. are the default system directories which represent ".": the current directory and "..": the parent directory
                    continue;

                cout << fileName << endl;
            }

            FindClose(hFind);
        }

        void crtdir(string s){
            s = "mkdir \"" + s + "\"";
            system(s.c_str());
        }

        void deldir(string s){
            s = "rmdir \"" + s + "\" /S /Q" ; // /S to also delete subdirectories and /Q to force pass the the confirmation message given by command prompt
            system(s.c_str());
        }

        void help(){            
            cout << "\nCREATE: To create a file SYNTAX-> create <fileName/Path>\n"
                 << "DEL: To delete a file SYNTAX-> del <fileName/Path>\n"
                 << "COPY: To copy file or directory to clipboard SYNTAX-> cnp <sourceFileName>\n"
                 << "PASTE: To paste the clipboard content\n"                 
                 << "CD: To change directory SYNTAX:\n\t cd <directoryName/Path>\n\t cd - : To go back by one directory\n"
                 << "CRTDIR: To create a dir SYNTAX: ctdir <dirName/path>\n"
                 << "DELDIR: To delete a dir SYNTAX: deldir <dirName/path> (DANGEROUS!!!)\n"
                 << "LIST: To display all the content present in the current working directory SYNTAX: list\n"
                 << "HIER: To switch to an hierarchy view SYNTAX: hier (Enter use hier command again to disable hier view)\n"
                 << "END: To close and Exit the Session"
                 << "\n";
            hier_status = false;
        }

        
};

void stimes(string s, int n){ // prints a specific string n numbers f times
    for(int i = 0; i < n; i++)
        cout << s;
}

void hier(string cwd){
    string temp_cwd = cwd;
    file_op op;
    vector<string> cwd_arr = split(cwd, '\\');
    cout << "\nWindows(C:)" << endl;
    int i = 1;
    for(i = 1; i < cwd_arr.size(); i++){
        stimes(" ", i);
        cout << "> " << cwd_arr[i] << endl;
    }

    cwd += "\\*";
    WIN32_FIND_DATA findFileData; 
    HANDLE hFind = FindFirstFile(cwd.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE){
        cout << "No files found.\n";
        return;
    }    
    while (FindNextFile(hFind, &findFileData) != 0){ // findnextfile return non zero if there are more files else it returns 0
        string fileName = findFileData.cFileName;

        if (fileName == "." || fileName == "..") // . and .. are the default system directories which represent ".": the current directory and "..": the parent directory
            continue;
        ofstream test_file(temp_cwd + "\\" + fileName + "\\test________test.txt");
        // Checks if its a directory or a file
        if(test_file.good()){
            test_file.close();
            op.del(temp_cwd + "\\" + fileName + "\\test________test.txt");
            stimes(" ", i + 1);
            cout << "> " << fileName << endl; // is folder then ad a > in beginning
        }
        else{
            stimes(" ", i + 1);
            cout << fileName << endl;
            test_file.close();
        }
        
    }
    FindClose(hFind);
}

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
// To vaidate the number of arguments of a command
/**
 * arg_inp = number of arguments present
 * min_arg = min args possible
 * max_arg= max args possible
 * cmd = name of the command
 */
bool validate_args(int arg_inp, int min_arg,int max_arg, string cmd){
    if(arg_inp > max_arg){
        cout << "Too many arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
        hier_status = false;
        return false;
    }
    else if(arg_inp < min_arg){
        cout << "Too few arguments for the command '" << cmd << "',\nuse help to display the list and syntax of commands.\n";
        hier_status = false;
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

// Function to open shell (OPTIONAL)
void openWin() { // Pending...
}

int main(){
    // cout << "\t\t\t\t\t\b================================== " << endl;
    // cout << "\t\t\t\t\tWelcome to " << APP_NAME << "\n";

    cout<<"\t\t\t\t    ======================================================\n";
	cout<<"\t\t\t\t   |           Welcome to FILE MANAGEMENT SYSTEM          |\n";
    cout<<"\t\t\t\t    ======================================================\n\n\n";

    int hier_view = 0;
    string cwdPath = getCWD();
    string cwd = cwdPath;
    vector<string> clipboard;
    vector<string> cnpdir;
    vector<string> cwd_arr;
    while(true){
        string cmd;
        vector<string> cmd_arr;
        file_op op;
        bool validity = true; // Flag to check if the command is valid, intoduced this to encounter of printing both invalid arg and cmd not recognised
        if(hier_view % 2 == 0)
            cout << "\n" << cwd << "> ";
        else if(hier_status){
            hier(cwd);
            cout << "\nEnter your command: ";
        }
        else
            cout << "\nEnter your command: ";
        getline(cin, cmd);
        cmd_arr = split_cmd(cmd);

        if(cmd_arr[0] == "help")
            op.help();
        else if(cmd_arr[0] == "create" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))          
            op.create(cwd + "\\" + cmd_arr[1]);
        else if(cmd_arr[0] == "del" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))
            op.del(cwd + "\\" + cmd_arr[1]);
        else if(cmd_arr[0] == "copy" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0]))){
            ifstream file1(cmd_arr[1]);
            ofstream file2(cwd + "\\" + cmd_arr[1] + "\\test________test.txt");
            if(file1.good()){
                clipboard = op.copy(cmd_arr[1]);
                file1.close(); 
                hier_status = false;
                cout << "File copied successfully\n";
            }        
            else if(file2.good()){
                clipboard.push_back(cwd + "\\" + cmd_arr[1]);
                clipboard.push_back("");
                clipboard.push_back(cmd_arr[1]);
                file2.close();
                op.del(cwd + "\\" + cmd_arr[1] + "\\test________test.txt");
                hier_status = false;
                cout << "File copied successfully\n";
            }
            else{
                file1.close();
                file2.close();
                cout << "No such file or directory as '" << cmd_arr[1] << "' found.\n";
                hier_status = true;
            }
        }
        else if(cmd_arr[0] == "paste" && (validity = validate_args(cmd_arr.size() - 1, 0, 0, cmd_arr[0]))){
            if(clipboard.size() == 0){
                cout << "Nothing to paste, please copy a fil or folder first\n";
                hier_status = false;
            }
            else if(clipboard.size() == 2){
                ofstream copied_file(cwd + "\\" + clipboard[0]);
                copied_file << clipboard[1];
                clipboard.clear();
                copied_file.close();
            }
            else{
                op.crtdir(clipboard[2]);
                string temp = "xcopy \"" + clipboard[0] + "\" \"" + cwd + "\\" + clipboard[2] + "_copy" + "\" /E /I"; // Command prompt function to copy and paste directories, /E also ccopies all the subdirectories
                system(temp.c_str());
                clipboard.clear();
            }
        }
        else if(cmd_arr[0] == "cd" && (validity = validate_args(cmd_arr.size() - 1, 1, 10, cmd_arr[0])))
            op.cd(&cwd, cmd_arr);
        else if(cmd_arr[0] == "crtdir" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0])))
            op.crtdir(cmd_arr[1]);
        else if(cmd_arr[0] == "deldir" && (validity = validate_args(cmd_arr.size() - 1, 1, 1, cmd_arr[0]))){
            ofstream test_file(cwd + "\\" +cmd_arr[1] + "\\test________test.txt");
            if(test_file.good()){
                test_file.close();
                string confirmation;
                cout << "Are you sure you want to remove directory?(yes/no): ";
                cin >> confirmation;
                if(confirmation == "yes"){
                    cout << "WARNING: THERE IS NO GOING BACK, YOU DIRECTORY WILL BE PERMANENTLY REMOVED\nDo you want to proceed?(yes/no): ";
                    cin >> confirmation;
                    if(confirmation == "yes"){
                        cout << "Type \"confirm\" to confirm the action\n"
                        << "Type \"cancel\" to cancel the action\n";
                        cin >> confirmation;
                        if(confirmation == "confirm"){
                            op.deldir(cwd + "\\" + cmd_arr[1]);                            
                            op.del(cwd + "\\" +cmd_arr[1] + "\\test________test.txt");
                        }
                    }
                }
            }   
            else{
                test_file.close();
                cout << "No such directory as '" << cmd_arr[1] << "' found.\n";
                hier_status = false;
            }                 
        }
        else if(cmd_arr[0] == "list" && (validity = validate_args(cmd_arr.size() - 1, 0, 0, cmd_arr[0]))){
            op.list(cwd);
            hier_status = false;
        }
        else if(cmd_arr[0] == "hier" && (validity = validate_args(cmd_arr.size() - 1, 0, 0, cmd_arr[0]))){
            if(!hier_status){
                hier_status = true;
                hier_view += 1;
            }
            else{
                hier_status = false;
                hier_view += 1;
            }
            if(hier_view % 2 == 1)
                hier_status = true;
        }        
        else if(cmd_arr[0] == "end" && (validity = validate_args(cmd_arr.size() - 1, 0, 0, cmd_arr[0])))
            break;
        else if(validity){
            cout << "Error:'" << cmd_arr[0] << "' is not recognised as a Command,\nuse help for list and of commands.\n";
            hier_status = false;
        }
    }
    cout << "Thank You for using " << APP_NAME << "\n Exiting...\n"; 
    
    return 0;
}