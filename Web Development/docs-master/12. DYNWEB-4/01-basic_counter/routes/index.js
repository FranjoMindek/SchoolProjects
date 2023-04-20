const express = require('express');
const router = express.Router();

//global state
let globalAccessCounter = 0

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { counterValue: ++globalAccessCounter });
});

module.exports = router;
