You can install the plugin in your home directory.

Currently, there is no 'visit' module, and I think that is because you should only use it in client-server mode.  But we need the xml stuff to compile the plugins.

VisIt 3.1.4 was compiled with gcc/9.2.0.  First, load those modules.
```
module load gcc/9.2.0
module load openmpi/3.1.6
```

Here is my modulefile for VisIt 3.1.4.
```
#%Module
prepend-path PATH {/cm/shared/apps/vis/visit/3.1.4/gcc/9.2.0/openmpi/3.1.6/3.1.4/linux-x86_64/bin};
```

And I have this in my .bashrc:
```
module use --append /home/llowe/modulefiles
```

So now:
```
module load visit
```

And then follow the instructions at [install-ubuntu20-visit3.1.4](install-ubuntu20-visit3.1.4.md).
