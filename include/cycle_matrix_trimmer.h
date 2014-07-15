/**
 * cycle_matrix_trimmer.h
 *
 * Trimmer which only outputs matrices which are the same size as the input
 * matrix.
 */
#pragma once
#include "matrix_trimmer.h"

#include "qv/int_matrix.h"
#include "qv/oriented_cycle_info.h"

namespace qvtrim {

class CycleMatrixTrimmer : public MatrixTrimmer<cluster::IntMatrix> {

	private:
		typedef cluster::OrientedCycleInfo Cycle;

	public:
		CycleMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out);

	protected:
		virtual bool valid(const MatrixPtr& mat) const final;

	private:
		Cycle cycle_;
};

}

