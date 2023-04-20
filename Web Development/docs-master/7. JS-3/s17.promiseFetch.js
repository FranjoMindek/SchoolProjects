//IMPORTANT: Run example with LiveServer - install from extensions
let promise = fetch("s17.promiseFetch.json");
promise
.then(
  function(response) {
    if (!response.ok) { throw new Error("Cannot load json file"); } 
    else { return response.json(); }
  },
  function(error) { throw error; }
)   
.then(jsonContents => {
    let spanElement = document.createElement('pre');
    console.log(jsonContents);
    spanElement.innerHTML = JSON.stringify(jsonContents);
    document.body.appendChild(spanElement);
  })
.catch(err => {
    console.log("An error occured while loading json");
});
