//IMPORTANT: Run example with LiveServer - install from extensions
async function LoadJSON(){
  let promise = await fetch("s19.asyncAwaitFetch.json");
  if (!promise.ok) { throw new Error("Cannot load json file"); } 
  else { var jsonContents = await promise.json();}
  let spanElement = document.createElement('pre');
  spanElement.innerHTML = JSON.stringify(jsonContents);
  document.body.appendChild(spanElement);
}

LoadJSON().catch(err => {
  console.log("An error occured while loading json: " + err);
});
