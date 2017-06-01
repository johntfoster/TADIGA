
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
#include "tadiga_opencascade_utilities.h"

tadiga::Geometry::Geometry(
    const Teuchos::RCP<const Teuchos::Comm<int>> &kComm,
    const Teuchos::RCP<Teuchos::ParameterList> &kGeometryParameters)
    : kComm_(kComm){};

void tadiga::Geometry::initialize() {
    // Convert transferred OCCT Shapes to NURBS & retrieve
    auto kNurbsConverter = BRepBuilderAPI_NurbsConvert();

    kNurbsConverter.Perform(transferred_occt_shape_);
    nurbs_converted_shape_ =
        kNurbsConverter.ModifiedShape(transferred_occt_shape_);

    tadiga::types::TadigaUnsignedInt edge_counter = 1;

    // Look for ToopDS_Edges in  nurbs_converted_shape_
    auto edge_explorer = TopExp_Explorer(nurbs_converted_shape_, TopAbs_EDGE);
    for (auto const &edge = edge_explorer.Current(); edge_explorer.More();
         edge_explorer.Next(), edge_counter++) {
        const auto extracted_edge = TopoDS::Edge(edge);

        const auto brep_adaptor_curve = BRepAdaptor_Curve(extracted_edge);

        auto extracted_bspline_curve = brep_adaptor_curve.BSpline();

        number_of_knots_ = extracted_bspline_curve->NbKnots();

        auto knot_sequence = TColStd_Array1OfReal(1, number_of_knots_);
        extracted_bspline_curve->Knots(knot_sequence);

        length_ = knot_sequence.Length();

        std::cout << "Length: " << length_ << endl;

        // Print  knot vector to integer array
        std::cout << "Edge #" << edge_counter << " Knot Sequence:";

        knot_sequence_.clear();
        OpencascadeArrayToVector(knot_sequence, knot_sequence_);

        for (const auto &knot_value : knot_sequence_) {
            std::cout << " " << knot_value;
        }
        std::cout << endl;
    }

    // Look for TopoDS_Faces in nurbs_converted_shape
    tadiga::types::TadigaUnsignedInt face_counter = 1;

    // Reset explorer on face now
    auto face_explorer = TopExp_Explorer(nurbs_converted_shape_, TopAbs_FACE);
    for (; face_explorer.More(); face_explorer.Next(), ++face_counter) {
        const auto extracted_face = TopoDS::Face(face_explorer.Current());

        const auto brep_adaptor_surface = BRepAdaptor_Surface(extracted_face);

        auto extracted_bspline_surface = brep_adaptor_surface.BSpline();

        number_of_u_knots_ = extracted_bspline_surface->NbUKnots();

        auto u_knot_sequence = TColStd_Array1OfReal(1, number_of_u_knots_);
        extracted_bspline_surface->UKnots(u_knot_sequence);

        u_length_ = u_knot_sequence.Length();

        std::cout << "U Length: " << u_length_ << std::endl;
        std::cout << "Face #" << face_counter << " U Knot Sequence:";

        u_knot_sequence_.clear();
        OpencascadeArrayToVector(u_knot_sequence, u_knot_sequence_);

        for (const auto &knot_value : u_knot_sequence_) {
            std::cout << " " << knot_value;
        }
        std::cout << std::endl;

        number_of_v_knots_ = extracted_bspline_surface->NbVKnots();

        auto v_knot_sequence = TColStd_Array1OfReal(0, number_of_v_knots_);
        extracted_bspline_surface->VKnots(v_knot_sequence);

        v_length_ = v_knot_sequence.Length();

        std::cout << "V Length: " << v_length_ << endl;
        std::cout << "Face #" << face_counter << " V Knot Sequence:";

        v_knot_sequence_.clear();
        OpencascadeArrayToVector(v_knot_sequence, v_knot_sequence_);

        for (const auto &knot_value : v_knot_sequence_) {
            std::cout << " " << knot_value;
        }
        std::cout << std::endl;
    }
};
