# C++ Primer Plus

## 16 String类和标准模板库

### 16.1 string 类

#### 16.1.1 构造字符串

- template<class Iter>string(Iter begin,Iter end);

  将string对象初始化为区间[begin)内的字符，begin和end为指针

- string(const string& str,size_type pos=0,size_type n=npos)

  将一个string对象初始化为对象str中从位置pos开始到结尾，或从pos位置开始的n个字符

#### 16.1.2 string输入 P533-534

- getline有/n,get无/n

- getline的两个版本(都有可选参数，用于指定使用哪个字符来确定输入的边界)

  ```c++
  cin.getline(array,10);
  //可能缩短输入
  getline(cin,array);
  //string版本会自动调整目标string对象的大小
  ```

- string类的getline()函数从输入中读取字符，并将其读取到目标string中，直到发生下列三种情况：
  - 到达文件尾,eof()将返回true;
  - 遇到分界字符(默认为\n)，在这种情况下，把分界字符从输入流中删除，但不存储它；
  - 读取的字符数达到最大允许值，fail()将返回true;

#### 16.1.3 使用字符串

比较字符串：ASCII码;

确定长度：.length()   .size();

搜索字符串或字符