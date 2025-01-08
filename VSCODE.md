# VS/Code Setup

## Global

Change Terminal to Bash:

| VSCode                                                             | VS2022 (Windows only)                                                             |
| ------------------------------------------------------------------ | --------------------------------------------------------------------------------- |
| Command Palette (Ctrl+Shift+P)<br>Terminal: Select Default Profile | Tools -> Options -> Environment -> Terminal -> Add;<br>Arguments: `--login -i -l` |

## C/C++

**Extensions**:
* [C/C++ by Microsoft](vscode:extension/ms-vscode.cpptools)

Generate a default `c_cpp_properties.json` by opening the command palette (`Ctrl+Shift+P`) and searching C/C++: Edit Configurations (UI). It will appear in `${workspaceFolder}/.vscode`.

It will try to find your compiler (`compilerPath`), set the `c/cpp` standards, and set the `includePath` to include all files in your workspace. They may not be properly detected; check the dropdown menu for compilerPath if it appears, otherwise make some manual adjustments.

The [official documentation](https://code.visualstudio.com/docs/languages/cpp) has additional setup and usage details.

### Windows

The extension first searches for the Visual Studio compiler `cl`, and it should automatically find the necessary header files. If it's not detected you may need to add it yourself:

```JSON
"compilerPath": "C:/Program Files (x86)/Microsoft Visual Studio/{year}/BuildTools/VC/Tools/MSVC/{14.xx}/bin/Hostx64/x64/cl.exe",
```

If you are instead using MinGW-w64, it might look something like this:

```JSON
"compilerPath": "C:/MinGW-w64/mingw64/bin/gcc.exe",
```

### Linux

Compiler path should be detected automatically. Make adjustments if using a non-standard location for your compiler.

## Haskell

Install the Haskell extension, it will ask you to install GHCup (recommended). Follow the instructions [here](https://www.haskell.org/ghcup/). We will want to add `~/.ghcup` to `PATH` (Linux).

The build system/package manager being used is called Stack. Add your basic information to Stack's global config file at `~/.stack/config.yaml`. For simple projects that won't have a `README` or `LICENSE` etc make sure those files aren't referenced in the `<projectName>.cabal` file or the build will fail.

Create a project: `stack new <projectName> <template>`
e.g. `stack new aHelloWorld simple`

Build a project: `cd dir/with/project.cabal`  ;   `stack build --copy-bins`

