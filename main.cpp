#include <iostream>
#include "rekord.h"
#include "telkonyv.h"
#include <fstream>
#include <cstdlib>
#include "memtrace.h"
#include "lakcim.h"
#include "gtest_lite.h"



using namespace std;


int main()
{
    //Telefonkönyv példányosítása
    Telkonyv t;
    //Beolvas a .txt fileból és létrehozza belőle a rekordokat, amikkel fel is tölti a telkönyvet
    t.readFromFile();

    int mission; //felhasználó választása
    do
    {
        cout << "Kerlek nyomd meg az altalad elvegzendo feladat sorszamat!\n";
        cout << "1 - Telefonkonyv kilistazasa\n";
        cout << "2 - Uj kontakt felvetele a telefonykonyvbe\n";
        cout << "3 - Mentes es kilepes\n";
        cout << "4 - Letezo kontakt modositasa\n";
        cout << "5 - Kontakt torlese\n";
        cout << "6 - Kereses a kontaktok kozott\n\n";
        cin >> mission;
        cout << std::endl;
            switch(mission)
            {
                case 1:
                    //Kitöröljük a konzol tartalmát, ezáltal kezelhetőbb és átláthatóbb a menü
                    system("cls");
                    t.printTelkonyv();
                    break;
                case 2:
                    {
                        system("cls");
                        string ujveznev,ujkernev,ujtelszam;
                        cout << "Kerlek ird be a vezeteknevet: \n";
                        cin >> ujveznev;
                        cout << "Kerlek ird be a keresztnevet: \n";
                        cin >> ujkernev;
                        cout << "Kerlek ird be a priv. telefonszamot: \n";
                        cin >> ujtelszam;
                        cout << "Kerlek ird be a lakcimet(iranyitoszam, telepules, utca, hazszam), szokozokkel elvalasztva): \n";
                         int zipcode, hazszam;
                        string telepules, utca;
                        cin >> zipcode >> telepules >> utca >> hazszam;
                        Lakcim ujcim(zipcode, &telepules[0], &utca[0], hazszam);
                        cout << endl;
                        Rekord ujrekord(ujveznev,ujkernev,ujtelszam, ujcim);

                        //Teszteset miatt vezettem be ezt a változót
                        int ellenorzo = t.getRekordokSzama();
                        t.addRekord(ujrekord);

                        //az új rekordunk telefonszámát(egyedi azonosító) hasonlítja össze
                        // a telefonkönyvünk utolsó elemének telszámával
                        TEST(KontaktFelvetel, Atmasolas)
                        EXPECT_EQ(ujrekord.getTelszam(), t.getPhoneNumOfAnElement(t.getRekordokSzama()-1)) <<
                         "A megadott uj rekord nem lett atmasolva a telefonykonyvbe"<<std::endl;
                        END

                        //Ellenőrzi, hogy a méretet megnöveltük-e a hozzáadás után
                        TEST(KontaktFelvetel, MeretNovelese)
                        EXPECT_EQ(ellenorzo+1, t.getRekordokSzama()) << "A telefonykonyv meretet nem noveltuk"<<std::endl;
                        END
                        break;
                    }
                case 3:
                        cout << "Goodbye!\n\nZumzum \n";
                        break;
                case 4:
                        {
                        string modositando;
                        cout << "Kerlek ird be a modositando kontakt vezeteknevet: \n";
                        cin >> modositando;
                        system("cls");
                        cout << "Mit szeretnel modositani?\n";
                        cout<< "1 - Vezeteknevet\n";
                        cout<< "2 - Keresztnevet\n";
                        cout<< "3 - Telefonszamot\n";
                        cout<< "4 - Cimet\n\n";
                        int choice;
                        cin >> choice;
                        std::cout<<std::endl;
                            switch(choice)
                                {
                                case 1:
                                    t.modositVeznev(&modositando[0]);

                                    break;
                                case 2:
                                    t.modositKernev(&modositando[0]);
                                    break;
                                case 3:
                                    t.modositTelszam(&modositando[0]);
                                    break;
                                case 4:
                                    t.modositCim(&modositando[0]);
                                    break;
                                default:{
                                    system("cls");
                                    cout << "Kerlek ervenyes sorszamot adj meg!\n\n";
                                    break;
                                        }


                                }

                        break;
                        }
                case 5:{
                        string torlendo;
                        cout << "Kerlek ird be a torlendo kontakt vezeteknevet: \n";
                        cin >> torlendo;
                        system("cls");
                        //Ahogy az uj rekord felvetelenel, itt is a teszteset miatt kell
                        int ellenorzo = t.getRekordokSzama();
                        t.torolByVeznev(&torlendo[0]);

                        //Ellenőrizzük, hogy a törlés után megváltozott-e a mérete a telefonkönyvnek
                        TEST(KontaktTorles, MeretEllenorzes)
                        EXPECT_NE(ellenorzo, t.getRekordokSzama()) <<
                        "A meret nem csokkent a torles utan"<<std::endl;
                        END
                        break;
                       }
                case 6:{
                        system("cls");
                        string keresendo;
                        cout << "Gepeld be a sorszamat a keresesi opciok egyikenek a sajat preferenciad alapjan!\n\n";
                        cout << "1 - Vezeteknevre szeretnek keresni\n";
                        cout << "2 - Keresztnevre szeretnek keresni\n";
                        cout << "3 - Telefonszamra szeretnek keresni\n";
                        cout << "4 - Telepulesre szeretnek keresni\n\n";
                        int choice;
                        cin >> choice;
                        system("cls");
                            switch(choice)
                                {
                                case 1:
                                    cout << "A keresendo vezeteknev: \n";
                                    cin >> keresendo;
                                    std::cout<<std::endl;
                                    t.keresByVeznev(&keresendo[0], 1);
                                    break;
                                case 2:
                                    cout << "A keresendo keresztnev: \n";
                                    cin >> keresendo;
                                    t.keresByVeznev(&keresendo[0], 2);
                                    break;
                                case 3:
                                    cout << "A keresendo telefonszam: \n";
                                    cin >> keresendo;
                                    t.keresByVeznev(&keresendo[0], 3);
                                    break;
                                case 4:
                                    cout << "A keresendo telepules: \n";
                                    cin >> keresendo;
                                    t.keresByVeznev(&keresendo[0], 4);
                                    break;
                                default:
                                    system("cls");
                                    cout << "Ervenyes sorszamot adj meg legkozelebb!\n\n";
                                    break;
                                }

                        break;
                       }
                default:
                        system("cls");
                        cout << "Kerlek ervenyes sorszamot adj meg!\n\n";
                        break;
            }
    }while(mission != 3);

    //amikor a 3-as menüpontot választja a felhasználó, akkor az addig végzett módosításokat elmenti a program a .txt fájlunkba
    t.saveToFile();
    return 0;
}
