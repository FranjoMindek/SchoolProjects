const express = require('express');
const router = express.Router();
const authHandler = require('./helpers/auth-handler')

router.get('/', authHandler, function (req, res, next) {
    console.log('req.session.promotional = ', req.session.promotional);
    res.render('promotional', {
        title: 'Promotional',
        linkActive: 'cart',
        user: req.session.user, //ako nema definirano bude login inace checkout
        promotional: req.session.promotional,
        err: undefined,
    });
}); 

router.post('/save', function (req, res, next) {
    console.log('save?');
    req.session.promotional = req.body;
    console.log('req.session.promotional = ', req.session.promotional)
    res.redirect('/cart');
});

router.post('/reset', function (req, res, next) {
    console.log('reset?');
    req.session.promotional = undefined;
    console.log('req.session.promotional = ', req.session.promotional)
    res.redirect('/promotional');
});

router.post('/checkout', function (req, res, next) {
    console.log('checkout?');
    req.session.promotional = undefined;
    res.redirect('/checkout');
});

module.exports = router;