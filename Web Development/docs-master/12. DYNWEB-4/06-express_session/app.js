const createError = require('http-errors');
const path = require('path')
const express = require('express');
//const cookieParser = require('cookie-parser')
const session = require('express-session')
const FileStore = require('session-file-store')(session);

const indexRouter = require('./routes/index');

const globalData = require('./model/GlobalData')

//express middleware setup
const app = express();

//body content parsing middleware
app.use(express.urlencoded({ extended: false }));
app.use(express.json());

//session middleware
app.use(session({
  secret: 'FER WiM',
  resave: false,
  store: new FileStore(),
  saveUninitialized: true
}))

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// routes 
app.use('/', indexRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

//read the global settings
app.global = new globalData('./data/global.json');
app.global.initialize(true);

module.exports = app;
