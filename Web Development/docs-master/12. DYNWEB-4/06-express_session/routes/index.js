//const app = require('../app');
const express = require('express');
const session = require('express-session')

const router = express.Router()

//create middleware method handler functions 
function makeRouteWithCounter(template) {

  return function(req, res, next) {

    if(req.session.access_counter === undefined)
      req.session.access_counter = 0;
    
    //global context
    if(req.app.global.data.access_counter === undefined)
      req.app.global.data.access_counter = 0
    
    //render page
    res.render(template, { 
      counterValue: ++req.app.global.data.access_counter,
      userCounterValue: ++req.session.access_counter
    })

    //save global context
    req.app.global.store()

  }
}

router.get('/', makeRouteWithCounter('index'));
router.get('/first', makeRouteWithCounter('index'));
router.get('/second', makeRouteWithCounter('second'));
router.get('/third', makeRouteWithCounter('third'));

module.exports = router;
