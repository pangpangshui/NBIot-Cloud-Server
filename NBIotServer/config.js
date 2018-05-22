// module.exports = {
//     getudpFlag() {
//         let udpflag = 0;//在函数内声明一个变量，作用域是函数内
//
//         return function(){ //返回的一个function能访问到_value，所以_value并不是global级别的变量，但是可以通过这个接口访问到
//             return udpflag;
//         };
//     },
//     setudpFlag(flag) {
//
//     }
// };//一个立即执行的匿名函数


global.udpRegisterFlag = 0;
global.udpCreateFlag = 0;
global.socketFlag = 0;
global.io;
global.UdpOrCoAP = 0;
global.sendCoapFlag = 0;