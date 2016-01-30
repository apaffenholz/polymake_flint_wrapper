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



#ifndef POLYMAKE_FLINT_MATRIX_H
#define POLYMAKE_FLINT_MATRIX_H

#include <polymake/client.h>
#include <polymake/Matrix.h>
#include <polymake/Array.h>
#include <polymake/Integer.h>
#include "flint/fmpz.h"
#include "flint/fmpz_mat.h"


namespace polymake {
  namespace common {
    namespace flint {
      class FlintMatrix {

	fmpz_mat_t M;
	int rows,cols;

      public:
	FlintMatrix() { rows=0; cols=0; fmpz_mat_init(M, rows, cols); };
	FlintMatrix( const fmpz_mat_t A );
	FlintMatrix(const Matrix<Integer> & A);

	const Matrix<Integer> get_matrix() const;

	const FlintMatrix        hermite_normal_form() const;
	const Array<FlintMatrix> hermite_normal_form_with_transform() const;
	const FlintMatrix        smith_normal_form() const;

	const FlintMatrix        lll_storjohann(const Rational delta , const Rational eta);
      };

    }
  }
}

#endif
