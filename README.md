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

## Bash Arrays and Loops

Bash can be very useful for testing, because it can easily automate the execution of command line software with different parameters. For example, lets create a new program that print to standard output whatever is passed to it as a command line argument:

```
```

## Bash Parameters

## Bash If and Else
