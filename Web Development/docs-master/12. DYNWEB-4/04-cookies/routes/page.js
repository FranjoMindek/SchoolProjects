const express = require('express');
const path = require('path')
const cookieParser = require('cookie-parser')

const router = express.Router();


/* GET any page. */
router.get('/*', function(req, res, next) {

  res.render('page', { 
    title: 'Cookie spotter',
    path: req.path,
    cookies: req.cookies
 });
});

module.exports = router;
