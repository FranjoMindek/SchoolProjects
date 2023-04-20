// https://www.fer.unizg.hr/?username=USERNAME&firstname=FIRSTNAME
console.log(location.search);
const params = location.search.substr(1).split('&');
const username = params[0].split('=')[1];
console.log(username);