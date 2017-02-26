// Copyright 2017 John T. Foster, Katy L. Hanson

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

#include "IGESControl_Reader.hxx"
#include "TColStd_HSequenceOfTransient.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"
#include "tadiga_IGES_geometry.h"

namespace tadiga_test {

class TestSetup {
   public:
    TestSetup() {}

    ~TestSetup() { fclose(temp_file_); };

    auto GetYamlFileName() { return std::to_string(fileno(temp_file_)); }

    auto GetComm() { return kComm_; }

   private:
    // Get communicator from test runner
    Teuchos::RCP<const Teuchos::Comm<int>> kComm_ =
        Tpetra::DefaultPlatform::getDefaultPlatform().getComm();

    // Create temporary file
    std::FILE* temp_file_ = std::tmpfile();
};

TEUCHOS_UNIT_TEST(IGES_Geometry, number_of_faces) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);

    TEST_EQUALITY(iges_geometry_reader.GetNumberFaces(),
                  iges_geometry_reader.GetNumberIgesFaces());
}

TEUCHOS_UNIT_TEST(IGES_Geometry, number_of_lines) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);

    TEST_EQUALITY(iges_geometry_reader.GetNumberLines(),
                  iges_geometry_reader.GetNumberIgesLines());
}

TEUCHOS_UNIT_TEST(IGES_Geometry, number_of_tab_cylinders) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);

    TEST_EQUALITY(iges_geometry_reader.GetNumberTabulatedCylinders(),
                  iges_geometry_reader.GetNumberIgesTabCylinders());
}

TEUCHOS_UNIT_TEST(IGES_Geometry, number_of_comp_curves) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);

    TEST_EQUALITY(iges_geometry_reader.GetNumberCompositeCurves(),
                  iges_geometry_reader.GetNumberIgesCompCurves());
}

TEUCHOS_UNIT_TEST(IGES_Geometry, number_of_curve_on_surface) {
    const auto kTestFixture = Teuchos::rcp(new TestSetup());

    auto parameters = Teuchos::rcp(new Teuchos::ParameterList());
    auto geometry_parameters =
        Teuchos::rcpFromRef(parameters->sublist("Geometry"));

    geometry_parameters->set("Type", "IGES");
    geometry_parameters->set("File Name", "test.igs");

    tadiga::IgesGeometry iges_geometry_reader(kTestFixture->GetComm(),
                                              geometry_parameters);
    TEST_EQUALITY(iges_geometry_reader.GetNumberCurveOnSurface(),
                  iges_geometry_reader.GetNumberIgesCurveOnSurface());
}
}
