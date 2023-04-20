const http = require('http');
const fs = require('fs');

http.createServer(function(req, res) {
    console.log(req.url);
    fs.readFile(__dirname + req.url, function(err, data) {
        if (err) {
            console.error(err);
            res.writeHead(404);
            res.end(JSON.stringify(err));
        } else {
            res.writeHead(200 /* MIME? */ );
            res.end(data);
        }
    });
}).listen(80); // sluša na portu 80