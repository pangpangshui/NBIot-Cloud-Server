let coap = require('coap');
let router = require('./../../lib/coap-router');
let mongo = require('mongoose');
let deviceInfo = require('./../../model/deviceInfo');

let route = new router();



route.post('/devices/{device_id}', (req, res) => {
    console.log(new Date().toLocaleString());

    let ts = Math.round(new Date().getTime()/10000);
    console.log(ts);

    let device_id = req.params.device_id;
    console.log(device_id);
    let payload = JSON.parse(req.payload);
    let deviceData = payload.deviceData;

    let db = mongo.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
    let content = {deviceID:device_id, deviceData:deviceData, date:(new Date().toLocaleString())};
    let monInsert = new deviceInfo(content);
    monInsert.save(function(err){
        if(err){
            console.log(err);
            res.code = '4.00';
            res.end();
        }else{
            //console.log('成功插入数据');
            res.code = '2.01';
            res.end();
        }
        db.close();
    });

    res.code = '2.04';
    res.setOption('Content-Format', 'application/json');
    res.end(JSON.stringify({ts: Math.round(new Date().getTime()/1000)}));
});


module.exports = route;
