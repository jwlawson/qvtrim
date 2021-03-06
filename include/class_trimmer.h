/**
 * class_trimmer.h
 * Copyright 2014-2015 John Lawson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Trims matrices by only outputting those in a mutation-class not seen before.
 */
#pragma once

#include "trimmer.h"

#include "qv/equiv_quiver_matrix.h"
#include "qv/mass_finite_check.h"

namespace qvtrim {
class ClassTrimmer : public __Trimmer<cluster::EquivQuiverMatrix> {

	public:
		ClassTrimmer(IStream& in, OStream& out);
		ClassTrimmer(IPtr in, OPtr out)	: __Trimmer(in, out) {}
		virtual ~ClassTrimmer() = default;

	private:
		typedef cluster::MassFiniteCheck Check;

		Check chk_;

		virtual bool valid(MatrixPtr) final;
};
}

