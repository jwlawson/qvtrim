/**
 * trimmer_builder.h
 */
#pragma once

#include "function.h"
#include "trimmer.h"

namespace qvtrim {

class TrimmerBuilder {
	private:
		typedef std::shared_ptr<std::istream> IPtr;
		typedef std::shared_ptr<std::ostream> OPtr;

	public:
		void input_stream(std::istream& in);
		void output_stream(std::ostream& out);
		void function(enum Function func);
		void size(int size);

		std::shared_ptr<Trimmer> build();

	private:
		IPtr in_;
		OPtr out_;
		enum Function func_ = UNSET;
		int size_ = -1;

		bool validate();

		struct NullDeleter {
			void operator()(const void *const) const {}
		};

};
}
