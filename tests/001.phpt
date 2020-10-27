--TEST--
Check if cooper_b is loaded
--SKIPIF--
<?php
if (!extension_loaded('cooper_b')) {
	echo 'skip';
}
?>
--FILE--
<?php
echo 'The extension "cooper_b" is available';
?>
--EXPECT--
The extension "cooper_b" is available
