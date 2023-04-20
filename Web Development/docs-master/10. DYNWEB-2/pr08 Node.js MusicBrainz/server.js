const http = require('http');
const db = require('./db');
const url = require('url');

getPreparedParams = (year, rating, params) => {
    let where = '';
    if (year) {
        where += ' AND first_release_date_year = $1';
        params.push(year);
    }
    if (rating) {
        where += ' AND rating = $' + (params.length + 1);
        params.push(rating);
    }
    return where;
}
getHref = (year, rating) => {
    let args = [];
    if (year) {
        args.push('year=' + year);
    }
    if (rating) {
        args.push('rating=' + rating);
    }
    return '/' + args.length ? '?' + args.join('&') : '';
}
getCenterPage = async(year, rating) => {
    let params = [];
    let where = getPreparedParams(year, rating, params);
    const { rows } = await db.query(`SELECT rg.name as release, ac.name as artist, rating
    FROM release_group rg 
    JOIN release_group_meta rgm on rg.id = rgm.id    
    JOIN artist_credit ac ON rg.artist_credit = ac.id  
    WHERE rating is not null ${where}
    ORDER BY first_release_date_year   DESC,
          first_release_date_month  DESC,
          first_release_date_day  DESC
      LIMIT 200`, params);
    return '<ul class="list-group">' +
        rows.map(x => `<li class="list-group-item d-flex justify-content-between align-items-center">
      ${x.artist}: ${x.release}
      <span class="badge badge-primary badge-pill">${x.rating}</span>
    </li>`).join('') +
        '</ul>';
}
getSideBarYears = async(rating) => {
    let params = [];
    let where = getPreparedParams(undefined, rating, params);
    const { rows } = await db.query(`SELECT first_release_date_year as year, count(*) as cnt
                FROM release_group_meta rgm    
                 WHERE first_release_date_year between 1990 and 2020 
                   ${where}
                 GROUP BY first_release_date_year
                 ORDER BY first_release_date_year desc`, params);
    return '<ul>' + rows.map(x => `<li><a href="${getHref(x.year, rating)}">${x.year}(${x.cnt})</a></li>`).join('') + '</ul>';
}
getSideBarRatings = async(year) => {
    let params = [];
    let where = getPreparedParams(year, undefined, params);
    const { rows } = await db.query(`SELECT rating, count(*) as cnt
                FROM release_group_meta rgm
                WHERE first_release_date_year between 1990 and 2020
                  AND rating is not null
                    ${where}
                GROUP BY rating
                ORDER BY rating desc`, params);
    let yearParam = year ? '&year=' + year : '';
    return '<ul>' + rows.map(x => `<li><a href="${getHref(year, x.rating)}">${x.rating}(${x.cnt})</a></li>`).join('') + '</ul>';
}

getHomePage = async(year, rating) => {
    let [left, center, right] = await Promise.all([
        getSideBarYears(rating),
        getCenterPage(year, rating),
        getSideBarRatings(year)
    ]);
    return `<html>
      <head>
        <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
      </head>
      <body>
        <div class="container">
          <div class="row">
            <div class="col"><img src="https://nextjournal.com/data/QmTocCJEhpPwDGyHXwMQnoVJHvcVHsJv87Rm1n4H4N5oni?content-type=image%2Fpng&filename=MusicBrainz_logo.png" /></div>
          </div>
          <hr>
          <div class="row">
            <div class="col-3">${left}</div>
            <div class="col-6">${center}</div>
            <div class="col-3">${right}</div>
          </div>
        </div>
      </body>
      </html>`;
}

http.createServer(async function(req, res) {
    var q = url.parse(req.url, true).query;
    res.writeHead(200);
    res.end(await getHomePage(q.year, q.rating));
}).listen(80);