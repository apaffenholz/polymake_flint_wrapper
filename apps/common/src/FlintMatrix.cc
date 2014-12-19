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
#include <polymake/common/FlintMatrix.h>
#include "flint/fmpz.h"
#include "flint/fmpz_mat.h"


namespace polymake { 
  namespace common {
    
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
	  fmpz_set_ui(fmpz_mat_entry(M,i,j), convert_to<long>(A(i,j)));
      
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
    
    
  }
  
}

