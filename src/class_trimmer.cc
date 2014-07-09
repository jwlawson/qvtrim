/**
 * class_trimmer.cc
 */
#include "class_trimmer.h"

#include "qv/int_matrix.h"
#include "qv/mass_finite_check.h"
#include "qv/stream_iterator.h"

namespace qvtrim {

ClassTrimmer::ClassTrimmer(IStream& in, OStream& out)
	: Trimmer(in, out) {}

void ClassTrimmer::run() {
	typedef cluster::IntMatrix Matrix;
	typedef std::shared_ptr<Matrix> MatrixPtr;
	typedef cluster::StreamIterator<Matrix> Iter;
	typedef cluster::MassFiniteCheck Check;

	Iter iter(*in_);
	Check chk;

	while(iter.has_next()) {
		MatrixPtr p = iter.next();
		chk.is_finite(*p);
		if(chk.last_new_class()) {
			*out_ << *p << std::endl;
		}
	}
}

}

