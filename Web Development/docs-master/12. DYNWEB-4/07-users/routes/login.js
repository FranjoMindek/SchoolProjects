var express = require('express');
var router = express.Router();
const cookieParser = require('cookie-parser')


router.get('/', function(req, res, next) {
  let loginName = req.cookies.appuserID || ""
  res.render('login', { err: undefined, user: req.session.user, login: loginName });
});

router.post('/', function(req, res, next) {
  
  //check that the user is registered
  if( req.session.user !== undefined ) {
    res.render('login', { user: req.session.user, err: "Please log out first." });
    return
  }

  //check for credentials
  if( req.app.users.userExists(req.body.email)  && 
    req.app.users.getUser(req.body.email).password == req.body.password ) {

      //if successful, set persistent cookie with username (timeout=1 week)
      let expiryDate = new Date(Number(new Date()) + 604800000);  
      res.cookie('appuserID', req.body.email, { expires: expiryDate, httpOnly: true });

      //if successful, redirect to the main page
      req.session.user = req.body.email
      res.redirect("/")
    }
    else {
      res.render('login', { user: req.session.user, err: "Incorrect username or password." });
    }
});

module.exports = router;
