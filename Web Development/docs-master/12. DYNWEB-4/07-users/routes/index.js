//const app = require('../app');
const express = require('express');
const session = require('express-session')

const router = express.Router()


router.get('/', (req,res) => {
  res.render('index', { user: req.session.user })
});

module.exports = router;
