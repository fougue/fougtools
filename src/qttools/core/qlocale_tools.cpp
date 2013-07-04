/****************************************************************************
**
**  FougTools
**  Copyright FougSys (1 Mar. 2011)
**  contact@fougsys.fr
**
** This software is a computer program whose purpose is to provide utility
** tools for the C++ language and the Qt toolkit.
**
** This software is governed by the CeCILL-C license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-C
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info".
**
** As a counterpart to the access to the source code and  rights to copy,
** modify and redistribute granted by the license, users are provided only
** with a limited warranty  and the software's author,  the holder of the
** economic rights,  and the successive licensors  have only  limited
** liability.
**
** In this respect, the user's attention is drawn to the risks associated
** with loading,  using,  modifying and/or developing or reproducing the
** software by the user in light of its specific status of free software,
** that may mean  that it is complicated to manipulate,  and  that  also
** therefore means  that it is reserved for developers  and  experienced
** professionals having in-depth computer knowledge. Users are therefore
** encouraged to load and test the software's suitability as regards their
** requirements in conditions enabling the security of their systems and/or
** data to be ensured and,  more generally, to use and operate it in the
** same conditions as regards security.
**
** The fact that you are presently reading this means that you have had
** knowledge of the CeCILL-C license and that you accept its terms.
**
****************************************************************************/

#include "qlocale_tools.h"

