/**
 * class_trimmer.cc
 * Copyright 2014-2015 John Lawson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

