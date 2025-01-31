import subprocess

cpp_file = "file_system.cpp"
exe_file = "file_system.exe" 
delay = 2 # time delay to close terminal after a delay after the execution stops

compile_command = f"g++ {cpp_file} -o {exe_file}"

run_command = f'start cmd /c "{exe_file} & timeout {delay}"' # this opens the terminal (/c closes the terminal when execution stops whereas /k keeps running the terminal)

subprocess.run(compile_command, shell=True)  # this is to compile
subprocess.run(run_command, shell=True)     # this is to run    