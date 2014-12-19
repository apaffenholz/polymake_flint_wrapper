polymake_flint_wrapper
======================

An extension providing a wrapper for the flint library (flintlib.org) in polymake (polymake.org)

This extension depends on the flint library. We wrap Hermite normal form and the LLL algorithm. Currently, those functions are only contained in the flint version on github, but not in any released version of flint. Thus, to use this extension you have to obtain a recent snapshot of flint from github. 

=== Installation ===

To install this extension in polymake do the following:
(1) install flint (note that the released versions of flint are too old, see above)

(2) start polymake

(3) execute import_extension("<path_to_extension>","--with_flint=<path_to_flint_installation"); at the polymake prompt

Now you should be set up to use the extension.
