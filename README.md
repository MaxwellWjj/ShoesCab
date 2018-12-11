# ShoesCab
Intelligent shoes cabinet based on STM32
## 功能介绍
众所周知，随着物联网应用的飞快发展，智能家居已经进入了普通家庭里，不再是一个抽象的概念。虽然市场上已经慢慢出现了健康家居产品，但经我们团队的调查研究，鞋柜系列产品还没出现可远程控制，自动工作的功能，所以我们小组设计了“鞋柜同学”这款产品，对于冬天气温低，下雨天湿鞋，运动后鞋子发臭这些让使用者心烦的事情，可以自动帮你搞定，充分保护你的健康。同时，这款鞋柜可以连接到我们设计的手机app，随时可以读取鞋柜内的各项环境指标，也可以通过app远程控制鞋柜，实现“自动+手动”的智能化家居方案。产品整体成本较低，性价比较高。
## 工程模块
HARDWARE文件夹：外部外设驱动  
FONT文件夹：中文字库导入程序  
main.c: 主程序  
GUI.c: 系统人机交互界面  
StateMachine.c: 系统状态机描述  
ESP8266文件夹： WiFi通信模块以及鞋柜工作模块  
