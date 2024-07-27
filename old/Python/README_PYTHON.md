# Python Setup

Assumption: Python is already installed and on your PATH.

When you install a package for Python, by default it is added to your global environment. It is good practice to create your Python projects in virtual environments instead, to decouple your (global) Python install from associated pip packages. This will allow you to not only keep track of the dependencies necessary for your project and prevent package collision errors, but also minimize headaches trying to get your projects to run on other devices.

Create a virtual environment for your Python project in VS Code:

* Open the command palette (Ctrl+Shift+P)
* Python: Create environment

In the bottom right you'll see the virtual environment you're in, and can easily switch back to another environment you have created, or the global environment. The nice thing about doing this in VSCode is that it will automatically search for "requirements.txt" and install the listed dependencies.

Create a virtual environment for your Python project outside of VSCode (using Git Bash):

```
cd /path/to/project
python -m venv .venv
source activate
```

If using PowerShell or cmd, the last line should be:

```.venv\Scripts\activate.bat```

You can verify that you're in the virtual environment by your terminal outputs ending with ```(.venv)```. Exit the virtual environment at any time with ```deactivate```.

To quickly go to your virtual environment (assumes it's named .venv and in the current directory), enter this command from your Bash terminal: ```source "$(dirname "$BASH_SOURCE")/.venv/Scripts/activate" && source activate```. Then to launch your program in the environment, do ```python your_script.py```

## Build with your IDE

In both VSCode and VS2022, it's as simple as hitting the "Play" icon and you're ready to go.

Since Python is interpreted it does not offer preprocessor conveniences as found in C++. However, you can still (sort of) simulate something like "#ifdef DEBUG" by having a variable in a convenient place (such as the top of your ```__init__.py```). Set it to true for thing you only want to check/print in a "Debug" build, and false otherwise. Not sure on how much overhead this realistically adds to a script, but since it's not automatically excluded before runtime, it's something to keep in mind.

### Including Additional Local Files

To include other .py files from the same directory as the current file:

```from file-in-same-directory import *```

To include other .py files from a subfolder of the current directory:

```from folder.file-name import *```

The ```*``` can and should be replaced with specific functions when possible.

### Including External libraries

In short: you shouldn't unless you have to. 

You can easily get a list of packages installed in your environment (virtual or otherwise), which should be dependencies of your project. You can quickly generate a list of these packages with the following command: ```pip freeze > requirements.txt```. 