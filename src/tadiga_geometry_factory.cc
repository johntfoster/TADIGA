// Copyright 2015 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include <Teuchos_Assert.hpp>

#include "tadiga_IGES_geometry.h"
#include "tadiga_geometry_factory.h"

tadiga::GeometryFactory::GeometryFactory(
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kGeometryParameters_(kGeometryParameters) {
    // check to see if a geometry type has been given
    if (!kGeometryParameters_->isParameter("Type")) {
        TEUCHOS_TEST_FOR_EXCEPTION(true, Teuchos::Exceptions::InvalidParameter,
                                   "Geometry type not specified, \"IGES\" is "
                                   "the only currently available"
                                   "option.");
    }
}

Teuchos::RCP<tadiga::Geometry> tadiga::GeometryFactory::create(
    const Teuchos::RCP<const Teuchos::Comm<int> >& kComm) {
    Teuchos::RCP<tadiga::Geometry> geometry;

    auto type = kGeometryParameters_->get<std::string>("Type");

    if (type == "IGES") {
        geometry =
            Teuchos::rcp(new tadiga::IgesGeometry(kComm, kGeometryParameters_));
    }
    // TODO(johntfosterjr@gmail.com): Add STEP file functionality
    // else if(type == "STEP"){
    // discretization = Teuchos::rcp(new tadiga::STEPGeometry(epetra_comm,
    // discParams));
    //}
    else {
        TEUCHOS_TEST_FOR_EXCEPTION(
            true, Teuchos::Exceptions::InvalidParameter,
            "**** Invalid geometry type.  Valid types are "
            "\"IGES\".\n");
    }

    return geometry;
}
