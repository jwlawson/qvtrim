/**
 * class_matrix_trimmer.h
 *
 * Trimmer which only outputs matrices which are from the same mutation class as
 * the provided matrix.
 */
#pragma once
#include "matrix_trimmer.h"

#include "qv/equiv_quiver_matrix.h"
#include "qv/mutation_class.h"

namespace qvtrim {

class ClassMatrixTrimmer : public MatrixTrimmer<cluster::EquivQuiverMatrix> {

	private:
		typedef cluster::MutationClass Class;

	public:
		ClassMatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out);

	protected:
		virtual bool valid(const MatrixPtr& mat) const final;

	private:
		Class class_;
};

}

