NOTES:
- This Assignment was completed by Jeremie Izzo (40016103), Gabriel Ribeiro and Michael
  Wilgus (29206388).

- Code is documented with comments.

COMPILATION:
- The commands below will compile individaul drivers corresponding to the
  parts of Assignment 1.

- These compilations were tested on ENCS Lab PCs running linux and run from the
  command line.

- If you have a version of g++ that conforms to c++11 then you can remove
  the -std=c++11 switch

# Driver for part 1
g++ -Wall -std=c++11 Map.cpp City.cpp driver1.cpp House.cpp -o driver1

# Driver for part 2
g++ -Wall -std=c++11 Map.cpp MapLoader.cpp City.cpp House.cpp driver2.cpp -o driver2

# Driver for part 3
g++ -Wall -g -std=c++11 MapLoader.cpp Map.cpp House.cpp City.cpp driver3.cpp -o driver3

# Driver for part 4
g++ -Wall -std=c++11 Player.cpp PowerplantCard.cpp Card.cpp driver4.cpp -o driver4

# Driver for part 5
g++ -Wall -std=c++11 Card.cpp PowerplantCard.cpp SummaryCard.cpp Step3Card.cpp driver5.cpp -o driver5

USAGE:
- To run the resulting binaries from the command line on a unix-like system
  first compile then enter the binary name indicated by the <binaryName> after
  the -o argument in the compilation command (might need ./<binaryName> depending
  on $PATH evironment variable).  This will work on any system that has the g++
  compiler.

- For other systems (and unix-like systems) the source can be imported
  into any IDE and should compile with minimal effort using the IDE's build system
  (but there are too many to document each one). The caveat to the last point is
  that only ONE of the driver files listed below can be included in the project at
  any given time. To ensure successfully compilation, simply comment out the
  entire contents of any drivers NOT being compiled.
