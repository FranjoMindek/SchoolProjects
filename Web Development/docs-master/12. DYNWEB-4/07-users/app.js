const createError = require('http-errors');
const path = require('path')
const cookieParser = require('cookie-parser')
const express = require('express');
const session = require('express-session')

const indexRouter = require('./routes/index');
const signupRouter = require('./routes/signup');
const loginRouter = require('./routes/login');
const logoutRouter = require('./routes/logout');
const profileRouter = require('./routes/profile');
const usersRouter = require('./routes/users');
const adminRouter = require('./routes/admin');

const globalData = require('./model/GlobalData')
const userData = require('./model/UserData')

//express middleware setup
const app = express();

//cookie-parsing middleware
app.use(cookieParser());

//body content parsing middleware
app.use(express.urlencoded({ extended: false }));
app.use(express.json());

//static content handling middleware
app.use(express.static(path.join(__dirname, 'public')));

//session middleware (transient session records)
app.use(session({secret: 'FER WiM', resave: false, saveUninitialized: true}))

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// routes 
app.use('/', indexRouter);
app.use('/signup', signupRouter);
app.use('/login', loginRouter);
app.use('/logout', logoutRouter);
app.use('/profile', profileRouter);
app.use('/users', usersRouter);
app.use('/admin', adminRouter);


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

//read the user settings
app.users = new userData('./data/users.json');
app.users.initialize(true);

module.exports = app;
