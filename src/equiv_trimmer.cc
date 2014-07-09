/**
 * equiv_trimmer.cc
 */
#include "equiv_trimmer.h"

#include <unordered_set>

#include "qv/equiv_quiver_matrix.h"
#include "qv/equiv_underlying_graph.h"
#include "qv/oriented_cycle_info.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

EquivTrimmer::EquivTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void EquivTrimmer::run() {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::StreamIterator<Matrix> Iter;

	std::unordered_set<MatrixPtr> set;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr m = iter.next();
		if(set.insert(m).second) {
			/* Matrix successfully inserted so has not been seen before. */
			*out_ << *m << std::endl;
		}
	}
}

}

