/*****************************************************************************
 *
 * Copyright (c) 2000 - 2011, Lawrence Livermore National Security, LLC
 * Produced at the Lawrence Livermore National Laboratory
 * LLNL-CODE-442911
 * All rights reserved.
 *
 * This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
 * full copyright notice is contained in the file COPYRIGHT located at the root
 * of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
 *
 * Redistribution  and  use  in  source  and  binary  forms,  with  or  without
 * modification, are permitted provided that the following conditions are met:
 *
 *  - Redistributions of  source code must  retain the above  copyright notice,
 *    this list of conditions and the disclaimer below.
 *  - Redistributions in binary form must reproduce the above copyright notice,
 *    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
 * ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
 * LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
 * DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
 * CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
 * LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
 * OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 *****************************************************************************/

// ************************************************************************* //
//                            avtpropFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_prop_FILE_FORMAT_H
#define AVT_prop_FILE_FORMAT_H

#include <avtSTSDFileFormat.h>
#include <string>
using namespace std;

// ****************************************************************************
//  Class: avtpropFileFormat
//
//  Purpose:
//      Reads in prop files as a plugin to VisIt.
//
//  Programmer: qshu -- generated by xml2avt
//  Creation:   Fri Aug 2 09:49:50 PDT 2013
//
// ****************************************************************************

class avtpropFileFormat : public avtSTSDFileFormat {
  public:
    avtpropFileFormat(const char* filename);
    virtual ~avtpropFileFormat() { ; };

    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    // virtual void      *GetAuxiliaryData(const char *var, const char *type,
    //                                  void *args, DestructorFunction &);
    //

    //
    // These are used to declare what the current time and cycle are for the
    // file.  These should only be defined if the file format knows what the
    // time and/or cycle is.
    //
    // virtual bool      ReturnsValidCycle() const { return true; };
    // virtual int       GetCycle(void);
    // virtual bool      ReturnsValidTime() const { return true; };
    // virtual double    GetTime(void);
    //

    virtual const char* GetType(void) { return "prop"; };
    virtual void        FreeUpResources(void);

    virtual vtkDataSet*   GetMesh(const char*);
    virtual vtkDataArray* GetVar(const char*);
    virtual vtkDataArray* GetVectorVar(const char*);

  protected:
    // DATA MEMBERS
    virtual void PopulateDatabaseMetaData(avtDatabaseMetaData*);

  private:
    bool loadGridFile();
    bool loadVar();

  private:
    bool        m_initialized;
    std::string m_propFile;
    std::string m_workingPath;
    std::string m_mesh2DName;
    std::string m_variableName;
    int         m_numMeshNodes;
    int         m_numMeshFaces;
    int*        m_faceNodesPtr;
    float*      m_nodeXPtr;
    float*      m_nodeYPtr;
    float*      m_depPtr;
    float*      m_varPtr;
};

#endif
