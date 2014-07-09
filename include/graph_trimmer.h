/**
 * graph_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class GraphTrimmer : public Trimmer {

	public:
		GraphTrimmer(IStream& in, OStream& out);
		GraphTrimmer(IPtr in, OPtr out) : Trimmer(in, out) {}

		virtual void run();

};
}
