var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var userInfo = require('./../model/userInfo');
var ids = require('./../model/ids')
var cors = require('cors');
//router.use(cors());

mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot');

mongoose.connection.on("connected", ()=> {
    console.log("MongoDB connect success");
});


mongoose.connection.on("error", ()=> {
    console.log("MongoDB connect error");
});

mongoose.connection.on("disconnected", ()=> {
    console.log("MongoDB connect disconnected");
});


/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send('respond with a resource');
});


router.post("/login",  (req, res, next) => {
    //res.send("hahha");
    var param = {
        userName: req.body.userName,
        userPwd: req.body.userPwd
    }
    userInfo.findOne(param, (err, doc) => {
        if (err) {
            msg: err.message
            console.log("查询错误, 连接错误还是？")
        } else {
            if (doc) {
                res.cookie("userId", doc.userId, {

                    path: '/',
                    maxAge: 1000*60*60
                });
                // req.session.user = doc;
                res.json({
                    status: '0',
                    msg: '',
                    //test: 'sdasd',
                    result: {
                        //count: doc.length,
                        //list: doc,
                        userName: doc.userName
                    }
                });
            } else {
                res.json({
                    status: '1',
                });
            }
        }
    })
});


router.post("/register",  (req, res, next) => {

    var param = {
        userName: req.body.userName,
        userPwd: req.body.userPwd,
        //userId:
    }

    ids.findAndModify({}, [], { $inc: { amount: 1 } }, {new:true}, (err, result) => {
        if (err) {
            console.log("查询错误, 连接错误还是？");
            err.message
        } else if (result) {
            // let id = result.value.amount;
            // return id.toString();
            param["userId"] = result.value.amount.toString();
            var InsertUserInfo = new userInfo(param);
            InsertUserInfo.save(param, (err, doc) => {
                if (err) {
                    res.json({
                        msg: err.message
                    });
                } else {
                    if (doc) {
                        res.cookie("userId", doc.userId, {

                            path: '/',
                            maxAge: 1000*60*60
                        });
                        // req.session.user = doc;
                        res.json({
                            status: '0',
                            msg: '',
                            //test: 'sdasd',
                            result: {
                                //count: doc.length,
                                //list: doc.userId,
                                userName: doc.userName
                            }
                        });
                    } else {
                        res.json({
                            status: '1',
                        });
                    }
                }
            });
        } else {
            console.log("取不到用户id");
        }
    });

});

module.exports = router;


