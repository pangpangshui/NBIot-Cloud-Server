let mongoose = require('mongoose');
let Schema = mongoose.Schema;


var idsSchema = new Schema({
    "ids": Number,
    "name": String
});

idsSchema.statics.findAndModify = function (query, sort, doc, options, callback) {
    return this.collection.findAndModify(query, sort, doc, options, callback);
};

module.exports = mongoose.model('ids', idsSchema, 'ids');

