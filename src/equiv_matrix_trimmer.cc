/**
 * equiv_matrix_trimmer.cc
 */
#include "equiv_matrix_trimmer.h"

namespace qvtrim {

EquivMatrixTrimmer::EquivMatrixTrimmer(MatrixPtr& matrix, IPtr& in,
		OPtr& out)
	: MatrixTrimmer(matrix, in, out) {}

bool EquivMatrixTrimmer::valid(const MatrixPtr& matrix) const {
	return matrix_->equals(*matrix);
}

}

