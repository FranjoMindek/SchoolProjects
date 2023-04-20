const express = require('express');
const session = require('../sessions/sessionFER')

//global state
let globalAccessCounter = 0

const router = express.Router();
router.use(session.sessionManager);

//create middleware method handler functions 
function makeRouteWithCounter(template) {

  return function(req, res, next) {

    if(req.session.access_counter === undefined)
      req.session.access_counter = 0;

      res.render(template, { 
      counterValue: ++globalAccessCounter,
      userCounterValue: ++req.session.access_counter//,
      //sessionID: req.session.id,
      //s_url: session.sessionURLBuilder(req.session.id)
    });
  }
}

router.get('/', makeRouteWithCounter('index'));
router.get('/first', makeRouteWithCounter('index'));
router.get('/second', makeRouteWithCounter('second'));
router.get('/third', makeRouteWithCounter('third'));

module.exports = router;
