let getData = async function () {
    let response = await fetch("https://web1lab2.azurewebsites.net/categories");
    let data = await response.json();
    addCategories(data); //nisam siguran zasto zasebne fetchove imamo u zasebnim funkcijama
}

let addCategories = async function (categories) {
    let main = document.querySelector('main');
    let categoryTemplate = document.querySelector('#category-template'); //template kategorije
    let productTemplate = document.querySelector('#product-template'); //template produkta
    for (let index = 0; index < categories.length; index++) { // za svaku kategoriju....
        let category = categoryTemplate.content.cloneNode(true);
        let categoryTitleElement = category.querySelector('.decorated-title > span');
        categoryTitleElement.textContent = categories[index].name;
        let categoryFetch = await fetch(`https://web1lab2.azurewebsites.net/products?categoryId=${index+1}`); //dovhati produkte odredjene kategorije
        let categoryContent = await categoryFetch.json();
        if(categoryContent.length > 0){ //ne vrijedi dodavati produkte ako ne postoje
            for(data of categoryContent){ // za svaki produkt kategorije...
                let product = productTemplate.content.cloneNode(true);
                product.querySelector(".photo-box-image").src = data.imageUrl; //posstavi sliku
                product.querySelector(".photo-box-title").innerHTML = data.name; //postavi naslov
                product.querySelector(".photo-box").setAttribute("data-id", data.id); //postavi id
                let temp = {};
                temp.name = data.name;
                temp.price = data.price;
                temp.count = 1; 
                product.querySelector(".cart-btn").addEventListener('click', (clicked) => {
                    let idProdukta = clicked.target.parentNode.getAttribute('data-id');
                    //console.log(idProdukta);
                    if(localStorage.getItem("kosara") != null){
                        let kosarica = JSON.parse(localStorage.getItem("kosara"));
                        let brArtikala = localStorage.getItem("brArtikala");
                        brArtikala++; //povecaj ukupan broj artikala
                        localStorage.setItem("brArtikala", brArtikala);
                        if(typeof kosarica[idProdukta] === 'undefined') { //nema tog elementa u kosarici jos
                            kosarica[idProdukta] = temp; //u slucaju da treba vise informacija, objekt unutar objekta!!
                        } else {
                            kosarica[idProdukta].count++; //+1 artikl
                        }
                        localStorage.setItem("kosara", JSON.stringify(kosarica)); 
                        document.getElementById("cart-items").innerHTML = brArtikala; //updejtaj kosaricu na trenutnoj stranici, kada idemo u drugi HTML
                    }                                                                  //updejt ce napraviti updateKosara.js
                });
                category.querySelector(".gallery").appendChild(product); //dodaj produkt u kategoriju
            }
        }
        main.appendChild(category); //dodaj kategoriju u order.html
    }
};

let makeKosarica = async function () {
    if(localStorage.getItem("kosara") == null){
        let kosara = {};                              
        console.log("Kosara ne postoji -> kosara stvorena");
        localStorage.setItem("kosara", JSON.stringify(kosara));
    }
    if(localStorage.getItem("brArtikala") == null){
        let brArtikala = 0;                             
        localStorage.setItem("brArtikala", brArtikala);
    }
}

makeKosarica(); //napravi pocetnu kosaricu ako ne postoji u local storage-u, potrebno tek kada po prvi puta odemo na order stranicu, zato nije u updateKosara
getData(); // doda galeriju na stranici order