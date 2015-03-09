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
 * streams, so subclasses just implement the Trimmer::run() method.
 */
#pragma once

#include <memory>

#include "qv/stream_iterator.h"

namespace qvtrim {
class Trimmer {
	protected:
		typedef std::istream IStream;
		typedef std::ostream OStream;
		typedef std::shared_ptr<IStream> IPtr;
		typedef std::shared_ptr<OStream> OPtr;

		Trimmer(IStream& in, OStream& out)
			:	in_(&in, NullDeleter()),
				out_(&out, NullDeleter()) {}
		Trimmer(IPtr in, OPtr out)
			: in_(in), out_(out) {}
		virtual ~Trimmer() = default;

		IPtr in_;
		OPtr out_;
	public:
		virtual void run() = 0;
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

template<class Matrix>
class __Trimmer : public Trimmer {
	public:
		virtual void run() final;
	protected:
		typedef typename std::shared_ptr<Matrix> MatrixPtr;
		__Trimmer(IStream& in, OStream& out)
			:	Trimmer(in, out),
				iter_(in) {}
		__Trimmer(IPtr in, OPtr out)
			: Trimmer(in, out), iter_(*in) {}
		virtual ~__Trimmer() = default;

		virtual bool valid(MatrixPtr) = 0;

	private:
		typedef cluster::StreamIterator<Matrix> Iter;
		Iter iter_;
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

