/**
 * size_trimmer.cc
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

