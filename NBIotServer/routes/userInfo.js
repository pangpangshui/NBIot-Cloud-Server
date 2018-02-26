var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var userInfo = require('./../model/userInfo');

mongoose.connect('mongodb://zjq:123zz321@127.0.0.1:27017/NBIot')

mongoose.connection.on("connected", ()=> {
    console.log("MongoDB connect success")
});


mongoose.connection.on("error", ()=> {
    console.log("MongoDB connect error")
});

mongoose.connection.on("disconnected", ()=> {
    console.log("MongoDB connect disconnected")
});


router.get("/", (req, res, next) => {
    //res.send("hahha");
    var param = {
        userName: req.body.userName,
        userPwd: req.body.userPwd
    }
    userInfo.findOne(param, (err, doc) => {
        if (err) {
            res.json({
                status: '1',
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
                        //list: doc,
                        userName: doc.userName
                    }
                });
            }
        }
    })
});


module.exports = router;