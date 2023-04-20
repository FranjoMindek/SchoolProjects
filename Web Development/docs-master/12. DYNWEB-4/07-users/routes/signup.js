const express = require('express');
//const app = require('../app')

const router = express.Router();
 

router.get('/', function(req, res, next) {
  res.render('signup', { err: undefined, user: req.session.user })
});

router.post('/', function(req, res, next) {

    //check for password consistency
    if( req.body.passwd1 != req.body.passwd2 ) {
      res.render('signup', { user: req.session.user, err: "Password entries do not match"})
      return
    }
    //console.log(req.body)
    
    //check for existing user with the same username
    if( req.app.users.userExists(req.body.email) ) {
      res.render('signup', { user: req.session.user, err: "User already exists"})
      return
    }

    //register a new user
    let user =  req.app.users.createUser(req.body.email, req.body.passwd1, req.body.email)
    user.firstName = req.body.firstName
    user.lastName  = req.body.lastName
    req.app.users.store()
    
    //associate the new user with the session
    req.session.user = req.body.email

    //TODO: redirect to profile page
    res.redirect('./profile')
});


module.exports = router;
