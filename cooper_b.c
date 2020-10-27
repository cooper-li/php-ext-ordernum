/* cooper_b extension for PHP (c) 2020 cooper */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_cooper_b.h"
#include "order.c"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif

/* {{{ void cooper_b_test1()
 */
PHP_FUNCTION(cooper_b_test1)
{
	ZEND_PARSE_PARAMETERS_NONE();

	php_printf("The extension %s is loaded and working!\r\n", "cooper_b");
}
/* }}} */

/* {{{ string cooper_b_test2( [ string $var ] )
 */
PHP_FUNCTION(cooper_b_test2)
{
	char *var = "World";
	size_t var_len = sizeof("World") - 1;
	zend_string *retval;

	ZEND_PARSE_PARAMETERS_START(0, 1)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(var, var_len)
	ZEND_PARSE_PARAMETERS_END();

	retval = strpprintf(0, "Hello %s", var);

	RETURN_STR(retval);
}
/* }}}*/

/* {{{ int cooper_a_genOrder( [ int $var ] )
 */
PHP_FUNCTION(cooper_a_genOrder)
        {
                zend_long bid;
        zend_long retval;

        ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_LONG(bid)
        ZEND_PARSE_PARAMETERS_END();
        retval = genOrderNum(bid);
        RETURN_LONG(retval);
        }
/* }}}*/

/* {{{ string cooper_a_parseOrder( [ long $var ] )
 */
PHP_FUNCTION(cooper_a_parseOrder)
        {
                struct OrderNumInfo ret;
                uint64_t orderNum;

                ZEND_PARSE_PARAMETERS_START(1, 1)
                Z_PARAM_LONG(orderNum)
                ZEND_PARSE_PARAMETERS_END();

                ret = parseOrderNum(orderNum);

                RETURN_STR(strpprintf(0, "时间 => %llu, 序号 => %d, 自增 => %d", ret.ts_c, ret.bid_c, ret.incrid_c));
        }
/* }}}*/

/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(cooper_b)
{
#if defined(ZTS) && defined(COMPILE_DL_COOPER_B)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(cooper_b)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "cooper_b support", "enabled");
	php_info_print_table_end();
}
/* }}} */

/* {{{ arginfo
 */
ZEND_BEGIN_ARG_INFO(arginfo_cooper_b_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cooper_b_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cooper_a_genOrder, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cooper_a_parseOrder, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

/* }}} */

/* {{{ cooper_b_functions[]
 */
static const zend_function_entry cooper_b_functions[] = {
	PHP_FE(cooper_b_test1,		arginfo_cooper_b_test1)
	PHP_FE(cooper_b_test2,		arginfo_cooper_b_test2)
    PHP_FE(cooper_a_genOrder,		arginfo_cooper_a_genOrder)
    PHP_FE(cooper_a_parseOrder,		arginfo_cooper_a_parseOrder)
	PHP_FE_END
};
/* }}} */

/* {{{ cooper_b_module_entry
 */
zend_module_entry cooper_b_module_entry = {
	STANDARD_MODULE_HEADER,
	"cooper_b",					/* Extension name */
	cooper_b_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(cooper_b),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(cooper_b),			/* PHP_MINFO - Module info */
	PHP_COOPER_B_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_COOPER_B
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(cooper_b)
#endif

