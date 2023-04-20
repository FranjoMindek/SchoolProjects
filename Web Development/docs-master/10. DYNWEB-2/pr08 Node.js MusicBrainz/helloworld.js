const db = require('./db');
(async() => {
    let rows = await db.query('SELECT id, name, description FROM place_type');
    console.log(rows);
})(); // IIFE: https://developer.mozilla.org/en-US/docs/Glossary/IIFE


(async() => {
    let rows = await db.query(`SELECT id, name, description 
        FROM place_type
        WHERE id BETWEEN $1 AND $2`, [1, 3]);
    console.log(rows);
})(); // IIFE: https://developer.mozilla.org/en-US/docs/Glossary/IIFE