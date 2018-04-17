var CoAP = require('coap-node');
var cnode = new CoAP('test');

cnode.on('registered', function () {
    
})


cnode.register('193.112.57.70', 5683, function (err, rsp) {
    console.log(rsp);
})