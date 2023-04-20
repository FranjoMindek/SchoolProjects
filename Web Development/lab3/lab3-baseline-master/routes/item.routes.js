var express = require('express');
var router = express.Router();
const db = require('../db')
const {
    body,
    validationResult,
} = require('express-validator');


router.get('/:id', async function(req, res, next) {
    let id = parseInt(req.params.id);
    if(isNaN(id)){
        res.status(404).send("Why?")
    }else{
        const [itemInfo, supplierInfo] = (await Promise.all([
            db.query('SELECT inventory.id, inventory.name, inventory.price as "Price", inventory.colors as "Available colors",\
                categories.name as "Category", categories.seasonal as "Seasonal", inventory.imageurl, categories.description FROM inventory JOIN categories\
                ON inventory.categoryid = categories.id WHERE inventory.id = ' + id),
            db.query('SELECT * FROM suppliers WHERE supplierFor =' + id),
        ])).map(a => a.rows);
        console.log(itemInfo, supplierInfo);
        res.render('item', {
            title: 'Item',
            linkActive: 'order',
            itemInfo: itemInfo[0],
            supplierInfo: supplierInfo
        });   
    }
});

router.get('/:id/addsupplier', async function(req, res, next) {
    
    let id = parseInt(req.params.id);
    if(isNaN(id)){
        res.status(404).send("Why?")
    }else{
        const [itemInfo, supplierInfo] = (await Promise.all([
            db.query('SELECT inventory.id, inventory.name, inventory.price as "Price", inventory.colors as "Available colors",\
                categories.name as "Category", categories.seasonal as "Seasonal", inventory.imageurl, categories.description FROM inventory JOIN categories\
                ON inventory.categoryid = categories.id WHERE inventory.id = ' + id),
            db.query('SELECT * FROM suppliers WHERE supplierFor =' + id),
        ])).map(a => a.rows);
        console.log(itemInfo, supplierInfo);
        res.render('form', {
            title: 'Form',
            linkActive: 'order',
            itemInfo: itemInfo[0],
            supplierInfo: supplierInfo
        });   
    }
});

router.post('/:id/addsupplier',
    [
        body('name')
            .trim()
            .isLength({min: 3, max: 25}),
        body('country')
            .trim()
            .isLength({min: 3, max: 25}),
        body('county')
            .trim()
            .isLength({min: 3, max: 25}),
        body('email')
            .trim().isEmail(),
        body('suppliersince')
            .trim()
            .isInt({min: 1940, max: 2021})
            .toInt()
            ,
    ], async function(req, res, next) {
    const errors = validationResult(req);
    let id = parseInt(req.params.id);
    if(!errors.isEmpty()) {
        res.render('error', {
            title: 'Error Add Supplier',
            linkActive: 'order',
            errors: errors.array(),
            itemID: id,
        })
    }else{
        try{
            await db.query('INSERT INTO suppliers (name, country, /
                county, email, supplierSince, supplierFor) VALUES ($1, $2, $3, $4, $5, $6)',
            [
                req.body.name,
                req.body.country,
                req.body.county,
                req.body.email,
                req.body.suppliersince,
                id,
            ],
            );
        res.redirect('/item/'+ id );
        } catch (err) {
            res.render('error', {
                title: 'Error Add Supplier',
                linkActive: 'order',
                errors: 'none',
                errDB: err.message,
                itemID: id,
            });
        }
    }

    console.log(req.body);
    res.status(404).send("Idk?")
});
module.exports = router;