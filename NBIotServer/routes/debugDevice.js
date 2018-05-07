let express = require('express');
let router = express.Router();
let mongo = require('mongoose');
let udpServer = require('./../routes/Iot/UDPServer');

router.post('/', (req, res) => {

    let format = req.query.deviceID,
    type = req.query.devicePwd;
    console.log(format, type);
    // let db = mongo.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
    // let content = { deviceID: param.deviceID, devicePwd: param.devicePwd, deviceName: param.deviceName,
    //     deviceAddr: param.deviceAddr,deviceDetail: param.deviceDetail };
    // let monInsert = new devicesDetailInfo(content);
    // monInsert.save(function(err){
    //     if(err){
    //         console.log(err);
    //         res.end();
    //     }else{
    //         console.log('成功插入数据');
    //         res.json({
    //             status: '1',
    //             deviceID: param.deviceID
    //         });
    //         res.end();
    //     }
    //     db.close();
    // });
    res.end();
});


module.exports = router;