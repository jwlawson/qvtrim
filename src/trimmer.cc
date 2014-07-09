/**
 * trimmer.cc
 */
#include "trimmer.h"

namespace qvtrim {

Trimmer::Trimmer(IStream& in, OStream& out)
  :	in_(&in, NullDeleter()),
		out_(&out, NullDeleter()) {}

}
