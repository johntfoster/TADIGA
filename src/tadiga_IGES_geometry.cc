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
#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "TopoDS_Shape.hxx"

#include "Teuchos_RCP.hpp"

#include "tadiga_IGES_geometry.h"

tadiga::IgesGeometry::IgesGeometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm) {
    const auto kFileName =
        kGeometryParameters->get<Standard_CString>("IGES File");

    // Open IGES Reader from OpenCASCADE
    const auto kIgesReader = Teuchos::rcp(new IGESControl_Reader);
    const auto status = kIgesReader->ReadFile(kFileName);

    // TODO(johntfoster@gmail.com): Check the status of the file

    Handle(TColStd_HSequenceOfTransient) myList =
        kIgesReader->GiveList("iges-faces");
    // selects all IGES faces in the file and puts them into a list  called
    // //MyList,

    const auto kIgesFaces = myList->Length();
    const auto kTransFaces = kIgesReader->TransferList(myList);
    // translates MyList,

    std::cout << "IGES Faces: " << kIgesFaces
              << "   Transferred:" << kTransFaces << std::endl;

    TopoDS_Shape sh = kIgesReader->OneShape();
};
