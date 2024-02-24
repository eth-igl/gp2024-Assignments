# Shape Modeling and Geometry Processing - Course Assignments 2024

## Student data

Name: 'Your real name'  
Legi-Nr: 'Your legi number'

Email: 'Your email address'

Carefully follow the instructions below to setup your assignment repository.

## General Rules and Instructions

### Plagiarism Note and Late Policy
Copying code (either from other students or from external sources) is strictly prohibited! We will be using automatic anti-plagiarism tools, and any violation of this rule will lead to expulsion from the class. Late submissions will generally not be accepted. In case of serious illness or emergency, please send an e-mail to <igl.lectures@inf.ethz.ch> and provide a relevant medical certificate.

### Publishing Code on Personal Git Repositories
We explicitly ask you to not create any public repositories containing copies of these assignments or solutions to them. In any case do not include any terms that are identifiably related to this course and make the repository easily searchable. 

### Provided Libraries
For each assignment, you will use the geometry processing library [libigl](https://github.com/libigl/libigl), which includes implementations of many of the algorithms presented in class. The libigl library includes a set of tutorials, an introduction which can be found [online](https://libigl.github.io/tutorial/). You are advised to look over the relevant tutorials before starting the implementation for the assignments; you are also encouraged to examine the source code of all the library functions that you use in your code to see how they were implemented. libigl relies on its header files for documentation on how to use the functions, so make sure to read those. To simplify compilation, we will use libigl as a header-only library (note that, if you prefer, you can compile it into a set of static libraries for faster builds at your own risk (this can be brittle on some platforms). All the library dependencies of the assignments (e.g. libigl, Eigen, imgui) will be downloaded automatically when the project is configured (via cmake). No libraries apart from those are permitted unless explicitly stated otherwise.

### Installing Git and CMAKE
Before we can begin, you must have Git running, a distributed revision control system which you need to handin your assignments as well as keeping track of your code changes. We refer you to the online [Pro Git book](https://git-scm.com/book/en/v2) for more information. There you will also find [instructions](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git]) on how to to install it. On Windows we suggest using [git for windows](https://git-for-windows.github.io/).

CMake is the system libigl uses for cross-platform builds. If you are using Linux or macOS, we recommend installing it with a package manager instead of the CMake download page. E.g. on Debian/Ubuntu:
```
sudo apt-get install cmake
```
or with MacPorts on macOS:
```
sudo port install cmake.
```
On Windows, please refer to [Building Each Assignment (on Windows)](#building-each-assignment-on-windows) for instructions on how to build the assignments.

### Cloning the Assignment Repository
Before you are able to clone your private assignment repository, you need to have an active [Github](https://github.com/) account. Then you can **create your own private online repository** by following [this link](https://classroom.github.com/a/k4xXrE-b). 

Note that GitHub deprecated the password authentication method for Git. We recommend using a [personal access token](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/creating-a-personal-access-token) or [SSH](https://docs.github.com/en/github/authenticating-to-github/connecting-to-github-with-ssh) to authenticate with GitHub when using Git on the command line.

In the next step you need to clone it to your local harddrive if you are using a personal access token:
```bash
git clone --recursive https://github.com/eth-igl/gp24-'Your_Git_Username'.git
```
or if you are using SSH:
```bash
git clone --recursive git@github.com:eth-igl/gp24-'Your_Git_Username'.git
```
'Your_Git_Username' needs to be replaced accordingly. This can take a moment.

Next, cd into the newly created folder, and add the base assignment repository as a remote:
```bash
# If you are using personal access token
cd gp24-'Your_Git_Username'
git remote add base https://github.com/eth-igl/gp2024-Assignments.git
git pull base main --allow-unrelated-histories
```

```bash
# If you are using SSH
cd gp24-'Your_Git_Username'
git remote add base git@github.com:eth-igl/gp2024-Assignments.git
git pull base main --allow-unrelated-histories
```
Now you should have your local clone of the assignment repository ready. Have a look at the new repository folder and open the 'README.md'. It contains the text you are just reading. Please fill in your name and student number at the top of this file and save. Then you need to stage and commit this changed file:
```bash
git add README.md
git commit -m "Adjust README.md"
git push
```
You should now be able to see your name online on your private repository: https://github.com/eth-igl/gp24-'Your_Git_Username'

In the assignment repository, you will find the different assignment directories 'assignmentX'. For now you only see the first one 'assignment1'. To compile the assignment code we will use the CMake building system.

### Building Each Assignment (on Mac/Linux)

Here are the instructions to build with command line tools:

- Create a `build` directory in the assignment directory, e.g.:
    ```bash
    cd assignment1; mkdir build
    ```
- Use CMake to generate the Makefiles needed for compilation inside the `build` directory:
    ```bash
    cd build; cmake -DCMAKE_BUILD_TYPE=Release ..
    ```

- Compile and run the executable, e.g.:
    ```bash
    make -j && ./assignment1 <some mesh file>
    ```

Alternatively, you may use your favorite IDE that supports CMake.

Please compile your final code in Release mode for optimal speed, and use Debug mode to debug your code.

If you encounter any problems, please use [github issues](#using-github-issues-for-discussion) or ask the assistants during the exercise session.

### Building Each Assignment (on Windows)

Building on Windows is not recommended as the environment setup is not optimized for command line tools. Here is one possible solution that provides a Unix-like environment on Windows:

- Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) and make sure to select the "Desktop development with C++" workload.

- Find `x64 Native Tools Command Prompt for VS 2022` in the start menu and open it.

- Use the following commands to create the `build` directory and set up the Makefile:

    ```powershell
    cd assignment1
    mkdir build
    cd build
    cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
    ```

- Use the following commands to compile and run the executable:

    ```powershell
    nmake
    .\assignment1.exe <some mesh file>
    ```

Alternatively, you may use your favorite IDE that supports CMake.

Please compile your final code in Release mode for optimal speed, and use Debug mode to debug your code.

If you encounter any problems, please use [github issues](#using-github-issues-for-discussion) or ask the assistants during the exercise session.

### Workflow
In general, you should use git to commit your edits as often as possible. This will help you with backtracking bugs and also serve as a backup mechanism. For more information we refer you to the [Pro Git book](https://git-scm.com/book/en/v2/Git-Basics-Recording-Changes-to-the-Repository).

Every new assignment needs to be pulled from the base repository:
```bash
git pull base main
```
or,
```bash
git pull base main --allow-unrelated-histories
```

#### Viewer_proxy files
To reduce compilation times we have create a proxy file for the libigl Viewer that encapsulates viewer-related function calls. You should be able to use viewer-related functions exactly as they appear in the libigl tutorials. If this does not work, please double check that there is a proxy for the function that you are trying to use in the viewer_proxy.cpp file. If there isn't, please add it yourself following the style for pre-existing functions. Try to avoid frequent updates to the two viewer_proxy files, as these will trigger long compilation times.

### Solution Submission
To submit your solution of the assignment (code) please add the following commit message: "Solution assignment X". E.g:
```bash
git commit -m "Solution assignment X"
git push
```
You can keep updating your code before the deadline. After the deadline, please don't change the code of that assignment before we send you the scores.

### Using github issues for discussion 
Please use the [github issues](https://github.com/eth-igl/gp2024-Assignments/issues) to post your questions and discussions about the assignments. Note that the issue created under your own repository will *not* be visible to others, so please use the provided link for that. 

While we aim to answer as quickly as possible, we cannot always guarantee this and we thus advise you to not wait till the last minute. All students are encouraged to answer questions of their fellows as well. Please make sure your question is not a duplicate before submitting it and tag it with the corresponding label.


**The solutions must be submitted before the deadlines mentioned in the assignment sheet and on the course website (we will check the git commit timestamp). Late submissions will not be accepted.**
