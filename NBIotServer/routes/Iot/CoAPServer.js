let router = require('./../../lib/coap-router');
let mongo = require('mongoose');
let deviceInfo = require('./../../model/deviceInfo');

let route = new router();
let coap   = require('coap'),
    server = coap.createServer({piggybackReplyMs: 50});
let coapPacket = require('coap-packet');
let ranNum = require('./../../model/randomNum');
let socketServer = require('./../../routes/SocketIO');
let remotePort;
let remoteAddress;
let agen;


module.exports = {

    CreateCoAPServer(deID, response) {
        // console.log('3' + (response));
        server.on('request', (req, res) => {

            if ((req.url == ('/t/r?ep=' + deID)) && req.method == "POST") {
                remotePort = req.rsinfo.port;
                remoteAddress = req.rsinfo.address;
                res.code = '2.04';
                res.end( () => {
                    setTimeout(() => {
                        server.close();
                        server.listen(38777);
                        let token = ranNum.randomWord(false, 7);
                        console.log(token);
                        let rPort = req.rsinfo.port;
                        rPort = rPort.toString(16);
                        let HexPort = [];
                        for (let i = 0; i < rPort.length; i += 2) {
                            HexPort.push(Number('0x' + rPort.slice(i, i + 2)));
                        }

                        // console.log(HexPort);

                        agen = new coap.Agent({type:"udp4", port:5683});
                        var requestOptions = {
                            host: req.rsinfo.address,
                            port: req.rsinfo.port,
                            pathname: '/t/d',
                            method: 'GET',
                            confirmable: true,
                            observe: true,
                            retrySend: 5,
                            agent: agen
                        };
                        var reqCoap = coap.request(requestOptions);
                        // reqCoap.setOption("observe", "0");
                        reqCoap.setOption("Uri-Port", Buffer.from(HexPort));
                        reqCoap.end();
                        reqCoap.on('response', (resp) => {
                            if (resp.code == '2.05') {
                                //返回给前端显示设备上线，对应的是响应码为2.05的ASK响应
                                // console.log((response));
                                response.json({
                                    status: '2'
                                });
                                response.end();
                            }
                            global.sendCoapFlag = 1;
                            resp.pipe(process.stdout); //只有该句可输出上行payload, 此处抓取的是第二个响应，即non响应(不是请求), 第一个是ASK响应
                            resp.setEncoding('utf8');
                            resp.on('data', (receCoAPData) =>{
                                console.log(receCoAPData);
                                socketServer.CreateSocketServer(deID, receCoAPData.toString(), null, null, null, coap, remoteAddress, remotePort, agen);
                            });

                            // console.log('Got response:', resp.code,resp.payload);
                            // server.close();
                            // server.listen(5683, () => {
                            //     console.log('server started again1');
                            // });

                        });
                    },"500");
                });

            } else {
                response.json({
                    status: '0'
                });
                response.end();
            }

        });

        // server.on('request', (req, res) => {
        //     if ((req.url == ('/t/r?ep=' + deID)) && req.method == "POST") {
        //
        //     } else {
        //         console.log(JSON.stringify(req));
        //     }
        // });

        server.listen(function() {
            console.log('server started');
        });

    }
};
