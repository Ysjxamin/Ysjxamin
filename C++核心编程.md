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

#### 4.2 对象的初始化和清理

```c++
对象的初始化和清理
//1.构造函数 进行初始化操作
    class Person
    {
        public:
        //1.构造函数
        //没有返回值 不用写void
        //函数名 与类名相同
        //构造函数可以有参数，可以发生重载
        //创建对象的时候，构造函数会自动调用，而且只调用一次
        Person()//自己写的
        {
            cout<<"Person 构造函数的调用"<<endl;
        }
        Person()//编译器写的空白函数
        {
            
        }
        //2.析构函数 进行清理的操作
        //没有返回值 不用写void
        //函数名 与类名相同 在名称前加~
        //构造函数不可以有参数，不可以发生重载
        //对象在销毁前，会自动调用析构函数
        ~Person()//自己写的
        {
            cout<<"Person 的析构函数调用"<<endl;
        }
        ~Person()//编译器写的空白函数
        {
            
        }
   }
```

### 4.2.1构造函数的分类和调用

#### 分类：

1.按照参数分类： 无参构造（默认构造）和有参构造

2.按照类型分类：  拷贝构造 和 普通构造

```c++
//拷贝构造函数
Person(const Person &p)//const 引用
{
    //将传入的人身上的所有属性，拷贝到我身上
    age = p.age;
}
```

#### 调用

1.括号法；2.显示法；3.隐式转换法

注意事项：

1.调用默认构造函数时，不要加（）

否则编译器会认为是一个函数的声明，不会构造一个类

2.不要利用拷贝构造函数 初始化匿名对象

Person(p3)；
![image-20210715160704011](C:\Users\huawei\Desktop\image-20210715160704011.png)

![image-20210715161458695](C++核心编程/image-20210715161458695.png)

#### 4.2.2 拷贝构造函数调用时机

拷贝构造函数调用时机
1、 使用一个已经创建完毕的对象来初始化一个新对象

```c++
void test01()
{
    Person p1(20);
    Person p2(p1);
    cout<<"p2的年龄为： "<<p2.m_Age<<endl;
}
```

2、值传递的方式给函数参数传值

```c++
void doWork(Person p)
{
    
}
void test02()
{
    Person p;
    doWork(p);
}
//两个屁不是同一个p
```

3、值方式返回局部对象

```c++
void doWork2()
{
    Person p1;
    cout<<(int*)&p1<<endl;
    return p1;
}
void test03()
{
    Person p=doWork2();
    cout<<(int*)&p<<endl;
}
```

![image-20210715170020656](C:\Users\huawei\AppData\Roaming\Typora\typora-user-images\image-20210715170020656.png)

#### 4.2.3 构造函数调用规则

默认情况下，C++编译器至少给一个类添加3个函数
1.默认构造函数(无参,函数体为空)
2.默认析构函数(无参，函数体为空)
3.默认拷贝构造函数,对属性进行值拷贝
构造函数调用规则如下:
●如果用户定义有参构造函数，C++不在提供默认无参构造，但是会提供默认拷贝构造
●如果用户定义拷贝构造函数，C++不会再提供其他构造函数

```c++

```

#### 4.2.4 深拷贝与浅拷贝

浅拷贝：简单的赋值拷贝操作

深拷贝：在堆区

```c++
class Person
{
    public:
    Person()
    {
        cout<<"Person的默认构造函数调用"<<endl;
    }
     Person(int age,int height)
    {
         m_Height =new int (height);//指针存放地址
         m_Age =age;
        cout<<"Person的有参构造函数调用"<<endl;
    }
    ~Person()
    {
        //析构代码，将堆区开辟数据做释放操作
        if(m_Height != NULL)
        {
            delete m_Height;
            m_Height=NULL;
        }
        cout<<"Person的析构函数调用"<<endl;
    }
    //自己实现拷贝构造函数，解决浅拷贝带来的问题
    Person(const Person &p)
    {
        cout<<"Person 拷贝构造函数调用"<<endl;
        m_Age =p.m_Age;
        //m_Height = p.m_Height; 编译器默认实现
        //深拷贝操作
        m_Height =new int(*p.m_Height);
    }
    int m_Age;//年龄
    int *m_Height;//身高 Height为指针存放地址 height为值
}
void test01()
{
    Person p1(18,160);
    cout<<"p1的年龄为： "<<p1.m_Age<<endl;
    Person p2(p1);
    cout<<"p2的年龄为： "<<p2.m_Age<<endl;
        
}
```

编译程序会崩，问题：浅拷贝导致堆区的内存重复释放

浅拷贝的问题，要利用深拷贝进行解决

#### 4.2.5 初始化列表

作用：C++提供了初始化列表语法，用来初始化属性

```c++
//初始化列表
class Person
{
    public:
    //传统初始化操作
    Person(int a,int b,int c)
    {
        m_A=a;
        m_B=b;
        m_C=c;
    }
    //初始化列表初始化属性
    Person(int a,int b,int c):m_A(a),m_B(b),m_C(c)
    {
        
    }
    int m_A;
    int m_B;
    int m_C;
}
```

