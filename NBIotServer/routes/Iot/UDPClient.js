var dgram = require('dgram');

var clientSocket = dgram.createSocket('udp4');

var message = [
    'hello udp server',
    'are you ok?'
];

var index = 0;

function sendMsg() {
    var msg = message[index];
    index += 1;
    if (index == message.length) {
        index = 0;
    }
    clientSocket.send(msg, 0, msg.length, 7, "localhost");
}


setInterval(sendMsg, 1000);


clientSocket.on('message', (msg, rinfo) => {
    console.log('recv %s(%d) from server\n', msg, msg.length);
})

clientSocket.on('error', (err) => {
    console.log('error, msg - %s, stack - %s\n', err.message, err.stack);
})

clientSocket.bind(54333);