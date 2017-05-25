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
#ifndef TADIGA_GEOMETRYFACTORY_H
#define TADIGA_GEOMETRYFACTORY_H

#include <Teuchos_Comm.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

#include "tadiga_geometry.h"

namespace tadiga {

class GeometryFactory {
   public:
    //! Default constructor
    GeometryFactory(
        const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters);

    virtual ~GeometryFactory(){};

    virtual Teuchos::RCP<Geometry> create(
        const Teuchos::RCP<const Teuchos::Comm<int> >& kComm);

   private:
    //! Private to prohibit copying
    GeometryFactory(const GeometryFactory&);

    //! Private to prohibit copying
    GeometryFactory& operator=(const GeometryFactory&);

   protected:
    //! Parameter list
    const Teuchos::RCP<Teuchos::ParameterList> kGeometryParameters_;
};
}

#endif  // TADIGA_GEOMETRYFACTORY_H