#### 4.2.6 类对象作为类成员

C++类中的成员可以说另一个类的对象，我们称之为

当其他类对象作为苯类成员，构造时候先构造类对象，再构造自身

#### 4.2.7 静态成员

静态成员就是在成员变量和成员函数前加上关键字static,称为静态成员
静态成员分为: .
●静态成员变量
。所有对象共享同一份数据
。在编译阶段分配内存
。类内声明，类外初始化
●静态成员函数
。所有对象共享同一个函数
。静态成员函数只能访问静态成员变量

![image-20210715214047526](C:\Users\huawei\AppData\Roaming\Typora\typora-user-images\image-20210715214047526.png)

![image-20210715212743957](C:\Users\huawei\AppData\Roaming\Typora\typora-user-images\image-20210715212743957.png)

### 4.3 C++对象模型和this指针

#### 4.3.1 成员变量和成员函数分开存储

只有非静态成员变量才属于类的对象上

空对象占用内存空间为：1 

加上一个int m_A//非静态成员变量 属于类的对象上

对象占用内存空间为：4

加上一个static int m_B//静态成员变量 不属于类对象上

对象占用内存空间为：4

加上一个void func(){}//非静态成员函数 不属于类对象上

对象占用内存空间为：4

加上一个static void func2(){}//非态成员函数 不属于类对象上

对象占用内存空间为：4

#### 4.3.2 this指针概念

this指针是隐含每一个非静态成员函数内的一种指针

不需要定义，直接使用即可

用途：

- 当形参和成员变量同名时，可用this指针来区分

  ```c++
  class Person
  {
      public:
      Person(int age)
      {
          //this指针指向 在main函数被调用的成员函数 所属的对象
          this->age = age;
      }
      Person& PersonAddAge(Person &p)
      {
          this->age+=p.age;
          //this为指向p2的指针，而*this指向的就是p2这个对象本体
          return *this;
      }
      int age;//否则无法正常赋值
  }
  ```

  

- 在类的非静态成员函数中返回对象本身，可使用return *this

```c++
void test02()
{
    Person p1(10);
    Person p2(10);
    //链式编程思想
    p2.PersonAddAge(p1).PersonAddAge(p1).PersonAddAge(p1).;
    cout<<"p2的年龄为： "<<p2.age<<endl;
}
```

#### 4.3.3 空指针访问成员函数

C++中空指针也是可以调用成员函数的，但是也要注意有没有用到this指针

#### 4.3.4 const修饰成员函数

常函数: .
●成员函数后加const后我们称为这个函数为常函数
●常函数内不可以修改成员属性
●成员属性声明时加关键字mutable后，在常函数中依然可以修改
常对象:
●声明对象前加const称该对象为常对象
●常对象只能调用常函数

```c++
//常函数
class Person
{
    public:
    
    //this指针的本质 是指针常量 指针的指向不可更改
    //const Person *const this;
    //在成员函数后面加const，修饰的是this指向，让指针指向的值也不可更改
    void showPerson() const
    {
        //this->m_A=100；
        //this =NULL;//this指针不可以修改指针的指向
    }
    int m_A;
    mutable int m_B;//特殊变量，即使在常函数中，也可以修改这个值，加关键字mutable
}
//常对象
void test02()
{
    const Person p;//在对象面前加const,变为常对象
    P.m_A=100;
    P.m_B=100;//m_B是特殊值
    //常对象只能调用常函数
    
}
```

![image-20210716092905304](D:\Qianrushi\image-20210716092905304.png)

### 4.4 友元

友元的三种实现：

- 全局函数做友元

  

- 类做友元

- 成员函数做友元

### 4.5 运算符重载

#### 4.5.1 加号运算符重载

作用:对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型

![image-20210717115842110](D:\Qianrushi\C++核心编程\image-20210717115842110.png)

```c++
//1.成员函数重载+号
Person operator+(Person &p)
{
    Person temp;
    temp.m_A=this->m_A+p.m_A;
    temp.m_B=this->m_B+p.m_B;
    return temp;
}
Person p3=p1 operator+(p2)
Person p3=p1+p2;
//2.全局函数重载+号
Person operator+(Person &p1，Person &p2)
{
    Person temp;
    temp.m_A=p1.m_A+p2.m_A;
    temp.m_B=p1.m_B+p2.m_B;
    return temp;
}
Person p3=operator+(p1,p2)
Person p3=p1+p2;
//运算符重载 也可以发生函数重载
Person operator+(Person &p1，num)
{
    Person temp;
    temp.m_A=p1.m_A+num;
    temp.m_B=p1.m_B+num;
    return temp;
}
Person p3=operator+(p1,10)
Person p3=p1+10;
```

#### 4.5.2 左移运算符重载

作用：可以输出自定义数据类型

