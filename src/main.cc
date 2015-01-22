/*
 * main.cc
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
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_set>

#include "function.h"
#include "trimmer_builder.h"

void usage() {
	std::cout << "qvtrim -ceglz [-s size] [-m matrix] [-i input] [-o output]" << std::endl;
	std::cout << "  -c Only show matrices with different oriented cycles " << std::endl;
	std::cout << "  -e Only show matrices which are equivalent up to permutation" << std::endl;
	std::cout << "  -g Only show matrices with different underlying graphs" << std::endl;
	std::cout << "  -l Only show matrices from different mutation classes" << std::endl;
	std::cout << "  -s Only show matrices of the specified size" << std::endl;
	std::cout << "  -z Only show matrices which do not contain an all zero row" << std::endl;
	std::cout << "  -m Specify the matrix to compare against" << std::endl;
	std::cout << "  -i Specify input file of matrices, if absent stdin is used." << std::endl;
	std::cout << "  -o Specify output or use stdout" << std::endl;
}

int main(int argc, char *argv[]) {
	enum qvtrim::Function func = qvtrim::UNSET;
	std::string ifile;
	std::string ofile;
	std::string matrix;
	int c;
	int size = -1;

	while ((c = getopt (argc, argv, "cegls::zm:i:o:")) != -1) {
		switch (c){
			case 'c':
				func = qvtrim::CYCLE;
				break;
			case 'e':
				func = qvtrim::EQUIV;
				break;
			case 'g':
				func = qvtrim::GRAPH;
				break;
			case 'l':
				func = qvtrim::CLASS;
				break;
			case 's':
				func = qvtrim::SIZE;
				if(optarg) {
					size = std::atoi(optarg);
				}
				break;
			case 'z':
				func = qvtrim::ZERO;
				break;
			case 'm':
				matrix = optarg;
				break;
			case 'i':
				ifile = optarg;
				break;
			case 'o':
				ofile = optarg;
				break;
			case '?':
				usage();
				return 1;
			default:
				usage();
				return 2;
		}
	}

	if(func == qvtrim::UNSET) {
		usage();
		std::cout << "Specify an option" << std::endl;
		return 0;
	} else {
		qvtrim::TrimmerBuilder builder;

		std::ifstream file_in;
		std::ofstream file_out;

		if(!ifile.empty()) {
			file_in.open(ifile);
			if(!file_in.is_open()) {
				std::cerr << "Error opening file "<< ofile << std::endl;
				return 1;
			}
			builder.input_stream(file_in);
		}

		if(!ofile.empty()){
			file_out.open(ofile);
			if(!file_out.is_open()) {
				std::cerr << "Error opening file "<< ofile << std::endl;
				return 1;
			}
			builder.output_stream(file_out);
		}

		builder.function(func);
		builder.size(size);

		if(!matrix.empty()) {
			builder.matrix(matrix);
		}

		/**
		 * Do the hard work...
		 * Could save the Trimmer as a variable, but it doesn't really matter.
		 */
		builder.build()->run();
		
		if(file_in.is_open()) {
			file_in.close();
		}
		if(file_out.is_open()){
			file_out.close();
		}

	}
}

