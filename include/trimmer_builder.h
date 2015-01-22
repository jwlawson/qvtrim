/**
 * trimmer_builder.h
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
 * Builder for all Trimmers. TrimmerBuilder::function() sets which of the
 * trimmers to build, and the various options are set using the builder
 * functions.
 */
#pragma once

#include "function.h"
#include "trimmer.h"

#include <string>

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
		void matrix(const std::string& mat);

		std::shared_ptr<Trimmer> build();

	private:
		IPtr in_;
		OPtr out_;
		enum Function func_ = UNSET;
		int size_ = -1;
		std::string matrix_;

		bool validate();

		std::shared_ptr<Trimmer> trimmer();
		std::shared_ptr<Trimmer> matrix_trimmer();

		struct NullDeleter {
			void operator()(const void *const) const {}
		};

};
}
