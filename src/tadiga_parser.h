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
#ifndef TADIGA_PARSER_H
#define TADIGA_PARSER_H

#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>

namespace tadiga {

class TadigaParser {
   public:
    TadigaParser() {}

    static Teuchos::RCP<Teuchos::ParameterList> parse(
        const std::string kInputFile);

   private:
    // Private function to set default problem parameter values
    static void SetTadigaParameterDefaults(
        Teuchos::Ptr<Teuchos::ParameterList> tadiga_parameters);

    // Private copy constructor to prohibit copying.
    TadigaParser(const TadigaParser&);

    // Private assignment operator to prohibit copying.
    TadigaParser& operator=(const TadigaParser&);
};
}
#endif  // TADIGA_PARSER_H
