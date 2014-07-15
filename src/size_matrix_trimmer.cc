/**
 * size_matrix_trimmer.cc
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

