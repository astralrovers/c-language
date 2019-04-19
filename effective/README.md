# Introduction

* [特殊语法总结](#special-grammar-sum)
  * [关于#和##的用法](#used-of-3)
  * [关于...的用法](#used-of-3-point)
* [标准库](#std-lib-c)
  * [assert.h](#assert)
  * [complex.h](#complex)
  * [ctype.h](#ctype)
  * [errno.h](#errno)
  * [fenv.h](#fenv)
  * [float.h](#float)
  * [inttypes.h](#inttypes)
  * [iso646.h](#iso646)
  * [limits.h](#limits)
  * [math.h](#math)
  * [setjmp.h](#setjmp)
  * [signal.h](#signal)
  * [stdarg.h](#stdarg)
  * [stdbool.h](#stdbool)
  * [stddef.h](#stddef)
  * [stdint.h](#stdint)
  * [stdio.h](#stdio)
  * [stdlib.h](#stdlib)
  * [string.h](#string)
  * [tgmath.h](#tgmath)
  * [time.h](#time)
  * [wchar.h](#wchar)
  * [wctype.h](#wctype)
* [GNUC扩展](#extern-gnuc)

# <a id="special-grammar-sum">特殊语法总结</a>

代码参考`code/use#.c`和`code/three_point.c`

## <a id="used-of-3">关于#和##的用法</a>

### \#的用法

除了引用头文件等常见预处理外，还可用于将标识符转换为字符串
```c
// 这里要注意，直接使用，宏定义也会被直接转换为字符串
#define TO_STR(sym) #sym

// 这种方式就会先取宏定义的值，不过需要注意的是不能取变量的值，因为这里是在编译的时候展开的，而变量是在运行时才知道
#define TRAN_VAL(val) TO_STR(val)

#define TOC_ID 2
#define TOC_NAME "use#"

void fn(void)
{
    printf("# >> %s\n", TO_STR(88));
    printf("# >> %s\n", TO_STR(hello world));
    printf("# >> %s\n", TO_STR(TOC_NAME));

    printf("# >> %s\n", TRAN_VAL(TOC_ID));
    printf("# >> %s\n", TRAN_VAL(TOC_NAME));
}

```

### \#\#的用法

- 用于连接标识符
```c
#define LINK_SYM(sym1, sym2) sym1##sym2

printf("# >> %s\n", TRAN_VAL(LINK_SYM(hello, world)));
```
- 用于宏定义可变参数列表展开，下一节也有实例
  [参考](https://www.cnblogs.com/langzou/p/6674528.html)

## <a id="used-of-3-point">关于...的用法</a>

### 在函数定义中使用

作为函数可变参数使用，这里需要用到`stdarg.h`标准库
```c
static void printf_args(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    return (void)(0);
}
```

### 在宏定义中使用

作为宏定义变参使用
```c
#define DEBUG(fmt, ...) printf("DEBUG >> "fmt, ##__VA_ARGS__)

#define LOG(fmt, args...) printf("LOG >> "fmt, ##args)
```

### 在变量定义中使用

这里都是用在数组定义时初始化使用的：
```c
int first_arry[10] = { [0 ... 9] = 2 };
int second_arry[] = { [0 ... 5] = 1, [6] = 2, [7 ... 10] = 3, [11] = 90 };
```

### 在`case`语句中使用

[参考](https://gcc.gnu.org/onlinedocs/gcc-2.95.3/gcc_4.html#SEC82)
你可以在`case`判断时指定一个范围，这一个范围内的值都是使用同一个`case`语句，
要求从高到低:`1 ... 5`; `'a' ... 'z'`。
**注意**:这是`GNU`的扩展，最好是使用`#ifdef __GNUC__ ... #endif`来判断。

```c
    switch (i)
    {
        case 0 ... 20:
            printf("case into\n");
            break;
        default:
            break;
    }
```


# <a id="std-lib-c">标准库</a>

代码参考`code/about_xxx.c`

> 摘自《C99标准》

## <a id="assert">assert</a>

### 作用

> 用于断言表达式，通常用来调试代码异常。

### 头文件

> \<assert.h\>

### 函数或宏

> assert.h包含的assert是一个宏定义，不是函数.

 - assert():`void assert(scalar expression);`
   报错的时候会打印错误的详细信息，对于错误定位非常方便，它实际上会调用`abort`函数。
   ```c
   #include <assert.h>

   // example: about_assert.c:14: assert_test: Assertion `1 == 0' failed
   assert(1 == 0); // 异常情况会打印错误信息
   assert(1 == 1); // 正常情况不会有任何作用
   ```
 - NDEBUG
   它是一个条件宏，`assert.h`头文件在使用`assert()`时会判断，当我们定义了它的时候`assert()`会被定义为：
   ```c
   #define assert(ignore) ((void)0)
   ```
   通常我们的正式发布代码必须使用到它:
   ```c
   #define NDEBUG // 必须放在引用文文件之前

   #include <assert.h>
   ```

## <a id="complex">complex</a>

## <a id="ctype">ctype</a>

### 作用
> 包含了一系列用于检测和转换单个字符的函数.

### 头文件

> \<ctype.h\>

### 函数或宏

> - 所有函数都只有一个参数，就是要检测或者要转换的字符，并且这个参数的类型是 int，它可以表示一个有效字符，或者一个EOF（无效字符）
> - 所有函数的返回值也都是 int 类型，它可以表示一个有效字符，或者一个EOF（无效字符），或者一个布尔值（0 值表示“假”，非 0 值表示“真”）
> - 一种是字符分类函数，这些函数用来检测由参数传入的字符是否属于某个特定的分类
> - 一种是字符转换函数，这些函数用来对大写字母和小写字母进行转换

 - isalnum()：
   判断一个字符是否是字母或者数字，原型：`int isalnum ( int c );`，
   另外两个函数`isalpha()`是否是字母和`isdigit()`是否是数字如果返回真，那么它也返回真。
   ```c
   #include <ctype.h>

   char atr[] = "*ab%c123_ABC-.";
   ```
 - isalpha():
   是否是字母，不过是否是字母严格来说和地域有关，有些语言有些字符也是字母。
 - isblank()
   是否是空白符:` `和`\t`，还有一个函数`isspace()`:` `、`\t`、`\n`、`f`...
   是`isspace()`的子集
 - iscntrl():
   是否是控制字符(ctrl组合键字符)，指那些具有某种特殊功能、不会显示在屏幕上、不会占用字符位置的特殊字符(`\n`)。
 - isdigit():
   是否是数字(0 ... 9)
 - isxdigit():
   是否是16进制数字(0 ... f)
 - islower():
   是不是小写字母
 - isupper():
   是不是大写字母
 - isprint():
   是否是可打印字符
 - ispunct():
   是不是标点符号
 - tolower():
   转换为小写字母
 - toupper():
   转换为大写字母

## <a id="errno">errno</a>

### 作用

> 用来保存错误代码编号。

### 头文件

> \<errno.h\>

### 函数或宏

> - 只包含一个宏`errno`，用来保存最后的错误代码，它是一个宏，被展开后是一个 int 类型的数据（在单线程程序中可以认为是一个全局变量），并且当前程序拥有读取和写入的权限。
> - 程序在运行过程中会产生各种各样的错误，我们可以给每种类型的错误分配一个唯一的编号，就像给班里的学生分配学号一样，在C语言中，我们将此称为错误代码。
> - errno 宏，它就用来存储错误代码，当系统调用或者函数调用发生错误时，就会将错误代码写入到 errno 中，再次读取 errno 就可以知道发生了什么错误。
> - 程序刚刚启动的时候，errno 被设置为 0；程序在运行过程中，任何一个函数发生错误都有可能修改 errno 的值，让其变为一个非零值，用以告知用户发生了特定类型的错误。
> - 标准库中的函数只会将 errno 设置为一个用以表明具体错误类型的非零值，不会再将 errno 设置回零值。
> - 在调用函数前最好将 errno 的值重新设置为 0。

两种根据错误编号`errno`获取具体错误的方式:
 - 使用 perror() 将错误信息（文本）打印到标准输出设备；
 - 使用 strerror() 将错误代码转换成对应的文本信息。

另外`<errno.h>`头文件中定义了许多具体的错误编号宏，他们都对应于一个整形常量，至少应该定义:`EDOM、ERANGE、EILSEQ`。

两种模拟实现方式：
 - 单线程中，可以简单认为`errno`实现如下:
   ```c
   extern int _errno;
   #define errno _errno
   ```
 - 上面这种方式在多线程当中是不安全的，可以如下实现:
   ```c
   #define errno (*_errno_fn())
   ```
   它被展开为一个函数调用，统一从函数中获取值的地址，可以在函数内部保证多线程安全。
   

## <a id="fenv">fenv</a>

## <a id="float">float</a>

## <a id="inttypes">inttypes</a>

> 定义了一组与系统无关的定长字节数据类型:
> `int8_t`
> `uint8_t`
> `int16_t`
> `uint16_t`
> `int32_t`
> `uint32_t`
> `int64_t`
> `uint64_t`

## <a id="iso646">iso646</a>

## <a id="limits">limits</a>

### 作用

> 整数类型的大小限制

### 头文件

> `<limits.h>`

### 内容

| 宏         | 说明                                                         | 取值                                    |
| ---------- | ------------------------------------------------------------ | --------------------------------------- |
| CHAR_BIT   | char 类型所包含的位（Bit）数。                               | 大于等于 8，一般为 8                    |
| SCHAR_MIN  | signed char 类型所能表示的最小值                             | 小于等于-127 (-27+1)，一般为 -127       |
| SCHAR_MAX  | signed char 类型所能表示的最大值                             | 大于等于 127 (27-1)，一般为 127         |
| UCHAR_MAX  | unsigned char 类型所能表示的最大值                           | 大于等于 255 (28-1)，一般为 255         |
| CHAR_MIN   | char 类型所能表示的最小值                                    | 要么是 0，要么是 SCHAR_MIN              |
| CHAR_MAX   | char 类型所能表示的最大值                                    | 要么是 SCHAR_MAX，要么是 UCHAR_MAX      |
| MB_LEN_MAX | 一个多字节字符最多能包含多少个字节（多字节字符和宽字符是相对的） | 大于等于 1                              |
| SHRT_MIN   | short int 类型所能表示的最小值                               | 小于等于 -32767 (-215+1)，一般是 -32767 |
| SHRT_MAX   | short int 类型所能表示的最大值                               | 大于等于 32767 (215-1)，一般是 32767    |
| USHRT_MAX  | unsigned short int 类型所能表示的最大值                      | 大于等于 65535 (216-1)，一般是 65535    |
| INT_MIN    | int 类型所能表示的最小值                                     | 小于等于 -32767 (-215+1)                |
| INT_MAX    | int 类型所能表示的最大值                                     | 大于等于 32767 (215-1)                  |
| UINT_MAX   | unsigned int 类型所能表示的最大值                            | 大于等于 65535 (216-1)                  |
| LONG_MIN   | long int 类型所能表示的最小值                                | 小于等于 -2147483647 (-231+1)           |
| LONG_MAX   | long int 类型所能表示的最大值                                | 大于等于 2147483647 (231-1)             |
| ULONG_MAX  | unsigned long int 类型所能表示的最大值                       | 大于等于 4294967295 (232-1)             |
| LLONG_MIN  | long long int 类型所能表示的最小值                           | 小于等于 -9223372036854775807 (-263+1)  |
| LLONG_MAX  | long long int 类型所能表示的最大值                           | 大于等于 9223372036854775807 (263-1)    |
| ULLONG_MAX | unsigned long long int 类型所能表示的最大值                  | 大于等于 18446744073709551615 (264-1)   |



## <a id="math">math</a>

## <a id="setjmp">setjmp</a>

### 作用

> 相当于距离更远的`goto`，能够在函数之间跳转

### 头文件

> `<setjmp.h>`

### 函数

> 只有一个数据类型和两个函数

- `jmp_buf`:
  使用之前必须定义它，并且要定义成全局变量，不过最好是定义成文件私有
  `static jmp_buf env`

- `int setjmp(jmp_buf env);`，使用跳转已之前必须先调用，第一次调用返回0，之后的返回值由`longjmp()`传递
  ```c
  if (setjmp(env))
  {
    return 0;
  }
  ```

- `void longjmp(jmp_buf env, int val);`，长跳转函数，`val`是我们传递的参数，调用它之后，函数会跳转到`setjmp`处执行，返回值就是`val`
  ```c
  longjmp(env, 2);
  ```

## <a id="signal">signal</a>

## <a id="stdarg">stdarg</a>

### 作用

> 主要是用来获取可变参数函数的参数列表的。

### 头文件

> `<stdarg.h>`

### 函数或宏

`va` --> `variable-argument`

**下面的函数都是宏**


- 这里之定义了一个数据类型`va_list`，获取参数列表必须通过这个类型的变量
- `void va_start(va_list ap, last);`:
  用于初始化`ap`，`last`很明显是传入的第一个参数，不过传参是通过压栈的，所以`last`在栈底，所以取名为`last`，用于确定参数列表的最后一个参数
- `type va_arg(va_list ap, type);`：
  根据传入的类型，返回参数列表里对应的参数，**注意：这里取参数是根据传参顺序来取的，即从`last`参数后面一个开始取**
- `void va_end(va_list ap);`：
  结束可变参数的获取。
- `void va_copy(va_list dest, va_list src);`，自己猜吧。

一个例子
```c
#include <stdarg.h>
#include <stdio.h>

static void print_one_arg(int last, ...)
{
    va_list ap;
    va_start(ap, last);
    int ret_int = va_arg(ap, int);
    va_end(ap);

    printf("about_args >> %s, last = [%d], one_arg = [%d]\n", __func__, last, ret_int);
    return (void)0;
}

static void my_print(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    printf("aboute_stdarg >> my_print : ");
    vprintf(fmt, ap);
    va_end(ap);

    return (void)0;
}

void stdarg_test(void)
{
    print_one_arg(20, 30);
    my_print("hello name = [%s] age = [%d]\n", "ywl", 24);

    return (void)0;
}


```

## <a id="stdbool">stdbool</a>

### 作用

> 新增的`bool`类型，不用自定义了，更加方便

### 头文件

> `<stdbool.h>`

### 函数或宏

一个类型，两个宏

- `bool`类型 --> `_Bool`，他的值只能为0，1
- `true`真
- `false`假

## <a id="stddef">stddef</a>

### 作用

> 定义了许多变量和宏，许多头文件也会包含它

### 头文件

> `<stddef.h>`

### 函数或宏

重要的几个

- `ptrdiff_t`：有符号整型，常用来表示两个指针的相减的结果:
  ```c
  int head_t = 9;
  int tail_t = 90;

  int * head = &head_t;
  int * tail = &tail_t;

  ptrdiff_t diff = tail - head;
  ```

- `size_t`：无符号整型，`sizeof`的结果，打印有专用符号`%zu`，其实用`%ld`也可以
- `NULL`：空指针常量的值
- `size_t offsetof(type, member);`：返回值为`size_t`类型常量，大小为结构体成员相对结构体首地址的偏移量

## <a id="stdint">stdint</a>

关于`for (unsigned int i = 1; i >= 0; --i);`，这行代码永远不会退出，没必要尽量不要用无符号整型表示该数值非负数，使用判断来保证，像这种临界点的比较十分危险。

## <a id="stdio">stdio</a>

## <a id="stdlib">stdlib</a>

## <a id="string">string</a>

## <a id="tgmath">tgmath</a>

## <a id="time">time</a>

## <a id="wchar">wchar</a>

## <a id="wctype">wctype</a>

# <a id="extern-gnuc">`GNUC`扩展</a>

代码参考`code/gnu_c_extern.c`
