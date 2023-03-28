Install VisIt on a Jetstream2 instance.  Assuming you have an account on Jetstream2:
- Go to the Project page
- Click Create, choose Instance
- Choose Ubuntu 20.04, to be compatible with an older version of VisIt

Create instance:
- Name: try-visit
- m3.medium
- Keep default 60GB
- 1 instance
- Yes, Enable web desktop
- Create

Click visit-plugin-for-schism, then Connect to Web Desktop.  Click the terminal icon. 

See the VisIt User Guide, [Installing and Starting VisIt](https://visit-sphinx-github-user-manual.readthedocs.io/en/develop/getting_started/Installing_VisIt.html)

We will use VisIt version [3.1.4](https://visit-dav.github.io/visit-website/releases-as-tables/#series-31) so we can use server mode on Expanse.  Get the source code and the install script.
```
wget https://github.com/visit-dav/visit/releases/download/v3.1.4/visit3_1_4.linux-x86_64-ubuntu20.tar.gz
wget https://github.com/visit-dav/visit/releases/download/v3.1.4/visit-install3_1_4
```
Change to executable mode
```
chmod +x visit-install3_1_4
```
For the following, we install visit in the home directory to avoid using sudo.  Choose '1', no specific configuration.
```
./visit-install3_1_4 3.1.4 linux-x86_64-ubuntu20 ~/visit
1
```
Set the path for the executable
```
export PATH=~/visit/bin:$PATH
```
Get a sample FVCOM file from OSN:
```
wget https://renc.osn.xsede.org/ees210015-bucket01/FVCOM/mi_gem_archive/042020161/mi_0001.nc
```

Try VisIt, open the FVCOM file, take a look:
```
visit
```
It works.

Now try the steps to install the plugin.

Get the plugin code:
```
git clone https://github.com/schism-dev/schism_visit_plugin.git
cd schism_visit_plugin
```

Before starting:

Stop it from using Ubuntu compiler:
```
alias c++='g++'
alias cc='gcc'
```

Set library and include paths
```
export LIB=~/visit/3.1.4/linux-x86_64/lib
export LIBRARY_PATH=~/visit/3.1.4/linux-x86_64/lib
export LD_LIBRARY_PATH=~/visit/3.1.4/linux-x86_64/lib
export INCLUDE=~/visit/3.1.4/linux-x86_64/include
export C_INCLUDE_PATH=~/visit/3.1.4/linux-x86_64/include
export CPLUS_INCLUDE_PATH=~/visit/3.1.4/linux-x86_64/include
```

Install the unstructure_data plugin:
```
cd unstructure_data
```
Save a copy of the main VisIt plugin class files to your home directory. These files will be overwritten in the next step by VisIt's code skeleton generating tool.
```
cp avtSCHISMFileFormat.C ~
cp avtSCHISMFileFormat.h ~
```
The command `xml2plugin` is a VisIt command.
```
xml2plugin -clobber SCHISMOutput.xml
```
SCHISMOutput.xml is the file used by VisIt code generating tool to create code skeleton and makelist file.

Use two backup plugin class file to overwrite the files avtSCHISMFileFormat.C and avtSCHISMFileFormat.h.
```
cp ~/avtSCHISMFileFormat.C .
cp ~/avtSCHISMFileFormat.h .
```

Use `cmake` to create the `make` system.
```
cmake -DCMAKE_BUILD_TYPE:STRING=Release
```

Run `make` to build plugins binary. 
```
make
```

There should be four new files in ~/.visit/3.1.4/linux-x86_64/plugins/databases:
```
libESCHISMDatabase_par.so
libESCHISMDatabase_ser.so
libISCHISMDatabase_par.so
libMSCHISMDatabase_par.so
```
So far, so good.

Repeat the steps for the other plugins:
```
cd ~/schism_visit_plugin/prop
cp avtpropFileFormat.C ~
cp avtpropFileFormat.h ~
xml2plugin -clobber prop.xml
cp ~/avtpropFileFormat.C .
cp ~/avtpropFileFormat.h .
cmake -DCMAKE_BUILD_TYPE:STRING=Release
make
ls ~/.visit/3.1.4/linux-x86_64/plugins/databases
```
Works.

And
```
cd ~/schism_visit_plugin/gr3
cp avtgr3FileFormat.C ~
cp avtgr3FileFormat.h ~
xml2plugin -clobber gr3.xml
cp ~/avtgr3FileFormat.C .
cp ~/avtgr3FileFormat.h .
cmake -DCMAKE_BUILD_TYPE:STRING=Release
make
ls ~/.visit/3.1.4/linux-x86_64/plugins/databases
```
Works.

And
```
cd ~/schism_visit_plugin/mdschism
cp avtMDSCHISMFileFormat.C ~
cp avtMDSCHISMFileFormat.h ~
xml2plugin -clobber mdschism.xml
cp ~/avtMDSCHISMFileFormat.C .
cp ~/avtMDSCHISMFileFormat.h .
cmake -DCMAKE_BUILD_TYPE:STRING=Release
make
```
Error.
```
exouser@try-visit:~/schism_visit_plugin/mdschism$ make
Scanning dependencies of target EMDSCHISMDatabase_par
[  2%] Building CXX object CMakeFiles/EMDSCHISMDatabase_par.dir/MDSCHISMEnginePluginInfo.C.o
c++: error: libnetcdf_c++.a: No such file or directory
c++: error: libnetcdf.a: No such file or directory
c++: error: libhdf5_hl.so: No such file or directory
c++: error: libhdf5.so: No such file or directory
c++: error: libsz.so: No such file or directory
c++: error: libz.so: No such file or directory
make[2]: *** [CMakeFiles/EMDSCHISMDatabase_par.dir/build.make:63: CMakeFiles/EMDSCHISMDatabase_par.dir/MDSCHISMEnginePluginInfo.C.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:82: CMakeFiles/EMDSCHISMDatabase_par.dir/all] Error 2
make: *** [Makefile:84: all] Error 2
```

I set the library path to
```
~/visit/3.1.4/linux-x86_64/lib
```

Then check if libraries are there by...
```
exouser@try-visit:~/schism_visit_plugin/mdschism$ grep libsz.so ~/visit/3.1.4/linux-x86_64/lib/*
```
And found all libraries except the netCDFs.  There are netCDF include files here:
```
~/visit/3.1.4/linux-x86_64/include/netcdf/include/
```
Since it can't even find libz.so, I suspect that doesn't matter.

Try the makefile hack?
