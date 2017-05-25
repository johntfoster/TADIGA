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
#include <fstream>
#include <iostream>

#include "Teuchos_UnitTestHarness.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "Teuchos_YamlParser_decl.hpp"

#include "tadiga_parser.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup() {}

    ~TestSetup() { fclose(temp_file_); };

    std::string GetFileName() { return std::to_string(fileno(temp_file_)); }

   private:
    // Get communicator from test runner
    Teuchos::RCP<const Teuchos::Comm<int>> kComm_ =
        Tpetra::DefaultPlatform::getDefaultPlatform().getComm();

    // Create temporary file
    std::FILE* temp_file_ = std::tmpfile();
};

// Tests the default value of "Verbose" is correctly set to false
// if an empty parameter list is given as an input to the parser
TEUCHOS_UNIT_TEST(Parser, Default) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    // Retrieve parsed parameter list from file
    const auto parameters =
        tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve value of "Verbose"
    const auto default_verbose_value = parameters->get<bool>("Verbose");

    TEST_EQUALITY(default_verbose_value, false)
}

// Tests the value of "Verbose" is true if we first create a parameter list
// and write it to file
TEUCHOS_UNIT_TEST(Parser, File) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Verbose", true);

    const auto& kParameters = *parameters;

    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetFileName(),
                                              kParameters);

    // Reads the parsed parameters
    parameters = tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve
    const auto verbose_value = parameters->get<bool>("Verbose");

    TEST_EQUALITY(verbose_value, true)
}

// Tests the aprepro algebra functionality for mutiplication
TEUCHOS_UNIT_TEST(Parser, Double_Multiplication) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Double Multiply", "{2.2 * 2.0}");

    const auto& kParameters = *parameters;

    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetFileName(),
                                              kParameters);

    // Reads the parsed parameters
    parameters = tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve
    const auto double_string_value =
        parameters->get<std::string>("Double Multiply");
    // Convert to double
    const auto double_value = std::stod(double_string_value, nullptr);

    TEST_FLOATING_EQUALITY(double_value, 4.4, 1e-14)
}

// Tests the aprepro algebra functionality for predefined constant
// substitution
TEUCHOS_UNIT_TEST(Parser, Pi_Value) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Pi", "{PI}");

    const auto& kParameters = *parameters;

    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetFileName(),
                                              kParameters);

    // Reads the parsed parameters
    parameters = tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve
    const auto pi_string_value = parameters->get<std::string>("Pi");
    // Convert to double
    const auto pi_value = std::stod(pi_string_value, nullptr);

    TEST_FLOATING_EQUALITY(pi_value, 3.1415, 1e-4)
}

// Tests the aprepro algebra functionality for function parsing
TEUCHOS_UNIT_TEST(Parser, Function) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Function", "{4.0 * atan(1.0)}");

    const auto& kParameters = *parameters;

    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetFileName(),
                                              kParameters);

    // Reads the parsed parameters
    parameters = tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve
    const auto function_string_value = parameters->get<std::string>("Function");
    // Convert to double
    const auto function_value = std::stod(function_string_value, nullptr);

    TEST_FLOATING_EQUALITY(function_value, 3.1415, 1e-4)
}

// Tests the aprepro algebra functionality for relational operations
TEUCHOS_UNIT_TEST(Parser, Relational) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());

    parameters->set("Relational", "{8 < 10}");

    const auto& kParameters = *parameters;

    Teuchos::YAMLParameterList::writeYamlFile(kTestFixture->GetFileName(),
                                              kParameters);

    // Reads the parsed parameters
    parameters = tadiga::TadigaParser::parse(kTestFixture->GetFileName());

    // Retrieve
    const auto int_string_value = parameters->get<std::string>("Relational");
    // Convert to int
    const auto int_value = std::stoi(int_string_value, nullptr);

    TEST_EQUALITY(int_value, 1)
}
}
