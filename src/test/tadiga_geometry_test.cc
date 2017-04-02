// Copyright 2016-2017 John T. Foster, Katy L. Hanson
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
#include <fstream>
#include <iostream>

#include "Teuchos_UnitTestHarness.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "Teuchos_YamlParser_decl.hpp"

#include "Teuchos_RCP.hpp"
#include "tadiga_IGES_geometry.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup() {}

    ~TestSetup() { fclose(temp_file_); };

    auto GetYamlFileName() { return std::to_string(fileno(temp_file_)); }
    auto GetActualKnotSequence() { return actual_knot_sequence_; }
    auto GetActual_UKnotSequence() { return actual_Uknot_sequence_; }
    auto GetActual_VKnotSequence() { return actual_Vknot_sequence_; }

    auto GetComm() { return kComm_; }

   private:
    // Get communicator from test runner
    Teuchos::RCP<const Teuchos::Comm<int>> kComm_ =
        Tpetra::DefaultPlatform::getDefaultPlatform().getComm();
    int actual_knot_sequence_[2] = {0, 1};
    int actual_Uknot_sequence_[4] = {0, 0, 1, 1};
    int actual_Vknot_sequence_[4] = {0, 0, 1, 1};
    // Create temporary file
    std::FILE* temp_file_ = std::tmpfile();
};

TEUCHOS_UNIT_TEST(Tadiga_Geometry, curve_knot_sequence_values) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");
    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);
    auto actual_knot_sequence_ = kTestFixture->GetActualKnotSequence();
    int knot_sequence_length_ = iges_geometry_reader.GetKnotSequenceLength();
    int i;
    for (i = 1; i <= knot_sequence_length_; i = i + 1) {
        TEST_EQUALITY(iges_geometry_reader.GetKnotSequence()[i - 1],
                      actual_knot_sequence_[i - 1]);
    }
};
TEUCHOS_UNIT_TEST(Tadiga_Geometry, face_Uknot_sequence_values) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");
    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);
    auto actual_Uknot_sequence_ = kTestFixture->GetActual_UKnotSequence();
    int U_sequence_length_ = iges_geometry_reader.GetUKnotSequenceLength();
    int i;
    for (i = 1; i <= U_sequence_length_; i = i + 1) {
        TEST_EQUALITY(iges_geometry_reader.GetUKnotSequence()[i - 1],
                      actual_Uknot_sequence_[i - 1]);
    }
};

TEUCHOS_UNIT_TEST(Tadiga_Geometry, face_Vknot_sequence_values) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");
    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);
    auto actual_Vknot_sequence_ = kTestFixture->GetActual_VKnotSequence();
    int V_sequence_length_ = iges_geometry_reader.GetVKnotSequenceLength();
    std::cout << "V length: " << V_sequence_length_ << endl;

    int i;
    for (i = 1; i <= V_sequence_length_; i = i + 1) {
        TEST_EQUALITY(iges_geometry_reader.GetVKnotSequence()[i - 1],
                      actual_Vknot_sequence_[i - 1]);
    }
};
};
