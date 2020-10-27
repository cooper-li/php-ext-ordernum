dnl config.m4 for extension cooper_b

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(cooper_b, for cooper_b support,
dnl Make sure that the comment is aligned:
dnl [  --with-cooper_b             Include cooper_b support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(cooper_b, whether to enable cooper_b support,
dnl Make sure that the comment is aligned:
[  --enable-cooper_b          Enable cooper_b support], no)

if test "$PHP_COOPER_B" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library FOO build options from pkg-config output
  dnl AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  dnl AC_MSG_CHECKING(for libfoo)
  dnl if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists foo; then
  dnl   if $PKG_CONFIG foo --atleast-version 1.2.3; then
  dnl     LIBFOO_CFLAGS=\`$PKG_CONFIG foo --cflags\`
  dnl     LIBFOO_LIBDIR=\`$PKG_CONFIG foo --libs\`
  dnl     LIBFOO_VERSON=\`$PKG_CONFIG foo --modversion\`
  dnl     AC_MSG_RESULT(from pkgconfig: version $LIBFOO_VERSON)
  dnl   else
  dnl     AC_MSG_ERROR(system libfoo is too old: version 1.2.3 required)
  dnl   fi
  dnl else
  dnl   AC_MSG_ERROR(pkg-config not found)
  dnl fi
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBDIR, COOPER_B_SHARED_LIBADD)
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)

  dnl # --with-cooper_b -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/cooper_b.h"  # you most likely want to change this
  dnl if test -r $PHP_COOPER_B/$SEARCH_FOR; then # path given as parameter
  dnl   COOPER_B_DIR=$PHP_COOPER_B
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for cooper_b files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       COOPER_B_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$COOPER_B_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the cooper_b distribution])
  dnl fi

  dnl # --with-cooper_b -> add include path
  dnl PHP_ADD_INCLUDE($COOPER_B_DIR/include)

  dnl # --with-cooper_b -> check for lib and symbol presence
  dnl LIBNAME=COOPER_B # you may want to change this
  dnl LIBSYMBOL=COOPER_B # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $COOPER_B_DIR/$PHP_LIBDIR, COOPER_B_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_COOPER_BLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong cooper_b lib version or lib not found])
  dnl ],[
  dnl   -L$COOPER_B_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(COOPER_B_SHARED_LIBADD)

  dnl # In case of no dependencies
  AC_DEFINE(HAVE_COOPER_B, 1, [ Have cooper_b support ])

  PHP_NEW_EXTENSION(cooper_b, cooper_b.c, $ext_shared)
fi
