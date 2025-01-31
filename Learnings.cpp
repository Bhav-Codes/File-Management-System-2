#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
//TESTING HEIRARCHY SYSTEM
// string rep(string a, int n){
//     string b = "";
//     for(int i = 0; i < n; i++){
//         b += a;
//     }
//     return b;
// }

// int main(){
//     int n;
//     string temp;
//     cout << "Enter";
//     cin >> n;
//     while(true){
//         for(int i = 0; i < n; i++){
//             cout << rep(" ",i) <<"File\n";
//         }

//         cout << "Enter: ";
//         getline(cin, temp);

//         if(temp == "cd +")
//             n += 1;
//         else if(temp == "cd -")
//             n -= 1;
//         else
//             cout << "Command not found";
//     }
// }

//----------------------------------------------------------------------------------------------------------
//TESTING VECTORS AND SPLITTING STRINGS
// READ HANDWRITTEN NOTES !!!!

// int countChr(string s, char splitter){
//     int count = 0;
//     for (int i = 0; i < s.length(); i++){
//         if (s[i] == splitter){
//             count++;
//         }
//     }
//     return count;
// }

// vector<string> split(string s, char splitter){
//     vector<string> arr;
//     string temp = "";

//     for(int i = 0; i < s.length() ; i++){
//         if(s[i] == splitter){
//             arr.push_back(temp);
//             temp = "";
//         }
//         else
//             temp += s[i];
//     }
//     return arr;
// }

// int main(){
//     string a = "Hello there my name is bhavya singhal";

//     vector<string> b = split(a, ' ');
    
//     for(int i = 0; i < countChr(a, ' ') + 1; i++){
//         cout << b[i] << " ";
//     }
// }

//------------------------------------------------------------------------------------------------------------------------

// LEARNING MACRO AND TESTING __FILE__ MACRO
//#include<filesystem> (issue: compiler cannot recognise this library )
// #include <limits.h> // for getting the current working direcctory
// #include <filesystem>// failed to integrate
// int main(){
//     string a = current_path().string();
//     string b = __FILE__;
//     cout << a << b << endl;
// }

//-----------------------------------------------------------------------------------------------------------------------------------

// LEARNING AND IMPLEMENTING OOPS
// #include<fstream>
// class file_op{
// public:
//         void create(string file_path) {
//             ofstream file(file_path);
//             file.close();
//         }
// };

// int main(){
//     string f;
//     cout << "Enter file name: ";
//     cin >> f;
//     file_op obj;
//     obj.create(f);
// }

//-----------------------------------------------------------------------------------------------------------------------------------

// TRYING TO INCLUDE FILESYSTEM/CSTDIO?

// #include <iostream>
// #include <cstdio>
// class file_op{
// public:

//         void del(string file_path){

//             if(remove(file_path.c_str()) != 0)// c_str used to type cast string to const char*, as remove has paramter as const char*

//                 cout << "No such file or directory as " << file_path << " found."<< endl;
//         }
// };

// ---------------------------------------------------------------------------------------------------------------------

// Including Windows API for getting cwd and opening terminal
// #include<windows.h>
// void openWin() {
//     // Command to open a new Command Prompt window
//     const char* command = "cmd.exe";

//     // Setting up the process information structures
//     STARTUPINFO si = { sizeof(STARTUPINFO) }; // Startup information structure
//     PROCESS_INFORMATION pi = {};             // Process information structure

//     // Create a new process (launch terminal)
//     if (CreateProcess(
//             nullptr,               // Application name (nullptr allows specifying it in `command`)
//             const_cast<char*>(command), // Command line
//             nullptr,               // Process security attributes
//             nullptr,               // Thread security attributes
//             FALSE,                 // Inherit handles
//             0,                     // Creation flags
//             nullptr,               // Environment
//             nullptr,               // Current directory
//             &si,                   // Startup information
//             &pi                    // Process information
//         )) {
//         std::cout << "Terminal opened successfully!" << std::endl;

//         // Close process and thread handles
//         // CloseHandle(pi.hProcess);
//         // CloseHandle(pi.hThread);
//     } else {
//         std::cerr << "Failed to open terminal. Error: " << GetLastError() << std::endl;
//     }
// }

// int main(){
//     openWin();
// }

// #include <windows.h>

// int main() {
//     char cwd[MAX_PATH];
//     if (GetCurrentDirectoryA(MAX_PATH, cwd)) {
//         cout << "Current working directory: " << cwd << std::endl;
//     } else {
//         cerr << "Error: Unable to get current working directory." << std::endl;
//     }
//     return 0;
// }

