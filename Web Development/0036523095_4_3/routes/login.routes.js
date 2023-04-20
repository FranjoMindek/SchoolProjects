const express = require('express');
const router = express.Router();
const User = require('../models/UserModel')


router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //vrati login stranicu
    res.render('login', {
        title: 'Log in',
        linkActive: 'login',
        user: req.session.user,
        err: req.session.err,
    });
    //#######################################################
});

router.post('/', function (req, res, next) {
    //####################### ZADATAK #######################
    //postupak prijave korisnika
    console.log(req.body);
    (async () => {
        let user = await User.fetchByUsername(req.body.username);
        console.log(user);
        if (user.id === undefined) { //2 zasebna errora, posebno ih handleati da mogu posebno ispisati gresku, prvo ako uopce ne postoji korisnik, onda niti ne moramo
            res.render('Login', {    //gledati lozinku, zato i odmah radimo render i retrun, tek onda gledamo lozinku i ako je potrebno ispisemo taj error
                title: 'Log in',
                linkActive: 'login',
                user: req.session.user,
                err: 'No user with such username',
            });
            return;
        }
        if (!user.checkPassword(req.body.password)) {
            res.render('Login', {
                title: 'Log in',
                linkActive: 'login',
                user: req.session.user,
                err: 'Password does not match user details',
            });
            return;
        }
        req.session.user = user; //povezivanje sesije s korisnikom 
        res.redirect('/');
    })();
    //#######################################################
});


module.exports = router;