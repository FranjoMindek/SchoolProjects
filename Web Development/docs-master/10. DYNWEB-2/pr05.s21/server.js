var http = require('http');
http.createServer(function(req, res) {
    console.log(req.url);
    res.writeHead(200, { 'Content-Type': 'text/html' }); // header
    res.write('Hello World!'); // body
    res.end();
}).listen(80); // sluša na portu 80