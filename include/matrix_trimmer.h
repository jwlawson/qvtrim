/**
 * matrix_trimmer.h
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
 * Trimmer which matches those matrices which share specific properties with a
 * provided comparison matrix.
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

template<class Matrix>
class MatrixTrimmer : public __Trimmer<Matrix> {
	protected:
		typedef std::istream IStream;
		typedef std::ostream OStream;
		typedef std::shared_ptr<IStream> IPtr;
		typedef std::shared_ptr<OStream> OPtr;
		typedef typename std::shared_ptr<Matrix> MatrixPtr;
		MatrixTrimmer(MatrixPtr& matrix, IPtr& in, OPtr& out)
			:	__Trimmer<Matrix>(in, out),
				matrix_(matrix) {}
		virtual ~MatrixTrimmer() = default;

		MatrixPtr matrix_;
		virtual bool valid(MatrixPtr mat) = 0;
};
}
	
