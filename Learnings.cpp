#include<iostream>
#include<string>
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
// Including Windows API for getting cwd and opening terminal COPIED FROM AI
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
#include <cstdlib> // For system()
int main() {
    string command = "start cmd /c \"g++ program.cpp -o program && program\"";
    system(command.c_str());
    return 0;
}