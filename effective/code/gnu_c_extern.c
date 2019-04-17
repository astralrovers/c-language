#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

int foo(void)
{
    return 1;
}
/*
 * 将表达式的扩展
 * 可以将代码块封装成一个表达式，得到一个值
 */
#define stats() ({int i = foo(); i; })

#define MAXINT(a, b) ({int _a = (a); int  _b = (b); _a > _b ? _a : _b; })

/*
 *局部标记的使用 __label__ 的定义
 */
int local_label(int i,int type)
{
    __label__ do_add, do_sub, do_multi, do_div;
    switch (type)
    {
        case 1:
            goto do_add;
        case 2:
            goto do_sub;
        case 3:
            goto do_multi;
        case 4:
            goto do_div;
    }
do_add:
    return i++;
do_sub:
    return i--;
do_multi:
    return i*i;
do_div:
    return 1/i;
}
/*
 *将标签当作变量来使用,标签被以"&&"开头来引用,被以"void*"的指针来指向，被goto时需要用*来得到其值
 */
int label_val(int i, int type)
{
    void* label_array[]={ &&do_add, &&do_sub, &&do_multi, &&do_div};

    goto *label_array[type];
do_add:
    return i++;
do_sub:
    return i--;
do_multi:
    return i*i;
do_div:
    return 1/i;
}
/**
 *内部函数，在函数内部定义函数
 *1.内部函数可以使用函数定义的局部变量。
 *2.如果先声明，再定义，需要用auto来声明。
 *3.如果内部函数需要被外部使用，可以以函数指针的形式被引用。
 */
int nested_func(int a, int b)
{
    auto int add();

    int do_add(int(*add)()) { return add(); }

    int c = do_add(add);

    if (c > 0)
    {
        return c;
    }
    else
    {
        return 0;
    }

    int add(){ return a + b; }
}
/**
 * 内置函数( built-in functions )
 * 使用内置函数时，他们会自动帮你记录外层函数调用时传入的参数，并且可以使用内置函数调用另一个目标函数，并把这些参数传递给它，无需关系参数数量和类型
 * 并且可以得到函数调用的返回值，而且你无需关心返回值类型
 * 使用的时候最好是作为参数传递的转发器
 *
 * 函数列表
 * void * __builtin_apply_args ()
 * void * __builtin_apply (void (*function)(), void *arguments, size t size)
 * void __builtin_return (void *result)
 * __builtin_va_arg_pack ()
 * size_t __builtin_va_arg_pack_len ()
 */


// 测试void * __builtin_apply_args ()
void error(const char* fmt, ...)
{
    void *args = __builtin_apply_args(); // 得到传入的参数列表，包含了fmt和后面的可变参数

    fprintf(stderr, "error: ");
    fflush(stderr);

    __builtin_apply(printf, args, 100); // 调用printf, 并且把外层传进来的参数给它，100指的是参数列表最大的内存字节大小

    int result = 2;
    __builtin_return(&result);
    printf("gnu-c extern >> 得到的内建函数调用后的返回值：%d\n", result);

    return (void)0;
}


/*
extern void built_in_test(const char *fmt, ...);
extern inline __attribute__((__gnu_inline__)) void built_in_test(const char *fmt, ...)
{

    fprintf(stdout, fmt, __builtin_va_arg_pack()); // 它返回的是所有匿名参数
    fprintf(stdout, "gnu-c extern >> 匿名参数个数：%d\n", __builtin_va_arg_pack_len()); // 它返回的是所有匿名参数的个数

    return (void)0;
}
*/
int built_func(int a)
{
    error("input a : %d\n", a);
    return a;
}
/**
 * 内置函数得到调用者的信息，用于调试系统，运行栈
 * void * __builtin_return_address (unsigned int level) // 函数的返回地址，不是函数地址，0表示当前函数的返回地址，1返回调用当前函数的函数的返回地址，以此类推
 * void * __builtin_extract_return_addr (void *addr)
 * void * __builtin_frob_return_address (void *addr)
 * void * __builtin_frame_address (unsigned int level)
 */
void built_func_caller()
{
    printf("gun-x-extern >> myself addr :0x%p\n", built_func_caller);
    printf("gun-x-extern >> caller 0:0x%p\n", __builtin_return_address(0));
    printf("gun-x-extern >> caller 1:0x%p\n", __builtin_return_address(1)); // 这里应该和上层函数调用__builtin_return_address(0)结果一致
}
/**
 *typeof的使用，获取变量的类型。
 */
