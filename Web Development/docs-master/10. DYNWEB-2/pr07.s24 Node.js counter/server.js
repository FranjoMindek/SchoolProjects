const http = require('http');
let counter = 0;
http.createServer(function(req, res) {
    console.log("req.path", req.url, counter);
    counter += req.url === '/';
    res.writeHead(200);
    res.end(`Ova stranica je posjecena ${counter} puta.`);
}).listen(80);