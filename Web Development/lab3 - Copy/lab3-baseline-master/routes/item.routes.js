var express = require('express');
var router = express.Router();
const db = require('../db')

router.get('/:id', async function(req, res, next) {
    let id = parseInt(req.params.id);
    if(isNaN(id)){
        res.status(404).send("Why?")
    }else{
        //console.log('SELECT inventory.id, inventory.name, inventory.price as "Price", inventory.colors as "Available colors", categories.name as "Category", categories.seasonal as "Seasonal", inventory.imageurl, categories.description FROM inventory JOIN categories ON inventory.categoryid = categories.id WHERE inventory.id ' + id);
        var itemInfo = (await db.query('SELECT inventory.id, inventory.name, inventory.price as "Price", inventory.colors as "Available colors",\
        categories.name as "Category", categories.seasonal as "Seasonal", inventory.imageurl, categories.description FROM inventory JOIN categories\
        ON inventory.categoryid = categories.id WHERE inventory.id = ' + id)).rows[0]; //array :(
        console.log(itemInfo);
        res.render('item', {
            title: 'Item',
            linkActive: ('Item ' + id),
            itemInfo: itemInfo
        });   
    }
});

module.exports = router;