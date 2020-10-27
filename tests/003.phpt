--TEST--
cooper_b_test2() Basic test
--SKIPIF--
<?php
if (!extension_loaded('cooper_b')) {
	echo 'skip';
}
?>
--FILE--
<?php
var_dump(cooper_b_test2());
var_dump(cooper_b_test2('PHP'));
?>
--EXPECT--
string(11) "Hello World"
string(9) "Hello PHP"
