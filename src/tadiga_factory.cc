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

#include "tadiga_factory.h"
#include "tadiga.h"
#include "tadiga_parser.h"

// Factory Method to create Tadiga objects
Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
    const std::string kInputFile,
    const Teuchos::RCP<const Teuchos::Comm<int> >& kComm,
    Teuchos::RCP<tadiga::Geometry> tadiga_geometry) {
    const auto tadiga_parameters = tadiga::TadigaParser::parse(kInputFile);

    // Create new Tadiga object
    return Teuchos::rcp(
        new tadiga::Tadiga(kComm, tadiga_parameters, tadiga_geometry));
}

Teuchos::RCP<tadiga::Tadiga> tadiga::TadigaFactory::create(
    const std::string kInputFile,
    const Teuchos::RCP<const Teuchos::Comm<int> >& kComm) {
    Teuchos::RCP<tadiga::Geometry> null_geometry;
    return create(kInputFile, kComm, null_geometry);
}
