var express = require('express');
var router = express.Router();
const db = require('../db');

router.get('/', async function(req, res, next) {
    const [categoryRows, inventoryRows] = (await Promise.all([
        db.query('SELECT * FROM categories'),
        db.query('SELECT * FROM inventory'),
    ])).map(a => a.rows);
    // var categoryRows = (await db.query('SELECT * FROM categories')).rows;
    // var inventoryRows = (await db.query('SELECT * FROM inventory')).rows;
    // console.log("kategorije");
    // console.log(categoryRows);
    // console.log("itemi");
    // console.log(inventoryRows);
    res.render('order', {
        title: 'Order',
        linkActive: 'order',
        categoryRows: categoryRows,
        inventoryRows: inventoryRows
    });
});

module.exports = router;