To try out the kernel use the following commands: (make sure that qemu is installed)

> svn checkout https://osgrub.googlecode.com/svn/trunk osgrub

> cd osgrub

> make

> ./qemu.sh

An console opens. You will get an overview over the available commands with

> help

If you type "multitask" the kernel will start two concurrent processes. You can access the console parrallel to that.