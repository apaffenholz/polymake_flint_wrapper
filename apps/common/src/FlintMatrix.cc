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
#include <polymake/Array.h>
#include <polymake/Integer.h>
#include <polymake/Rational.h>
#include <polymake/common/FlintMatrix.h>
#include "flint/fmpz.h"
#include "flint/fmpq.h"
#include "flint/fmpz_mat.h"


namespace polymake { 
  namespace common {
    namespace flint {
      
      FlintMatrix::FlintMatrix( const fmpz_mat_t A ) {

        rows = fmpz_mat_nrows(A);
        cols = fmpz_mat_ncols(A);
        fmpz_mat_init_set(M,A);
      }
      
      FlintMatrix::FlintMatrix(const Matrix<Integer> & A) {
	
        rows = A.rows();
        cols = A.cols();
	
        fmpz_mat_init(M, rows, cols);
	
        for (long i = 0; i < rows; ++i)
          for (long j = 0; j < cols; ++j)
            fmpz_set_mpz(fmpz_mat_entry(M,i,j), A(i,j).get_rep());

      }
      
      const Matrix<Integer> FlintMatrix::get_matrix() const {
	
        Matrix<Integer> A(rows,cols);
	
        for (long i=0; i < rows; ++i) {
          for (long j=0; j < cols; ++j) {
            A(i,j) = convert_to<Integer>(*fmpz_mat_entry(M,i,j));
          }
	      }
	
        return A;
      }
      
      
      const FlintMatrix FlintMatrix::hermite_normal_form() const {
	
        fmpz_mat_t H;
        fmpz_mat_init(H, rows, cols);
        
        fmpz_mat_hnf(H,M);
        
        return FlintMatrix(H);
      }

      const Array<FlintMatrix> FlintMatrix::hermite_normal_form_with_transform() const {
	
        fmpz_mat_t H;
        fmpz_mat_init(H, rows, cols);
        fmpz_mat_t U;
        fmpz_mat_init(U, rows, rows);
        
        fmpz_mat_hnf_transform(H,U,M);

	Array<FlintMatrix> HNF(2);
	HNF[0] = FlintMatrix(H);
	HNF[1] = FlintMatrix(U);
        
        return HNF;
      }

      
      const FlintMatrix FlintMatrix::smith_normal_form() const {
	
        fmpz_mat_t S;
        fmpz_mat_init(S, rows, cols);
        
        fmpz_mat_snf(S,M);
        
        return FlintMatrix(S);
      }
      
      
      
      const FlintMatrix FlintMatrix::lll_storjohann(const Rational delta , const Rational eta) {
	
        fmpq_t d;
        fmpq_t e;
        fmpq_init(d);
        fmpq_init(e);
        
        fmpq_set_mpq(d, delta.get_rep());
        fmpq_set_mpq(e, eta.get_rep());
        
        fmpz_mat_t H;
        fmpz_mat_init_set(H, M);
        fmpz_mat_lll_storjohann(H, d, e);
        
        fmpq_clear(d);
        fmpq_clear(e);
        
        return FlintMatrix(H);
      }
      
    }  
  }
}
  
