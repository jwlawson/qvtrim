/**
 * zero_trimmer.cc
 */
#include "zero_trimmer.h"

#include "qv/int_matrix.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

ZeroTrimmer::ZeroTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void ZeroTrimmer::run() {
	typedef cluster::IntMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::StreamIterator<Matrix> Iter;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr p = iter.next();
		if(p->zero_row() == -1) {
			*out_ << *p << std::endl;
		}
	}
}

}

