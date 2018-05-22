
let express = require('express');
let router = express.Router();
let http = require('http');
let flag = require('./../config');
let StoreDeInfo = require('./../model/storeDeviceInfo');
let sendCoAP = require('./Iot/SendDataCoAP');
let io;

module.exports  = {
    CreateSocketServer(deID, receMsg, serverSocket, rport, raddress, coap, remoteAddress, remotePort, agen) {

        // let receMsg = msg.toString();
        if (global.socketFlag == 0) {
            var server = http.createServer((req, res) => {

            }).listen(3200, "10.135.50.141");//创建http服务
            // }).listen(3200, "193.112.57.70");//创建http服务
            console.log('Server running at http://10.135.50.141:3200/');
            // console.log('Server running at http://193.112.57.70:3200/');
            io = require('socket.io').listen(server);
            global.socketFlag = 1;
        }

        if (global.socketFlag == 2) {
            console.log(receMsg);

            io.sockets.emit('ReceUdpData', {//触发emit,前端接收
                receUdpData: receMsg
            });
            if ((serverSocket != null && rport != null && raddress != null) && receMsg != '') {
                StoreDeInfo.storeDeviceInfo(deID, receMsg, "上行数据", "UDP");
            }
            else if ((coap != null && remotePort != null && remoteAddress != null && agen != null) && receMsg != '')
                StoreDeInfo.storeDeviceInfo(deID, receMsg, "上行数据", "CoAP");

            receMsg = "";
        }


        io.sockets.on('connection', (socket) => {

            console.log('链接成功');
            console.log(receMsg);

            io.sockets.emit('ReceUdpData', {//触发emit,前端接收
                receUdpData: receMsg
            });
            if ((serverSocket != null && rport != null && raddress != null)  && receMsg != '') {
                StoreDeInfo.storeDeviceInfo(deID, receMsg, "上行数据", "UDP");
            }
            else if ((coap != null && remotePort != null && remoteAddress != null && agen != null) && receMsg != '')
                StoreDeInfo.storeDeviceInfo(deID, receMsg, "上行数据", "CoAP");
            receMsg = "";
            global.socketFlag = 2;

            socket.on('TxData', (Data) => {//监听前端发送的TxData
                console.log(Data);
                socket.emit('TransUdpData', {//触发emit,前端接收
                    transUdpData: Data
                });
                if ((serverSocket != null && rport != null && raddress != null) && receMsg != '') {
                    serverSocket.send(Data, 0, Data.length, rport, raddress);
                    StoreDeInfo.storeDeviceInfo(deID, Data, "下行数据", "UDP");
                }
                else {
                    sendCoAP.SendDataByCoAP(Data, coap, remoteAddress, remotePort, agen);
                    StoreDeInfo.storeDeviceInfo(deID, receMsg, "下行数据", "CoAP");
                }


            });

            socket.on('disconnect', () => {
                console.log('链接断开');
            });

        });
    }
};


// module.exports = router;