```c++
//左移运算符重载
//利用成员函数左移运算符重载
class Person
{
    public:
    void operator<< (cout)//无法实现
}
//只能利用全局函数重载左移运算符
void operator<<(ostream &cout,Person p)//本质operator<<(cout,p)简化cout<<p
{
    cout<<"m_A= "<<p.m_A<<"m_B "<<p.m_B;
}
cout<<p//即可以输出对象p中的xx个对象的值
       //但后面不可加<<endl,因重载函数的返回void
    
    
ostream & operator<<(ostream &cout,Person p)//本质operator<<(cout,p)简化cout<<p
{
    cout<<"m_A= "<<p.m_A<<"m_B "<<p.m_B;
}
cout<<p<<endl;//即可以输出对象p中的xx个对象的值
       //后面可加<<endl,因重载函数的返回值为cout
```

#### 4.5.3 递增运算符重载

作用：通过重载递增运算符，实现自己的整型数据

```c++
//重载前置++运算符 返回引用是为了一直对一个值递增
MyInteger& operator++()
{
    //先进行++运算
    m_Num++;
    
    //再将自身做返回
    return *this;
}
//重载后置—++运算符
void operator++(int) //int代表占位参数,可用于区分前置和后置递增
{
    //先 记录当时结果
    MyInteger temp = *this;
    //后 递增
    m_Num++;
    //最后将记录结果做返回
    return temp;
}
    
```

#### 4.5.4 赋值运算符重载

![image-20210718090720482](D:\Qianrushi\C++核心编程\image-20210718090720482.png)

#### 4.5.5 关系运算符重载

作用：重载关系运算符，可以让两个自定义类型对象进行对比操作

![image-20210718092932954](D:\Qianrushi\C++核心编程\image-20210718092932954.png)

#### 4.5.6 函数调用运算符重载

![image-20210718093923465](D:\Qianrushi\C++核心编程\image-20210718093923465.png)

```c++
//匿名函数对象
cout<<MyAdd()(100,100)<<endl;
//MyAdd为匿名函数对象
```

### 4.6 继承

#### 4.6.1 继承的基本语法

作用：减少重复的代码

语法：class 子类：继承方式   父类

子类：也称为   派生类

父类：也称为   基类

```c++
class BasePage
{
    public:
    void header()
    {
        cout<<"首页，公开课，登录，注册..（公共头部）"<<endl;
    }
    void footer()
    {
        cout<<"帮助中心，交流合作，站内地图...（公共底部）"<<endl;
        void left()
        {
            cout<<"Java,Pyhthon,C++,...（公共分类列表）"<<endl;
        }
    }
}
//Java页面
class Java:public:BasePage
{
    public:
    void content()
    {
        cout<<"Java学科视频"<<endl;
    }
}
//C++页面
class CPP:public:BasePage
{
    public:
    void content()
    {
        cout<<"C++学科视频"<<endl;
    }
}
```

#### 4.6.2 继承方式

继承的语法：

继承方式：

- 公共继承
- 保护继承
- 私有继承

[![W8IYIe.png](https://z3.ax1x.com/2021/07/19/W8IYIe.png)](https://imgtu.com/i/W8IYIe)

#### 4.6.3 继承中的对象模型

问题：从父类继承过来的成员，哪些属于子类对象中？

#### 4.6.4 子父类构造和析构顺序

**白发人送黑发人**

[![W8I0Mt.png](https://z3.ax1x.com/2021/07/19/W8I0Mt.png)](https://imgtu.com/i/W8I0Mt)

####  4.6.5 继承同名成员处理方式

问题：当子类与父类出现同名的成员，如何通过子类对象，访问到子类或父类中同名的数据呢？

- 访问子类同名成员  直接访问即可
- 访问父类同名成员  需要加作用域 
- 成员变量

[![W8IDqf.png](https://z3.ax1x.com/2021/07/19/W8IDqf.png)](https://imgtu.com/i/W8IDqf)

- 成员函数

  [![W8IsZ8.png](https://z3.ax1x.com/2021/07/19/W8IsZ8.png)](https://imgtu.com/i/W8IsZ8)

#### 4.6.6 继承同名静态成员处理方式

[![W8IOzR.png](https://z3.ax1x.com/2021/07/19/W8IOzR.png)](https://imgtu.com/i/W8IOzR)

[![W8oiJH.png](https://z3.ax1x.com/2021/07/19/W8oiJH.png)](https://imgtu.com/i/W8oiJH)

#### 4.6.7 多继承语法

C++允许一个类继承多个类

语法：class 子类：继承方式  父类1，继承方式 父类2，......

需加作用域区分不同父类

#### 4.6.8 菱形继承

[![W8oI1A.png](https://z3.ax1x.com/2021/07/19/W8oI1A.png)](https://imgtu.com/i/W8oI1A)

[![W870MR.png](https://z3.ax1x.com/2021/07/19/W870MR.png)](https://imgtu.com/i/W870MR)

以上所继承的animal的成员即通过指针实现仅为一个值

甚至可以不用加作用域进行访问

[![W87Wzd.png](https://z3.ax1x.com/2021/07/19/W87Wzd.png)](https://imgtu.com/i/W87Wzd)