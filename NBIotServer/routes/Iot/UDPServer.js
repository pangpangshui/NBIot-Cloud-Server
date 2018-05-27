let dgram = require('dgram');
// let express = require('express');
// let router = express.Router();
let flag = require('./../../config');
let socketServer = require('./../../routes/SocketIO');

// module.exports = router;

module.exports = {
    CreateUdpServer(deID, dePwd, res){
        let serverSocket = dgram.createSocket('udp4');
        serverSocket.on('message', (msg, rinfo) => {

            if ((msg != "ID=" + deID + "&pwd=" + dePwd) && global.udpFlag == 0) {
                console.log("重新注册");
                res.json({
                    status: '0'
                });
                res.end();
                return "";
            }

            else if ((msg == "ID=" + deID + "&pwd=" + dePwd) || global.udpRegisterFlag == 1){
                if (msg != "ID=" + deID + "&pwd=" + dePwd)
                    serverSocket.send(msg, 0, msg.length, rinfo.port, rinfo.address);

                if ((msg == "ID=" + deID + "&pwd=" + dePwd) && global.udpRegisterFlag == 0) {
                    global.udpRegisterFlag = 1;

                    res.json({
                        status: '1'
                    });
                    res.end( () => {

                    });
                }
                else if (global.udpRegisterFlag == 1) {
                    console.log('recv %s(%d bytes) from client %s:%d\n', msg, msg.length, rinfo.address, rinfo.port);
                    socketServer.CreateSocketServer(deID, msg.toString(), serverSocket, rinfo.port, rinfo.address, null, null, null, null);
                }
            }

        });


        serverSocket.on('error', (err) => {
            console.log('error, msg - %s, statck - %s\n', err.message, err.stack);
        });

        serverSocket.on('listening', () => {
            console.log("echo server is listening on port 18777")
        });
        if (global.udpCreateFlag == 0) {
            serverSocket.bind(18777);
            global.udpCreateFlag = 1;
        }

    }
};