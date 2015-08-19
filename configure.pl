#  Copyright (c) 2014-2015
#  Silke Horn, Andreas Paffenholz (Technische Universitaet Darmstadt, Germany)
#  http://www.polymake.org
#
#  This program is free software; you can redistribute it and/or modify it
#  under the terms of the GNU General Public License as published by the
#  Free Software Foundation; either version 2, or (at your option) any
#  later version: http://www.gnu.org/licenses/gpl.txt.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#-------------------------------------------------------------------------------


@make_vars=qw(  CXXflags LDflags Libs );

sub allowed_options {
   my ($allowed_options, $allowed_with)=@_;
   @$allowed_with{ qw( flint ) }=();
}


sub usage {
   print STDERR "  --with-flint=PATH to installation path of flint library, if non-standard\n";
}


sub proceed {
   my ($options)=@_;
   my $lib_ext=$Config::Config{dlext};
   if ($^O eq "darwin") {
     $lib_ext="dylib";  # on Mac dlext points to bundle, but we need a shared lib, not a module
   }
   my $flint_path;
   if (defined ($flint_path=$$options{flint})) {
      my $flint_inc="$flint_path/include";
      my $flint_lib="$flint_path/lib";
      if (-f "$flint_inc/flint/fmpz.h" && -f "$flint_lib/libflint.$lib_ext" ) {
         $CXXflags="-I$flint_inc";
         $LDflags="-L$flint_lib -Wl,-rpath,$flint_lib";
      } elsif (-f "$flint_inc/flint/fpmz.h" && -f "$flint_lib/libflint.a" ) {
         $CXXflags="-I$flint_inc";
         $LDflags="-L$flint_lib";
      } else {
         die "Invalid installation location of flint library: header file flint/fpmz.h and/or library libflint.$lib_ext / libflint.a not found\n";
      }

   } else {
      local $Polymake::Configure::Libs="-lflint $Polymake::Configure::Libs";
      my $error=Polymake::Configure::build_test_program(<<'---');
#include "flint/fpmz.h"
int main() {
    fpmz_t  n;
    return 1;
}
---
      if ($?==0) {
         $error=Polymake::Configure::run_test_program();
         if ($?) {
            die "Could not run a test program checking for flint library.\n",
                "The complete error log follows:\n$error\n\n",
                "Please investigate the reasons and fix the installation.\n";
         }
      } else {
         die "Could not compile a test program checking for flint library.\n",
             "The most probable reasons are that the library is installed at a non-standard location,\n",
             "is not configured to build a shared module, or missing at all.\n",
             "The complete error log follows:\n$error\n\n",
             "Please install the library and specify its location using --with-flint option, if needed.\n",
      }
   }

   $Libs="-lflint";
   return $flint_path;
}
