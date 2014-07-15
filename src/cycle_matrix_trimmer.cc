/**
 * cycle_matrix_trimmer.cc
 */
#include "cycle_matrix_trimmer.h"

namespace qvtrim {

CycleMatrixTrimmer::CycleMatrixTrimmer(MatrixPtr& matrix, IPtr& in,
		OPtr& out)
	: MatrixTrimmer(matrix, in, out),
		cycle_(*matrix) {}

bool CycleMatrixTrimmer::valid(const MatrixPtr& matrix) const {
	Cycle g(*matrix);
	return cycle_.equals(g);
}

}

