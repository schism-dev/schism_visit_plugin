#ifndef _ZCOORDFILEMESHPROVIDER10_H_
#define _ZCOORDFILEMESHPROVIDER10_H_
#include "SCHISMMeshProvider10.h"

class ZCoordMeshProvider10:public SCHISMMeshProvider10
{

public:
	ZCoordMeshProvider10(const std::string & a_fileHasMeshData);

	bool zcoords3D(float * a_zCachePtr,const int & a_timeStep) const;
	//return z coords cache but layer dim change first
    bool zcoords3D2(float * a_zCachePtr,const int & a_timeStep) const;

private:

   float  convertStoZ(const float    & a_sigma,
                       const float    & a_surface,
                       const float    & a_depth,
                       const float    & a_hs,
                       const float    & a_hc,
                       const float    & a_thetab,
                       const float    & a_thetaf) const;

};
#endif