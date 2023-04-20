function updateKosarica() {
    if(localStorage.getItem("brArtikala") != null){ //updejta items broj, ako kosarica postoji, ne postoji ako nismo nikad bili na order.html
        let broj = localStorage.getItem("brArtikala");
        console.log('Broj artikala u kosarici: ', broj); //test da vidimo da se dobro prenosi
        document.getElementById("cart-items").innerHTML = broj;
    }
}

updateKosarica(); //updejta broj artikal na stranici -> potrebno na svakoj stranici





