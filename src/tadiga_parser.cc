// Copyright 2017 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "Teuchos_ParameterList.hpp"
#include "Teuchos_RCP.hpp"
#include "Teuchos_XMLParameterListHelpers.hpp"
#include "Teuchos_YamlParameterListCoreHelpers.hpp"
#include "Teuchos_YamlParser_decl.hpp"

#include "aprepro.h"

#include "tadiga_parser.h"

// Input file parser
Teuchos::RCP<Teuchos::ParameterList> tadiga::TadigaParser::parse(
    const std::string kInputFile) {
    // Set application parameters to default values
    auto tadiga_parameters = Teuchos::rcp(new Teuchos::ParameterList());

    SetTadigaParameterDefaults(tadiga_parameters.ptr());

    // Create aprepro instance
    SEAMS::Aprepro aprepro;
    std::ifstream input_file_stream(kInputFile.c_str());

    // get results from aprepro's parsing
    aprepro.parse_stream(input_file_stream,
                         kInputFile);  // TODO(johntfosterjr@gmail.com): Check
                                       // return value (bool).

    // Update parameters with data from yaml string
    Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters_ptr(
        tadiga_parameters.get());

    Teuchos::updateParametersFromYamlCString(
        (aprepro.parsing_results().str()).c_str(), tadiga_parameters_ptr, true);

    return tadiga_parameters;
}

void tadiga::TadigaParser::SetTadigaParameterDefaults(
    Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters) {
    tadiga_parameters->set("Verbose", false);
}
