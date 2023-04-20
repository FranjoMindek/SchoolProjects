var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {

  //check if a registered user is trying to access the admin page
  if( req.session.user === undefined) {
    res.redirect("/login")
    return
  }
  
  //if not defined, initialize overall page access counter
  if( req.app.global.data.userspace_count === undefined )
    req.app.global.data.userspace_count = 0
  
  //if not defined, initialize per-user page access counter
  if( req.app.users.getUser(req.session.user).userspace_count === undefined )
    req.app.users.getUser(req.session.user).userspace_count = 0

  //increase overall and per-user page access counters
  req.app.global.data.userspace_count++
  req.app.users.getUser(req.session.user).userspace_count++

  //save global and user data
  req.app.global.store()
  req.app.users.store()

  //render the page
  res.render('users', { 
    user: req.session.user, 
    user_count: req.app.users.getUser(req.session.user).userspace_count,
    global_count: req.app.global.data.userspace_count
   });
});

module.exports = router;
