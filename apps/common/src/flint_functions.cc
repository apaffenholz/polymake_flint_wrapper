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


#include <polymake/client.h>
#include <polymake/Matrix.h>
#include <polymake/Integer.h>
#include <polymake/Rational.h>

#include <polymake/common/flint_functions.h>
#include <polymake/common/FlintMatrix.h>


namespace polymake { 

  namespace common {

    Matrix<Integer> HermiteNormalForm(const Matrix<Integer> & M ) {

      FlintMatrix FM(M);
     
      return FM.hermite_normal_form().get_matrix();
    }
   

    Matrix<Integer> LLL(const Matrix<Integer> & M, Rational delta, Rational eta ) {


      FlintMatrix FM(M);

      // meaning of eta is unclear even after consulting the paper...
      FlintMatrix LLL = FM.lll_storjohann(delta,eta);

      return LLL.get_matrix();
    }

    UserFunction4perl(" ", &HermiteNormalForm, "HerminteNormalForm( $ )");

    UserFunction4perl(" ", &LLL, "LLL( $; $=1/4, $=1 )");

  }
}
