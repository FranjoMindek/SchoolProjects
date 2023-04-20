var express = require('express');
var router = express.Router();

router.get('/', function(req, res, next) {
  
  //clear session-user mapping
  req.session.user == undefined
  
  //destroy session object
  req.session.destroy((err) => {
    
    if(err) {
      //report possible error
      console.log(err)
    }
    else {
      //redirect to the main page
      res.redirect('./')
    }
  })
});

module.exports = router;
