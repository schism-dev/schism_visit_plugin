#include "gtest/gtest.h"
#include "MeshConstants10.h"
#include "NetcdfSCHISMOutput10.h"
#include "SCHISMFile10.h"
#include "SCHISMFileUtil10.h"
#include "SCHISMMeshProvider10.h"
#include "SchismGeometry10.h"
#include "ZCoordFileMeshProvider10.h"
#include <cmath>
#include <fstream>
#include <iostream>

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

namespace 
{
    std::string meshFile;
    std::string soutFile;
    std::string hotstartFile;
    std::string scribe3DFile;

    NcFile* ncPtr;
    NcFile* ncMeshPtr;
    NcFile* ncHotStartPtr;
    NcFile* ncScribe3DPtr;
    NetcdfSchismOutput10 * soutPtr;
    NetcdfSchismOutput10* scribe3DPtr;
    NetcdfSchismOutput10* hotPtr;
    SCHISMMeshProvider10* meshPtr;


    TEST(ScribIO2DTest, scribeAttr) 
    {
        // This test is named "scribe1", and belongs to the "ScribeIOTest"
        // test case. Check for global attrbutes

        //no global attribute needed
       
    }

    TEST(ScribIO3DTest, scribeAttr)
    {
        // This test is named "scribe1", and belongs to the "ScribeIOTest"
        // test case. Check for global attrbutes

        //no global attribute needed

    }


    TEST(SchoutTest, schoutAttr)
    {
        //
        EXPECT_TRUE(ncPtr->get_att("source") != nullptr);
        EXPECT_EQ(soutPtr->global_att_as_string("source"),"SCHISM model output version v10");

    }

    TEST(HotSchouTest, hotAttr)
    {

        //
        EXPECT_TRUE(ncHotStartPtr->get_att("source") != nullptr);
        EXPECT_EQ(hotPtr->global_att_as_string("source"), "SCHISM model output version v10");

    }

