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
#include <array>
#include <fstream>
#include <iostream>

#include "Teuchos_RCP.hpp"
#include "Teuchos_UnitTestHarness.hpp"
#include "Teuchos_YamlParser_decl.hpp"
#include "Tpetra_DefaultPlatform.hpp"

#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"

#include "tadiga_IGES_geometry.h"
#include "tadiga_types.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup() {}

    ~TestSetup(){};

    auto GetKnotSequence() { return knot_sequence_; }
    auto GetUKnotSequence() { return u_knot_sequence_; }
    auto GetVKnotSequence() { return v_knot_sequence_; }

    auto GetComm() { return kComm_; }

   private:
    // Get communicator from test runner
    Teuchos::RCP<const Teuchos::Comm<int>> kComm_ =
        Tpetra::DefaultPlatform::getDefaultPlatform().getComm();

    tadiga::types::TadigaRealArray<2> knot_sequence_ = {0, 1};
    tadiga::types::TadigaRealArray<4> u_knot_sequence_ = {0, 0, 1, 1};
    tadiga::types::TadigaRealArray<4> v_knot_sequence_ = {0, 0, 1, 1};
};

TEUCHOS_UNIT_TEST(Tadiga_Geometry, curve_knot_sequence_values) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));
    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    auto iges_geometry_reader = Teuchos::rcp(
        new tadiga::IgesGeometry(kTestFixture->GetComm(), geometry_parameters));

    TEST_COMPARE_FLOATING_ARRAYS(iges_geometry_reader->GetKnotSequence(),
                                 kTestFixture->GetKnotSequence(), 0.001);
};

// TEUCHOS_UNIT_TEST(Tadiga_Geometry, face_u_knot_sequence_values) {
// const auto kTestFixture = Teuchos::rcp(new TestSetup());

// auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
// auto geometry_parameters =
// Teuchos::rcpFromRef(parameters->sublist("Geometry"));

// geometry_parameters->set("Type", "IGES");
// geometry_parameters->set("File Name", "test.igs");
// tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
// geometry_parameters);

// TEST_COMPARE_FLOATING_ARRAYS(iges_geometry_reader.GetUKnotSequence(),
// kTestFixture->GetUKnotSequence(), 0.001);
//};

// TEUCHOS_UNIT_TEST(Tadiga_Geometry, face_v_knot_sequence_values) {
// const auto kTestFixture = Teuchos::rcp(new TestSetup());

// auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
// auto geometry_parameters =
// Teuchos::rcpFromRef(parameters->sublist("Geometry"));

// geometry_parameters->set("Type", "IGES");
// geometry_parameters->set("File Name", "test.igs");
// tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
// geometry_parameters);

// TEST_COMPARE_FLOATING_ARRAYS(iges_geometry_reader.GetVKnotSequence(),
// kTestFixture->GetVKnotSequence(), 0.001);
//}
};
