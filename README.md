
### 注意，拨码开关，往no方向位0，全off输出为7，1号为no是为0x01
### 传感器IO没有设置位输入模式，为默认的应该没问题的

-- -
|     |    |   |     |
| ----:
| ---- | ---- | ---- - |
| 头  | 0x53 0x44,  |  2字节 |    头为"S" "D" 不会变了 |
| 地址 | 0x00 - 0x06 |  1字节 |  地址为0x00 - 0x07，建议在0x01 - 0x07中使用
| 长度 | 0x05        |  1字节 |    长度定为0x05应该不会变了
| 应答 |   ?         |  1字节 |
| 数据 |   ?         |  2字节 |      高位为电机x值。低位为电机转的时间
| 校验 |   ?         |  2字节 |

--------
#### 主板到从板  调试用
HEAD	数据头      2字节	"SD"
ADDR    地址        1字节   0x00 - 0x06
LEN	    长度值	    1字节	5
CMDR	请求命令值	1字节	0x60
DATA	数据	    2字节	0x01 - 0x03, 0x00 - 0xff
CRC	    校验	    2字节	计算值
110
----------
#### 主板到从板  出货工作流程
HEAD	数据头      2字节	"SD"
ADDR    地址        1字节   0x00 - 0x06
LEN	    长度值	    1字节	5
CMDR	请求命令值	1字节	0x61
DATA	数据	    2字节	0x01 - 0x03, //
CRC	    校验	    2字节	计算值

-- -
#### 从板到主板
HEAD	数据头      2字节	"SD"
ADDR    地址        1字节   0x00
LEN	    长度值	    1字节	5
CMDR	请求命令值	1字节	0X70  正常，0x71 无货，0x72 卡货
DATA	数据	    2字节	地址, 数据见附录（xx） //0x90表示成功，0x6d表示失败
CRC	    校验	    2字节	计算值

-- -
####  发送的指令
调试用1s中，电机1
53 44 02 05 60 01 0a af 72
调试用，10s，电机2
53 44 02 05 60 02 64 77 49
调试用，5s，电机全转
53 44 02 05 60 04 32 e7 dc
-- -
发货流程，电机1
53 44 02 05 61 01 00 39 08
.......


53 44 06 05 61 01 00 b0 0e

53 44 05 05 61 01 00 5e dc





