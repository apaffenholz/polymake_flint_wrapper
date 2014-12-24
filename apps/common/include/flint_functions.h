/****************************************************************************
  Copyright (c) 2014
  Silke Horn, Andreas Paffenholz (Technische Universitaet Darmstadt, Germany)
  http://www.polymake.org

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2, or (at your option) any
  later version: http://www.gnu.org/licenses/gpl.txt.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
****************************************************************************/


#ifndef POLYMAKE_FLINT_FUNCTIONS_H
#define POLYMAKE_FLINT_FUNCTIONS_H

#include <polymake/client.h>
#include <polymake/Matrix.h>
#include <polymake/Integer.h>


namespace polymake { 

  namespace common {

    Matrix<Integer> HermiteNormalForm(const Matrix<Integer> & M );
    Matrix<Integer> SmithNormalForm(const Matrix<Integer> & M );
    
  }

}

#endif
