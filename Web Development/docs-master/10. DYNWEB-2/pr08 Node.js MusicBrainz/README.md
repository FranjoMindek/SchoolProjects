# Kako pokrenuti kod kuće:

* Naravno: `npm install`
* Kako instalirati bazu podataka:

  * instalirati besplatni VirtualBox
  * skinuti musicbrainz VM npr. preko torrenta i importirati .ova (to će potrajati cca pola sata)
  * spojio se s puttyijem na localhost:2222, user/pwd = vagrant/vagrant, te obavio:
    * `bin/turn-port db on`
    * `docker-compose -f ~/musicbrainz/musicbrainz-docker/docker-compose.yml up -d db`
    * (detaljne upute su na https://musicbrainz.org/doc/MusicBrainz_Server/Setup)
  * Sad se mogu spojiti s hosta na pg db koristeći npr.:
psql -h localhost -U musicbrainz -p 15432
"By default, the password for the user musicbrainz is musicbrainz"
  * ali to spajanje nije ni nužno, node aplikacija se sama spaja i sada bi trebalo sve raditi ako ju pokrenete s `node server.js`
  * probajte i `node helloworld.js`

