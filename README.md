# Bash and Unit Testing

> Author(s): Brian Crites ([@brrcrites]()), Rachid Ouit

In this lab you will learn the basics of how to use bash (Bourne Again SHell) scripting to automate common tasks and improve your workflow. Bash is a perfect language when you need to automate a small task on the command line and the cost of building the same script in a higher level lanuage is higher than the task itself. While bash is usually used to automate small tasks, there are lots of systems that are built on top of it or use it as part of their running process. These include many of the UNIX commands  you are familiar with as well as many major build and package management systems.

## Basic Shell Script

> Note: Bash will be executable on most UNIX and Mac systems, however does not natively work with Windows. The easiest way to do this lab on a Windows machine is either to ssh into the Hammer server and run it there, or to install the Ubuntu Subsystem for Windows, which is avaialbe in the app store for Windows 10.

First, you should clone this repository and perform the rest of the lab within that clone. This lab will point out good places to commit your changes as an example, however future labs will not have these hints. The TA will grade your last commit to this repository before the deadline.

Were going to start with the basics, creating a hello world bashs script that you can execute on the command line. Start by opening a new `hello.sh` file in your editor of choice and writing the following:

```
#!/bin/sh

echo "hello world"
```

The first line `#!/bin/sh` is used to tell the system that the file we are writing should be an input to another program. The `#!` symbols (knwon as a shebang or hashbang) notes that this program should be used as an executable, and the `/bin/sh` is the executable the rest of the code should be sent to. In this case, it is the path to the bash executable. The rest of the code is the basic [echo](http://www.linfo.org/echo.html) command, which prints the next strip back to standard output.

Now, save the file and try and execute it from the command line:

```
$ ./hello.sh
```

You should get an error like the following, `-bash: ./hello.sh: Permission denied`. This has to do with the permissions that files are given by default in unix environments, and is essentially a security feature to stop you from accidentally executing files. In order to make the file executable, we have to chmod (change mode) the file, where in this case the mode is readable, writing, executable and by who, owner, group, or all. Run an `ls -l` and you should be able to see the current mode for all the files in this directory.

```
$ ls -l
total 16
-rw-r--r--  1 user  staff  2669 Sep 13 12:42 README.md
-rw-r--r--  1 user  staff    30 Sep 13 12:39 hello.sh
```

The left three characters are the owner mode, the middle three are the group mode, and the last three are for everyone who isn't the owner for in the group. You can read more about the nuances of [chmod here](https://ss64.com/bash/chmod.html), but right now we are going to focus on making the file executable. In order to add the executable (`x`) attribute to a file, we can use the `+x` shorthand in the following way:

```
chomd +x hello.sh
```

Now, try executing the file again using `./hell.sh` and you should see `hell world` print out to your console. Congratulations, you've created your first bash script. The most important things to remember from this section are the shebang line that starts your bash script (`#!/bin/sh`) and how to make your script executable (`chomd +x <file>`).

> Make a commit here with the hello.sh file

## Bash Arrays and Loops

Bash can be very useful for testing, because it can easily automate the execution of command line software with different parameters. For example, lets create a new program named `c-echo.cpp` that prints to standard output whatever is passed to it as a command line argument:

```
#include <iostream>

int main(int argv, char** argc) {
    // Skip the first argc index because its the program
    for(int i = 1; i < argv; i++) {
        std::cout << argc[i] << " ";
    }
    std::cout << std::endl;
}
```

Compile this program as `c-echo` (`g++ c-echo.cpp -o c-echo`) and test it with some different inputs to verify that it prints whatever is passed to it as an input parameter. Now, lets create a program named `array.sh` which can automatically run this program with some known inputs to automate it's testing.

```
#!/bin/sh

INPUTS=("first input" "second input" "third input")

./c-echo ${INPUTS[2]}
./c-echo ${INPUTS{1]}
./c-echo ${INPUTS[0]}
```

Lets dig into the top line (after the shebang). Variables are declared the same way in bash as they are in C++ with an equals sign (`=`), and its common to have global variables names written in call capitol latters like in C++. Here we are declaring a bash style array with three values. Note that the array has parentheses (`()`) surrounding all its values, and that the values are seperated by spaces rather than commas. Becuase the values are seperated by spaces and not commas, its common to surround the values in quotes. Without the quotes above the array would have six values instead of three.

When you run this script, you should see that it prints out the inputs (in reverse order) and nothing else. What is happening is that the `INPUT[i]` is being replaced by the i'th indexed array value. The dollar sign and curly bracket syntax (`${INPUTS[i}}`) are used to tell bash that this is a variable and not a string literal. All variables that you use in your bash should be surrounded by the dollar sign and curly brackets (`${VAR}`). So the following lines

```
./c-echo ${INPUTS[2]}
./c-echo ${INPUTS{1]}
./c-echo ${INPUTS[0]}
```

Are replaced instead with the values from the array, and the following is executed instead

```
./c-echo third input
./c-echo second input
./c-echo first input
```

Because this will simply execute the code, it is often common to have the system echo out what it is going to run before running it. This makes it easier for the user of the script to understand what is going on and what they should expect to be output. Update your script to the following:

```
#!/bin/sh

INPUTS=("first input" "second input" "third input")

echo "Executing ./c-echo third input"
./c-echo ${INPUTS[2]}
echo "Executing ./c-echo second input"
./c-echo ${INPUTS{1]}
echo "Executing ./c-echo first input"
./c-echo ${INPUTS[0]}
```

> Make a commit here with the c-echo.cpp and array.sh files

Obviously if we have a large array, or multiple arrays where we want to iterate to run all combinations, then hand coding the combinations is less than desirable. Luckily bash supports various types of loops including iteration loops. Lets try and replace our hard coded execution lines with a loop instead. Update your array.sh file with the following:

```
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    ./c-echo ${input}
done
```

Make sure to take careful note of the quotes around the inputs array (`"${INPUTS[@]}"`), and lets take a closer look at that line. The line is structured as `for x in y` where `x` is the variable that `y` will be unpacked into. In the case of bash for loops it supports in-line lists, so if you put a single value for `y` it will do a single iteration replaced the variable `x` with `y`. Alternatively you could have put multiple values seperated by spaces in place of the `y` and `x` would iterate over all of them. We've already discussed that we need the dollar sign and curly braces (`${}`) to tell bash that this is a variable and not a literal, but lets look at the index of operator with ampersand (`[@]`). This expands the array inputs into its consituent parts, and without it the for loop would only iterate over the first element in the array. 

The last thing we need to consider is why we need the extra quotes around the `inputs` variable, which has to do with the way shell replaces and parses values. When bash sees the variable symbols (`${}`) it replaces that variable with the value, which in the case of the first iteration would be `first input`. The problem we now have is with the for loop, since this type of loop allows for a list of comma seperated values to be put in-line when the variable is replaced with two different values it will try and iterate over them seperatly and each word in the array will be run seperatly. When we add the quotes the loop then sees these two words as a single entry (which is what we want) and will execute it correctly. These little details can make bash a bit difficult to work with at first, but will become more natrual the more you work with it (and Stack Overflow is your friend).

As for the loop itself, it starts with the `for` keyword, but must be followed with a `do` keyword on the next line (or seperated from the `for` line with a semicolon (`;`), which represents a newline. Everything after the `do` keyword makes up the loop body, and will be executed each iteration, until we reach the `done` keyword, which represents the end of the loop body.

Loop iterations are not only useful for user defined arrays, but are also useful for iterating over data that bash interprets as array. For instnace, you can easily iterate over a directory of files like you would when you need to process multiple files through a program and didn't want to do it one file at a time. Create a new file, `list.sh`, with the following code:

```
for file in ./*
do
    echo $(basename "$file")
done
```

Here, the `./*` piece of the for loop returns all the files (using the wildcard character `*`) at the directory path `./` which is the local directory. The `$(basename "$file")` calls the [basename command](http://pubs.opengroup.org/onlinepubs/007908799/xcu/basename.html) within bash, replace the input to the command with the iteration variable. The basename command strips out the path from a file path leaving only the file name.

> Make a commit here with the list.sh file

## Bash If and Else

Loops make it easy for us to iterate over a set of files to bulk process data or to run a number of different inputs through a program, but we'll need conditionals if we want to validate output or run only a subset of files from a directory for process. Lets open our `array.sh` file and update it to make sure that the output of our program matches what we expect.

```
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
```

The first thing we do differently here is we run the command using the bash command syntax that we used when we ran the basename command earlier. This executes the command and saves the result to the variable `output`. Next, we have our if statement which starts with the `if` keyword and then has a condition to evaluate within square brackets (`[]`). The square brakcets are actually a shorthand for a conditional test in bash, and will always return a true or false value (which is very convenient when working with if/else). Next we have the `then` keyword, which like `do` in the loop represents the start of the loop body. We then have what we want the condition to execute if the condition is met, follow by and `else` keyword and what we want the condition to execute if its false. Finally, the entire condition body is ended with the `fi` keyword (`if` backwards) in the same way that `done` ends the loop body.

Now, lets run this code and take a look at the output. You should see something like the following:

```
./c-echo first input
Test failed
./c-echo second input
Test failed
./c-echo third input
Test failed
```

Looks like our outputs didn't match out inputs, why could that be? Lets take a closer look at the output we get and what we compare it to and see if we can find the issue. Rewrite the `array.sh` script to print both values **surrounded by string literals**.

```
#!/bin/sh

INPUTS=("first input" "second input" "third input")

for input in "${INPUTS[@]}"
do
    echo "./c-echo ${input}"
    output=$(./c-echo ${input})
    echo "Output: \"${output}\""
    echo "Input: \"${input}\""
    if [ "${output}" = "${input}" ]
    then
        echo "Test passed"
    else
        echo "Test failed"
    fi
done
```

Run the updated test code and the issue should be fairly obvious. Out c-echo program prints a space after every word in `argc`, leading to a traiing whitespace that doesn't exist in the input. Lets go ahead and update the c-echo program so that we skip printing the trailing whitespace.

```
#include <iostream>

int main(int argv, char** argc) {
    // Skip the first argc index because its the program
    for(int i = 1; i < argv; i++) {
        std::cout << argc[i];
        // Print a whitespace after all but the last iteration
        if(i < argv - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
```

Now, re-compile the program (remember to use `g++ c-echo.cpp -o c-echo` so it generates the correct executable) and re-run your `assay.sh` test script. It should now say that all the tests have been passed.

> Make a commit here with the assay.sh and c-echo.cpp files

There are lots of different ways you can generate useful conditions within bash, especially when also using other bash commands. We are only covering the most basic version here, but we encourage you to explore more conditions on your own as the need arises.

## Bash Parameters

