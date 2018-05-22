var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
let infolist = [];

/* GET users listing. */
router.get('/', function(req, res, next) {
    get_device_list((staticsData) =>{
        infolist.push(staticsData);
        console.log(infolist);
        if (infolist.length == 3) {
            res.end(JSON.stringify(infolist));
            infolist = [];
        }
    })
});



function get_device_list(callback) {
    //let db = mongo.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
    var selectData = (db, callback) => {    //连接到表
        var collection = db.collection('DevicesInfo');  //上行数据数量
        collection.find({"dataDir":'上行数据'}).count((err, result) => {
            if(err) {
                console.log('Error:'+ err);
                return;
            }
            callback({"receNum" :result});
        });
        collection.find({"dataDir":'下行数据'}).count((err, result) => {  //下行数据数量
            if(err) {
                console.log('Error:'+ err);
                return;
            }
            callback({"tranNum" :result});
        });

        collection = db.collection('DevicesDetailInfo');  //设备数量
        collection.find().count((err, result) => {
            if(err) {
                console.log('Error:'+ err);
                return;
            }
            callback({"deNum" :result});
        });
    };
    mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot', (err, db) => {
        selectData(db, (result) => {
            //console.log(result);
            callback(result);
            db.close();
        });
    });
}



module.exports = router;


