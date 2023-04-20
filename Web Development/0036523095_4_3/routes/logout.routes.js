const express = require('express');
const router = express.Router();

router.get('/', function (req, res, next) {
    //####################### ZADATAK #######################
    // - obrisati sadržaj košarice
    // - odjaviti registriranog korisnika iz sustava
    // - napraviti redirect na osnovnu stranicu

    //#######################################################
    if (req.session.cart !== undefined) {
        req.session.cart.invalid = true;  // u sljedecem kojegod koraku middleware funkcija ce napraviti novu kosaricu
    } 
    req.session.destroy((err) => {
        if(err){
            console.log(err); //u slucjau ako bude
        }
        res.redirect('/');
    });

}); 

module.exports = router;