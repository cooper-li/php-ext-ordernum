/* cooper_b extension for PHP (c) 2020 cooper */

#ifndef PHP_COOPER_B_H
# define PHP_COOPER_B_H

extern zend_module_entry cooper_b_module_entry;
# define phpext_cooper_b_ptr &cooper_b_module_entry

# define PHP_COOPER_B_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_COOPER_B)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_COOPER_B_H */

