/**
 * sinksource_trimmer.cc
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
#include "sinksource_trimmer.h"

namespace qvtrim {
bool SinkSourceTrimmer::valid(MatrixPtr p) {
	if(_set.find(p) == _set.end()) {
		Loader l(p, {});
		while(l.has_next()) {
			_set.insert(l.next());
		}
		return true;
	}
	return false;
}
}

