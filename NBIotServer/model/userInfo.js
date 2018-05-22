var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var usersInfoSchema = new Schema({
    "userName": String,
    "userPwd": String,
    "userId": String,
    "userEmail": String,
    "userPhone": String,
    "userQQ": String,
    "userAdd": String
});


module.exports = mongoose.model('userInfo', usersInfoSchema, 'Users');