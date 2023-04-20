let makeCart = async function () {
    let cartHeader = document.querySelector('#cart-template-header'); //template kategorije
    let cartItem = document.querySelector('#cart-template-item'); //template produkta
    let cartTotal = document.querySelector('#cart-total-template');
    let categoryTemplate = document.querySelector('#category-template'); 
    let category = categoryTemplate.content.cloneNode(true);
    let main = document.querySelector('main');
    main.append(category);
    let cart = document.querySelector('.cart');
    let header = cartHeader.content.cloneNode(true);
    cart.appendChild(header);
    let kosarica = JSON.parse(localStorage.getItem("kosara"));
    let ukupno = 0;
    for(bruh in kosarica){
        let itemInfo = kosarica[bruh];
        let item = cartItem.content.cloneNode(true);
        item.querySelector(".cart-item-title").innerHTML = itemInfo.name;
        item.querySelector(".cart-item-price").innerHTML = `${itemInfo.price} kn`;
        item.querySelector(".cart-item-quantity-div > input").setAttribute("value", itemInfo.count);
        item.querySelector(".cart-item-total-price").innerHTML = `${itemInfo.price*itemInfo.count} kn`;
        ukupno += itemInfo.price*itemInfo.count;
        cart.appendChild(item);
    }
    let total = cartTotal.content.cloneNode(true);
    total.querySelector(".cart-total > div").innerHTML = `Total: ${ukupno}`;
    cart.appendChild(total);
};

makeCart();
// doda galeriju na stranici order