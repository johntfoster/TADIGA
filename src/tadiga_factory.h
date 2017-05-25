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
#ifndef TADIGA_FACTORY_H
#define TADIGA_FACTORY_H

#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

#include "tadiga.h"
#include "tadiga_geometry.h"

namespace tadiga {

class TadigaFactory {
   public:
    TadigaFactory() {}

    virtual ~TadigaFactory(){};

    virtual Teuchos::RCP<tadiga::Tadiga> create(
        const std::string kInputFile,
        const Teuchos::RCP<const Teuchos::Comm<int> >& kComm,
        Teuchos::RCP<tadiga::Geometry> tadiga_geometry);

    virtual Teuchos::RCP<tadiga::Tadiga> create(
        const std::string kInputFile,
        const Teuchos::RCP<const Teuchos::Comm<int> >& kComm);

   private:
    // Private copy constructor to prohibit copying.
    TadigaFactory(const TadigaFactory&);

    // Private assignment operator to prohibit copying.
    TadigaFactory& operator=(const TadigaFactory&);
};
}
#endif  // TADIGA_FACTORY_H
