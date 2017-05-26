// Copyright 2017 John T. Foster

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//    http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include <array>
#include <vector>

namespace tadiga {
namespace types {

// Standard Tadiga types
typedef int TadigaInt;
typedef std::size_t TadigaUnsignedInt;
typedef double TadigaReal;

// Templated types from standard library;
template <typename T>
using TadigaVector = std::vector<T>;

template <typename T, TadigaUnsignedInt S>
using TadigaArray = std::array<T, S>;

template <TadigaUnsignedInt S>
using TadigaIntArray = TadigaArray<TadigaInt, S>;

template <TadigaUnsignedInt S>
using TadigaRealArray = TadigaArray<TadigaReal, S>;

typedef TadigaVector<TadigaInt> TadigaIntVector;
typedef TadigaVector<TadigaReal> TadigaRealVector;
}
}
