# NBIot-Cloud-Server
NB-Iot project including a cloud server


  该项目分为两部分，第一部分是云平台，第二部分是硬件部分，目前只支持Stm32f10x系列，如果适配其他的STM32系列只需要一直对应的NB驱动库即可，参考textNB的子项目。
  
  第一部分由前端后台和数据库构成，前端对应的是NBIot子项目，后台对应的是NBIotServer子项目。前端采用Vue.js开发，后端采用Node.js开发。具体技术可参考pdf文档。数据库采用MongoDB，具体的集合设计也可参考pdf文档。
  
  目前以实现UDP和CoAP协议的通信，本项目将持续开发，后续会支持MQTT、TCP等协议，并支持Adruino、树莓派、ARM9以上等硬件。
  
  前端后台部署需要先运行cnpm i安装所有依赖的模块。
