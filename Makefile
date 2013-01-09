#
# Platform Independent
# Bitmap Image Reader Writer Library
# By Arash Partow - 2002
#
# URL: http://www.partow.net
#
# Copyright Notice:
# Free use of this library is permitted under the
# guidelines and in accordance with the most
# current version of the Common Public License.
# http://www.opensource.org/licenses/cpl1.0.php
#

COMPILER      = -c++
OPTIONS       = -ansi -pedantic-errors -Wall -Wall -Werror -Wextra -o
LINKER_OPT    = -L/usr/lib -lstdc++

all: bitmap_test

bitmap_test: bitmap_test.cpp bitmap_image.hpp
	$(COMPILER) $(OPTIONS) bitmap_test bitmap_test.cpp $(LINKER_OPT)

clean:
	rm -f core *.o *.bak *stackdump *~
  
#
# The End !
#
