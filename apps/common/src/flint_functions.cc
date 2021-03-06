/****************************************************************************
  Copyright (c) 2014-2015
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
    namespace flint {

      Matrix<Integer> HermiteNormalForm(const Matrix<Integer> & M ) {
  
        FlintMatrix FM(T(M));
    
        return T(FM.hermite_normal_form().get_matrix());
     }
  
      perl::ListReturn HermiteNormalForm_WithTransform(const Matrix<Integer> & M ) {

        FlintMatrix FM(T(M));
	const Array<FlintMatrix> HNF_Flint = FM.hermite_normal_form_with_transform();

	perl::ListReturn HNF;
	HNF << T(HNF_Flint[0].get_matrix()) << T(HNF_Flint[1].get_matrix());
	return HNF;
     }
      
      Matrix<Integer> SmithNormalForm(const Matrix<Integer> & M ) {
    
        FlintMatrix FM(T(M));
    
        return T(FM.smith_normal_form().get_matrix());
      }
      
      
      
      Matrix<Integer> LLL(const Matrix<Integer> & M, Rational delta, Rational eta ) {
    
        FlintMatrix FM(M);
    
        // meaning of eta is unclear even after consulting the paper...
        FlintMatrix LLL = FM.lll_storjohann(delta,eta);
    
        return LLL.get_matrix();
      }
    }
      
    UserFunction4perl(  "# @category Linear Algebra\n"
      "# Computes the unique (column) __Hermite normal form__ of //A//."
      "# @param Matrix<Integer> A\n"
      "# @return Matrix<Integer>",
      &flint::HermiteNormalForm, "hermite_normal_form_flint( $ )");

    UserFunction4perl(  "# @category Linear Algebra\n"
      "# Computes the unique (column) __Hermite normal form__ of //A//."
      "# @param Matrix<Integer> A\n"
      "# @return perl::ListReturn (Matrix N, Matrix R) such that M*R=N, R quadratic unimodular.\n",
      &flint::HermiteNormalForm_WithTransform, "hermite_normal_form_with_transform_flint( $ )");
    
    UserFunction4perl(  "# @category Linear Algebra\n"
      "# Computes the unique __Smith normal form__ of //A//."
      "# Note that the flint function __does not__ return the companion matrices."
      "# @param Matrix<Integer> A\n"
      "# @return Matrix<Integer>",
      &flint::SmithNormalForm, "smith_normal_form_flint( $ )");
    
    
    UserFunction4perl(  "# @category Linear Algebra\n"
      "# Takes a basis of a lattice (as the rows of //A//) and returns an (//delta//, //eta//)-reduced basis of the same lattice."
      "#"
      "# Uses a modified version of the LLL-algorithm, which has better complexity in terms of the lattice dimension, introduced by Storjohann. See"
      "\tA. Storjohann Faster Algorithms for Integer Lattice Basis Reduction. Technical Report 249. Zurich, Switzerland: Department Informatik, ETH. July 30, 1996."
      "# @param Matrix<Integer> A\n"
      "# @param Rational delta optional, default: 1/4 TODO: WTF?\n"
      "# @param Rational eta optional, default: 1 TODO: WTF?\n"
      "# @return Matrix<Integer>", &flint::LLL, "lll_flint( $; $=1/4, $=1 )");
        
    
  }
}
