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
#include <vector>

#include <Teuchos_Comm.hpp>
#include <Teuchos_ParameterList.hpp>

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

    const auto GetKnotSequence() { return knot_sequence_; }
    const auto GetUKnotSequence() { return u_knot_sequence_; }
    const auto GetVKnotSequence() { return v_knot_sequence_; }

   private:
    //! Private to prohibit copying.
    Geometry(const Geometry &);

    Geometry &operator=(const Geometry &);

   protected:
    void initialize();
    types::TadigaRealVector knot_sequence_;
    types::TadigaRealVector u_knot_sequence_;
    types::TadigaRealVector v_knot_sequence_;

    //  Communicator
    const Teuchos::RCP<const Teuchos::Comm<int>> &kComm_;

    types::TadigaUnsignedInt number_of_iges_entities_;
    types::TadigaUnsignedInt number_of_transferred_entities_;
    types::TadigaUnsignedInt number_of_u_knots_;
    types::TadigaUnsignedInt number_of_v_knots_;
    types::TadigaUnsignedInt number_of_knots_;
    types::TadigaUnsignedInt length_;
    types::TadigaUnsignedInt u_length_;
    types::TadigaUnsignedInt v_length_;
    TopoDS_Shape transferred_occt_shape_;
    TopoDS_Shape nurbs_converted_shape_;
};
};

#endif  // TADIGA_GEOMETRY_H
