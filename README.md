# php-ext-ordernum    

## 一、基础扩展
#### 生成扩展骨架
```
cd ~/Work/c/php-7.3.22/ext

./ext_skel.php --ext cooper_b --author cooper
```

#### 修改config.m4配置文件
```
# 去掉 相关注释, 保证
PHP_ARG_ENABLE(cooper_b, whether to enable cooper_b support,
Make sure that the comment is aligned:
[  --enable-cooper_b          Enable cooper_b support], no)
```
> 备注: config.m4的作用就是配合phpize工具生成configure文件。configure文件是用于环境检测的。检测扩展编译运行所需的环境是否满足。其中，dnl 是注释符号。上面的代码说，如果你所编写的扩展如果依赖其它的扩展或者lib库，需要去掉PHP_ARG_WITH相关代码的注释。否则，去掉 PHP_ARG_ENABLE 相关代码段的注释。我们编写的扩展不需要依赖其他的扩展和lib库。因此，我们去掉PHP_ARG_ENABLE前面的注释。

#### 执行编译安装即可
```
# 当前目录编译
~/Work/c/php73/bin/phpize

# 注意要指定特定版本的 php-cfg
./configure --with-php-config=/Users/cooper/Work/c/php73/bin/php-config

# 安装
make
sudo make install

# 完成后会提示:
Installing shared extensions:     /Users/cooper/Work/c/php73/lib/php/extensions/debug-non-zts-20180731/
```

#### 增加扩展即可
```
# 找打配置文件路径
~/Work/c/php73/bin/php --ini

# 编辑增加扩展: vim xxx/php.ini
extension=cooper_b
```

#### 查看扩展
```
# 测试文件, 默认生成的函数
<?php
$a = cooper_b_test1();
$b = cooper_b_test2("cooper");
var_dump($a, $b);

# 输出
The extension cooper_b is loaded and working!
string(11) "Hello World"

```

## 二、实现订单号

- 以上步骤已经生成基础扩展, 生成订单号扩展需要我们增加自己的方法

#### 在 ext/cooper_b 目录下编写文件: order.c
```c
#include <stdio.h>
#include<sys/time.h>

// 左 -->  右
// 64 --> 25:  40位时间戳差
// 24 --> 11:  13位业务分区: 8192 个业务
// 1  --> 10:  10位自增id: (1024 * 1000) / s 理论值


typedef unsigned long long uint64_t;

const long ORDER_TIME_BIT = 0x1fff;
const long ORDER_SORT_BIT = 0x2ff;
const uint64_t START_TIME = 1598889600000; // 2020-09-01
int incrNum = 0;

struct OrderNumInfo {
    uint64_t ts_c;
    int bid_c;
    int incrid_c;
};

// 获取毫秒时间戳
uint64_t getMillTs() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// 生成订单号
// 参数 业务id
uint64_t genOrderNum(int bid) {
    uint64_t orderNum;
    uint64_t millTs;
    int businessPart;
    uint64_t tsPart;
    long tsReduce;

    // 时间戳部分
    millTs = getMillTs();
    // printf("当前时间是: %llu \n", millTs);
    tsReduce = millTs - START_TIME;
    // printf("时间差: %ld \n", tsReduce);
    tsPart = tsReduce << 23;

    // 业务id部分
    businessPart = bid << 10;

    // 自增部分
    incrNum++;

    // 组装
    orderNum = (tsPart | businessPart | incrNum);
    return orderNum;
}

// 解析订单号
struct OrderNumInfo parseOrderNum(uint64_t orderNum)
{
    uint64_t ts;
    int bid;
    int incrNum;
    struct OrderNumInfo ret;

    // 获取时间戳
    ts = orderNum >> 23;

    // 获取业务id
    bid = orderNum >> 10 & ORDER_TIME_BIT;

    // 获取自增id
    incrNum = orderNum & ORDER_SORT_BIT;

    ret.ts_c = (ts + START_TIME);
    ret.bid_c = bid;
    ret.incrid_c = incrNum;

    return ret;
}
```

#### 修改 cooper_b.c 文件, 增加我们需要的方法
1. 头文件引入
```
#include "order.c"
```
2. 在 PHP_FUNCTION(cooper_b_test2) 方法下面增加两个方法
```c
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
```

3. 在/* {{{ arginfo */ 注释段中增加增加两段参数引入
```c
ZEND_BEGIN_ARG_INFO(arginfo_cooper_a_genOrder, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_cooper_a_parseOrder, 0)
ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
```

4. 在数组: cooper_b_functions 中注册函数, 结果为:
```
static const zend_function_entry cooper_b_functions[] = {
	PHP_FE(cooper_b_test1,		arginfo_cooper_b_test1)
	PHP_FE(cooper_b_test2,		arginfo_cooper_b_test2)
    PHP_FE(cooper_a_genOrder,		arginfo_cooper_a_genOrder)  
    PHP_FE(cooper_a_parseOrder,		arginfo_cooper_a_parseOrder)
	PHP_FE_END
};
```

5. 到此函数开发已经完成, 重复执行第一步中的编译安装即可重新加载扩展
6. 编写脚本测试, 测试脚本
```php
<?php

$a = cooper_b_test1();
$b = cooper_b_test2();
var_dump($a, $b);
$c = cooper_a_genOrder(111);
$d = cooper_a_parseOrder($c);

var_dump($c, $d);

// 获取时间
$t = substr($d, 10, 13);
var_dump($t);

$c = cooper_a_genOrder(666);
$d = cooper_a_parseOrder($c);
```
脚本输出
```
The extension cooper_b is loaded and working!
string(11) "Hello World"
int(40969617455299585)
string(51) "时间 => 1603773558990, 序号 => 111, 自增 => 1"
string(13) "1603773558990"
NULL
string(11) "Hello World"
int(40969617455867906)
string(51) "时间 => 1603773558990, 序号 => 666, 自增 => 2"

```



#### 参考:
> 韩天峰: https://yuerblog.cc/wp-content/uploads/%E9%9F%A9%E5%A4%A9%E5%B3%B0%E2%80%94%E2%80%94%E4%BD%BF%E7%94%A8C++%E5%BC%80%E5%8F%91PHP7%E6%89%A9%E5%B1%95.pdf

> 韩天峰: https://segmentfault.com/a/1190000011111074

> 鱼儿: https://yuerblog.cc/2017/07/11/php-x-extension/





​    

