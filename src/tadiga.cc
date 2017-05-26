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
#include "tadiga.h"
#include "tadiga_geometry_factory.h"

tadiga::Tadiga::Tadiga(const Teuchos::RCP<const Teuchos::Comm<int> >& kComm,
                       Teuchos::RCP<Teuchos::ParameterList> parameters,
                       Teuchos::RCP<tadiga::Geometry> tadiga_geometry) {
    Teuchos::RCP<Teuchos::ParameterList> geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry", true));

    if (tadiga_geometry.is_null()) {
        tadiga::GeometryFactory geometry_factory(geometry_parameters);
        auto tadiga_geometry = geometry_factory.create(kComm);
    }
}