// #include <windows.h>

// int main() {
//     char cwd[MAX_PATH];
//     // if (GetCurrentDirectoryA(MAX_PATH, cwd)) {
//     GetCurrentDirectoryA(MAX_PATH, cwd);
//     string path = cwd;
//     cout << path << endl;
//     return 0;
// }
// TRYING CSTDLIB FOR OPENING TERMINAL WINDOW

// #include <cstdlib> // For system()
// int main() {
//     string command = "start cmd /c \"g++ program.cpp -o program && program && pause\"";// This command opens a new cmd window, compiles the program, runs it, and then pauses it
//     // It automatically closes the cmd window after the program has finished running
//     system(command.c_str());
//     int a;
//     cout << "Enter a number: ";
//     cin >> a;
//     cout << "Hello";
    
//     return 0;
// }

//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//TESTING OUT FORMAT

// int main(){
//     // cout<<"\t    ======================================================\n";
// 	// cout<<"\t   |               FILE MANAGEMENT SYSTEM                 |\n";
//     // cout<<"\t    ======================================================\n\n\n\n\n\n\n\n\n\n\n";

//     cout << "FILE MANAGEMENT SYSTEM";
// }

//------------------------------------------------------------------------------------------------------------------------------------------------

// COPYING FILE

// int main(){
//     ifstream src("file.txt");
//     ofstream dest("file_copy.txt", ios::out);
//     string buff;
//     while(getline(src, buff)){
//         dest << buff << endl;
//     }
// }

//----------------------------------------------------------------------------------------------------------------------------------------------------------------

// EXPLORING CSTDLIB FOR SYSTEM()

// #include<windows.h>
// string getCWD(){
//     char cwd[MAX_PATH]; // An array of char to store path of var, array of 260 char for windows, MAX_PATH is a constn defined in windows.h 
//     GetCurrentDirectoryA(MAX_PATH, cwd);// Function in windows.h  here cwd:A pointer to the buffer where the directory path will be stored
//     string path = cwd;
//     return path;
// }

// int main(){
//     string cmd = "cd C:/Desktop files/IT ALL BEGINS HERE/Zine/File Management System in C++";

//     system(cmd.c_str());
//     cout << getCWD();
//     ofstream file("file.txt");
//     file << "Hello, World!";
//     file.close();
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     ifstream files("C:/Desktop files/IT ALL BEGINS HERE/Zine/File Explorer/hello.txt");
//     cout << files.good();
//     files.close();
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     cout << !0; 
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// LEARNING HASHMAPS FOR DIRECTORIES
// #include<unordered_map>

// int main(){
//     unordered_map<string, string> dir;

//     dir = {{"Hello", "There"} , {"File", "Access"} , {"System", "In C++"} , {"Directory", "Access "} , {"File", "Management"}};
//     // DUPLICATES SO 2ND ONE IGNORED ALSO NOT COUNTED IN SIZE
//     // dir.insert({"My", "name"});
//     cout << dir["qwert"]; // Defined here but empty value
//     cout << dir.size() << dir["poiu"]; // !! SIZE NOT
//     cout << dir["asdf"];

//     dir["qwert"] = "ghfjd";
//     cout << dir["qwert"];
// } 

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     string temp;
//     ofstream file("C:\\Desktop files\\IT ALL BEGINS HERE\\Zine\\Doesn't exist path\\Hello.txt");
//     cout << bool(file.good()); // outputs false
//     file.close();

// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     string temp = "Hello there";
//     temp.pop_back();
//     cout << temp;
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     vector<int> a = {1,2,3,4,5};
//     a.erase(a.begin());
//     cout << a[0];
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// string join(vector<string> arr, char joiner){
//     string str = "";
//     for(int  i = 0; i < arr.size(); i++){
//         str += arr[i];
//         str += joiner;
//     }
//     str.pop_back();
//     return str;
// }

// vector<string> split(string s, char splitter){
//     s += splitter;
//     vector<string> arr;
//     string temp = "";

//     for(int i = 0; i < s.length() ; i++){
//         if(s[i] == splitter){
//             arr.push_back(temp);
//             temp = "";
//         }
//         else
//             temp += s[i];
//     }
//     return arr;
// }

// // This algo handles the splitting of path if directory name has space in it
// vector<string> split_cmd(string s){
//     vector<string> temp1, temp2, temp3;
    
