var io = require('socket.io').listen(3002);
var express = require('express');
var app = express();
var router = express.Router();

app.get('/onlineusers', function(request,response) {
    //console.log(io.sockets.adapter.rooms);
    response.send(io.sockets.adapter.rooms);
});

io.on('connection', function (socket) {
     console.log('io connected' + socket.id)
     io.emit('user joined', socket.id)

     socket.on('chat.message', function (message) {
        io.emit('chat message', message);
     });

     socket.on('disconnect', function () {
         console.log('User left:' + socket.id);
         socket.broadcast.emit('user left', socket.id);
     });
});


module.exports = router;

