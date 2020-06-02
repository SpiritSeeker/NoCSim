# NoCSim
A Cycle Accurate Network-on-Chip Simulator

## Building and running
### Linux
Clone the repo and ```cd``` into it.
Generate the Makefiles with
```shell
vendor/bin/premake/Linux/premake5 gmake2
```
Make the project with
```shell
make
```
Run the executable with
```shell
./bin/Debug-linux-x86_64/Sandbox/Sandbox
```

### Windows
  * Clone the repo and open it in file explorer. 
  * Run ```GenerateProjects.bat``` to generate Visual Studio solution files.
  * Open the ```.sln``` in Visual Studio and run the project.
  
_* Edit the ```GenerateProjects.bat``` file to match your version of Visual Studio_  
_* This project is not tested on Windows. Any pull requests are welcome_
