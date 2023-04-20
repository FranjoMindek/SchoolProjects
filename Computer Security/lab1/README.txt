U razvoju aplikacije korišteni su KDF, Crypto RNG i AES (EAX mode, koji također po završetku enkripcije računa hash za integritet).
Aplikacija se služi 2 pomoćne datoteke binarnog sadržaja za rad: init.bin i data.bin.

init.bin datoteka se sastoji od Python dictionaryja koji kao ključ ima adresu, a kao vrijednost položaj te adrese u data.bin
data.bin datoteka se sastoji od ključeva spremljenih adresa
također obje datoteke imaju dodatne pomoćne podatke kao: salt, nonce i tag

Proces kriptiranja sadržaja je sljedeći:
Pomoću kriptografskog generatora nasumićnih brojeva storimo salt.
Pomoću master_password i salt stvaramo ključ za AES.
Pomoću novostvorenog ključa i samogeneriranog nonce enkriptiramo sadržaj datoteke (koji je padded do 256 bajta) te odmah i stovrimo tag (za integritet) enkriptiranog sadržaja.
U datoteku redom spremamo salt, nonce, tag, enkriptirani sadržaj

Proces dekriptiranja sadržaja je sljedeći:
Pročitamo spremljeni salt, nonce, tag i enkriptirani sadržaj.
Pomoću master_password i pročitanog salt stvaramo ključ.
Pomoću novostvorenog ključa pokušamo dekriptirati sadržaj (koji je sada unpadded) i po završetku dekripcije provjerimo integritet sadržaja preko taga.
U slučaju uspjeha bajtove pretvorimo u string i dobivamo spremljenu šifru.

vizualno init.bin:
| salt | nonce | tag | data |
   16      16     16    variable

vizualno data.bin:
| salt1 | nonce1 | tag1 | encrypted_data1 | salt2 | nonce2 | tag2 | encrypted_data 2 | ....
   16       16      16          256           16      16      16          256


Interakcija s alatom jednaka je predloženoj u uputama za labos.
Inicijalizacija programa:
    init <master_password>
Unos/promjena šifre:
    put <master_password> <address> <password>
Dohvaćanje šifre:
    get <master_password> <address>
Također je dodana funkcionalnost brzog testiranja aplikacije preko sljedeće naredbe:
    test <master_password>
Ta naredba 4 puta pozove put s kombinacijama adresa/šifra te zatim preko get naredbi ispiše vrijednosti šifri adresa.
Nakon toga promjeni 2 šifre unošenjem novih šifri na postojeće adrese te preko get naredbi ispiše nove vrijednosti.
Nakon toga aplikacija pokušava dohvatiti šifru unošenjem krive glavne šifre što izbacuje grešku.
Nakon svega toga moguće je nastaviti interakciju s trenutnim stanjem programa koristeći unesenu glavnu šifru.


