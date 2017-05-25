
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
#include "BRepAdaptor_Curve.hxx"
#include "BRepAdaptor_Surface.hxx"
#include "BRepBuilderAPI_NurbsConvert.hxx"
#include "BRep_Tool.hxx"
#include "BSplCLib.hxx"
#include "Geom_BSplineCurve.hxx"
#include "Geom_BSplineSurface.hxx"
#include "ShapeAnalysis_Edge.hxx"
#include "TColStd_Array1OfReal.hxx"
#include "Teuchos_RCP.hpp"
#include "TopExp_Explorer.hxx"

#include "tadiga_IGES_geometry.h"
#include "tadiga_geometry.h"

tadiga::Geometry::Geometry(
    const Teuchos::RCP<const Teuchos::Comm<int>>& kComm,
    const Teuchos::RCP<Teuchos::ParameterList>& kGeometryParameters)
    : kComm_(kComm){};

void tadiga::Geometry::initialize() {
    // Convert transferred OCCT Shapes to NURBS & retrieve
    const auto kNurbsConverter = Teuchos::rcp(new BRepBuilderAPI_NurbsConvert);

    kNurbsConverter->Perform(transferred_occt_shape_);

    nurbs_converted_shape_ =
        kNurbsConverter->ModifiedShape(transferred_occt_shape_);

    tadiga::types::TadigaUnsignedInt edge_counter = 1;

    // Look for ToopDS_Edges in  nurbs_converted_shape_
    auto shape_explorer = TopExp_Explorer(nurbs_converted_shape_, TopAbs_EDGE);
    for (auto const& shape = shape_explorer.Current(); shape_explorer.More();
         shape_explorer.Next()) {
        const auto extracted_edge = TopoDS::Edge(shape);

        const auto brep_adaptor_curve =
            Teuchos::rcp(new BRepAdaptor_Curve(extracted_edge));

        auto extracted_bspline_curve = brep_adaptor_curve->BSpline();

        number_of_knots_ = extracted_bspline_curve->NbKnots();

        auto knot_sequence = extracted_bspline_curve->Knots();

        length_ = knot_sequence.Length();

        std::cout << "Length: " << length_ << endl;

        // Print  knot vector to integer array
        std::cout << "Edge #" << edge_counter << " Knot Sequence:";

        for (tadiga::types::TadigaUnsignedInt i = 1; i < length_; i += 1) {
            std::cout << " " << knot_sequence.Value(i);
            knot_sequence_[i - 1] = knot_sequence.Value(i);
        }
        std::cout << endl;
        edge_counter++;
    }

    // Look for TopoDS_Faces in nurbs_converted_shape
    tadiga::types::TadigaUnsignedInt face_counter = 1;

    for (shape_explorer.Init(nurbs_converted_shape_, TopAbs_FACE);
         shape_explorer.More(); shape_explorer.Next()) {
        const TopoDS_Face& extracted_face =
            TopoDS::Face(shape_explorer.Current());

        const auto brep_adaptor_surface =
            Teuchos::rcp(new BRepAdaptor_Surface(extracted_face));

        auto extracted_bspline_surface = brep_adaptor_surface->BSpline();

        auto u_knot_sequence = extracted_bspline_surface->UKnotSequence();

        u_length_ = u_knot_sequence.Length();

        std::cout << "U Length: " << u_length_ << endl;
        std::cout << "Face #" << face_counter << " U Knot Sequence:";

        for (int i = 1; i <= u_length_; i = i + 1) {
            std::cout << " " << u_knot_sequence.Value(i);
            u_knot_sequence_[i - 1] = u_knot_sequence.Value(i);
        }
        std::cout << endl;

        auto v_knot_sequence = extracted_bspline_surface->VKnotSequence();

        v_length_ = v_knot_sequence.Length();

        std::cout << "V Length: " << v_length_ << endl;
        std::cout << "Face #" << face_counter << " V Knot Sequence:";

        for (int i = 1; i <= v_length_; i = i + 1) {
            std::cout << " " << v_knot_sequence.Value(i);
            v_knot_sequence_[i - 1] = v_knot_sequence.Value(i);
        }
        std::cout << endl;
        face_counter++;
    }
}
