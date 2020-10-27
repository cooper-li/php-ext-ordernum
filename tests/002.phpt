--TEST--
cooper_b_test1() Basic test
--SKIPIF--
<?php
if (!extension_loaded('cooper_b')) {
	echo 'skip';
}
?>
--FILE--
<?php
$ret = cooper_b_test1();

var_dump($ret);
?>
--EXPECT--
The extension cooper_b is loaded and working!
NULL
