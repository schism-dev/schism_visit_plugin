# Installing on mac studio

Installing on my mac.

Using VisIt 3.1.4, to use client-server mode from Expanse.

Download CMake for mac, drag it into the applications bin.  Open CMake, in the top menu bar, click Tools, 
choose How to Install For Command Line Use.  I chose this way:
```
sudo "/Applications/CMake.app/Contents/bin/cmake-gui" --install
```


Get the plugin code:
```
git clone https://github.com/schism-dev/schism_visit_plugin.git
cd schism_visit_plugin
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

Make a build directory:
```
mkdir build
cd build
```

Use `cmake` to create the `make` system.  My mac is arm but the executable for VisIt 3.1.4 is x86_64, so the next command tells it to target x86.
```
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_OSX_ARCHITECTURES=x86_64 ..
```

Run `make` to build plugins binary. 
```
make
```

Now I get a bunch of errors because of `malloc.h`.  Searching on the internets, I find [this possible solution](https://github.com/RIOT-OS/RIOT/issues/2361).
So for every subroutine where there is `malloc.h`, do this:
```
#if defined(__MACH__)
#include <stdlib.h>
#else
#include <malloc.h>
#endif
```

My VisIt is here:
```
/Applications/VisIt.app/Contents/Resources/bin/VisIt
```


There should be four new files in ~/.visit/3.1.4/darwin-x86_64/plugins/databases:
```
libESCHISMDatabase_par.so
libESCHISMDatabase_ser.so
libISCHISMDatabase_par.so
libMSCHISMDatabase_par.so
```


Repeat the steps for the other plugins:
```
cd ~/schism_visit_plugin/prop
cp avtpropFileFormat.C ~
cp avtpropFileFormat.h ~
xml2plugin -clobber prop.xml
cp ~/avtpropFileFormat.C .
cp ~/avtpropFileFormat.h .
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_OSX_ARCHITECTURES=x86_64 ..
make
ls ~/.visit/3.1.4/darwin-x86_64/plugins/databases
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
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_OSX_ARCHITECTURES=x86_64 ..
make
ls ~/.visit/3.1.4/darwin-x86_64/plugins/databases
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
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_OSX_ARCHITECTURES=x86_64 ..
make
```
Error.  
So, this is where we hack the makefiles, as per Eric's email (see below).  Also, there are more malloc.h to fix.

For this error:
```
/Users/lllowe/schism_visit_plugin/mdschism/avtMDSCHISMFileFormatImpl.C:42:10: fatal error: 'malloc.h' file not found
#include <malloc.h>
```
Open the C file for the error, e.g., above is, from the build directory:
```
vi ../avtMDSCHISMFileFormatImpl.C
```
Then replace
```
#include <malloc.h>
```
with
```
#if defined(__MACH__)
#include <stdlib.h>
#else
#include <malloc.h>
#endif
```

These were the files:
```
(base) lllowe@LisasMacStudio schism_visit_plugin % grep malloc.h */*
mdschism/avtMDSCHISMFileFormatImpl.C
unstructure_data/avtSCHISMFileFormat.C
unstructure_data/avtSCHISMFileFormatImpl.C
unstructure_data/avtSCHISMFileFormatImpl10.C
unstructure_data/avtSCHISMFileFormatImpl11.C
```


And here you go:
```
exouser@visit-plugin-for-schism:~/schism_visit_plugin/mdschism$ ls ~/.visit/3.1.4/linux-x86_64/plugins/databases
libEMDSCHISMDatabase_par.so  libEpropDatabase_par.so  libMMDSCHISMDatabase.so
libEMDSCHISMDatabase_ser.so  libEpropDatabase_ser.so  libMSCHISMDatabase.so
libESCHISMDatabase_par.so    libIMDSCHISMDatabase.so  libMgr3Database.so
libESCHISMDatabase_ser.so    libISCHISMDatabase.so    libMpropDatabase.so
libEgr3Database_par.so	     libIgr3Database.so
libEgr3Database_ser.so	     libIpropDatabase.so
```

*from Eric*

Remove references to libraries in the CXX_FLAGS in schism_visit_plugin/mdschism/build/CMakeFiles/*.dir/flags.make

For example:
```
CXX_FLAGSx86_64 = -O3 -DNDEBUG -std=gnu++11 -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.1.sdk -fPIC   -std=c++0x libnetcdf_c++.dylib libnetcdf.dylib libhdf5_hl.dylib libhdf5.dylib libsz.dylib libz.dylib

CXX_FLAGS = -O3 -DNDEBUG -std=gnu++11 -arch x86_64 -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.1.sdk -fPIC   -std=c++0x libnetcdf_c++.dylib libnetcdf.dylib libhdf5_hl.dylib libhdf5.dylib libsz.dylib libz.dylib
```
i.e. we removed this part of CXX_FLAGS:

libnetcdf_c++.a libnetcdf.a libhdf5_hl.so libhdf5.so libsz.so libz.so


Now try it out.  Links to data are on the [SCHISM visualization page](https://schism-dev.github.io/schism/master/getting-started/visualization.html)

```
wget -r -nH --cut-dirs=2 -np -R "index.html*" http://ccrm.vims.edu/yinglong/SVN_large_files/Scribe_IO_outputs/
wget -r -nH --cut-dirs=2 -np -R "index.html*" http://ccrm.vims.edu/yinglong/SVN_large_files/SCHISM_v5.6.1_sample_outputs/
```
