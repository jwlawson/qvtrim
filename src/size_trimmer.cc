/**
 * size_trimmer.cc
 */
#include "size_trimmer.h"

#include "qv/int_matrix.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

SizeTrimmer::SizeTrimmer(int size, IStream& in, OStream& out)
	: Trimmer(in, out),
		size_(size) {}

void SizeTrimmer::run() {
	typedef cluster::IntMatrix Matrix;
	typedef cluster::StreamIterator<Matrix> Iter;
	typedef std::shared_ptr<Matrix> MatrixPtr;

	Iter iter(*in_);

	while(iter.has_next()) {
		MatrixPtr p = iter.next();
		if(p->num_rows() == size_ && p->num_cols() == size_) {
			*out_ << *p << std::endl;
		}
	}
}

}

