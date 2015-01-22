/**
 * size_matrix_trimmer.cc
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
#include "size_matrix_trimmer.h"

namespace qvtrim {

SizeMatrixTrimmer::SizeMatrixTrimmer(MatrixPtr& matrix, IPtr& in,
		OPtr& out)
	: MatrixTrimmer(matrix, in, out),
		rows_(matrix->num_rows()),
		cols_(matrix->num_cols()) {}

bool SizeMatrixTrimmer::valid(const MatrixPtr& matrix) const {
	return matrix->num_rows() == rows_ && matrix->num_cols() == cols_;
}

}

