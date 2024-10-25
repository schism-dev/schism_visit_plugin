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
#include <vector>

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

    std::vector<std::string> var_id = { "time", "SCHISM_hgrid_face_nodes", "SCHISM_hgrid_edge_nodes",
    "SCHISM_hgrid_node_x","SCHISM_hgrid_node_y", "node_bottom_index","SCHISM_hgrid_face_x" ,
    "SCHISM_hgrid_face_y" ,"ele_bottom_index" ,"SCHISM_hgrid_edge_x" ,"SCHISM_hgrid_edge_y" ,
    "edge_bottom_index" ,"depth" ,"dry_value_flag" ,"wetdry_elem" ,"zcor" };

    std::vector<std::string> dim_id = {"nSCHISM_hgrid_node","nSCHISM_hgrid_face","nSCHISM_hgrid_face",
    "nMaxSCHISM_hgrid_face_nodes","nSCHISM_vgrid_layers"};

    long max_num_node_test = 30000;
    long max_num_ele_test = 60000;
    long max_num_side_test = 60000;
    long max_num_layer_test = 60;


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

        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_TRUE(ncMeshPtr->get_dim((*it).c_str()) != nullptr);
        }     

    }

    TEST(ScribIO3DTest, scribeDim)
    {

        //

        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_TRUE(ncScribe3DPtr->get_dim((*it).c_str()) != nullptr);
        }

        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_NO_THROW({SCHISMDim10 * dimptr = scribe3DPtr->get_dim(*it);
             });
        }

    }

    TEST(SchoutTest, schoutDim)
    {

        //
        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_TRUE(ncPtr->get_dim((*it).c_str()) != nullptr);
        }

        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_NO_THROW({ SCHISMDim10 * dimptr = soutPtr->get_dim(*it);
                });
        }
    }

    TEST(HotSchoutTest, hotDim)
    {
        //test a hotstart nc file in schout style
        //hotstart nc file can be viewed by VisIt
        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_TRUE(ncHotStartPtr->get_dim((*it).c_str()) != nullptr);
        }

        for (std::vector<std::string>::iterator it = dim_id.begin(); it != dim_id.end(); ++it) {
            EXPECT_NO_THROW({ SCHISMDim10 * dimptr = hotPtr->get_dim(*it);
                });
        }
    }

    TEST(ScribIO2DTest, scribeMesh)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.
        EXPECT_EQ(20641, meshPtr->numberOfNode());
        EXPECT_EQ(59615, meshPtr->numberOfSide());
        EXPECT_EQ(38960, meshPtr->numberOfElement());
        EXPECT_EQ(54, meshPtr->numberOfLayer());

        float* cache = new float[max_num_node_test * 3];
        int step = 1;

        EXPECT_NO_THROW(
            {
            meshPtr->fillPointCoord2D(cache, step); 
            }
        );


        delete[] cache;

        long* eleCache = new long[max_num_ele_test * 5];
        EXPECT_NO_THROW(
            {
             meshPtr->fillMeshElement(eleCache);
            }
        );

        delete[] eleCache;

        int* kbs = new int[max_num_side_test];
        EXPECT_NO_THROW
        (
            {
              meshPtr->fillKbs(kbs, 0);
            }
        );
        delete [] kbs;

        int* kbp = new int[max_num_node_test];
        EXPECT_NO_THROW(
            {
              meshPtr->fillKbp00(kbp, 0);
            }
        );
        delete [] kbp;

        int* kbe = new int[max_num_ele_test];
        EXPECT_NO_THROW(
            {
              meshPtr->fillKbe(kbe, 0);
            }
        );
        delete[] kbe;

        float* nodeCoord3D = new float[3 * max_num_layer_test * max_num_node_test];
        EXPECT_NO_THROW(
            {
              meshPtr->fillPointCoord3D(nodeCoord3D, 0);
            }
        );
        delete [] nodeCoord3D;
       
        float* sideCoord3D = new float[3 * max_num_layer_test * max_num_side_test];
        EXPECT_NO_THROW(
            {
              meshPtr->fillSideCenterCoord3D(sideCoord3D, 0);
            }
        );
        delete[] sideCoord3D;

        float* zCache = new float[max_num_layer_test * max_num_ele_test];
        EXPECT_NO_THROW(
            {
              meshPtr->zEleCenter3D(zCache, 0);
            }
        );
        delete[] zCache;
    }


    TEST(SchoutTest, schoutVar)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.

        for (std::vector<std::string>::iterator it = var_id.begin(); it != var_id.end(); ++it) {
            EXPECT_TRUE(ncPtr->get_var((*it).c_str())->is_valid());
        }

        for (std::vector<std::string>::iterator it = var_id.begin(); it != var_id.end(); ++it) {
            EXPECT_TRUE(soutPtr->inquire_var(*it));
        }
       
    }

    TEST(HotSchoutTest, hotVar)
    {
        // This test is named "mesh", and belongs to the "ScribeIOTest"
        // test case.


        for (std::vector<std::string>::iterator it = var_id.begin(); it != var_id.end(); ++it) {
            EXPECT_TRUE(ncHotStartPtr->get_var((*it).c_str())->is_valid());
        }

        for (std::vector<std::string>::iterator it = var_id.begin(); it != var_id.end(); ++it) {
            EXPECT_TRUE(hotPtr->inquire_var(*it));
        }



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
        std::string var_name("time");
        EXPECT_TRUE(scribe3DPtr->inquire_var(var_name));
        EXPECT_NO_THROW({
        SCHISMVar10 * svarptr = scribe3DPtr->get_var(var_name);;
            });

        size_t      found_underline = scribe3DFile.find_last_of("_");
        var_name = scribe3DFile.substr(0, found_underline);
        EXPECT_TRUE(scribe3DPtr->inquire_var(var_name));
        EXPECT_NO_THROW({
            SCHISMVar10 * svarptr = scribe3DPtr->get_var(var_name);
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