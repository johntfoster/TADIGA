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
#ifndef TADIGA_GEOMETRY_H
#define TADIGA_GEOMETRY_H
#include <Teuchos_Comm.hpp>
#include <Teuchos_ParameterList.hpp>
#include <array>

#include "TColStd_Array1OfReal.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Edge.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "TopoDS_Vertex.hxx"
#include "TopoDS_Wire.hxx"

#include "tadiga_types.h"

namespace tadiga {

class Geometry {
   public:
    Geometry(const Teuchos::RCP<const Teuchos::Comm<int>> &kComm,
             const Teuchos::RCP<Teuchos::ParameterList> &kGeometryParameters);

    auto GetNumberIges_Entities() { return number_of_iges_entities_; }

    auto GetNumberTransferred_Entities() {
        return number_of_transferred_entities_;
    }

    auto GetKnotSequenceLength() { return length_; }
    auto GetNumberKnots() { return number_of_knots_; }
    auto GetNumberUKnots() { return number_of_u_knots_; }
    auto GetNumberVKnots() { return number_of_v_knots_; }
    auto GetUKnotSequenceLength() { return u_length_; }
    auto GetVKnotSequenceLength() { return v_length_; }

    const auto &GetKnotSequence() { return knot_sequence_; }
    const auto &GetUKnotSequence() { return u_knot_sequence_; }
    const auto &GetVKnotSequence() { return v_knot_sequence_; }

   private:
    //! Private to prohibit copying.
    Geometry(const Geometry &);

    Geometry &operator=(const Geometry &);

   protected:
    void initialize();
    std::array<int, 2> knot_sequence_;
    std::array<int, 4> u_knot_sequence_;
    std::array<int, 4> v_knot_sequence_;

    //  Communicator
    const Teuchos::RCP<const Teuchos::Comm<int>> &kComm_;

    types::TadigaInt number_of_iges_entities_;
    types::TadigaInt number_of_transferred_entities_;
    types::TadigaInt number_of_u_knots_;
    types::TadigaInt number_of_v_knots_;
    types::TadigaInt number_of_knots_;
    types::TadigaInt length_;
    types::TadigaInt u_length_;
    types::TadigaInt v_length_;
    TopoDS_Shape transferred_occt_shape_;
    TopoDS_Shape nurbs_converted_shape_;
};
};

#endif  // TADIGA_GEOMETRY_H
