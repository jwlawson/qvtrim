/**
 * cycle_trimmer.h
 */
#pragma once

#include "trimmer.h"

namespace qvtrim {

class CycleTrimmer : public Trimmer {

	public:
		CycleTrimmer(IStream& in, OStream& out);
		CycleTrimmer(IPtr in, OPtr out)
			: Trimmer(in, out) {}

		virtual void run();

};
}