//     if(split(s, '/').size() > 1){ // Taking care of user input path can be of form / or "\"        
//         temp1 = split(s, '/');
//         temp3 = split(temp1[0], ' ');        
//         temp2.push_back(temp3[0]);
//         temp1.erase(temp1.begin());
//         temp1.insert(temp1.begin(), temp3[1]);
//         temp2.push_back(join(temp1, '/'));
//         return temp2;
//     }    
//     else if( split(s, '\\').size() > 1){ // Taking care of user input path can be of form / or "\"
//         temp1 = split(s, '\\');
//         temp3 = split(temp1[0], ' ');        
//         temp2.push_back(temp3[0]);
//         temp1.erase(temp1.begin());
//         temp1.insert(temp1.begin(), temp3[1]);
//         temp2.push_back(join(temp1, '\\'));
//         return temp2;
//     }
//     else
//         return split(s, ' ');
// }

// int main(){
//     // string test = "cd C:/Desktop files/IT ALL BEGINS HERE/Zine/File Management System in C++";
//     string test = "Hello there my name is";
//     vector<string> test2 = split_cmd(test);
//     for(int i = 0; i < test2.size(); i++){
//         cout << test2[i] << endl;
//     }
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// #include<cstdlib>

// int main(){
//     string s = "mkdir \"C:\\Desktop files\\IT ALL BEGINS HERE\\Zine\\hello\"";
//     system(s.c_str());
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// BUILDING HIERARCHY SYSTEM:

// #include <iostream>
// #include <windows.h>

// int main() {
//     string path = "C:\\Desktop files\\IT ALL BEGINS HERE";
//     path += "\\*";
//     WIN32_FIND_DATA findFileData; // WIN32_FIND_DATA is a struct that stores information about any file or folder 
//     HANDLE hFind = FindFirstFile(path.c_str(), &findFileData);// HANDLE is a data type  in the Windows API that represents a reference (or pointer) to an object managed by the Windows operating system It is used to interact with system resources like files and foldrs, HANDLE is like an ID that Windows gives you when you open or create a system resource
//     // if there are no files in the directory then FindFirstFile resturns INVALID_HANDLE_VALUE
//     if (hFind == INVALID_HANDLE_VALUE){
//         std::cout << "No files found.\n";
//         return 1;
//     }    
//     while (FindNextFile(hFind, &findFileData) != 0){ // findnextfile return non zero if there are more files else it returns 0
//         string fileName = findFileData.cFileName;

//         if (fileName == "." || fileName == "..") // . and .. are the default system directories which represent ".": the current directory and "..": the parent directory
//             continue;

//         std::cout << fileName << std::endl;
//     }

//     FindClose(hFind);
//     return 0;
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// int main(){
//     for(int i = 0; i < 5; i++){

//     }
//     cout << i;
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------

// Including Windows API for getting cwd and opening terminal
// #include<windows.h>
// void openWin() {
//     // Command to open a new Command Prompt window
//     const char* command = "cmd.exe";

//     // Setting up the process information structures
//     STARTUPINFO si = { sizeof(STARTUPINFO) }; // Startup information structure
//     PROCESS_INFORMATION pi = {};             // Process information structure

//     // Create a new process (launch terminal)
//     if (CreateProcess(
//             nullptr,               // Application name (nullptr allows specifying it in `command`)
//             const_cast<char*>(command), // Command line
//             nullptr,               // Process security attributes
//             nullptr,               // Thread security attributes
//             FALSE,                 // Inherit handles
//             0,                     // Creation flags
//             nullptr,               // Environment
//             nullptr,               // Current directory
//             &si,                   // Startup information
//             &pi                    // Process information
//         )) {
//         std::cout << "Terminal opened successfully!" << std::endl;

//         // Close process and thread handles
//         // CloseHandle(pi.hProcess);
//         // CloseHandle(pi.hThread);
//     } else {
//         std::cerr << "Failed to open terminal. Error: " << GetLastError() << std::endl;
//     }
// }

// int main(){
//     openWin();
//     int a;
//     cout << "Enter : ";
//     cin >> a;
// }

// ------------------------------------------------------------------------------------------------------------------------------------------------------
// #include<cstdlib>
// void openWin(string filePath){ 
//     string cmd = "python test.py \"" + filePath + "\"";
//     ifstream test_file(filePath);
//     if(test_file.good()){
//         system(filePath.c_str());
//     }
// }

// int main(){
//     openWin("C:\\Desktop files\\AutoCAD\\Asmt3.pdf");
// }

// -----------------------------VERSION 1.0 ENDS HERE-----------------------------------------------