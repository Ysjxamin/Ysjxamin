# C++ Core Code

[TOC]



# 1.内存分区模型

程序每次执行都会重新分配内存

内存划分为4个区域：

代码区，全局区，堆区，栈区

## 1.1（未执行exe程序前）：

- 代码区：存放函数体的二进制代码

  共享，在内存中只有一份代码；

  只读，防止程序意外地修改了他的指令

- 全局区：存放全局变量和静态变量以及常量

  常量区中存放**const修饰地全局常量和字符串常量**

  该区域地数据在程序结束后**由操作系统释放**

  [![WeHZaq.png](https://z3.ax1x.com/2021/07/15/WeHZaq.png)](https://imgtu.com/i/WeHZaq)

  

  ## 1.2程序运行后

- 栈区：由编译器自动分配释放，存放函数的参数值，局部变量等

  不要返回局部变量的**地址**

  （**函数执行完**局部变量被释放）

- 堆区：由程序员分配和释放，若程序员不释放，**程序结束时**由操作系统回收

- ```c++
  //利用new关键字 可以将数据开辟到堆区
  int*func()
  {
      //指针 本质也是局部变量，放在栈上，指针保存的数据是放在堆区
      int *p=new int(10);
      return p;
  }
  //在堆区开辟数据
  int *p=func();
  ```

  

- 意义：不同区域存放的数据，赋予不用的生命周期，给我们更大的灵活编程

  ## 1.3 new 操作符

  C++利用new操作符在堆区开辟数据

  堆区开辟的数据，由程序员手动开辟，手动释放，释放利用操作符delete

  语法：**new 数据类型**

  利用new创建的数据，会**返回**该数据对应地类型地**指针**

  ```c++
  //1.new的基本语法
  int *func()
  {
      //在堆区创建整型数据
      //new返回是 该数据类型的指针
      int *p =new int(10);
      return p;
  }
  void test01()
  {
      int*p=func();
      cout<<*p<<endl;
      //如果想释放，利用关键字delete
      delete p;
  }
  //2.在堆区利用new开辟数组
  void test02()
  {
      //创建10整型数据的数组，在堆区
      int*arr =new int[10];
      //释放堆区数组，注意要加[]
      delete[] arr;
  }
  ```

  # 2.引用
  
  用途：给变量起别名
  
  语法：数据类型 &别名 = “原名”
  
  ```c++
  int a =10;
  int &b =a;
  b=20;
  cout<<a<<endl; //输出a的值也为20
  ```
  
  ## 2.1 引用注意事项
  
  1.引用必须初始化;
  
  int &b;//错误的
  
  2.引用一旦初始化后，就不可以更改了；
  
  ## 2.2 引用做函数参数
  
  作用：函数传参时，可以利用引用的技术让形参修饰实参；
  
  ```c++
  //交换函数
  //1.值传递 （形参改变实参不改变）
  void mySwap01(int a,int b)
  {
      int temp=a;
      a=b;
      b=temp;
  }
  //形参修饰实参
  //2.地址传递(main函数中mySwap02（&a,&b）)
  void mySwap02(int *a,int *b)
  {
      int temp=*a;
      *a=*b;
      *b=temp;
  }
  //2.引用传递(main函数中mySwap03(a,b))
  void mySwap03(int &a,int &b)//a就是a,b就是b
  {
      int temp=a;
      a=b;
      b=temp;
  }
  ```
  
  ## 2.3 引用做函数的返回值
  
  ```c++
  //引用做函数的返回值
  //1.不要返回局部变量的引用
  int& test01()//引用类型的返回值
  {
      int a=10;//局部变量存放在四区中的栈区
      return a;
  }
  //2.函数的调用可以作为左值
  int& test02()
  {
      static int a=10;//静态变量，存放在全局区
      return a;
  }
  
  int main()
  {
      int &ref =test01();//ref为别名
      cout<<ref<<endl;
      //只可输出第一次，后面全部错误乱码
      int &ref2 =test02();//ref为别名
      cout<<ref2<<endl;
      test02()=1000//若函数返回值为引用，则调用可以作左值
  }
  
  ```
  
  ## 2.4引用的本质
  
  本质：引用的本质在C++内部实现是一个指针常量
  
  **int * const ref=&a**
  
  编译器省略了解引用操作

![image-20210713110321111](C:\Users\huawei\AppData\Roaming\Typora\typora-user-images\image-20210713110321111.png)

## 2.5 常量引用

作用：常量引用主要用来修饰形参，防止误操作

在函数形参列表中，可以加形参

```c++
int a=10;
int &ref =10;//引用必须引一块合法的内存空间
//加上const之后，编译器把代码修改 
//int temp=10;const int &ref=temp; 
const int &ref=10;

//引用使用的场景，通常用来修饰形参
void showValue(const int& v)
{
    cout<<v<<endl;
}
```

# 3. 函数提高

## 3.1函数默认参数

语法：返回值类型 函数名（参数=默认值）、

**注意事项**：

1.如果某个位置已经有了默认参数，那么从这个位置往后都必须有默认值；

2.如果函数声明有默认参数，函数实现就不能有默认参数

```c++
//函数默认参数
int func(int a.int b,int c)
{
    return a+b+c;
}//func(10)缺少参数报错
==
int func(int a,int b=20,int c=30)
{
    return a+b+c;
}//func(10)不报错

```

## 3.2 函数占位参数

C++中函数的形参列表里可以有占位参数，用来做占位，调用函数时必须填补该位置

占位参数还可以有默认参数

**语法：返回值类型 函数名（数据类型）**

```c++
//占位参数
void func(int a,int)//第二个int占位（占座）
{
    
}
```

## 3.3函数重载

### 3.3.1函数重载概述

作用：函数名可以相同，提高复用性

**函数重载满足条件：**

- 同一个作用域下
- 函数名称相同
- 函数**参数类型不同** 或者**个数**不同 或者**顺序**不同

```c++
//函数重载
//可以让函数名相同，提高复用性
void func()
{
    cout<<"func的调用"<<endl;
}
void func(int a)
{
    cout<<"func(int a)的调用"<<endl;
}
void func(double a)
{
    cout<<"func(double a)的调用"<<endl;
}
void func(int a,double b)
{
    cout<<"func(int a,double b)的调用"<<endl;
}
void func(double a,int b)
{
    cout<<"func(double a,int b)的调用"<<endl;
}
```

### 3.3.2函数重载注意事项

- 引用作为重载条件

  ```c++
  void fun(int &a)
  {
      cout<<"func(int &a)"<<endl;
  }
  void fun(const int &a)
  {
      cout<<"func(const int &a)"<<endl;
  }
  fun(a)//调用第一个函数
  fun(10)//调用第二个函数
  ```

  

- 函数重载遇到函数默认参数

  ```c++
  void func(int a，int b)
  {
      cout<<"func(int a，int b)"<<endl;
  }
  void func( int a)
  {
      cout<<"func(int a)"<<endl;
  }
  fun(10)//编译器傻了
  ```

  

# 4. 类和对象

C++面向对象的三大特性：封装，继承，多态

```c++
class Student
{
    public://公共权限
    //类中的属性和行为 我们统一称为成员
    //属性  成员属性 成员变量
    //行为  成员函数 成员方法
    //属性
    string m_Name;//姓名
    int m_Id;//学号
    //行为
    //显示姓名和学号
    void showStudent()
}
```

![image-20210713153353742](C:\Users\huawei\AppData\Roaming\Typora\typora-user-images\image-20210713153353742.png)

### 4.1封装意义：

类在设计时，可以把属性和行为放在不同的权限下，加以控制，访问权限有三种：

1.**public** 公共权限   成员  类内可以访问  类外可以访问

2.**protected** 保护权限  成员 类内可以访问 类外不可以访问

3.**private** 私有权限  类内可以访问 类外不可以访问

## 4.1.2 class和struct

区别：class默认权限为 私有 private

​            struct默认权限为公共 public

## 4.1.3 成员属性设置为私有

优点：

1.可以自己控制读写权限；

2.对于写可以检测数据的有效性；

```c++
//设计人类
class Person
{
    public:
    //设置姓名
    void setName(string name)
    {
        m_Name =name;
    }
    //获取姓名
    string getName()
    {
        return m_Name;
    }
    //获取年龄
    int getAge()
    {
        m_Age=0;
        return m_Age;
    }
    //设置情人 只写
    void setLover(string lover)
    {
        m_Lover =lover;
    }
    private:
    //姓名 可读可写
    string m_Name;
    //年龄 只读
    int m_Age;
    //情人 只写
    string m_Lover;
}
```

**注意事项：类可嵌套！**