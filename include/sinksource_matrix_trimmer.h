/**
 * sinksource_matrix_trimmer.h
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
 * Trimmer which only outputs matrices which can be obtained from the initial
 * matrix through a sequence of sink-source mutations.
 */
#pragma once
#include "matrix_trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/move_class_loader.h"

namespace qvtrim {

class SinkSourceMatrixTrimmer : public MatrixTrimmer<cluster::EquivQuiverMatrix> {
	public:
		typedef cluster::MoveClassLoader Loader;
		SinkSourceMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out)
			: MatrixTrimmer(matrix, in, out),
			  class_() {
			Loader::MoveVec vec;
			Loader l( matrix, vec );
			while(l.has_next()) {
				class_.insert(l.next());
			}
		}
		virtual ~SinkSourceMatrixTrimmer() = default;

	protected:
		virtual bool valid(MatrixPtr mat) final;

	private:
		typedef std::unordered_set<MatrixPtr> Class;
		Class class_;
};
}

