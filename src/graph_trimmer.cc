/**
 * graph_trimmer.cc
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
#include "graph_trimmer.h"

namespace qvtrim {
bool GraphTrimmer::valid(MatrixPtr p) {
	GPtr g = std::make_shared<Graph>(*p);
	EGPtr e = std::make_shared<EquivGraph>(*p);
	return m_set_.emplace(p).second
			&& g_set_.insert(g).second
			&& eg_set_.insert(e).second;
}
}

