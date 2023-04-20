https://web2-lab6-zary.onrender.com/

interpolation/one-way binding: IMPLEMENTIRANO
npr. u StoreItemCard.vue propse ispisujemo na ekran preko interpolation bindinga

two-way binding: IMPLEMENTIRANO
npr. u StoreCatalogue.vue koristimo v-model kako bi smo povezali varijablu offer i input element

methods: IMPLEMENTIRANO
npr. u StoreCatalogue.vue getItems() ili checkOffer()
   
computed properties: IMPLEMENTIRANO
npr. u PointsInfo.vue imamo varijablu inDebt koja je computed property

barem jedan scoped style: IMPLEMENTIRANO
npr. u NotFound.vue imamo klasu .big-title u scoped stilu

koristiti barem jedan lifecycle hook: IMPLEMENTIRANO
npr. u StoreCatalogue.vue korisitmo onBeforeMount()
   
routing (više stranica): IMPLEMENTIRANO
    aplikacija mora biti bookmarkable, tako da rade linkovi (ne samo na root, već i moj-web.com/stranica1, moj-web.com/stranica2)
    dinamičko usmjeravanje s 404 stranicom ("catch all")
npr. u index.ts možemo vidjeti:
	- 2 rute:
		- "/" i "/cart"
      - "/:patchMatch(.*)*" - tj. catch all za 404 stranicu
      
(barem) dvije komponente: IMPLEMENTIRANO
    komponenta bez stanja, koristiti properties
    npr. u CartItemCard.vue možemo vidjeti da koristimo samo propse
    komponenta sa stanjem
    npr. u StoreCatalogue.vue gdje se odvija većina logike
    
barem jedna komponenta mora emitirati barem jedan event: IMPLEMENTIRANO
npr. u StoreItemCard.vue gdje se klikom na gumb emitira event "bought" -> a logiku potom obavlja StoreCatalogue.vue

store (Pinia): IMPLEMENTIRANO
npr. itemsStore.ts u koju se spremaju "kupljeni" itemi

asinkroni dohvat podataka s backenda, možete: IMPLEMENTIRANO
    koristiti Firebase ili Back4App, Mocky, itd.
    vlastiti storage, ili
    možete mock napraviti, držati podatke u memoriji, ali mora biti asinkroni poziv/upis
    ostvariti asinkrono (lazy, po potrebi) učitavanje nekog dijela aplikacije (stranice ili komponente)
npr. u StoreCatalogue.vue se koristi poziv na firebase - firestore
