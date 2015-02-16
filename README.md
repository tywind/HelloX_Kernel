HelloX operating system is a open source project dedicated to M2M(or IoT,Internet of Things) application,it include a compact kernel,some auxillary applications and development environment.
Any one can contribute it,and any contribution will be recorded in authors.txt file under the same directory as README file.

Here is the steps to run HelloX kernel in Virtual Machines(Such as Virtual PC,Virtual BOX,VMWare Workstation,etc):
1. Download the whole repository and build it with Microsoft Visual Studio 2010,adaptation maybe required if you use other development environment;
2. Use Release Version(Select Build->Batch Build...->Tick on Win32 Release option->Click Rebuild All button),debug version will not work;
3. Master.dll will be generated into /Release directory;
4. Copy the Master.dll file into /bin directory,overwrite the old one if exist;
5. Run Batch.bat in /bin directory,a new virtual floppy image named vfloppy.vfd will appear;
6. Use this vfloppy.vfd to boot virtual machina,it should work if no exception;
7. Type 'help' to get help information under the command line UI of HelloX.

NOTE:PLEASE DO NOT DELETE ANY FILE UNDER BIN DIRECTORY.

Here is the include directory configuration for your IDE:
1. Set the following directories as include directory:
   a) /lib
   b) /include
   c) /shell
   d) /network
   e) /network
   f) /include/lwip
2. Delete the default include directory set by your IDE,since it may conflict with source files under /lib.

Wish you good luck!:-),please contact garryxin@gmail.com or QQ/WeChat:89007638 for assistance.

