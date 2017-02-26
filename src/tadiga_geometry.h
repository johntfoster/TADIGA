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
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Wire.hxx>
namespace tadiga {

class Geometry {
   public:
    Geometry(){};

    void LoadBalanceFaceList();

    auto GetNumberFaces() { return nb_face_; }
    auto SetNumberFaces(int number_of_face) {
        nb_face_ = number_of_face;
        return;
    }
    auto GetNumberLines() { return nb_line_; }
    auto SetNumberLines(int number_of_line) {
        nb_line_ = number_of_line;
        return;
    }
    auto GetNumberTabulatedCylinders() { return nb_tabulated_cylinder_; }
    auto SetNumberTabulatedCylinders(int number_of_tabulated_cylinder) {
        nb_tabulated_cylinder_ = number_of_tabulated_cylinder;
        return;
    }
    auto GetNumberCompositeCurves() { return nb_composite_curve_; }
    auto SetNumberCompositeCurves(int number_of_composite_curve) {
        nb_composite_curve_ = number_of_composite_curve;
        return;
    }
    auto GetNumberCurveOnSurface() { return nb_curve_on_surface_; }
    auto SetNumberCurveOnSurface(int number_of_curve_on_surface) {
        nb_curve_on_surface_ = number_of_curve_on_surface;
        return;
    }

    auto GetNumberIgesFaces() { return kIgesFaces_; }
    auto SetNumberIgesFaces(int kIgesFaces) {
        kIgesFaces_ = kIgesFaces;
        return;
    }
    auto GetNumberIgesLines() { return kIgesLines_; }
    auto SetNumberIgesLines(int kIgesLines) {
        kIgesLines_ = kIgesLines;
        return;
    }
    auto GetNumberIgesTabCylinders() { return kIgesTabulatedCylinders_; }
    auto SetNumberIgesTabCylinders(int kIgesTabulatedCylinders) {
        kIgesTabulatedCylinders_ = kIgesTabulatedCylinders;
        ;
        return;
    }
    auto GetNumberIgesCompCurves() { return kIgesCompositeCurves_; }
    auto SetNumberIgesCompCurves(int kIgesCompositeCurves) {
        kIgesCompositeCurves_ = kIgesCompositeCurves;
        return;
    }
    auto GetNumberIgesCurveOnSurface() { return kIgesCurveOnSurface_; }
    auto SetNumberIgesCurveOnSurface(int kIgesCurveOnSurface) {
        kIgesCurveOnSurface_ = kIgesCurveOnSurface;
        return;
    }

   private:
    //! Private to prohibit copying.
    Geometry(const Geometry &);

    Geometry &operator=(const Geometry &);
    int kIgesFaces_;
    int kIgesLines_;
    int kIgesTabulatedCylinders_;
    int kIgesCompositeCurves_;
    int kIgesCurveOnSurface_;
    int kIgesBSplineCurve_;

    int nb_face_;
    int nb_line_;
    int nb_tabulated_cylinder_;
    int nb_composite_curve_;
    int nb_curve_on_surface_;
    int nb_point_;
    int nb_bspline_curve_;

    TopoDS_Edge line_;
    TopoDS_Face face_;
    TopoDS_Face tabulated_cylinder_;
    TopoDS_Wire composite_curve_;
    TopoDS_Wire curve_on_surface_;
};
}

#endif  // TADIGA_GEOMETRY_H
