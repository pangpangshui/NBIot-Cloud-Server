var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var deviceInfoSchema = new Schema({
    "deviceID": String,
    "deviceData": String,
    "date": String
});


module.exports = mongoose.model('deviceInfo', deviceInfoSchema, 'DevicesInfo');