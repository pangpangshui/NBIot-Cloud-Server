let express = require('express');
let router = express.Router();

var coapServer = require('./Iot/CoAPServer');
let udpServer = require('./Iot/UDPServer');
// let socketServer = require('./../routes/SocketIO');

// var coap_port = 5683;
// var host = '0.0.0.0';

function isRealNum(val){
    // isNaN()函数 把空串 空格 以及NUll 按照0来处理 所以先去除
    if(val === "" || val == null){
        return false;
    }
    if(!isNaN(val)){
        return true;
    }else{
        return false;
    }
}


router.post('/deviceInfo', (req, res) => {

    let deID = req.query.deviceID,
    dePwd = req.query.devicePwd;

    if (!isRealNum(deID)) {
        global.UdpOrCoAP = 2;
        let udpmsg = udpServer.CreateUdpServer(deID, dePwd, res);
        // socketServer.CreateSocketServer();
    } else {
        global.UdpOrCoAP = 1;
        // 启动coap服务器
        // coap.createServer(coap_routes).listen(coap_port);
        // console.log('CoAP Server Listening on :' + host + ':' + coap_port);
        // console.log((res));
        let response = res;
        // console.log((response));
        coapServer.CreateCoAPServer(deID, response);
    }


});


module.exports = router;