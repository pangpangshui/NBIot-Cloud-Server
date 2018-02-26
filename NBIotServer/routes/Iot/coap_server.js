let express = require('express');
let router = express.Router();
let coap = require('coap');

router.get('/', (req, res, next) => {
    server = coap.createServer();
    server.on('request', (req, res) => {
        res.end('Hello' + req.url.split('/')[1] + '\n');
    })


    server.listen(() => {
        console.log('server created');
        let req = coap.request('coap://localhost/coap')
        req.on('response', (res) => {
            res.pipe(process.stdout);
            console.log("client recieved");
            res.on('end', () => {
                process.exit(0)
            })
        })

        req.end();
    })
});


module.exports = router;
