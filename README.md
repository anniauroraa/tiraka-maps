# Seuraavaksi tulee esitys tietorakenteista ja selitys miksi juuri ne ovat valittu

# Tämä on työohjeessa vaadittu readme-tiedosto (muodossa "readme.md")

Harjoitustyön tietorakenteeksi valitsin unordered mapin, jossa avaimena on PlaceID tai AreaID ja valuena struct-rakenne,
joka tallentaa sisälleen id:n muut tiedot. Valitsin unordered mapin, koska tietorakenteen ei tarvitse olla kokoajan 
järjestyksessä ja järjestyksen luominen aiheuttaisi tehonkulutusta. Unordered map on keskiarvoltaan vakio, kun sieltä 
etsitään tiettyjä alkioita ja työssä tarvitsee kaikkein eniten etsiä tiettyjä alkioita tietorakenteesta. Avaimeksi 
valitsin id:n, koska milläkään paikalla ei voi olla samaa id:tä toisen kanssa ja näin mapin ei tarvitse olla multimap, 
eli se pysyy tehokkaampana. 

Tietoja tallennetaan unordered mappiin, mutta sitten paikoille ja alueille on myös ajantasaiset listat, joissa on id:t 
tallennettuna. Paikoilla on std::list<PlaceID>, koska sitä pystyy iteroimaan helpommin ja remove_place() funktiossa 
tästä on hyötyä tehokkuuksien kannalta. Std::list hidastaa tässä kohtaa funktiota all_places(), mutta mielummin niin, 
kuin että remove_place() olisi ollut lineaarista huonompi. Alueilla tämä lista on std::vector<AreaID>, koska näin 
all_areas() funktio saadaan tehokkuudeltaan vakioksi. 