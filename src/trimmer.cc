/**
 * trimmer.h
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
/**
 * Abstract class that all trimmers extend. Contains the input and output
 * streams, so subclasses just implement the Trimmer::valid() method.
 */
#include "trimmer.h"

#include "qv/equiv_quiver_matrix.h"

namespace qvtrim {
template<class Matrix>
void __Trimmer<Matrix>::run() {
	while(iter_.has_next()) {
		MatrixPtr p = iter_.next();
		if(valid(p)) {
			*out_ << *p << std::endl;
		}
	}
}
template class __Trimmer<cluster::IntMatrix>;
template class __Trimmer<cluster::EquivQuiverMatrix>;
}
