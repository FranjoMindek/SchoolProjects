U razvoju aplikacije korišteni su KDF, Crypto RNG i AES (EAX mode, koji također po završetku enkripcije računa hash za integritet)
te HMAC u kombinaciji sa SHA256.
Aplikacija se služi 2 pomoćne datoteke binarnog sadržaja za rad: init.bin i data.bin.

init.bin datoteka se sastoji od Python dictionaryja koji kao ključ ima ime korisnika, a kao vrijednost položaj hasha lozinke u data.bin i flag o tome forsira li se korisnika na promjenu lozinke pri sljedećoj prijavi.
data.bin datoteka se sastoji od hasheva ključeva spremljenih adresa i njihovih saltova.
init.bin također sadrži pomoćne podatke: salt, nonce i tag.

Proces kriptiranja sadržaja je sljedeći:
Pomoću kriptografskog generatora nasumićnih brojeva storimo salt.
Pomoću MASTERPASSWORD i salt stvaramo ključ za AES.
Pomoću novostvorenog ključa i samogeneriranog nonce enkriptiramo sadržaj te odmah i stovrimo tag (za integritet) enkriptiranog sadržaja.
U datoteku redom spremamo salt, nonce, tag, enkriptirani sadržaj

Proces dekriptiranja sadržaja je sljedeći:
Pročitamo spremljeni salt, nonce, tag i enkriptirani sadržaj.
Pomoću MASTERPASSWORD i pročitanog salt stvaramo ključ.
Pomoću novostvorenog ključa pokušamo dekriptirati sadržaj i po završetku dekripcije provjerimo integritet sadržaja preko taga.

Proces spremanja hasha lozinke je sljedeći:
Pomoću kriptografskog generatora nasumićnih brojeva storimo salt.
Pomoću HASH_SECRET i salt stvaramo ključ za HMAC.
Pomoći novostvorenog ključa koristeći SHA256 stvaramo hash korisnikove lozinke.
U datoteku redom spremamo salt i hash.

Proces usporedbe hash lozinki je sljedeći:
Pročitamo spremljeni salt i hashiranu lozinku.
Pomoću HASH_SECRET i pročitanog salt stvaramo ključ.
Pomoću novostvorenog ključa koristeći SHA256 stvaramo hash unesene lozinke.
Napravimo usporedbu novonastalog hasha lozinke i pročitanog hasha lozinke.

vizualno init.bin:
| salt | nonce | tag | data |
   16      16     16    variable

vizualno data.bin:
| salt1 | password_hash1 | salt2 | password_hash2 | ....
   16           32          16           32        


Interakcija s alatom jednaka je predloženoj u uputama za labos.

Za usermgmt.py:
Dodavanje korisnika:
    add <ime_korisnika> # te zatim unos lozinke korisnika 2 puta
Promjena lozinke korisnika:
    passwd <ime_korisnika> # te zatim unos nove lozinke korisnika 2 puta
Forisranje promjene loznike korisnika pri sljedećoj prijavi:
    forcepass <ime_korisnika>
Također je dodana funkcionalnost brisanja sadržaja init.bin i data.bin:
    clear

Za login.py:
Prijava korisnika:
    <ime_korisnika> # te zatim unos lozinke korisnika 1 put


