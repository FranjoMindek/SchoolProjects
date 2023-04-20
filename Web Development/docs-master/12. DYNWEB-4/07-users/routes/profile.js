var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {

  //check if a registered user is trying to access the admin page
  if( req.session.user === undefined) {
    res.redirect("/")
    return
  }

  //render the page with the profile data for the registered user
  res.render('profile', { user: req.app.users.getUser(req.session.user) });
});

module.exports = router;
