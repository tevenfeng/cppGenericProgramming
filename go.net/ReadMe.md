# 局域网P2P围棋-五子棋小游戏
### 冯定文 2016229064 
https://github.com/tevenfeng/cppGenericProgramming/tree/master/go.net

# 具体展示请参考视频
视频地址：[https://v.qq.com/x/page/f051479v0ez.html](https://v.qq.com/x/page/f051479v0ez.html)

## 简介
&emsp;&emsp;本软件使用Qt5.8在Windows 10下配合Visual Studio 2015开发；软件采用P2P的形式，用户打开软件时向局域网内广播自己上线的消息，所有其他在线用户收到后保存下来并返回自己的信息，这样每个用户都可以及时更新在线用户的信息。在获取到在线用户信息后即可选择一个用户发起游戏邀请，对方同意后即可开始游戏。游戏过程中，鼠标点击棋盘位置落子。围棋提子使用的是广度优先搜索算法搜索死棋串并将其从棋盘上删除；五子棋输赢判断采取以落子点为起点向八个方向搜索的策略。

## 主要数据结构
顺序表：已落棋子的信息的存储  
队列：广度优先搜索中存储待扩展搜索的棋子信息  

## 主要类说明
Chess：棋子类，定义了棋子的颜色，横纵坐标信息  
DataGram：数据报文类，定义了数据报文的类型，源地址和目的地址，游戏类型（围棋或五子棋），以及一个Chess类实例用于传输落子信息；同时包含一个函数用于将数据报文转成Json以便发送  
DataReceiver：数据接收器，用于监听局域网内发送给本地的数据报文  
DataSender：数据发送器，用于发送数据报文，发送形式包括广播和定向发送两种；其中广播用于发送用户上线、下线消息，定向发送用于游戏中途用户间互发落子信息  
GameWindow：游戏窗口类，包括了围棋、五子棋两种游戏的游戏中各种逻辑的实现  
GoChecker：主要实现了以广度优先搜索为基础的围棋提子算法  
gonet：主窗口，实现了用户上线、下线以及发起、接受游戏邀请的功能  
JsonParser：json解析类  
MessageType：枚举类，定义了数据报文的类型枚举  
MessageWindow：消息窗口类，实现了游戏邀请、拒绝邀请等提示窗口  
Owner：枚举类，定义了棋盘上交叉点以记棋子的黑白归属，0为空，1为黑，2为白  

## 截图
#### 在线用户信息、邀请界面  
![初始界面](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/start2.png)  

### 围棋  
#### 收到围棋邀请  
![围棋邀请](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/request.png)  
#### 同意游戏并开始游戏  
![围棋](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/gaming2.png)  
![围棋](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/gaming4.png)  
![围棋](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/gaming5.png)  
&emsp;&emsp;从上图可知，黑棋被围住了以后就被提子了。此处围棋所采用的提子算法为广度优先搜索算法，搜索死棋串后进行提子。  
&emsp;&emsp;由于围棋判断输赢的方法是根据双方同意的情况下定的，过于复杂，所以本软件没有做自动判断输赢的算法。  

### 五子棋
#### 收到五子棋邀请
![五子棋邀请](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/requestFive.png)  
#### 同意游戏并开始游戏
![五子棋](https://raw.githubusercontent.com/tevenfeng/cppGenericProgramming/master/go.net/screenshots/FiveWin.png)  
&emsp;&emsp;五子棋的输赢判断算法：从当前刚刚落下的棋子向上、向下、向左、向右以及左上、左下、右上、右下八个方向分别统计是否满足五子棋赢的条件即可。  