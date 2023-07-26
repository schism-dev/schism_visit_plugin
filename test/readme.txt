
this test code were build in MS Visual studio to debug SCHISM NetCDF output class used in the plugin.

Those plugin header files need to be added to the project,

 "SCHISMFile10.h"
 "MesHconstants10.h"
 "SCHISMFileUtil10.h"
 "SchismGeometry10.h"
 "SCHISMMeshProvider10.h"
 "ZCoordFileMeshProvider10.h"
 "NetcdfSCHISMOutput10.h"
 
And netcdf_c++.lib and its path needed in the project linker option.


