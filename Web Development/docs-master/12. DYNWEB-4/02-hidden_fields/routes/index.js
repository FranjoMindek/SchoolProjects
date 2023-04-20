const express = require('express');
const session = require('../sessions/sessionFER')

const router = express.Router();

//global state
let globalAccessCounter = 0

//session manager middleware
router.use(session.sessionManager);

/* GET home page. */
router.get('/', function(req, res, next) {
  if(req.session.access_counter === undefined)
    req.session.access_counter = 0;

  res.render('index', { 
    counterValue: ++globalAccessCounter,

    userCounterValue: ++req.session.access_counter,
    sessionID: req.session.id
   });
});

module.exports = router;