namespace qttools {

QLocale::MeasurementSystem toQLocaleMeasurementSystem(int measSys)
{
  switch (measSys) {
  case QLocale::MetricSystem : return QLocale::MetricSystem;
  case QLocale::ImperialSystem : return QLocale::ImperialSystem;
  default : return QLocale::MetricSystem;
  }
}

QLocale::Country toQLocaleCountry(int code)
{
  switch (code) {
  case QLocale::AnyCountry : return QLocale::AnyCountry;
  case QLocale::Afghanistan : return QLocale::Afghanistan;
  case QLocale::Albania : return QLocale::Albania;
  case QLocale::Algeria : return QLocale::Algeria;
  case QLocale::AmericanSamoa : return QLocale::AmericanSamoa;
  case QLocale::Andorra : return QLocale::Andorra;
  case QLocale::Angola : return QLocale::Angola;
  case QLocale::Anguilla : return QLocale::Anguilla;
  case QLocale::Antarctica : return QLocale::Antarctica;
  case QLocale::AntiguaAndBarbuda : return QLocale::AntiguaAndBarbuda;
  case QLocale::Argentina : return QLocale::Argentina;
  case QLocale::Armenia : return QLocale::Armenia;
  case QLocale::Aruba : return QLocale::Aruba;
  case QLocale::Australia : return QLocale::Australia;
  case QLocale::Austria : return QLocale::Austria;
  case QLocale::Azerbaijan : return QLocale::Azerbaijan;
  case QLocale::Bahamas : return QLocale::Bahamas;
  case QLocale::Bahrain : return QLocale::Bahrain;
  case QLocale::Bangladesh : return QLocale::Bangladesh;
  case QLocale::Barbados : return QLocale::Barbados;
  case QLocale::Belarus : return QLocale::Belarus;
  case QLocale::Belgium : return QLocale::Belgium;
  case QLocale::Belize : return QLocale::Belize;
  case QLocale::Benin : return QLocale::Benin;
  case QLocale::Bermuda : return QLocale::Bermuda;
  case QLocale::Bhutan : return QLocale::Bhutan;
  case QLocale::Bolivia : return QLocale::Bolivia;
  case QLocale::BosniaAndHerzegowina : return QLocale::BosniaAndHerzegowina;
  case QLocale::Botswana : return QLocale::Botswana;
  case QLocale::BouvetIsland : return QLocale::BouvetIsland;
  case QLocale::Brazil : return QLocale::Brazil;
  case QLocale::BritishIndianOceanTerritory : return QLocale::BritishIndianOceanTerritory;
  case QLocale::Bulgaria : return QLocale::Bulgaria;
  case QLocale::BurkinaFaso : return QLocale::BurkinaFaso;
  case QLocale::Burundi : return QLocale::Burundi;
  case QLocale::Cambodia : return QLocale::Cambodia;
  case QLocale::Cameroon : return QLocale::Cameroon;
  case QLocale::Canada : return QLocale::Canada;
  case QLocale::CapeVerde : return QLocale::CapeVerde;
  case QLocale::CaymanIslands : return QLocale::CaymanIslands;
  case QLocale::CentralAfricanRepublic : return QLocale::CentralAfricanRepublic;
  case QLocale::Chad : return QLocale::Chad;
  case QLocale::Chile : return QLocale::Chile;
  case QLocale::China : return QLocale::China;
  case QLocale::ChristmasIsland : return QLocale::ChristmasIsland;
  case QLocale::CocosIslands : return QLocale::CocosIslands;
  case QLocale::Colombia : return QLocale::Colombia;
  case QLocale::Comoros : return QLocale::Comoros;
  case QLocale::DemocraticRepublicOfCongo : return QLocale::DemocraticRepublicOfCongo;
  case QLocale::PeoplesRepublicOfCongo : return QLocale::PeoplesRepublicOfCongo;
  case QLocale::CookIslands : return QLocale::CookIslands;
  case QLocale::CostaRica : return QLocale::CostaRica;
  case QLocale::IvoryCoast : return QLocale::IvoryCoast;
  case QLocale::Croatia : return QLocale::Croatia;
  case QLocale::Cuba : return QLocale::Cuba;
  case QLocale::Cyprus : return QLocale::Cyprus;
  case QLocale::CzechRepublic : return QLocale::CzechRepublic;
  case QLocale::Denmark : return QLocale::Denmark;
  case QLocale::Djibouti : return QLocale::Djibouti;
  case QLocale::Dominica : return QLocale::Dominica;
  case QLocale::DominicanRepublic : return QLocale::DominicanRepublic;
  case QLocale::EastTimor : return QLocale::EastTimor;
  case QLocale::Ecuador : return QLocale::Ecuador;
  case QLocale::Egypt : return QLocale::Egypt;
  case QLocale::ElSalvador : return QLocale::ElSalvador;
  case QLocale::EquatorialGuinea : return QLocale::EquatorialGuinea;
  case QLocale::Eritrea : return QLocale::Eritrea;
  case QLocale::Estonia : return QLocale::Estonia;
  case QLocale::Ethiopia : return QLocale::Ethiopia;
  case QLocale::FalklandIslands : return QLocale::FalklandIslands;
  case QLocale::FaroeIslands : return QLocale::FaroeIslands;
  case QLocale::Finland : return QLocale::Finland;
  case QLocale::France : return QLocale::France;
  case QLocale::FrenchGuiana : return QLocale::FrenchGuiana;
  case QLocale::FrenchPolynesia : return QLocale::FrenchPolynesia;
  case QLocale::FrenchSouthernTerritories : return QLocale::FrenchSouthernTerritories;
  case QLocale::Gabon : return QLocale::Gabon;
  case QLocale::Gambia : return QLocale::Gambia;
  case QLocale::Georgia : return QLocale::Georgia;
  case QLocale::Germany : return QLocale::Germany;
  case QLocale::Ghana : return QLocale::Ghana;
  case QLocale::Gibraltar : return QLocale::Gibraltar;
  case QLocale::Greece : return QLocale::Greece;
  case QLocale::Greenland : return QLocale::Greenland;
  case QLocale::Grenada : return QLocale::Grenada;
  case QLocale::Guadeloupe : return QLocale::Guadeloupe;
  case QLocale::Guam : return QLocale::Guam;
  case QLocale::Guatemala : return QLocale::Guatemala;
  case QLocale::Guinea : return QLocale::Guinea;
  case QLocale::GuineaBissau : return QLocale::GuineaBissau;
  case QLocale::Guyana : return QLocale::Guyana;
  case QLocale::Haiti : return QLocale::Haiti;
  case QLocale::HeardAndMcDonaldIslands : return QLocale::HeardAndMcDonaldIslands;
  case QLocale::Honduras : return QLocale::Honduras;
  case QLocale::HongKong : return QLocale::HongKong;
  case QLocale::Hungary : return QLocale::Hungary;
  case QLocale::Iceland : return QLocale::Iceland;
  case QLocale::India : return QLocale::India;
  case QLocale::Indonesia : return QLocale::Indonesia;
  case QLocale::Iran : return QLocale::Iran;
  case QLocale::Iraq : return QLocale::Iraq;
  case QLocale::Ireland : return QLocale::Ireland;
  case QLocale::Israel : return QLocale::Israel;
  case QLocale::Italy : return QLocale::Italy;
  case QLocale::Jamaica : return QLocale::Jamaica;
  case QLocale::Japan : return QLocale::Japan;
  case QLocale::Jordan : return QLocale::Jordan;
  case QLocale::Kazakhstan : return QLocale::Kazakhstan;
  case QLocale::Kenya : return QLocale::Kenya;
  case QLocale::Kiribati : return QLocale::Kiribati;
  case QLocale::DemocraticRepublicOfKorea : return QLocale::DemocraticRepublicOfKorea;
  case QLocale::RepublicOfKorea : return QLocale::RepublicOfKorea;
  case QLocale::Kuwait : return QLocale::Kuwait;
  case QLocale::Kyrgyzstan : return QLocale::Kyrgyzstan;
  case QLocale::Latvia : return QLocale::Latvia;
  case QLocale::Lebanon : return QLocale::Lebanon;
  case QLocale::Lesotho : return QLocale::Lesotho;
  case QLocale::Liberia : return QLocale::Liberia;
  case QLocale::Liechtenstein : return QLocale::Liechtenstein;
  case QLocale::Lithuania : return QLocale::Lithuania;
  case QLocale::Luxembourg : return QLocale::Luxembourg;
  case QLocale::Macau : return QLocale::Macau;
  case QLocale::Macedonia : return QLocale::Macedonia;
  case QLocale::Madagascar : return QLocale::Madagascar;
  case QLocale::Malawi : return QLocale::Malawi;
  case QLocale::Malaysia : return QLocale::Malaysia;
  case QLocale::Maldives : return QLocale::Maldives;
  case QLocale::Mali : return QLocale::Mali;
  case QLocale::Malta : return QLocale::Malta;
  case QLocale::MarshallIslands : return QLocale::MarshallIslands;
  case QLocale::Martinique : return QLocale::Martinique;
  case QLocale::Mauritania : return QLocale::Mauritania;
  case QLocale::Mauritius : return QLocale::Mauritius;
  case QLocale::Mayotte : return QLocale::Mayotte;
  case QLocale::Mexico : return QLocale::Mexico;
  case QLocale::Micronesia : return QLocale::Micronesia;
  case QLocale::Moldova : return QLocale::Moldova;
  case QLocale::Monaco : return QLocale::Monaco;
  case QLocale::Mongolia : return QLocale::Mongolia;
  case QLocale::Montserrat : return QLocale::Montserrat;
  case QLocale::Morocco : return QLocale::Morocco;
  case QLocale::Mozambique : return QLocale::Mozambique;
  case QLocale::Myanmar : return QLocale::Myanmar;
  case QLocale::Namibia : return QLocale::Namibia;
  case QLocale::NauruCountry : return QLocale::NauruCountry;
  case QLocale::Nepal : return QLocale::Nepal;
  case QLocale::Netherlands : return QLocale::Netherlands;
  case QLocale::NewCaledonia : return QLocale::NewCaledonia;
  case QLocale::NewZealand : return QLocale::NewZealand;
  case QLocale::Nicaragua : return QLocale::Nicaragua;
  case QLocale::Niger : return QLocale::Niger;
  case QLocale::Nigeria : return QLocale::Nigeria;
  case QLocale::Niue : return QLocale::Niue;
  case QLocale::NorfolkIsland : return QLocale::NorfolkIsland;
  case QLocale::NorthernMarianaIslands : return QLocale::NorthernMarianaIslands;
  case QLocale::Norway : return QLocale::Norway;
  case QLocale::Oman : return QLocale::Oman;
  case QLocale::Pakistan : return QLocale::Pakistan;
  case QLocale::Palau : return QLocale::Palau;
  case QLocale::Panama : return QLocale::Panama;
  case QLocale::PapuaNewGuinea : return QLocale::PapuaNewGuinea;
  case QLocale::Paraguay : return QLocale::Paraguay;
  case QLocale::Peru : return QLocale::Peru;
  case QLocale::Philippines : return QLocale::Philippines;
  case QLocale::Pitcairn : return QLocale::Pitcairn;
  case QLocale::Poland : return QLocale::Poland;
  case QLocale::Portugal : return QLocale::Portugal;
  case QLocale::PuertoRico : return QLocale::PuertoRico;
  case QLocale::Qatar : return QLocale::Qatar;
  case QLocale::Reunion : return QLocale::Reunion;
  case QLocale::Romania : return QLocale::Romania;
  case QLocale::RussianFederation : return QLocale::RussianFederation;
  case QLocale::Rwanda : return QLocale::Rwanda;
  case QLocale::SaintKittsAndNevis : return QLocale::SaintKittsAndNevis;
  case QLocale::Samoa : return QLocale::Samoa;
  case QLocale::SanMarino : return QLocale::SanMarino;
  case QLocale::SaoTomeAndPrincipe : return QLocale::SaoTomeAndPrincipe;
  case QLocale::SaudiArabia : return QLocale::SaudiArabia;
  case QLocale::Senegal : return QLocale::Senegal;
  case QLocale::Seychelles : return QLocale::Seychelles;
  case QLocale::SierraLeone : return QLocale::SierraLeone;
  case QLocale::Singapore : return QLocale::Singapore;
  case QLocale::Slovakia : return QLocale::Slovakia;
  case QLocale::Slovenia : return QLocale::Slovenia;
  case QLocale::SolomonIslands : return QLocale::SolomonIslands;
  case QLocale::Somalia : return QLocale::Somalia;
  case QLocale::SouthAfrica : return QLocale::SouthAfrica;
  case QLocale::SouthGeorgiaAndTheSouthSandwichIslands : return QLocale::SouthGeorgiaAndTheSouthSandwichIslands;
  case QLocale::Spain : return QLocale::Spain;
  case QLocale::SriLanka : return QLocale::SriLanka;
  case QLocale::Sudan : return QLocale::Sudan;
  case QLocale::Suriname : return QLocale::Suriname;
  case QLocale::SvalbardAndJanMayenIslands : return QLocale::SvalbardAndJanMayenIslands;
  case QLocale::Swaziland : return QLocale::Swaziland;
  case QLocale::Sweden : return QLocale::Sweden;
  case QLocale::Switzerland : return QLocale::Switzerland;
  case QLocale::SyrianArabRepublic : return QLocale::SyrianArabRepublic;
  case QLocale::Taiwan : return QLocale::Taiwan;
  case QLocale::Tajikistan : return QLocale::Tajikistan;
  case QLocale::Tanzania : return QLocale::Tanzania;
  case QLocale::Thailand : return QLocale::Thailand;
  case QLocale::Togo : return QLocale::Togo;
  case QLocale::Tokelau : return QLocale::Tokelau;
  case QLocale::TrinidadAndTobago : return QLocale::TrinidadAndTobago;
  case QLocale::Tunisia : return QLocale::Tunisia;
  case QLocale::Turkey : return QLocale::Turkey;
  case QLocale::Turkmenistan : return QLocale::Turkmenistan;
  case QLocale::TurksAndCaicosIslands : return QLocale::TurksAndCaicosIslands;
  case QLocale::Tuvalu : return QLocale::Tuvalu;
  case QLocale::Uganda : return QLocale::Uganda;
  case QLocale::Ukraine : return QLocale::Ukraine;
  case QLocale::UnitedArabEmirates : return QLocale::UnitedArabEmirates;
  case QLocale::UnitedKingdom : return QLocale::UnitedKingdom;
  case QLocale::UnitedStates : return QLocale::UnitedStates;
  case QLocale::UnitedStatesMinorOutlyingIslands : return QLocale::UnitedStatesMinorOutlyingIslands;
  case QLocale::Uruguay : return QLocale::Uruguay;
  case QLocale::Uzbekistan : return QLocale::Uzbekistan;
  case QLocale::Vanuatu : return QLocale::Vanuatu;
  case QLocale::VaticanCityState : return QLocale::VaticanCityState;
  case QLocale::Venezuela : return QLocale::Venezuela;
  case QLocale::BritishVirginIslands : return QLocale::BritishVirginIslands;
  case QLocale::WallisAndFutunaIslands : return QLocale::WallisAndFutunaIslands;
  case QLocale::WesternSahara : return QLocale::WesternSahara;
  case QLocale::Yemen : return QLocale::Yemen;
  case QLocale::Zambia : return QLocale::Zambia;
  case QLocale::Zimbabwe : return QLocale::Zimbabwe;
  case QLocale::Montenegro : return QLocale::Montenegro;
  case QLocale::Serbia : return QLocale::Serbia;
  case QLocale::SaintBarthelemy : return QLocale::SaintBarthelemy;
  case QLocale::SaintMartin : return QLocale::SaintMartin;
  case QLocale::LatinAmericaAndTheCaribbean : return QLocale::LatinAmericaAndTheCaribbean;
#if QT_VERSION >= 0x050000
  case QLocale::Brunei : return QLocale::Brunei;
  case QLocale::Fiji : return QLocale::Fiji;
  case QLocale::PalestinianTerritories : return QLocale::PalestinianTerritories;
  case QLocale::Libya : return QLocale::Libya;
  case QLocale::SaintLucia : return QLocale::SaintLucia;
  case QLocale::SaintVincentAndTheGrenadines : return QLocale::SaintVincentAndTheGrenadines;
  case QLocale::SaintHelena : return QLocale::SaintHelena;
  case QLocale::SaintPierreAndMiquelon : return QLocale::SaintPierreAndMiquelon;
  case QLocale::Tonga : return QLocale::Tonga;
  case QLocale::Vietnam : return QLocale::Vietnam;
  case QLocale::UnitedStatesVirginIslands: return QLocale::UnitedStatesVirginIslands;
  case QLocale::Laos : return QLocale::Laos;
#else
  case QLocale::BruneiDarussalam : return QLocale::BruneiDarussalam;
  case QLocale::FijiCountry : return QLocale::FijiCountry;
  case QLocale::MetropolitanFrance : return QLocale::MetropolitanFrance;
  case QLocale::LibyanArabJamahiriya : return QLocale::LibyanArabJamahiriya;
  case QLocale::NetherlandsAntilles : return QLocale::NetherlandsAntilles;
  case QLocale::PalestinianTerritory : return QLocale::PalestinianTerritory;
  case QLocale::StLucia : return QLocale::StLucia;
  case QLocale::StVincentAndTheGrenadines : return QLocale::StVincentAndTheGrenadines;
  case QLocale::StHelena : return QLocale::StHelena;
  case QLocale::StPierreAndMiquelon : return QLocale::StPierreAndMiquelon;
  case QLocale::TongaCountry : return QLocale::TongaCountry;
  case QLocale::VietNam : return QLocale::VietNam;
  case QLocale::USVirginIslands : return QLocale::USVirginIslands;
  case QLocale::Yugoslavia : return QLocale::Yugoslavia;
  case QLocale::SerbiaAndMontenegro : return QLocale::SerbiaAndMontenegro;
  case QLocale::Lao : return QLocale::Lao;
#endif // QT_VERSION
  }
  return QLocale::AnyCountry;
}

QList<QLocale::Country> allQLocaleCountries()
{
  QList<QLocale::Country> countries;
  countries << QLocale::AnyCountry
            << QLocale::Afghanistan
            << QLocale::Albania
            << QLocale::Algeria
            << QLocale::AmericanSamoa
            << QLocale::Andorra
            << QLocale::Angola
            << QLocale::Anguilla
            << QLocale::Antarctica
            << QLocale::AntiguaAndBarbuda
            << QLocale::Argentina
            << QLocale::Armenia
            << QLocale::Aruba
            << QLocale::Australia
            << QLocale::Austria
            << QLocale::Azerbaijan
            << QLocale::Bahamas
            << QLocale::Bahrain
            << QLocale::Bangladesh
            << QLocale::Barbados
            << QLocale::Belarus
            << QLocale::Belgium
            << QLocale::Belize
            << QLocale::Benin
            << QLocale::Bermuda
            << QLocale::Bhutan
            << QLocale::Bolivia
            << QLocale::BosniaAndHerzegowina
            << QLocale::Botswana
            << QLocale::BouvetIsland
            << QLocale::Brazil
            << QLocale::BritishIndianOceanTerritory
            << QLocale::Bulgaria
            << QLocale::BurkinaFaso
            << QLocale::Burundi
            << QLocale::Cambodia
            << QLocale::Cameroon
            << QLocale::Canada
            << QLocale::CapeVerde
            << QLocale::CaymanIslands
            << QLocale::CentralAfricanRepublic
            << QLocale::Chad
            << QLocale::Chile
            << QLocale::China
            << QLocale::ChristmasIsland
            << QLocale::CocosIslands
            << QLocale::Colombia
            << QLocale::Comoros
            << QLocale::DemocraticRepublicOfCongo
            << QLocale::PeoplesRepublicOfCongo
            << QLocale::CookIslands
            << QLocale::CostaRica
            << QLocale::IvoryCoast
            << QLocale::Croatia
            << QLocale::Cuba
            << QLocale::Cyprus
            << QLocale::CzechRepublic
            << QLocale::Denmark
            << QLocale::Djibouti
            << QLocale::Dominica
            << QLocale::DominicanRepublic
            << QLocale::EastTimor
            << QLocale::Ecuador
            << QLocale::Egypt
            << QLocale::ElSalvador
            << QLocale::EquatorialGuinea
            << QLocale::Eritrea
            << QLocale::Estonia
            << QLocale::Ethiopia
            << QLocale::FalklandIslands
            << QLocale::FaroeIslands
            << QLocale::Finland
            << QLocale::France
            << QLocale::FrenchGuiana
            << QLocale::FrenchPolynesia
            << QLocale::FrenchSouthernTerritories
            << QLocale::Gabon
            << QLocale::Gambia
            << QLocale::Georgia
            << QLocale::Germany
            << QLocale::Ghana
            << QLocale::Gibraltar
            << QLocale::Greece
            << QLocale::Greenland
            << QLocale::Grenada
            << QLocale::Guadeloupe
            << QLocale::Guam
            << QLocale::Guatemala
            << QLocale::Guinea
            << QLocale::GuineaBissau
            << QLocale::Guyana
            << QLocale::Haiti
            << QLocale::HeardAndMcDonaldIslands
            << QLocale::Honduras
            << QLocale::HongKong
            << QLocale::Hungary
            << QLocale::Iceland
            << QLocale::India
            << QLocale::Indonesia
            << QLocale::Iran
            << QLocale::Iraq
            << QLocale::Ireland
            << QLocale::Israel
            << QLocale::Italy
            << QLocale::Jamaica
            << QLocale::Japan
            << QLocale::Jordan
            << QLocale::Kazakhstan
            << QLocale::Kenya
            << QLocale::Kiribati
            << QLocale::DemocraticRepublicOfKorea
            << QLocale::RepublicOfKorea
            << QLocale::Kuwait
            << QLocale::Kyrgyzstan
            << QLocale::Latvia
            << QLocale::Lebanon
            << QLocale::Lesotho
            << QLocale::Liberia
            << QLocale::Liechtenstein
            << QLocale::Lithuania
            << QLocale::Luxembourg
            << QLocale::Macau
            << QLocale::Macedonia
            << QLocale::Madagascar
            << QLocale::Malawi
            << QLocale::Malaysia
            << QLocale::Maldives
            << QLocale::Mali
            << QLocale::Malta
            << QLocale::MarshallIslands
            << QLocale::Martinique
            << QLocale::Mauritania
            << QLocale::Mauritius
            << QLocale::Mayotte
            << QLocale::Mexico
            << QLocale::Micronesia
            << QLocale::Moldova
            << QLocale::Monaco
            << QLocale::Mongolia
            << QLocale::Montserrat
            << QLocale::Morocco
            << QLocale::Mozambique
            << QLocale::Myanmar
            << QLocale::Namibia
            << QLocale::NauruCountry
            << QLocale::Nepal
            << QLocale::Netherlands
            << QLocale::NewCaledonia
            << QLocale::NewZealand
            << QLocale::Nicaragua
            << QLocale::Niger
            << QLocale::Nigeria
            << QLocale::Niue
            << QLocale::NorfolkIsland
            << QLocale::NorthernMarianaIslands
            << QLocale::Norway
            << QLocale::Oman
            << QLocale::Pakistan
            << QLocale::Palau
            << QLocale::Panama
            << QLocale::PapuaNewGuinea
            << QLocale::Paraguay
            << QLocale::Peru
            << QLocale::Philippines
            << QLocale::Pitcairn
            << QLocale::Poland
            << QLocale::Portugal
            << QLocale::PuertoRico
            << QLocale::Qatar
            << QLocale::Reunion
            << QLocale::Romania
            << QLocale::RussianFederation
            << QLocale::Rwanda
            << QLocale::SaintKittsAndNevis
            << QLocale::Samoa
            << QLocale::SanMarino
            << QLocale::SaoTomeAndPrincipe
            << QLocale::SaudiArabia
            << QLocale::Senegal
            << QLocale::Seychelles
            << QLocale::SierraLeone
            << QLocale::Singapore
            << QLocale::Slovakia
            << QLocale::Slovenia
            << QLocale::SolomonIslands
            << QLocale::Somalia
            << QLocale::SouthAfrica
            << QLocale::SouthGeorgiaAndTheSouthSandwichIslands
            << QLocale::Spain
            << QLocale::SriLanka
            << QLocale::Sudan
            << QLocale::Suriname
            << QLocale::SvalbardAndJanMayenIslands
            << QLocale::Swaziland
            << QLocale::Sweden
            << QLocale::Switzerland
            << QLocale::SyrianArabRepublic
            << QLocale::Taiwan
            << QLocale::Tajikistan
            << QLocale::Tanzania
            << QLocale::Thailand
            << QLocale::Togo
            << QLocale::Tokelau
            << QLocale::TrinidadAndTobago
            << QLocale::Tunisia
            << QLocale::Turkey
            << QLocale::Turkmenistan
            << QLocale::TurksAndCaicosIslands
            << QLocale::Tuvalu
            << QLocale::Uganda
            << QLocale::Ukraine
            << QLocale::UnitedArabEmirates
            << QLocale::UnitedKingdom
            << QLocale::UnitedStates
            << QLocale::UnitedStatesMinorOutlyingIslands
            << QLocale::Uruguay
            << QLocale::Uzbekistan
            << QLocale::Vanuatu
            << QLocale::VaticanCityState
            << QLocale::Venezuela
            << QLocale::BritishVirginIslands
            << QLocale::WallisAndFutunaIslands
            << QLocale::WesternSahara
            << QLocale::Yemen
            << QLocale::Zambia
            << QLocale::Zimbabwe
            << QLocale::Montenegro
            << QLocale::Serbia
            << QLocale::SaintBarthelemy
            << QLocale::SaintMartin
            << QLocale::LatinAmericaAndTheCaribbean;

  countries <<
             #if QT_VERSION >= 0x050000
               QLocale::Brunei
            << QLocale::Fiji
            << QLocale::PalestinianTerritories
            << QLocale::Libya
            << QLocale::SaintLucia
            << QLocale::SaintVincentAndTheGrenadines
            << QLocale::SaintHelena
            << QLocale::SaintPierreAndMiquelon
            << QLocale::Tonga
            << QLocale::Vietnam
            << QLocale::UnitedStatesVirginIslands
            << QLocale::Laos;
#else
               QLocale::BruneiDarussalam
            << QLocale::FijiCountry
            << QLocale::MetropolitanFrance
            << QLocale::LibyanArabJamahiriya
            << QLocale::NetherlandsAntilles
            << QLocale::PalestinianTerritory
            << QLocale::StLucia
            << QLocale::StVincentAndTheGrenadines
            << QLocale::StHelena
            << QLocale::StPierreAndMiquelon
            << QLocale::TongaCountry
            << QLocale::VietNam
            << QLocale::USVirginIslands
            << QLocale::Yugoslavia
            << QLocale::SerbiaAndMontenegro
            << QLocale::Lao;
#endif // QT_VERSION

  return countries;
}

} // namespace qttools
