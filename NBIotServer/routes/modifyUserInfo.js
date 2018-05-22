var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var userInfo = require('./../model/userInfo');
var ids = require('./../model/ids')


// mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');
//
// mongoose.connection.on("connected", ()=> {
//     console.log("MongoDB connect success");
// });
//
//
// mongoose.connection.on("error", ()=> {
//     console.log("MongoDB connect error");
// });
//
// mongoose.connection.on("disconnected", ()=> {
//     console.log("MongoDB connect disconnected");
// });




/* GET users listing. */
router.post('/', function(req, res, next) {
    // let db = mongoose.createConnection('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');

    let queryParam = {
        userName: req.body.userName
    };
    let updateParam = {
        userName: req.body.userName,
        userEmail: req.body.userEmail,
        userPhone: req.body.userPhone,
        userQQ: req.body.userQQ,
        userAdd: req.body.userAdd
    };

    mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot',  (err, db) => {
        userInfo.findOneAndUpdate(queryParam, {$set: updateParam}, {new: true}, (err, doc) => {
            if (err) {
                console.log("更新错误");
            } else if (doc) {
                // console.log(doc);
                res.json({
                    status: '1',
                    result: {
                        userName: doc.userName,
                        userEmail: doc.userEmail,
                        userPhone: doc.userPhone,
                        userQQ: doc.userQQ,
                        userAdd: doc.userAdd
                    }
                });
            }
            db.close((err) => {
                console.log("关闭错误");
            });
        });
    });
});


module.exports = router;


