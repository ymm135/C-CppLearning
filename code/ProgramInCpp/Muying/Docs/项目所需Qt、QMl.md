[toc]

# 一、Qt

## 1.简介

Qt常用于开发图形界面应用程序，但它除了绘制优秀的界面外还内置了很多其他的功能，多线程、访问数据库、图库处理、音频视频处理、网络通信、文件操作等。其主要用于桌面级和嵌入式的开发。

## 2.优点

Qt相对于其他GUI库的优点：

* 简单易学：封装的很好，不需要了解windows API
* 资料丰富：其用户数量庞大，无论是官方还是非官方的资料都很齐全
* 界面优秀：可以较为容易的做出漂亮的界面和炫酷的动画
* 独立安装：全部编译为本地代码，不需要其他库的支撑
* 跨平台：跨平台支持很好，成本很低

## 3.Qt开发工具列表：

| 工具          | 说明                                                         |
| ------------- | ------------------------------------------------------------ |
| **qmake**     | 核心的项目构建工具，可以生成跨平台的 **.pro 项目文件**，并能依据不同操作系统和编译工具生成相应的 Makefile，用于构建可执行程序或链接库。 |
| **uic**       | User Interface Compiler，用户界面编译器，Qt 使用 XML 语法格式的 .ui 文件定义用户界面，uic 根据 .ui 文件生成用于创建用户界面的 C++ 代码头文件，比如 ui_xxxx.h 。 |
| moc           | Meta-Object Compiler，元对象编译器，moc 处理 C++ 头文件的类定义里面的 Q_OBJECT 宏，它会生成源代码文件，比如 moc_*****.cpp ，其中包含相应类的元对象代码，元对象代码主要用于实现 Qt 信号/槽机制、运行时类型定义、动态属性系统。 |
| rcc           | Resource Compiler，资源文件编译器，负责在项目构建过程中编译 .qrc 资源文件，将资源嵌入到最终的 Qt 程序里。 |
| **qtcreator** | 集成开发环境，包含项目生成管理、代码编辑、图形界面可视化编辑、 编译生成、程序调试、上下文帮助、版本控制系统集成等众多功能， 还支持手机和嵌入式设备的程序生成部署。 |
| assistant     | Qt 助手，帮助文档浏览查询工具，Qt 库所有模块和开发工具的帮助文档、示例代码等都可以检索到，是 Qt 开发必备神器，也可用于自学 Qt。 |
| **designer**  | Qt 设计师，专门用于可视化编辑图形用户界面（所见即所得），生成 .ui 文件用于 Qt 项目，或者用于设计QML界面。 |
| **linguist**  | Qt 语言家，代码里用 tr() 宏包裹的就是可翻译的字符串，开发人员可用 lupdate 命令生成项目的待翻译字符串文件 .ts，用 linguist 翻译多国语言 .ts ，翻译完成后用 lrelease 命令生成 .qm 文件，然后就可用于多国语言界面显示。 |
| qmlscene      | 在 Qt 4.x 里是用 qmlviewer 进行 QML 程序的原型设计和测试，Qt 5 用 qmlscene 取代了旧的 qmlviewer。新的 qmlscene 另外还支持 Qt 5 中的新特性 scenegraph 。 |

## 4.项目组成和管理

在Qt Creator左侧工具栏中单击“编辑”按钮，即可进入项目管理窗口，Qt Creator可以打开多个项目，但只有一个活动项目，活动项目名称加粗显示。

在项目名称节点下，分组管理着各种源文件，文件和分组如下：

* xxx.pro文件是项目管理文件，包括一些对项目的设置项。
*  Headers 分组，该节点下是项目内的所有头文件（.h） 
*  Sources 分组：该节点下是项目内的所有 C++源文件（.cpp） 
* Resources分组：该节点下是项目内的各种资源文件，如QML文件，图标（图片）文件，翻译文件等
  * 使用qrc文件加载资源
*  Forms 分组：该节点下是项目内的所有界面文件（.ui） 用QML编写界面则没有（.ui）文件

## 5.pro文件详解

在此文件中#为注释

```pro
TEMPLATE = app                  #表示项目使用的模板是app，是一般的应用程序
QT += qml quick gui widgets     #表示项目中加入qml quick gui widgets模块
TARGET = MYPlayer               #表示生成的目标可执行文件的名称
RESOURCES += resource/MYPlayer.qrc   #资源项目文件
TRANSLATIONS += ./resource/ui/translation/MYPlayer_zh_CN.ts  #翻译文件
SOURCES += \            
        main.cpp \
        MainApp.cpp
HEADERS += MainApp.h
```

