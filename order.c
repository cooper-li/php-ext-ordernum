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