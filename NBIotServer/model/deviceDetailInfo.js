var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var deviceInfoSchema = new Schema({
    deviceID: String,
    devicePwd: String,
    deviceName: String,
    deviceAddr: String,
    deviceDetail: String
});


module.exports = mongoose.model('devicesDetailInfo', deviceInfoSchema, 'DevicesDetailInfo');