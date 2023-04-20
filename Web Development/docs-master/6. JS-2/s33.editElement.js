const div = document.createElement('div')

div.style.width = '100px';
div.style.height = '200px';
div.style.backgroundColor = 'red';

div.onclick = (event) => console.log('KLIK');

div.innerText = 'INNER TEXT';

console.log(div);