# Programming Wiki

This repository is meant as a catalog/reference for various aspects of different programming languages, syntax, type systems, compilation, build systems, and performing common tasks (setting up/using relevant libraries when applicable).

Written from the perspective of a new college graduate. Trying to lean more towards practical over theoretical.

Jump to any language's README:  
[--> C](C/README_C.md)
[--> Haskell](Haskell/README_Haskell.md)

## Topics

<table style="width: 100%;">
  <tr>
    <td style="width: 50%; vertical-align: top;">
      <strong>Operators</strong>
      <ul>
        <li>Numerical operators (+ - * / % sqrt **)</li>
        <li>Increment/decrement (++ --)</li>
        <li>Bitwise operators (& | ~ !)</li>
        <li>Compound operators</li>
        <li>Logical operators (&gt; &lt; ==)</li>
        <li>Operator associativity & precedence</li>
      </ul>
    </td>
    <td style="width: 50%; vertical-align: top;">
      <strong>Type system</strong>
      <ul>
        <li>Numeric types</li>
        <li>Aggregate types</li>
        <li>Type qualifiers</li>
        <li>Storage-class specifiers</li>
        <li>Pointers, references</li>
        <li>Type conversion & casting</li>
        <li>Copying/cloning</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td style="width: 50%; vertical-align: top;">
      <strong>Conditionals</strong>
      <ul>
        <li>Definition of true/false</li>
        <li>Selection statements</li>
        <li>Iteration statements</li>
        <li>Jump statements</li>
      </ul>
    </td>
    <td style="width: 50%; vertical-align: top;">
      <strong>Data Structures</strong>
      <ul>
        <li>Iterate over iterable type</li>
        <li>Dictionaries/Maps, Sets, Tuples</li>
        <li>Arrays/vectors, linked lists</li>
        <li>Multidimensional arrays</li>
        <li>Hash tables</li>
        <li>Stacks, queues, deques</li>
        <li>Graphs, Trees</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td style="width: 50%; vertical-align: top;">
      <strong>Strings/Files</strong>
      <ul>
         <li>Strings (print/format, concat, case, sort, split)</li>
         <li>Write to/read from the console, file, binary file</li>
         <li>Traverse the file system</li>
         <li>Parse JSON, XML, CSV</li>
         <li>Regular expressions</li>
         <li>Built-in/common logging techniques</li>
         <li>Date & time recording, manipulation, formatting</li>
      </ul>
    </td>
    <td style="width: 50%; vertical-align: top;">
      <strong>Functions, Objects, Memory</strong>
      <ul>
         <li>Passing & returning semantics</li>
         <li>Error handling (try-catch, return values)</li>
         <li>Abstract classes</li>
         <li>Inheritance and polymorphism</li>
         <li>Access specifiers and visibility</li>
         <li>Keywords otherwise not covered</li>
         <li>Operator overloading</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td style="width: 50%; vertical-align: top;">
      <strong>Multithreading</strong>
      <ul>
         <li>Threading/multiprocessing syntax</li>
         <li>Conditions, mutexes, synchronization</li>
      </ul>
    </td>
    <td style="width: 50%; vertical-align: top;">
      <strong>Networking</strong>
      <ul>
         <li>Send HTTP requests, handle responses</li>
         <li>Basic Socket programming</li>
      </ul>
    </td>
  </tr>
</table>

<strong>Language External</strong>
<ul>
   <li>Language description</li>
   <li>Creating a Binary</li>
   <li>Build systems</li>
   <li>External Libraries</li>
   <li>Using the Debugger</li>
   <li>Virtual environments</li>
</ul>


## Recommended Applications
1. [Git](https://github.com/git-guides/install-git). Download code repositories, and version control your projects. Comes with git bash (Windows).
2. [Visual Studio Code](https://code.visualstudio.com/). Snappy code editor. Can be molded into somewhat of an IDE for a number of languages. Git integration and search capabilities are excellent. 
   - [Code - OSS](https://github.com/microsoft/vscode) if on Linux and your package manager's only option is a Flatpak.
3. [Visual Studio](https://visualstudio.microsoft.com/vs/) (Windows only). Top tier support for C++, C#, .NET. Integrated profiler. Built-in debugger works on *any* Windows executable<sup>†</sup>; .NET UI designer tools.

<sup>† Seriously!</sup>

## VS/Code Setup

Language-specific setup for VS/Code in [VSCODE.md](VSCODE.md).

## Language Essentials

Language-specific tools, rationale, links found in [TOOLS.md](TOOLS.md).

## Plans

In no particular order.

**C and C++** - widely influential powerhouses that are still useful today; good foundations

**Python** - dynamic types, popular and useful for scripting and data science

**Ruby** - dynamic types, opinionated; most especially for comparison with Python 

**Lua** - dynamic types, lightweight, fast, simple to embed in other applications

**HTML/CSS** - not languages; but the basics are important for...

**JavaScript/TypeScript** - vanilla-focused; it's ubiquitous and I don't know it well

**Go** - see what the fuss is about, high praise for its networking capabilities

**Haskell** - functional programming paradigm

**Rust** - functional influence and memory safety

**C#** - just want to learn more. Popular.