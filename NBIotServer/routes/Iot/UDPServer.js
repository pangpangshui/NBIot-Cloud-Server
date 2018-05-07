let dgram = require('dgram');
let express = require('express');
let router = express.Router();



// router.post('/', (req, res) => {

var serverSocket = dgram.createSocket('udp4');
serverSocket.on('message', (msg, rinfo) => {
    console.log('recv %s(%d bytes) from client %s:%d\n', msg, msg.length, rinfo.address, rinfo.port);
    serverSocket.send(msg, 0, msg.length, rinfo.port, rinfo.address);
});


serverSocket.on('error', (err) => {
    console.log('error, msg - %s, statck - %s\n', err.message, err.stack);
});

serverSocket.on('listening', () => {
    console.log("echo server is listening on port 18777")
});
serverSocket.bind(18777);

// });


module.exports = router;