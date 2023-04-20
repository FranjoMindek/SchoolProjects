const express = require('express');
const router = express.Router();
const cart = require('../models/CartModel')
const cartSanitizer = require('./helpers/cart-sanitizer');

// Ulančavanje funkcija međuopreme
router.get('/', cartSanitizer, function (req, res, next) {
    //####################### ZADATAK #######################
    // prikaz košarice uz pomoć cart.ejs
    res.render('cart', {
        title: 'Cart',
        linkActive: 'cart',
        user: req.session.user, //ako nema definirano bude login inace checkout
        cart: req.session.cart, //svakako potrebno, inace greska?
        err: undefined,
    });
    //#######################################################
});

router.get('/add/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //dodavanje jednog artikla u košaricu
    (async () => {
        await cart.addItemToCart(req.session.cart, req.params.id, 1);
        res.end();
    })();
    //#######################################################
});

router.get('/remove/:id', function (req, res, next) {
    //####################### ZADATAK #######################
    //brisanje jednog artikla iz košarice
    (async () => {
        await cart.removeItemFromCart(req.session.cart, req.params.id, 1); //ova funkcija vec sama pazi da izbrise item ako broj artikala padne na 0 
        res.end();                                                         //tako da sve vec radi kako treba
    })();
    //#######################################################
});

module.exports = router;