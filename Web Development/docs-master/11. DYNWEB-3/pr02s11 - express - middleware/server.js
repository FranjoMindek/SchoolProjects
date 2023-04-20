const express = require('express');
const app = express();

app.use(function(req, res, next) {
    console.log('Incoming request:', req.url);
    next();
});

app.use(function(req, res, next) {
    // zamislimo da ovdje provjeravamo u bazi podataka
    // je li (a) korisnik postojeći.
    //       (b/c) ako je postojeći, je li: admin ili user?
    let i = Math.floor(Math.random() * 3);
    if (i == 2) {
        res.status(403).send('Unknown user');
    } else {
        req.user = ["user", "admin"][i];
        next();
    }
});

app.get('/', function(req, res) {
    if (req.user === 'admin') {
        res.send('Hello Admin!');
    } else {
        res.send('This page is for admins only.');
    }
});

app.listen(3000);