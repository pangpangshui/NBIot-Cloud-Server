var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');



router.get('/', (req, res) => {
    get_device_list((rows) =>{
        let device_id = rows[0].deviceID;
        let deData = rows[0].deviceData;
        let date = rows[0].date;
        let url = '/devices/' + device_id + '/data.json';

        // res.json({
        //     status: '1',
        //     result: {
        //         device_id: device_id,
        //         deviceData: deData,
        //         date:date
        //     }
        // });
        res.send(JSON.stringify(rows));
        //res.render('deviceHistory.html', {url: url, device_id: device_id, devices: rows});
    })
});


router.get('/devices/:device_id/data.json', (req, res) => {
    var device_id = req.params.device_id;
    var total = 0;
    var rows = null;

    console.log('device_id: ' + device_id);

    let db = mongoose.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
    db.find( (err) => {
        if(err){
            console.log(err);
            res.end();
        }else{
            console.log('查询成功');
            res.code = '2.01';
            res.end();
        }
        db.close((err) => {
            res.json({total:total, rows:rows});
        });
    });

});

function get_device_list(callback) {
    //let db = mongo.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
    var selectData = (db, callback) => {    //连接到表
        var collection = db.collection('DevicesInfo');  //查询数据
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
