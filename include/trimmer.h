/**
 * trimmer.h
 */
#pragma once

#include <memory>
#include <string>

namespace qvtrim {

class Trimmer {
	protected:
		typedef std::istream IStream;
		typedef std::ostream OStream;
		typedef std::shared_ptr<IStream> IPtr;
		typedef std::shared_ptr<OStream> OPtr;

	public:
		virtual void run() = 0;

	protected:
		Trimmer(IStream& in, OStream& out)
			:	in_(&in, NullDeleter()),
				out_(&out, NullDeleter()) {}
		Trimmer(IPtr in, OPtr out)
			: in_(in), out_(out) {}

		IPtr in_;
		OPtr out_;

	private:
		/**
		 * Deleter for the StreamPtr. As the pointer is always made from
		 * references to input streams they should not be deleted after the
		 * shared_ptr goes out of scope. This deleter actually does nothing when
		 * the shared_ptr determines that it should be deleted.
		 */
		struct NullDeleter {
			void operator()(const void *const) const {}
		};
};
}

