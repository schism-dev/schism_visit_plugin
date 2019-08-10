#include "ZCoordFileMeshProvider10.h"
#include "MeshConstants10.h"
#include "SCHISMFile10.h"
#include "SCHISMFileUtil10.h"
#include <algorithm> 

using namespace std;

ZCoordMeshProvider10::ZCoordMeshProvider10(const std::string& a_zcoordFile):SCHISMMeshProvider10(a_zcoordFile)
{

}



float  ZCoordMeshProvider10::convertStoZ(const float    & a_sigma,
                                     const float    & a_surface,
                                     const float    & a_depth,
                                     const float    & a_hs,
                                     const float    & a_hc,
                                     const float    & a_thetab,
                                     const float    & a_thetaf) const
{

  float surface = a_surface;

  if (fabs(a_surface-MeshConstants10::DRY_SURFACE)<1.0e-6)
    {
      surface = 0.0;
    }

  float one =1.0;
  float half=0.5;
  float two =2.0;

  float csigma = (one-a_thetab)*sinh(a_thetaf*a_sigma)/sinh(a_thetaf)
  +a_thetab*(tanh(a_thetaf*(a_sigma+half))-tanh(a_thetaf/two))/(two*tanh(a_thetaf/two));
  

  float hat    = a_depth;
  if (a_hs < a_depth)
    {
      hat       = a_hs;
    }
   float z        = MeshConstants10::DRY_SURFACE;
   if (hat>a_hc)
    {
            z      = surface*(one+a_sigma)+a_hc*a_sigma+(hat-a_hc)*csigma;
    }
   else
    {
            z      = (hat+surface)*a_sigma+surface;   
    }
   
  return z;

}




//return  z core with node dim the first change then layer
bool ZCoordMeshProvider10::zcoords3D(float * a_zCachePtr,const int & a_timeStep) const
{
	 int timeStart    = a_timeStep;

     SCHISMVar10 * zVarPtr = m_dataFilePtr->get_var(MeshConstants10::ZCOORD);
  
     if (!(zVarPtr->is_valid()))
     {
      
       throw SCHISMFileException10("invlaid var "+MeshConstants10::ZCOORD+" for data file "+m_dataFilePtr->file());
     }
   
	
     float missing_val = (zVarPtr->get_att("missing_value"))->float_value(0);
	 float dry_zcor = MeshConstants10::DRY_ZCOR;

     zVarPtr->set_cur(timeStart);

	 long z_var_size =0;
	 long * node_start_index= new long [m_number_node];
	 int * kbp00 = new int [m_number_node];
	 fillKbp00(kbp00,a_timeStep);
	 for(int iNode=0;iNode<m_number_node;iNode++)
	 {
		 node_start_index[iNode]=z_var_size;
		 z_var_size+=m_number_layer-std::max(1,kbp00[iNode])+1;
	 }

	float * nodeDepthPtr  = new float [m_number_node];
    
 
    retrieve1DVar(nodeDepthPtr,
	              m_dataFilePtr,
                  MeshConstants10::NODE_DEPTH,
                  m_number_node);

     float*           zPtr = new float [z_var_size];
     if (!(zVarPtr->get(zPtr)))
     {
        throw SCHISMFileException10("fail to retrieve var "+MeshConstants10::ZCOORD+" from data file "+m_dataFilePtr->file());
     }

	  for (int iLayer= 0; iLayer<m_number_layer;iLayer++)
      { 
		 
          for(long iNode=0;iNode <m_number_node; iNode++)
            {
			  long start_index = node_start_index[iNode];
		      if (iLayer<(std::max(1,kbp00[iNode])-1))
			  {
				 
			  }
			  else
			  {
				  float temp =   zPtr[start_index+iLayer+1-std::max(1,kbp00[iNode])];
				  if((temp!=dry_zcor)&&(temp!=missing_val))
				  {
                      *a_zCachePtr = temp;
				  }
				  else
				  {
					  float surface= MeshConstants10::DUMMY_ELEVATION;
				      float sigma        = m_layerSCoords[iLayer]; 
				      float depth        = nodeDepthPtr[iNode];    
				      float z            = convertStoZ(sigma,
												       surface,
												       depth,
												       m_hs,
												       m_hc,
												       m_thetab,
												       m_thetaf);
				      *a_zCachePtr         = z;
				  }
				  a_zCachePtr++;
			  }

            }
       }
	 delete zPtr;
	 delete kbp00;
	 delete nodeDepthPtr;
	 return true;
}

bool ZCoordMeshProvider10::zcoords3D2(float * a_zCachePtr,const int & a_timeStep) const
{
	 int timeStart    = a_timeStep;

     SCHISMVar10 * zVarPtr = m_dataFilePtr->get_var(MeshConstants10::ZCOORD);
  
     if (!(zVarPtr->is_valid()))
     {
      
       throw SCHISMFileException10("invlaid var "+MeshConstants10::ZCOORD+" for data file "+m_dataFilePtr->file());
     }
   
     zVarPtr->set_cur(timeStart);
	 float missing_val = (zVarPtr->get_att("missing_value"))->float_value(0);
	 float dry_zcor = MeshConstants10::DRY_ZCOR;
	 float * node_depth_ptr  = new float [m_number_node];
    
 
    retrieve1DVar(node_depth_ptr,
	              m_dataFilePtr,
                  MeshConstants10::NODE_DEPTH,
                  m_number_node);

	 long z_var_size =0;
	 long * node_start_index= new long [m_number_node];
	 int * kbp00 = new int [m_number_node];
	 fillKbp00(kbp00,a_timeStep);
	
	 for(long iNode=0;iNode<m_number_node;iNode++)
	 {
	    node_start_index[iNode]=z_var_size;	     
		z_var_size+=m_number_layer-std::max(1,kbp00[iNode])+1;
	 }

     float*           zPtr = new float [z_var_size];
     if (!(zVarPtr->get(zPtr)))
     {
        throw SCHISMFileException10("fail to retrieve var "+MeshConstants10::ZCOORD+" from data file "+m_dataFilePtr->file());
     }

	  for (int iLayer= 0; iLayer<m_number_layer;iLayer++)
      { 
		 
          for(long iNode=0;iNode <m_number_node; iNode++)
            {
			  long start_index = node_start_index[iNode];
		      if (iLayer<(std::max(1,kbp00[iNode])-1))
			  {
				 
			  }
			  else
			  {
				  float temp =   zPtr[start_index+iLayer+1-std::max(1,kbp00[iNode])];
				  if((temp==dry_zcor)||(temp==missing_val))
				  {
					  float surface= MeshConstants10::DUMMY_ELEVATION;
				      float sigma        = m_layerSCoords[iLayer]; 
				      float depth        = node_depth_ptr[iNode];    
				      float z            = convertStoZ(sigma,
												       surface,
												       depth,
												       m_hs,
												       m_hc,
												       m_thetab,
												       m_thetaf);
				      zPtr[start_index+iLayer+1-std::max(1,kbp00[iNode])] = z;
				  }
			  }

            }
       }

	  for (int i= 0; i<z_var_size;i++)
      { 
         a_zCachePtr[i] =  zPtr[i];
       }
	 delete zPtr;
	 delete kbp00;
	 delete node_start_index;
	 delete node_depth_ptr;
	 return true;
}