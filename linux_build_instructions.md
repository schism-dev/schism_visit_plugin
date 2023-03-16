Note: command xml2plugin in step 3 is a VisIt command.
1. Navigate to a database type folder, for instance ./unstructure_data.
2. Backup two main VisIt plugin class files, they are named as avt***FileFormat.C and avt***FileFormat.h. 
   Those two files will be overwrote in the next step by VisIt code skeleton generating tool.
3. run command "xml2plugin -clobber ***Output.xml ".  ***Output.xml is the file used by VisIt code generating tool
   to create code skeleton and makelist file, for the case of ./unstructure_data, it is SCHSIMOutput.xml.
4. Use two backup plugin class file to overwrite the files avt***FileFormat.C and avt***FileFormat.h.
5. run "cmake -DCMAKE_BUILD_TYPE:STRING=Release " to create make system.
6. run "make" to build plugins binary. You should found four new files under your /home/qshu/.visit/visit_version/linux-x86_64/plugins/databases.
   They are named as libE***Database_par.so, libE***Database_ser.so, libI***Database_par.so, libM***Database_par.so.
   
Install VisIt on a Jetstream2 instance, with Ubuntu20 image. We will use VisIt version [3.1.4](https://visit-dav.github.io/visit-website/releases-as-tables/#series-31) so we can use server mode on Expanse.
```
wget https://github.com/visit-dav/visit/releases/download/v3.1.4/build_visit3_1_4yes
mkdir third_party
./build_visit3_1_4
yes
```
  
Custom plugin documenation

https://visit-sphinx-github-user-manual.readthedocs.io/en/develop/using_visit/Preferences/File_Locations.html?highlight=plugin#custom-plugin-files

VUSER_HOME/<visit-version>/<visit-arch>/plugins/databases/