#define max(a,b) \
    ({ typeof (a) _a = (a); \
     typeof (b) _b = (b); \
     _a > _b ? _a : _b; })
#define Max(a,b) ((a)>(b)?(a):(b))
/*
 *扩展标准c表达式的灵活处理
 *1.结构体与数组的初始化
 *2.case 语句的连续表示
 *3."?:"运算符的简化
 *4.长度为0的数组：定义时，节约空间
 *5.长度可变的数组
 *6.可变参数的宏定义
 *7.数组非常量初始化
 *8.灵活的动态数据转换
 *9.混合声明与定义
 *10.offsetof(type,member)的使用：得到member在结构体type中的偏移（stddef.h）中定义，
 *一个重要的实例——container_of（通过局部指针得到整体指针）,在linux内核中，链表的使用。
 */
/*
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 */
#define container_of(ptr, type, member) ({			\
        const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define debug(format, ...) fprintf (stderr, format, ##__VA_ARGS__)
#define warning(format0, args...) fprintf(stdout, format0, ##args)

void basic_extend(void)
{
    int array[5] = { [2] = 1, [3 ... 4] = 3 }; // 连续初始化赋值

    __int128 long_long_int = 9;
    printf("gnu-c-extern >> 128位int类型：%zu\n", sizeof(long_long_int)*8);

    struct point { int x, y; };
    struct point p0 = {
        .x = 5,
        .y = 6
    };
    int i =0;
    int v = 8 ;
    for (i = 0; i < 5; i++)
    {
        switch (i)
        {
            case 1 ... 3 : // 判断为在一个范围内
                v = array[i];
                break;
            case 4:
                v = array[i] ? : p0.y; // ? : 简化 ==> v = array[i] ? array[0] : p0.y;
                break;
        }
    }

    // 变长数据要放在末尾，如果结构体内还包含一个变长结构体，那么给内层结构体赋值时不允许赋非空值
    struct line {
        int len;
        char  p[0]; // 0长度属性
    };

    struct line *one;
    int len = 5;

    one = (struct line *)malloc(sizeof(struct line) + len + 1);
    one->len = len;

    strcpy(one->p, "this");
    printf("gnu-c etxern >> 结构体0长度属性，常用来做不确定的长度扩展 one.p = %s\n", one->p);
    free(one);

    // struct fill_len { char content[]; };
    // struct fill_len { char content[]; } _file_len = {{1, 2, 3}};
    // printf("gnu-c-extern >> 结构体填充式变长：%zu\n", sizeof(_file_len));

    struct S { int x[v]; }; // 变长定义
    struct S Sex ;
    printf("gnu-c-extern >> 结构体属性变长定义 define len = %ld, real size Sex = %ld\n", v*sizeof(int), sizeof(Sex));

    for (len = 0; len < v; len++)
    {
        Sex.x[len] = len;
        printf("gnu-c-extern >> 结构体属性变长定义验证：%d\n", Sex.x[len]);
    }

    // 变量定义 char arry[len];
    // 函数定义 void print_arry(int len, int arry[len]);

    int av[4] = {v, len, Sex.x[2], i}; // 使用变量初始化数组
    printf("gnu-c-extern >> 数组变量初始化验证：av[2] = %d\n", av[2]);

    struct Fst { int a; char b[2]; } fst;
    fst = ( struct Fst ){v, len, i}; // 整体的数据转换 
    printf("gnu-c-extern >> 更灵活的结构体数据转换：fst.b[1] = %d\n", fst.b[1]);

    static short sb[] = (short[3]){'6', 8, 9};
    printf("gnu-c-extern >> 更灵活的数组数据转换：sb[0] = %d\n", sb[0]);

    printf("属性相对于结构内偏移 >> offsetof(struct Fst,a) = %ld\n", offsetof(struct Fst, a)); 

    char *pb = fst.b;
    struct Fst *pst = container_of(pb, struct Fst, b); // 根据结构体成员地址获取结构体首地址
    printf("gnu-c-extern >> 通过成员地址获取结构体首地址：src[0x%p] == dst[0x%p]\n", &fst, pst);
}
/*
 * gnu属性(__attribute__)的使用,增强c语言对数据与函数的编译控制,主要作用于函数/变量声明/结构体定义
 * 函数：编译对函数调用的优化,对程序进行更严格的检测,用于声明函数，不能用于函数定义。
 * 变量：指定变量的相关属性
 * 结构体/联合/枚举:指定数据结构定义的属性
 * 关于__attribute__还有很多，这里不一一介绍
 */
void attr_func() __attribute__((aligned(16)));
void attr_func()
{
    struct Attr1{
        int a;   //4
        short b; //2
        char c;  //2偶地址对齐
    };
    struct Attr_P{
        int a;   //4
        short b; //2
        char c;  //1
    }__attribute__((packed));

    int a __attribute__((aligned(32))) = 6;
    printf("gnu-c-extern >> 关于__attribute__属性使用，变量对齐a addr:0x%p\n", &a);
    printf("gnu-c-extern >> 关于__attribute__属性使用，结构体默认对齐Attr1 size:%ld\n", sizeof(struct Attr1));
    printf("gnu-c-extern >> 关于__attribute__属性使用，绝对长度对齐Attr_P size:%ld\n", sizeof(struct Attr_P));
    printf("gnu-c-extern >> 关于__attribute__属性使用，函数对齐%s addr:0x%p\n", __func__, attr_func);

    printf("gun-x-extern >> attr_func返回地址 :0x%p\n", __builtin_return_address(0));
    built_func_caller();
}
/*
 *volatile 属性的使用，告之编译器，该对象不能够被优化处理。
 *gcc 的优化措施，可能将某些变量与逻辑给改变，该属性让c代码不被优化。
 *主要使用场景为会被硬件修改或者其他线程修改的变量。
 */
void volatile_func()
{
    volatile int a = 5;
    a++;
    printf(" i coming \n");
}
/**
 *asm用于c语言内嵌汇编
 */
void asm_func(long a, long b)
{
    unsigned long rbp;
    unsigned long rsp;
    printf("gnu-c-extern >> 汇编扩展\n");
    asm("movq %%rbp,%0":"=g"(rbp));
    printf("current ebp value:0x%lx\n",rbp);
    printf("last ebp value:0x%lx\n",*(long*)rbp);
    asm("movq %%rsp,%0":"=g"(rsp));
    printf("last caller leave addr:0x%lx\n",((long*)rbp)[1]);
    printf("last caller leave arg1:%ld\n",((long*)rsp)[0]);
    printf("last caller leave arg2:%ld\n",((long*)rsp)[1]);
}

int main(void)
{
    for (int i = 0; i < 5; i++); // 可以将遍历用的临时变量放在for里面

    int express_extern = stats();
    printf("gnu-c-extern >> 表达式扩展 : %d\n", express_extern);

    int max_int = MAXINT(10, 12);
    printf("gnu-c-extern >> 表达式扩展运用获取较大的值 : %d\n", max_int);

    int label_statement = local_label(4, 3);
    printf("gnu-c-extern >> 标签声明扩展 : %d\n", label_statement);

    int label_value = label_val(4, 2);
    printf("gnu-c-extern >> 标签当作值使用 : %d\n", label_value);

    int internal_func_def = nested_func(3, 6);
    printf("gnu-c-extern >> 定义内部函数 : %d\n", internal_func_def);

    built_func(1);
    printf("gnu-c-extern >> 关于函数参数的内置函数\n");

    int typeof_get_max = max(9, 30);
    printf("gnu-c-extern >> typeof 比较大小: %d\n", typeof_get_max);

    double d0 = 2.3;
    typeof(d0) d1 = 3.2;
    printf("gnu-c-extern >> typeof 定义变量:%lf\n", d1);

    // 你是无法显示知道什么类型的
    // printf("gnu-c-extern >> 打印具体类型：%s\n", typeof(d0));

    basic_extend();
    debug("this is at func:%s\n", __func__);
    warning("this is at line:%d\n", __LINE__);
    debug("this is void!!!\n");//当没有多余的参数，需要在宏定义时用"##"声明

    attr_func();

    built_func_caller();
    volatile_func();
    asm_func(4,5);

    printf("普通函数：%s\n", __FUNCTION__);
    printf("gnu-c-extern >> 更好的函数信息：%s\n", __PRETTY_FUNCTION__);

    return 0;
}