## 6.Qt元对象系统

 Qt 的元对象系统（Meta-Object System）提供了对象之间通信的信号与槽机制、运行时类型信息和动态属性系统。 

元对象系统由以下三个基础组成：

1. QObject 类是所有使用元对象系统的类的基类。
2. 在一个类的 private 部分声明 Q_OBJECT宏，使得类可以使用元对象的特性，如动态属性、信号与槽。
3. MOC（元对象编译器）为每个 QObject 的子类提供必要的代码来实现元对象系统的特性。

 构建项目时，MOC 工具读取 C++ 源文件，当它发现类的定义里有 Q_OBJECT 宏时，它就会为这个类生成另外一个包含有元对象支持代码的 C++ 源文件，这个生成的源文件连同类的实现文件一起被编译和连接。 

## 7.Qt基本模块

| 模块                  | 描述                                                         |
| --------------------- | ------------------------------------------------------------ |
| Qt Core               | 其他模块都用到的核心非图形类                                 |
| **Qt GUI**            | 设计 GUI 界面的基础类，包括 OpenGL                           |
| **Qt Multimedia**     | 音频、视频、摄像头和广播功能的类                             |
| Qt Multimedia Widgets | 实现多媒体功能的界面组件类                                   |
| Qt Network            | 使网络编程更简单和轻便的类                                   |
| Qt QML                | 用于 QML 和 [JavaScript](http://c.biancheng.net/js/) 语言的类 |
| **Qt Quick**          | 用于构建具有定制用户界面的动态应用程序的声明框架             |
| **Qt Quick Controls** | 创建桌面样式用户界面，基于 Qt Quick 的用户界面控件           |
| **Qt Quick Dialogs**  | 用于 Qt Quick 的系统对话框类型                               |
| Qt Quick Layouts      | 用于 Qt Quick 2 界面元素的布局项                             |
| Qt SQL                | 使用 SQL 用于数据库操作的类                                  |
| Qt Test               | 用于应用程序和库进行单元测试的类                             |
| Qt Widgets            | 用于构建 GUI 界面的 [C++](http://c.biancheng.net/cplus/) 图形组件类 |

## 8.Qt定时器

QTimer类： 如果Qt无法交付所请求的计时器事件数量，它将静默地丢弃一些计时器事件。所以有时候用QTimer可能不能正常刷新，此时可以使用startTimer。

1. 用 startTimer启动一个定时器，并返回定时器id。如果启动失败，返回0.
2. 定时器每隔interval 毫秒就会启动一次，直到调用killTimer(). 如果interval=0,当没有其他系统时间发生时，会调用一次。
3. 当定时器发生时，会调用timerEvent(QTimerEvent *event).如果多个定时器在运行，可用通过timeId()来区分。

如：startTimer(40);   //一秒25帧

## 9.QThread

线程等待

void msleep(unsigned long msecs)

强制当前线程睡眠msecs毫秒

## 10.QAudioFormat、QAudioOutput

需要在qmake中添加 QT += multimedia 

QAudioFormat：

| 参数               | 描述                                                   |
| ------------------ | ------------------------------------------------------ |
| Sample Rate        | 每秒音频数据采样数（以赫兹为单位）。                   |
| Number of channels | 音频通道数（通常为单声道一个，为立体声两个）           |
| Sample size        | 每个样本中存储了多少数据（通常为8或16位）              |
| Sample type        | 样本的数值表示（通常为有符号整数，无符号整数或浮点数） |
| Byte order         | 样本的字节顺序（通常为小端，大端）                     |

| 函数                  | 功能                         |
| --------------------- | ---------------------------- |
| setSampleRate()       | 设置采样数                   |
| setSampleSize()       | 设置每个样本中存储了多少数据 |
| setChannelCount()     | 设置声道数                   |
| setCodec("audio/pcm") | 将编解码器设置为"audio/pcm"  |
| setByteOrder()        | 设置字节序                   |
| setSampleType()       | 设置样本类型                 |

QAudioOutput：（创建对象时将QAudioFormat的对象赋给它即可）

| 函数         | 作用                                                         |
| ------------ | ------------------------------------------------------------ |
| start()      | 返回一个指向内部QIODevice的指针，该指针用于将数据传输到系统的音频输出。write()可以直接向其中写入数据。 |
| stop()       | 停止音频输出，与系统资源分离。                               |
| suspend()    | 停止处理音频数据，保留缓冲的音频数据。                       |
| resume()     | 在suspend()后恢复处理音频数据                                |
| bufferSize() | 返回音频缓冲区大小                                           |
| bytesFree()  | 返回音频缓冲区中可用的可用字节数。                           |
| ...          | ...                                                          |

## 11.其余qt类

### （1）QDir(框架使用)

此类用于操作路径名及底层文件系统，获取关于目录路径及文件的相关信息，也可以用来获取Qt资源系统的文件信息。

Qdir类使用相对或绝对路径来指向一个文件/目录。

绝对路径使用“/”作为目录分隔符，以“/”或盘符做起始（Unix除外），如：

```c++
#include <QDir>

QDir path1{"/ui/image"}
QDir path2{"D:/"}
```

 相对文件名是由一个目录名称或者文件名开始并且指定一个相对于当前路径的路径。 当前路径为应用程序工作目录。

```C++
QDri path3{"images/isPlay.png"}
```

本项目只是用来判断目录是否存在，即使用其exists()函数来判断

```c++
if(!path1.exits())  //如果路径不存在则返回
{return;}
```

其余函数

|      函数      |                             功能                             |
| :------------: | :----------------------------------------------------------: |
|     path()     |                     获得所关联的目录路径                     |
|   setPath()    |                         设置新的路径                         |
| absolutePath() |                      获得目录的绝对路径                      |
|   dirName()    | 返回绝对路径中最后一个项目，即目录名，如果关联的是当前工作目录，返回“.” |
|    mkdir()     |                         创建一个目录                         |
|    rename()    |                     对关联目录进行重命名                     |
|    rmdir()     |                         一处一个目录                         |
|    exists()    |                       检测目录是否存在                       |
|   refresh()    |                         刷新目录内容                         |

还有很多相关内容及操作，这里就不一一说明了

### （2）QFont(框架使用)

QT自带的字体类，使用简单，此项目只是用其修改UI界面字体，这里直接演示一个示例,需要设置字体使用setFont(font)即可

```c++
#include<QFont>

QFont font;

font.setFamily("微软雅黑");                            //设置字体
font.setPixelSize(20);                                //设置文字像素大小
font.setPointSize(20);                                //文字大小
font.setUnderline(true);                              //下划线
font.setStrikeOut(true);                              //中划线
font.setOverline(true);                               //上划线
font.setItalic(true);                                 //斜体
font.setBold(true);                                   //粗体
font.setStyle(QFont::StyleOblique);                   //样式倾斜
font.setCapitalization(QFont::Capitalize);            //首字母大写
font.setLetterSpacing(QFont::PercentageSpacing,200);  //间距
```

### （3）QIcon(框架使用)

QT对于ico图标的处理类，此程序只利用其设置程序图标

此处只演示基础用法

```C++
setWindowIcon(QIcon(path));           //path为图标路径
```

### （4）QDebug

Qt用于输出调试信息的类，其使用既可以类似cout来使用，也可以像printf一样使用，会自动换行。

输出到控制台的两种使用方式：

1. 将字符串当作参数传给qDebug()函数（可以不用添加头文件#include <QDebug>）
2. 使用六输出的方法输出多个字符串，类似cout的使用。（需要添加头文件）

```C++
qDebug()<<"Hello World!";
```

### （5）QSetting

Qt对于配置文件(.ini)操作的类，远比直接读写文件方便。此项目使用其来储存读取语言，背景路径及其他路径等信息。

配置文件格式：其由节、键、值组成。

节：

```ini
[section]
```

参数（键=值）：

```ini
name=value
```

注释：

注解使用分号表示，在分号后面的文字，直到该行结尾全是注释

```ini
name=value;this is the comment text
```

举例：

```ini
[section1]
num1=value
num2=value2
[section2]
num3=value3;this is the num3
num4=value4
```

这里也只展示QSettings的基础用法

```C++
QSettings *defaultIni = new QSettings("default.ini",QSettings::IniFormat);//如果没有该文件会自行创建
//前面的参数为ini文件的路径，此处为相对路径，即位于工作目录下，后面的参数为声明将设置存储至ini文件中
//读取操作：
QSting num1 = defaultIni->value("section1/num1".toString());//读取section1节中键num1的值储存至num1中
//如上方没有相应值，则为空""
//写操作：
defaultInt->setValue("section2/num5",QString("value5"));//没有该节或该键都会自行创建并赋值
```

### （6）QFileInfo

Qt用于获取文件信息的类，可用于获取文件所在路径（去除文件名），获取文件名等操作，此项目中使用其来获取文件所在路径，以获取上一次打开相关文件的目录。

```C++
QFileInfo fileInfo(path);              //声明文件路径
QString string1 = fileInfo.paht();     //获取文件所在路径（去除文件名）
```

其他操作：

|        函数        |         功能         |
| :----------------: | :------------------: |
|      exits()       |   判断文件是否存在   |
|       size()       |     获取文件大小     |
|      isFile()      |    是否为普通文件    |
|      isDIr()       |      是否为目录      |
|    isSymLink()     |    是否为符号链接    |
|  symLinkTarget()   | 返回符号链接所指文件 |
| absoluteFilePath() |     返回绝对路径     |
|      suffix()      | 返回后缀名（不带.）  |

还有诸如此类的函数，这里不一一说明

### （7）QObject

Qt中所有Qt类的基类，是Qt对象模型的核心，其核心功能是信号和槽的通信机制，由于我们的程序使用的是QML，且没有特殊需求，无需特地去了解绑定机制，因为并没有自己添加的槽函数，如果使用的是QWidget的话将会常用connect这种连接机制。

这里注意只有继承了QObject的类，才具有信号槽的能力，凡是QObject类，都应该在第一行代码写上Q_OBJECT（头文件中），不管使不使用信号槽，都应该添加这个宏，这个宏的展开将为我们的类提供信号槽机制，国际化机制以及 Qt 提供的不基于 C++ RTTI 的反射能力。很多操作都会依赖这个宏。

### （8）QString

Qt中对于字符串操作的类，其特点为

* 采用Unicode编码，所以一个QChar占用两个字节
* 使用隐式共享技术来节省内存和减少不必要的数据拷贝
* 跨平台使用，不用考虑字符串的平台兼容性
* QString直接支持字符串和数字之间的相互转换
* QString直接支持字符串之间的大小比较（按照字典序）
* QString直接支持不同编码下的字符串转换
* QString直接支持std::string和std::wstring之间的相互转换
* QString直接支持正则表达式的使用

在我们转换一个“字符串常量”为QString对象的时候我们需要使用**QStringLiteral**函数。“字符串常量”指在源码中由""包含的字符串。

在Qt中除了QML处使用的是string之外，其他位置直接使用QString即可，否则在字符串传递的情况可能会出错。

### （9）QAppliction(框架使用)

Qt中用于管理GUI程序的控制流和主要设置的类，其包含窗口系统和其他来源处理过和发送过的主事件循环。它也处理应用程序的初始化和收尾工作，并提供对话管理，QApplication可以对系统和应用的大部分设置项进行设置。

对于Qt系的任何一个GUI应用，不管其有多少窗口或者没有窗口，其有且仅有一个QApplication对象.

|             函数             |      功能      |
| :--------------------------: | :------------: |
|          setFont()           |  设置程序字体  |
|     setApplicationName()     |   设置程序名   |
|       setWindowIcon()        |  设置程序图标  |
| setApplicationgDisplayName() | 设置程序显示名 |

### （10）QCoreApplication(框架使用)

继承关系：QApplication——QGUIApplication——QCoreApplication——QObject，从左到右依次继承

高清屏幕自适应设置

```C++
QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
```

|        函数         |   功能   |
| :-----------------: | :------: |
| installTranslator() | 加载语言 |

### （11）QUrl(框架使用)

此类提供了一个方便的接口使用URLs,用于转换路径为url

### （12）QList(框架使用)

 QList以列表形态存储并管理值，并能进行基于快速索引的访问，也可以进行快速的数据删除操作。 

isEmpty()用于判断是否为空。

### （13）QScopedPointer(框架使用)

需要包含头文件QPointer

QPointer为Qt中的一个模板类，为了QObject提供的一种监视指针。

声明方式为：

QPointer<T> p;

QScopedPointer为Qt里的智能指针

它包装了new操作符在堆上分配的动态对象，能够保证动态创建的对象在任何时候可以被正确的删除，其拥有更严格的所有权，并且不能转让，一旦获取了对象的管理权，你就无法再取回来，只要出了作用域，指针就会被自动删除，其拷贝构造和赋值操作都是私有的。

声明方式为：

QScopedPointer<T>  p;

|  函数   |                         功能                         |
| :-----: | :--------------------------------------------------: |
| reset() | 删除其指向的现有对象（如果有），并将指针设置为新的值 |
| data()  |               返回此对象引用的指针的值               |



### （14）QTranslator(框架即切换语言使用)

翻译文件的生成与更新具体查看下方操作一栏

该类为Qt类用于生成多语言版本的类，该类用于加载语言文件

|  函数  |                    功能                    |
| :----: | :----------------------------------------: |
| load() | 将翻译文件添加到要用于翻译的翻译文件列表中 |

如果想要不加载语言文件，直接加载默认值，只需要先reset()后不load()，并且直接installTranslator即可。

### （15）QStandardPaths(框架使用)

Qt中的系统标准路径类。所谓的系统标准路径指的是本地文件系统中，用户的特定目录或系统的配置目录。比如在Windows系统中的“我的文档”，“视频”，“图片”等目录位置。

——————我没有找到使用这个类的地方，不知道为何要包含这个头文件

### （16）QQmlApplicationEngine(框架使用)

继承自QQmlEngine

其提供了从一个QML文件里面加载应用程序的方式

### （17）QQmlContext(框架使用)

用于设置QML文件的上下文，框架中最后取消使用了该项目

### （18）QIODevice

 Qt中用于对输入输出设备进行管理 的类

|                   函数                   |                 功能                  |
| :--------------------------------------: | :-----------------------------------: |
|                 reset()                  |              重打开设备               |
|                 close()                  |          简单理解为关闭设备           |
| write(const char * data, qint64 maxSize) | 最多将数据的maxSize大小的字节写入设备 |

# 二、QML

1. QML是一种标记语言，类似于网页设计的HTML，主要用于描述程序界面，其用于定义用户界面元素的外观和行为，可以借助CSS对它进行美化，也可以借助JavaScript进行交互。其注释方式与C++相同，//和/* */
2. 使用QML开发界面优点
   * QML很灵活，可以做出炫酷的效果
   * QML是标记语言，容易编写和理解，也易于学习
   * QML界面简洁且美观，自带很多动画
   * 不同平台的QML使用相同的渲染机制，界面效果一致，不会随操作系统的同而变化

## QML基础语法

### 1.示例

一个QML文档分为import和对象生命两个部分

* import：用于指定该文档所需要引入的模块。通常这是一个模块名和版本号，比如QtQuick 2.0，也可以引入自己的模块或者其他文件
* QML元素：一个QML文档有且只有一个根元素，类似XML文档的规定。QML文档中的元素同样类似XML文档

### 2.元素关系：

* 层次关系
  * 子元素处于相对于父元素的坐标系统中，即子元素的x和y的坐标值始终相对于父元素。

### 3.基础属性

（1）属性的值由其类型决定，如果一个属性没有给值，则会使用属性的默认值,自定义属性会给定系统类型的默认值。

（2）属性可以依赖于其他属性，这种行为被称为绑定，其类似于信号槽机制，所依赖属性发生变化，该属性会得到通知，自动更新自己的值。int类型的属性会自动转换成字符串，在值发生变化时，绑定依然成立

（3）我们可以声明默认属性

* id                                                          //标识符，[^必须唯一]，相当于该元素的指针，可以直接用名字指代该元素。id不是字符串，而是一个特殊的标识符类型。一旦指定不可更改，命名规则与C++指针一致，不允许反查id
* x、y坐标                                              //相对于父元素的坐标
* width、height                                       //宽高
* property int times:24                               //自定义属性，格式为property <type> <name>:<value>

  * property alias anotherTimes:times   //属性别名，“别名即引用”
* text:"Greetings" + times                        //文本和值
* onHeightChanged:console.log('height:',height)   //属性值改变的信号处理回调，后面为控制台输出信息
* focus:true                                             //接受键盘事件需要设置focus
* color:focus?"red":"black"                      //根据focus值改变颜色

所有属性都有对应数值改变的槽函数，格式为on+属性名+Changed，属性名首字母大写，属性改变会发出相应的信号比如height属性改变，发出heightChanged信号

### 4.所用组件

#### 可视元素

1. Item           //一般用作容器
   * Item是所有可视元素中最基本的一个，其是所有其它可视元素的父元素
2. Image       //图片组件
   * smooth  :设置平滑
   * source：图面路径设置，资源中选取文件，相对路径前需要加**qrc:///**,绝对路径前需要加**file:///**
3. Rectanle    //默认的长方形组件
   * radius：半径，可以绘制圆
4. Text          //文本组件
   * text
5. MouseArea      //鼠标事件处理组件，不可见
   * onDoubleClicked
   * onEntered
   * onExited

可视元素通用属性：

| 分组     | 属性                                                         |
| -------- | ------------------------------------------------------------ |
| 几何     | x和y 用于定义元素左上角的坐标，width 和height 则定义了元素的范围。z定义了元素上下的层叠关系。 |
| 布局     | anchors（具有 left、right、top、bottom、vertical 和 horizontal center 等属性）用于定位元素相对于其它元素的margins的位置。 |
| 键盘处理 | Key 和 KeyNavigation 属性用于控制键盘；focus 属性则用于启用键盘处理，也就是获取焦点。 |
| 变形     | 提供 scale 和 rotate 变形以及更一般的针对 x、y、z 坐标值变换以及transformOrigin点的 transform 属性列表。 |
| 可视化   | opacity 属性用于控制透明度；visible 属性用于控制显示/隐藏元素；clip 属性用于剪切元素；smooth 属性用于增强渲染质量。 |
| 状态定义 | 提供一个由状态组成的列表 states 和当前状态 state 属性；同时还有一个transitions列表，用于设置状态切换时的动画效果。 |

#### 其它元素

1. Slider      //进度条
   * stepSize     //精度
2. Button      //按钮
   * onClicked
3. FileDialog      //选择文件框，需要执行open函数
   * title：标题
   * folder：默认选择路径
   * nameFilters：过滤器，过滤出可选择文件，
     * ["xxxx(\*.xx \*.xx)","xxxx(\*)"],如：["Video files(\*.mp4 \*.rmvb \*.flv)","All files(*)"]
   * onAccepted：选择了文件
   * onRejected：取消选择
4. Timer       //计时器，需要调用start开启计时，也可以用stop结束计时
   * interval：时间
   * onTriggered            //开始计时后经过相应时间后触发
5. Dialog     //弹出框，默认含有ok按钮和关闭
   * title: 弹出框的标题
   * onAccepted           //点击ok后触发事件
6. GroupBox                   // 提供带有标题的组框框架 ,相当于一个容器
   * title:容器的标题，不设置就没有
7. ColumnLayout          //垂直布局组件，内部元素一一垂直排列，RowLayout为水平布局组件，需要包含Layouts
8. RadioButton            //单选组件，在Controls 1.x版本时需要设置一个分组组件，将多个RadioButton包含在同一个分组组件内才可以实现单选，但在Controls 2.x版本后取消了那个分组组件，只需要将RadioButtion写在同一个组件下即可实现单选
   * text:文字显示
   * checked:是否处于选中状态，默认为false

# 三、QML与C++的交互

## 1.qmlRegisterType 的使用

qmlRegisterType 是一个可以将C++实现的类在QML中调用的，连接C++和QML的一个工具 ，其格式为

```C++
//qmlRegisterType<Class>( const char * uri, int versionMajor, int versionMinor, const char * qmlName)
qmlRegisterType<MYPlay>("com.imooc.myplayer", 1, 0, "MYPlay");
qmlRegisterType<MYVideoOutput>("com.imooc.myplayer", 1, 0, "MYVideoOutput");
```

<>中为C++中的类名，第一个参数指的是QML中import后的内容，相当于头文件名，第二个第三个参数分别是主次版本号，第四个指的是QML中类的名字。**第四个参数首字母一定要大写**，否则会报很难排查的错误。

可以将多个类写在同一个import头文件中，如上所示。

**在QML中如果需要使用对应函数和属性需要使用其id。**

C++的类如不需要显示继承自QObject即可，如需要显示继承自相应的QML显示类即可，如QQuickItem，QQuickPaintedItem等。

 qmlRegisterSingletonType：（框架用）
这个是一个带回调的注册函数 ，作用是将C++类注册到QML系统中并带一个回调函数。该回调函数在每次qml中调用该类函数的的时候调用，然后再回调函数里产生新的C++类提供给QML嗲用，此方法可以实现C++类的动态加载和动态切换。

```C++
qmlRegisterSingletonType<MainApp>("com.imooc.myplayer", 1, 0, "MainApp",
                                      &MainApp::GetInstance);
```



这些注册函数一般卸载main.cpp中，或者程序窗体框架类的初始化中，在注册时记得包含对应类的头文件。

**这种情况下，在QML中需要直接使用第四个参数来进行相应函数的调用**        （我不确定是否为注册方式的不同决定的使用方式不同）

## 2.交互的C++类的实现

在注册完后，QML文件中import后就可以把注册函数的第四个参数当作QML组件使用，其默认属性参考C++所继承的类，比如继承自QQuickItem类（对应QML中Item组件）就会包含QML中Item组件的属性，如x，y，anchors，width，height等属性。属性的实现如下：C++类中用于储存属性值的成员，一般设置为私有。而后需要编写三个部分：

* 用于读取和更新对应属性值的函数，为了方便一般写作

  ```C++
  属性类型 属性名() const;        //是QML中的属性名，不是成员名，读取
  void set属性名(属性类型 参数);   //更新
  ```

* 信号，一般写作

  ```C++
  signals：
  	void 属性名Changed(属性类型 参数);   //只是一个信号，不需要实现
  ```

* 声明

  ```C++
  Q_PROPERTY(属性类型 属性名 READ 读取函数名 WRITE 更新函数名 NOTIFY 信号函数名) 
  //结尾无分号，注意里面都是函数名，不带括号和其他东西
  ```

声明和信号照着编写即可，无特殊问题，需要注意的是函数的编写，读取函数的实现直接返回对应的用于存储属性值的成员即可，更新函数在编写时为了节省资源，一般会先比较传递过来的值是否与用于存储属性值的成员相同，如果相同就不再更新值，也不发送更新信号。更新函数在赋值过后需要发送值改变的信号，信号会发送给QML让他更新值。

发送信号的语句为：

```C++
emit 属性名Changed(用于存储属性值的成员);  //只要发送对应信号，QML就会更新对应属性的值
```

函数的调用：如果需要在QML中调用C++类中的函数，则需要在函数声明前添加关键字Q_INVOKABLE

```C++
Q_INVOKABLE void testFuc();
```

## 3.QML中对C++类的使用

在C++类注册以及QML中import后，QML中就可以将类当作QML组件来使用，比如：

```QML
MYPlay {
	id:myplay
}
```

这样QML中就写入了C++的类，我们来尝试写我们自己编写的属性：

假如C++头文件为如下实现：

```C++
#ifndef TEST_H
#define TEST_H

#include <QObject>
class Test : public QObject
{
    Q_OBject
    Q_PROPERTY(int testNum READ testNum WRITE setTestNum NOTIFY testNumChanged)
    public:
    	Test();
    	~Test();
    Public:
    	Q_INVOKABLE void changeTestNum(int newValue);
    
    	int testNum() const;
    	void setTestNum(int newValue);
    signals:
    	void testNumChanged(int newValue);
    private:
    	int m_mTestNum{0};
}
#endif //TEST_H
```

Cpp:

```C++
#include "Test.h"

Test::Test(){}
Test::~Test(){}

void Test::changeTestNum(int newValue)
{
    setTestNum(newValue);
}
int Test::testNum() const
{
    return m_mTestNum;
}
void Test::setTestNum(int newValue)
{
    if(m_mTestNum != newValue)
    {
        m_mTestNum = newValue;
        emit testNumChanged(m_mTestNum);
    }
}
```

上面我们定义了一个属性testNum，它已经可以在QML中使用，我们还编写了一个可以在QML中调用的函数changeTestNum，让我们看看QML中如何操作

QML:

```QML
Item {
	id: item
	width: 50
	height: 50
	property int basic: test.testNum        //自定义属性绑定了test的属性testNum
	property int advanced: 
	{
		item.width = 60
		item.height = 60
		console.log(test.testNum)
		console.log(item.width)
		console.log(item.height)
		console.log(basic)
		
		return test.testNum
	}
	Test {
		id:test
	}
	MouseArea {
		anchors.fill: parent
		onClicked:{
			test.changeTestNum(5)
		}
	}
}

```

我们定义了一个50x50大小的Item，设置了两个自定义属性都绑定了test的testNum属性，我们还定义了一个MouseArea控件填满了整个Item，当我们单击Item的时候，它会调用Test类的changeTestNum函数来更新m_mTestNum的值，由于一开始默认值为0，现在传入的值为5，所以会更新它的值并发送testNumChanged信号，让我们思考一下这个信号会影响到谁，首当其冲的自然是test的testNum属性，它会被更新为5，而后就是两个绑定到testNum属性的自定义属性，basic的值也会被更新为5，而advanced的值会使得它所包含的一系列语句全部被执行，依旧是说虽然我们没有直接发送item的width和height更新信号，却也改变了它们的值，并且还可以同步输出相应调试信息，这种较为高级的用法在我们实现实时更换语言的时候会用到。

如果我们再次点击item的时候，由于Test类的m_mTestNumy已经为5，则它并未执行更新并发送信号的语句，相应的值不会再次刷新，也就不会再输出相应的调试信息了。

## 4.QML中把C++类的相应组件当作对象传回给C++

QML中的每一个组件相当于一个QObject，我们如果需要在QML中把一个C++类的组件当作对象传给另一个C++类的话，只需要给需要获取的C++类写一个返回值属性为QObject*的属性即可，实现如下：

```C++
//第一个类GetTest类
Q_PROPERTY(QObject* source READ source WRITE setSource NOTIFY sourceChanged)
public:
	QObject *source() const;
    void setSource(QObject *source);
private:
	QObject* m_mSource{nullptr};

//第二个类为Test类
```

QML中：

```QML
GetTest {
	id: gettest
	source: test  //将test组件直接赋给source即可
}
Test {
	id: test
}
```

我们在获取这种对象后一般是要将其转换回对应类对象的，其转换语句为：

```C++
//GetTest类中
Test* test = qobject_cast<Test*>(source());
```

# 四、C++补充

## 1.List

Lists将元素按顺序储存在链表中. 与 向量(vectors)相比, 它允许快速的插入和删除，但是随机访问却比较慢。

|      函数       |              作用              |
| :-------------: | :----------------------------: |
|    assign()     |           给list赋值           |
|     back()      |        返回最后一个元素        |
|     begin()     |   返回指向第一个元素的迭代器   |
|     clear()     |          删除所有元素          |
|   **empty()**   |  **如果list是空的则返回true**  |
|      end()      |        返回末尾的迭代器        |
|     erase()     |          删除一个元素          |
|   **front()**   |       **返回第一个元素**       |
| get_allocator() |        返回list的配置器        |
|    insert()     |      插入一个元素到list中      |
|   max_size()    |  返回list能容纳的最大元素数量  |
|     merge()     |          合并两个list          |
|   pop_back()    |        删除最后一个元素        |
| **pop_front()** |       **删除第一个元素**       |
| **push_back()** |  **在list的末尾添加一个元素**  |
|  push_front()   |    在list的头部添加一个元素    |
|    rbegin()     | 返回指向第一个元素的逆向迭代器 |
|    remove()     |         从list删除元素         |
|   remove_if()   |       按指定条件删除元素       |
|     rend()      |    指向list末尾的逆向迭代器    |
|    resize()     |         改变list的大小         |
|    reverse()    |        把list的元素倒转        |
|   **size()**    |    **返回list中的元素个数**    |
|     sort()      |           给list排序           |
|    splice()     |          合并两个list          |
|     swap()      |          交换两个list          |
|    unique()     |      删除list中重复的元素      |

## 2.mutex(互斥锁)

多线程访问同一资源时，为了保证数据的一致性，最简单的方式就是使用 mutex（互斥锁）。 

创建实例，直接调用mutex的lock/unlock函数即可

```c++
mutex mux;
mux.lock();
/////////////////////////////
mux.unlock();
```

## 3.string

QML中可以直接使用一些基础的C++函数，比如string中的tostring和substring函数，tostring就是转成字符串没什么可说的。

substring：用于返回位于 String 对象中指定位置的子字符串。 其方法为string1.substring(5,[10])即返回string1中从字符索引为5开始取10个字符的子字符串。（字符串第一个字符字符索引为0），在此程序中使用该函数去除QML获取文件路径的前缀。

# 五、操作

## 1.语言翻译更新

1. 在pro文件中添加 TRANSLATIONS = xxxxxx.ts
2. 编译程序后，于Qt Creator中工具——外部——Qt语言家——更新翻译   //此时生成.ts文件
3. 使用Qt Linguist打开.ts文件选择对应语句填写对应译文并勾选翻译内容
4. Qt Creator——工具——外部——Qt语言家——发布更新      //此时生成.qm文件
5. 在项目中加载.qm文件

```QML
//rectangle.qml
import QtQuick 2.0
//根元素：Rectangle
Rectangle{
	//命名根元素
	id:root //声明属性：<name>:<value>，id必须唯一
	width:120;height:240
	color:"#D8D8D8" //颜色属性
	//声明一个嵌套元素（根元素的子元素）
	Image{
		id:rocket
			x:(parent.width - width)/2;y:40//使用parent引用父元素
			source:'assets/rocket.png'
	}
	//根元素的另一个子元素
	Text{
		//该元素未命名
		y:rocket.y + rocket.height + 20 //使用id引用元素
		width:root.width   //使用id引用元素
		horizontalAlignment:Text.AlignHCenter
		text:'Rocket'
	}
}
```





[^必须唯一]:QML有一种动态作用域机制，后加载的文档会覆盖掉前面加载的文档的相同id，但这样极其难以维护，所以请保证id唯一