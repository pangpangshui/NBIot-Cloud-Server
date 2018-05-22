
let mongo = require('mongoose');
let deviceInfo = require('./deviceInfo');


module.exports = {
    storeDeviceInfo(deID, receMsg, UpOrDown, proto) {
        mongo.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot',  (err, db) => {
            if (err) {
                // console.log("数据库连接失败");
                return;
            }
            db.collection('DevicesInfo').insertOne({
                "deviceID": deID,
                "deviceData": receMsg,
                "dataDir": UpOrDown,
                "protocol": proto,
                "date": (new Date().toLocaleString())
            }, (err, result) => {
                if (err) {
                    return;
                }
                else {
                    // console.log(result)
                }
                db.close();
            });
        });
    }
};