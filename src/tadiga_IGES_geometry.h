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
#ifndef TADIGA_IGES_GEOMETRY_H
#define TADIGA_IGES_GEOMETRY_H

#include <Teuchos_Comm.hpp>
#include <Teuchos_ParameterList.hpp>

#include "tadiga_geometry.h"

namespace tadiga {

//! Geometry class that reads an IGES file
class IgesGeometry : public tadiga::Geometry {
   public:
    // Constructor
    IgesGeometry(
        const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
        const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters);

   private:
    // Private to prohibit copying
    IgesGeometry(const IgesGeometry&);

    // Private to prohibit copying
    IgesGeometry& operator=(const IgesGeometry&);

   protected:
    //  Communicator
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm_;
};
};

#endif  // TADIGA_IGES_GEOMETRY_H