    TEST(ScribIO2DTest, scribeDim)
    {

        //
        EXPECT_TRUE(ncMeshPtr->get_dim("nSCHISM_hgrid_node")!= nullptr);
        EXPECT_TRUE(ncMeshPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncMeshPtr->get_dim("nSCHISM_hgrid_edge") != nullptr);
        EXPECT_TRUE(ncMeshPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(ncMeshPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);
      

    }

    TEST(ScribIO3DTest, scribeDim)
    {

        //
        EXPECT_TRUE(ncScribe3DPtr->get_dim("nSCHISM_hgrid_node") != nullptr);
        EXPECT_TRUE(ncScribe3DPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncScribe3DPtr->get_dim("nSCHISM_hgrid_edge") != nullptr);
        EXPECT_TRUE(ncScribe3DPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(ncScribe3DPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);

        EXPECT_NO_THROW({
              SCHISMDim10 * dimptr = scribe3DPtr->get_dim("nSCHISM_hgrid_node");;
         });
        EXPECT_NO_THROW({
              SCHISMDim10 * dimptr = scribe3DPtr->get_dim("nSCHISM_hgrid_face");;
            });
        EXPECT_NO_THROW({
              SCHISMDim10 * dimptr = scribe3DPtr->get_dim("nSCHISM_hgrid_edge");;
            });
        EXPECT_NO_THROW({
              SCHISMDim10 * dimptr = scribe3DPtr->get_dim("nMaxSCHISM_hgrid_face_nodes");;
            });
        EXPECT_NO_THROW({
              SCHISMDim10 * dimptr = scribe3DPtr->get_dim("nSCHISM_vgrid_layers");;
            });


    }

    TEST(SchoutTest, schoutDim)
    {

        //
        EXPECT_TRUE(ncPtr->get_dim("nSCHISM_hgrid_node") != nullptr);
        EXPECT_TRUE(ncPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(ncPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);
        EXPECT_TRUE(soutPtr->get_dim("nSCHISM_hgrid_node") != nullptr);
        EXPECT_TRUE(soutPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(soutPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(soutPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(soutPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);

    }

    TEST(HotSchoutTest, HotDim)
    {
        //test a hotstart nc file in schout style
        //hotstart nc file can be viewed by VisIt

        EXPECT_TRUE(ncHotStartPtr->get_dim("nSCHISM_hgrid_node") != nullptr);
        EXPECT_TRUE(ncHotStartPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncHotStartPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(ncHotStartPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(ncHotStartPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);
        EXPECT_TRUE(hotPtr->get_dim("nSCHISM_hgrid_node") != nullptr);
        EXPECT_TRUE(hotPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(hotPtr->get_dim("nSCHISM_hgrid_face") != nullptr);
        EXPECT_TRUE(hotPtr->get_dim("nMaxSCHISM_hgrid_face_nodes") != nullptr);
        EXPECT_TRUE(hotPtr->get_dim("nSCHISM_vgrid_layers") != nullptr);

    }

    TEST(ScribIO2DTest, scribeMesh)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.
        EXPECT_EQ(23456, meshPtr->numberOfNode());
        EXPECT_EQ(23, meshPtr->numberOfLayer());
    }


    TEST(SchoutTest, schoutVar)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.
        
        EXPECT_TRUE(ncPtr->get_var("time")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_face_nodes")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_edge_nodes")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_node_x")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_node_y")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("node_bottom_index")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_face_x")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_face_y")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("ele_bottom_index")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_edge_x")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("SCHISM_hgrid_edge_y")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("edge_bottom_index")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("depth")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("dry_value_flag")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("wetdry_elem")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("zcor")->is_valid());
        EXPECT_TRUE(ncPtr->get_var("elev")->is_valid());

        EXPECT_TRUE(soutPtr->inquire_var("time"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_face_nodes"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_edge_nodes"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_node_x"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_node_y"));
        EXPECT_TRUE(soutPtr->inquire_var("node_bottom_index"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_face_x"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_face_y"));
        EXPECT_TRUE(soutPtr->inquire_var("ele_bottom_index"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_edge_x"));
        EXPECT_TRUE(soutPtr->inquire_var("SCHISM_hgrid_edge_y"));
        EXPECT_TRUE(soutPtr->inquire_var("edge_bottom_index"));
        EXPECT_TRUE(soutPtr->inquire_var("depth"));
        EXPECT_TRUE(soutPtr->inquire_var("dry_value_flag"));
        EXPECT_TRUE(soutPtr->inquire_var("wetdry_elem"));
        EXPECT_TRUE(soutPtr->inquire_var("zcor"));
        EXPECT_TRUE(soutPtr->inquire_var("elev"));
       
    }

    TEST(HotSchoutTest, hotVar)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.

        EXPECT_TRUE(ncHotStartPtr->get_var("time")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_face_nodes")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_edge_nodes")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_node_x")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_node_y")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("node_bottom_index")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_face_x")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_face_y")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("ele_bottom_index")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_edge_x")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("SCHISM_hgrid_edge_y")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("edge_bottom_index")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("depth")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("dry_value_flag")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("wetdry_elem")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("zcor")->is_valid());
        EXPECT_TRUE(ncHotStartPtr->get_var("elev")->is_valid());

        EXPECT_TRUE(hotPtr->inquire_var("time"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_face_nodes"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_edge_nodes"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_node_x"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_node_y"));
        EXPECT_TRUE(hotPtr->inquire_var("node_bottom_index"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_face_x"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_face_y"));
        EXPECT_TRUE(hotPtr->inquire_var("ele_bottom_index"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_edge_x"));
        EXPECT_TRUE(hotPtr->inquire_var("SCHISM_hgrid_edge_y"));
        EXPECT_TRUE(hotPtr->inquire_var("edge_bottom_index"));
        EXPECT_TRUE(hotPtr->inquire_var("depth"));
        EXPECT_TRUE(hotPtr->inquire_var("dry_value_flag"));
        EXPECT_TRUE(hotPtr->inquire_var("wetdry_elem"));
        EXPECT_TRUE(hotPtr->inquire_var("zcor"));
        EXPECT_TRUE(hotPtr->inquire_var("elev"));

    }

    TEST(ScribIO2DTest, scribeVar)
    {
        // This test is named "scribevar", and belongs to the "ScribeIOTest"
        // test case.
        std::string varID("time");
        EXPECT_TRUE(soutPtr->inquire_var(varID));
        EXPECT_NO_THROW({
        SCHISMVar10 * svarptr = soutPtr->get_var(varID);
         });
        
    }

    TEST(ScribIO3DTest, scribeVar)
    {
        // This test is named "scribevar", and belongs to the "ScribeIOTest"
        // test case.
        std::string varID("time");
        EXPECT_TRUE(scribe3DPtr->inquire_var(varID));
       

        size_t      found_underline = scribe3DFile.find_last_of("_");
        std::string var_name = scribe3DFile.substr(0, found_underline);
        EXPECT_TRUE(scribe3DPtr->inquire_var(var_name));

        EXPECT_NO_THROW({
          SCHISMVar10* svarptr = scribe3DPtr->get_var(varID);;
         });  

    }
}

int main(int argc, char** argv) {
    
    // The first arg is an out2d file, if it exists.
    // The second one is a SCHISM file to test.
    // The third one is a hot start nc file
    meshFile = argc > 1 ? argv[1] : "out2d_1.nc";
    soutFile = argc > 2 ? argv[2] : "depth_averaged_salinity_75.nc";
    hotstartFile = argc > 3 ? argv[3] : "hotstart_schout_1.nc";
    scribe3DFile = argc > 4 ? argv[4] : "temperature_1.nc";

    soutPtr = new NetcdfSchismOutput10(soutFile);
    hotPtr = new NetcdfSchismOutput10(hotstartFile);
    scribe3DPtr = new  NetcdfSchismOutput10(scribe3DFile);
    ncPtr = new NcFile(soutFile.c_str());
    ncMeshPtr = new NcFile(meshFile.c_str());
    ncHotStartPtr = new NcFile(hotstartFile.c_str());
    ncScribe3DPtr = new NcFile(scribe3DFile.c_str());
    meshPtr = new ZCoordMeshProvider10(meshFile);

    InitGoogleTest(&argc, argv);
    int ret_val = RUN_ALL_TESTS();

    delete soutPtr;
    delete meshPtr;
    delete ncPtr;
    delete ncMeshPtr;
    delete hotPtr;
    delete ncHotStartPtr;
    delete ncScribe3DPtr;
    delete scribe3DPtr;
    return ret_val;
}