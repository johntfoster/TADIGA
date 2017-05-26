// Copyright 2016-2017 John T. Foster, Katy L. Hanson

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "BRepAdaptor_Curve.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "BRep_Tool.hxx"
#include "BSplCLib.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_BSplineSurface.hxx"
#include "IGESControl_Reader.hxx"
#include "ShapeAnalysis_Edge.hxx"
#include "TColStd_Array1OfReal.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "Teuchos_RCP.hpp"
#include "TopExp_Explorer.hxx"
#include "TopoDS.hxx"

#include "tadiga_IGES_geometry.h"
#include "tadiga_geometry.h"

tadiga::IgesGeometry::IgesGeometry(
    const Teuchos::RCP<const Teuchos::Comm<int> >& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : Geometry(kComm, kGeometryParameters), kComm_(kComm) {
    const auto kFileName = kGeometryParameters->get<std::string>("File Name");

    const auto kIgesReader = Teuchos::rcp(new IGESControl_Reader);
    const auto status = kIgesReader->ReadFile(kFileName.c_str());
    // TODO(johntfoster@gmail.com): Check the status of the file

    // Returns list of all entities from IGES file
    auto iges_entity_list = kIgesReader->GiveList();

    // Transfer all entities at once
    number_of_iges_entities_ = iges_entity_list->Length();
    number_of_transferred_entities_ =
        kIgesReader->TransferList(iges_entity_list);

    // Obtain result in a single OCCT shape
    transferred_occt_shape_ = kIgesReader->OneShape();

    // Print output to check status
    this->initialize();
}
