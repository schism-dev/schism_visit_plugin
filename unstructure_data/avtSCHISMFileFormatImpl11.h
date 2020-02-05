#ifndef AVTSCHISMFILEFORMATIMPL11_H
#define AVTSCHISMFILEFORMATIMPL11_H
#include <vector>
#include <map>
#include <vtkUnstructuredGrid.h>
#include "SCHISMFile10.h"
#include "MeshProvider10.h"
#include "FileFormatFavorInterface.h"
#include "avtSCHISMFileFormatImpl10.h"

// this Implementation change x,y coordates to double precision to match new double xy schsim output
class avtSCHISMFileFormatImpl11 : public avtSCHISMFileFormatImpl10
{
  public:
                    avtSCHISMFileFormatImpl11();
  virtual           ~avtSCHISMFileFormatImpl11() {;};

  static           FileFormatFavorInterface * create();


  private:
	  void           create2DUnstructuredMesh( vtkUnstructuredGrid *a_uGrid,
	                                       long                 *a_meshEle,
										   const  int          &a_timeState);

      void           create2DUnstructuredMeshNoDryWet( vtkUnstructuredGrid *a_uGrid,
	                                                  long                 *a_meshEle,
												      const  int          &a_timeState);

      void           create3DUnstructuredMesh(vtkUnstructuredGrid *a_uGrid,
	                                      long                 *a_meshEle,
										  long                 *a_2DPointto3DPoints,
										  const  int          &a_timeState);

      void           createLayerMesh(vtkUnstructuredGrid *a_uGrid,
	                             long                 *a_meshEle,
								 long                 *a_2DPointto3DPoints,
							     const  int          &a_timeState);

      void           create2DPointMesh( vtkUnstructuredGrid *a_uGrid,
	                                long                 *a_meshEle,
								    const  int          &a_timeState);

      void           create3DPointMesh( vtkUnstructuredGrid *a_uGrid,
	                                long                 *a_meshEle,
								    const  int          &a_timeState);

      void           create3DPointFaceMesh( vtkUnstructuredGrid *a_uGrid,
	                                    long                *a_meshEle,
								        const  int          &a_timeState);

	  void           loadMeshCoordinates(MeshProvider10 * a_meshProviderPtr);

   




  private:

  bool         m_initialized;
  bool         m_mesh_is_static;
  std::string  m_data_file;
  // path where  m_data_file is under
  std::string  m_data_file_path; 
  std::string  m_plugin_name;
  SCHISMFile10*   m_data_file_ptr;
  

  // element centered data use mesh from other file
  MeshProvider10* m_external_mesh_provider;
 
  
  // a number of token of saved vars and attributes
  std::string  m_data_description;
  std::string  m_mesh_var;
  std::string  m_var_label_att;
  std::string  m_var_location_att; 
  
  // name for meshes
  std::string  m_mesh_3d;
  std::string  m_layer_mesh;
  std::string  m_mesh_2d;
  std::string  m_mesh_2d_no_wet_dry;
  std::string  m_side_center_point_3d_mesh;
  std::string  m_side_center_point_2d_mesh;
  // vertical side-faces center points, 3d flux data uses it
  std::string  m_face_center_point_3d_mesh;
  
  // dimension size of single layer of 2D Mesh 
  long          m_num_mesh_nodes;
  long          m_num_mesh_edges;
  long          m_num_mesh_faces;
  

  // number of time step 
  std::string  m_dim_time;
  long         m_num_time_step;
  float *      m_time_ptr;
  std::string  m_time;

  //coordinates and depth
  std::string  m_node_depth;
  std::string  m_node_depth_label;
  std::string  m_node_surface;
  std::string  m_node_surface_label;
  std::string  m_layerSCoord;
  std::string  m_dim_layers;
  std::string  m_dim_var_component;
  // this is number of level in schsim
  int          m_num_layers;
  double     *  m_node_x_ptr;
  double     *  m_node_y_ptr;
  float      *  m_node_z_ptr;
  // this is kbp read from mesh provider, always node center
  int       *  m_kbp00;
  int       *  m_kbp_node;
  bool         m_kbp_node_filled;
  int       *  m_kbp_ele;
  bool         m_kbp_ele_filled;
  int       *  m_kbp_side;
  bool         m_kbp_side_filled;
  int          m_cache_kbp_id;
  //  this is the kbp read from data file itself
  //  it is differnt from m_kbp00 for element/prism centred data
  int       *  m_kbp_data;


  int       *  m_node_dry_wet;
  int       *  m_ele_dry_wet;
  int       *  m_side_dry_wet;
  int          m_node_dry_wet_cached_time;
  int          m_side_dry_wet_cached_time;
  int          m_ele_dry_wet_cached_time;
 
  long          m_total_valid_3D_point;
  long          m_total_valid_3D_side;
  long          m_total_valid_3D_ele;
  

  std::string  m_surface_state_suffix;
  std::string  m_bottom_state_suffix;
  std::string  m_depth_average_suffix;

  //map convert netcdf centering into avt centering
  std::map<std::string, avtCentering> m_center_map;

  //map convert var label into netcdf varname token
  std::map<std::string, std::string>  m_var_name_label_map;


  //map convert var label into netcdf varname token
  std::map<std::string, std::string>  m_var_vertical_center_map;


  //map convert var label into netcdf varname token
  std::map<std::string, std::string>  m_var_horizontal_center_map;


  // maping var label to its mesh name
  std::map<std::string,std::string> m_var_mesh_map;

  // caching SCHISM var (not visit labeled var)  dim 3D/2D only
  std::map<std::string,int> m_var_dim;

 // norminal num data per layer for different centering, node,side,element
  std::map<std::string,int> m_nominal_size_per_layer;

  // dry state
  float       m_dry_surface;  

  std::string m_data_center;

  //half or full level, only meaningfull for 3d data
  std::string m_level_center;


  //debug var del after done
  int m_tri_wedge;
  int m_tri_pyramid;
  int m_tri_tetra;

  int m_quad_hexhedron;
  int m_quad_wedge;
  int m_quad_pyramid;


};

#endif