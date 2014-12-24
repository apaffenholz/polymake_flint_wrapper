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

	UserFunction4perl("", &test_flint_conversion, "test_flint_conversion( $ )");

    UserFunction4perl(	"# @category Linear Algebra\n"
    							"# Computes the unique (row) __Hermite normal form__ of //A//."
    							"# @param Matrix<Integer> A\n"
    							"# @return Matrix<Integer>",
    							&HermiteNormalForm, "hermite_normal_form( $ )");


    UserFunction4perl(	"# @category Linear Algebra\n"
    							"# Takes a basis of a lattice (as the rows of //A//) and returns an (//delta//, //eta//)-reduced basis of the same lattice."
    							"#"
    							"# Uses a modified version of the LLL-algorithm, which has better complexity in terms of the lattice dimension, introduced by Storjohann. See"
    							"\tA. Storjohann Faster Algorithms for Integer Lattice Basis Reduction. Technical Report 249. Zurich, Switzerland: Department Informatik, ETH. July 30, 1996."
    							"# @param Matrix<Integer> A\n"
    							"# @param Rational delta optional, default: 1/4 TODO: WTF?\n"
    							"# @param Rational eta optional, default: 1 TODO: WTF?\n"
    							"# @return Matrix<Integer>", &LLL, "lll( $; $=1/4, $=1 )");

  }
}
