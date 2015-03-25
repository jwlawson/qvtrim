# qvtrim

Removes duplicate matrices from an input.

### Usage

```
qvtrim -ceglz [-s size] [-m matrix] [-i input] [-o output]
  -c Only show matrices with different oriented cycles 
  -e Only show matrices which are equivalent up to permutation
  -g Only show matrices with different underlying graphs
  -k Only show matrices which are mutation-infinite
  -l Only show matrices from different mutation classes
  -s Only show matrices of the specified size
  -z Only show matrices which do not contain an all zero row
  -m Specify the matrix to compare against
  -i Specify input file of matrices, if absent stdin is used.
  -o Specify output or use stdout
```

The `cegklsz` options specify how matrixes are trimmed from the input.

 * `-c` Check the oriented cycles in the quiver. If a quiver contains the same
	 combination of cycles as one previously seen then it will not be output.
 * `-e` Check whether the quiver is a permutation of one already seen.
 * `-g` Check whether the quiver has a different underlying graph. The graph is
	 the one obtained by forgetting the orientations on the edges.
 * `-k` Check whether the quiver is mutation-infinite.
 * `-l` Check whether the quiver belongs to a different mutation class. This
	 option will lead to a single representative of each class being output.
 * `-s size` Check whether the quiver has `size` vertices.
 * `-z` Check whether the matrix contains a zero row and only output it if it
	 does *not*. This ensure that the output only contains matrices without zero
	 rows.

The `-m` option specifies a matrix `M` to compare the input against. This must be
used in conjunction with one of the above options, which get altered slightly to
the following.

 * `-c` Only output the quivers with the same cycles as `M`.
 * `-e` Only output quivers which are permutations of `M`.
 * `-g` Only output quivers which have the same underlying graph as `M`.
 * `-l` Only output quivers mutation-equivalent to `M`.

The input option specifies a file to read the matrices from. If left blank then
stdin is used.

The output option specifies a file to write the output to. If left blank then
stdout is used.

##### Examples

```
qvtrim -z -i in_file
```
Read all matrices from `in_file` and write all which do not contain zero rows to
stdout.

```
qvtrim -e -m "{ { 0 1 0 } { -1 0 1 } { 0 -1 0 } }"
```
Read matrices from stdin and output to stdout only those which are permutations
of the specified quiver with 3 vertices.

```
qvtrim -s 10 -i in_file -o out_file
```
Read all matrices from `in_file` and output to `out_file` only those with 10
rows and columns.

### Build

Run `make` to compile `qvtrim`.

##### Dependencies

`qvtrim` requires the following libraries and their headers to be
installed and accessible by the compiler:

 * [libqv][libqv site]

The Makefile can be modified to include the install locations of these
libraries, by changing the `INCLUDES` and `LFLAGS` variables.

### License

```
   Copyright 2014-2015 John Lawson

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
```

[libqv site]: http://github.com/jwlawson/qv
