var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
//let devicesDetailInfo = require('./../model/deviceDetailInfo');


router.get('/', (req, res) => {
    get_device_list((rows) =>{
        res.send(JSON.stringify(rows));
    })
});


function get_device_list(callback) {
    var selectData = (db, callback) => {    //连接到表
        var collection = db.collection('DevicesDetailInfo');  //查询数据
        collection.find().toArray((err, result) => {
            if(err) {
                console.log('Error:'+ err);
                return;
            }
            callback(result);
        });
    }
    mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot', (err, db) => {
        selectData(db, (result) => {
            //console.log(result);
            callback(result);
            db.close();
        });
    });
}


module.exports = router;
