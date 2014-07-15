/**
 * matrix_trimmer.h
 */
#include "matrix_trimmer.h"

#include "qv/equiv_quiver_matrix.h"

namespace qvtrim {

template<class M>
void MatrixTrimmer<M>::run() {
	while(iter_.has_next()) {
		MatrixPtr p = iter_.next();
		if(valid(p)) {
			*out_ << *p << std::endl;
		}
	}
}

template class MatrixTrimmer<cluster::IntMatrix>;
template class MatrixTrimmer<cluster::EquivQuiverMatrix>;
}

