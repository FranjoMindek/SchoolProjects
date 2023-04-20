const express = require('express');
const app = express();

app.use(express.static('www.hr'));
// Tipično:
// app.use(express.static('public'));
// app.use(express.static('assets'));
// (može ih biti više!)

app.listen(3000);