let router = require('./../../lib/coap-router');
let mongo = require('mongoose');
let deviceInfo = require('./../../model/deviceInfo');

let route = new router();
let coap   = require('coap'),
    server = coap.createServer({piggybackReplyMs: 50});
let coapPacket = require('coap-packet');


module.exports = {

    SendDataByCoAP(payload, coap, remoteAddress, remotePort, agen) {
        if (global.sendCoapFlag == 1) {
            console.log(new Date().toLocaleString());
            // server.close();
            // server.listen(38777);
            // var payload = "testdown";
            var requestOptions = {
                host: remoteAddress,
                port: remotePort,
                pathname: '/t/d',
                method: 'POST',
                confirmable: true,
                observe: true,
                retrySend: 5,
                agent: agen
            };
            var reqreturn = coap.request(requestOptions);
            reqreturn.on('response', (resp) => {
                // resp.pipe(process.stdout); //只有该句可输出上行payload
                console.log('Got response:', resp.code, resp.payload);
            });
            reqreturn.end(payload);
        }
    }

};
