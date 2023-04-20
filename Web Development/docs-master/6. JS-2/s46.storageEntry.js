class StorageEntry{
    constructor(val){
      this.val = val;
    }
}

let entry = new StorageEntry(1);
let entryJSON = JSON.stringify(entry);
localStorage.entry = entryJSON;
let entryJSONFromStorage = JSON.parse(localStorage.entry);
alert("Storage value: " + entryJSONFromStorage.val);