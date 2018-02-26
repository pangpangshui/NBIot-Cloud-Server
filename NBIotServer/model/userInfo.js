var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var usersInfoSchema = new Schema({
    "userName": String,
    "userPwd": String,
    "userId": String
});


module.exports = mongoose.model('userInfo', usersInfoSchema, 'Users');