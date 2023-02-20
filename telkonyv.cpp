#include "telkonyv.h"
#include "gtest_lite.h"
#include "memtrace.h"


void Telkonyv::addRekord (const Rekord& ujrekord)
    {
        Rekord *temp = NULL; //átmásoláshoz szükséges
        temp = new Rekord[rekordokSzama +1];
        if(rekordokSzama == 0) //ha még nincs elem a tömbben
            {
                temp[rekordokSzama] = ujrekord;
                delete[] rekordok;
                rekordok = new Rekord[this->rekordokSzama + 1];
                rekordok[rekordokSzama] = temp[rekordokSzama];
                rekordokSzama++;
                delete[] temp;
                return;
            }
        else{ //ha már van legalább 1 elem a telefonkönyvben
                for (int i =0; i< rekordokSzama; i++)
                    {
                        if(ujrekord.getTelszam() == rekordok[i].getTelszam())
                            {
                                std::cout<<"Mar van ilyen telefonszamu ember az adatbazisban"<<
                                ", kerlek a hozzáadott emberhez tartozo telefonszamot adj meg"<<std::endl;
                                delete[]temp;
                                return;
                            }
                        temp[i] = rekordok[i];
                    }
                temp[rekordokSzama] = ujrekord;
                delete[] rekordok;
                rekordok = new Rekord [rekordokSzama+1];
                for (int j = 0; j <= rekordokSzama; j++)
                    {
                        rekordok[j] = temp[j];
                    }

                rekordokSzama++;
                delete[] temp;
            }
    }

//kiírja a telefonkönyv elemeit soronként
void Telkonyv::printTelkonyv() const
    {
        std::cout<<"Jelenlegi lista: "<<std::endl;
        for(int i =0; i< rekordokSzama; i++)
            {
            std::cout << i<< ". " << rekordok[i];
            }
        std::cout<<std::endl;
        return;
    }

//Keresés részsztringek alapján is akár
void Telkonyv::keresByVeznev (const std::string keresendo, const int choice)
    {
        for(int i = 0; i<rekordokSzama; i++){

            if(choice == 1)
            {
            //if(strcmp(keresendo,rekordok[i].getVeznev())==0 && choice == 1) <-- ez volt a str.find() előtti verzió
            //letisztultabb volt, viszont a str.find() segítségével már részstringekkel is működik a keresés például, ha "Al" az input akkor "Almási"-t megkapjuk..
                std::string str1(rekordok[i].getVeznev());
                size_t found = str1.find(keresendo);
                if(found == 0)
                    {
                        std::cout<<"Talalat: "<<i<<". "<<rekordok[i]<<std::endl;
                    }
            }
             if(choice == 2)
            {
                std::string str1(rekordok[i].getKernev());
                size_t found = str1.find(keresendo);
                if(found == 0)
                    {
                        std::cout<<"Talalat: "<<i<<". "<<rekordok[i]<<std::endl;
                    }
            }
             if(choice == 3)
            {
                std::string str1(rekordok[i].getTelszam());
                size_t found = str1.find(keresendo);
                if(found == 0)
                    {
                        std::cout<<"Talalat: "<<i<<". "<<rekordok[i]<<std::endl;
                    }
            }
             if(choice == 4)
            {
                std::string str1(rekordok[i].getCimTelepules());
                size_t found = str1.find(keresendo);
                if(found == 0)
                    {
                        std::cout<<"Talalat: "<<i<<". "<<rekordok[i]<<std::endl;
                    }
            }
        }
        std::cout<<std::endl;

    }


//A paraméterként kapott vezetéknevű rekordot törli
void Telkonyv::torolByVeznev (const std::string keresendo)
    {
        //több egyforma vezetéknévvel rendelkező embernél van erre szükségünk, akkor a telefonszám(egyedi azonosító) alapján tisztázzuk a dolgot
        int* egyezoNevek = new int[0];
        int talalatok = 0;
        Rekord* temp = new Rekord[rekordokSzama-1];
        for(int i = 0; i< rekordokSzama; i++){

                if(keresendo == rekordok[i].getVeznev()) //ha a megadott vezetéknévvel van egyezés akkor elkezdjük feltölteni az egyezonevek tömböt
                    {
                        int* tempTalalatok = new int[talalatok+1];
                        for(int iter = 0; iter<talalatok; iter++)
                        {
                            tempTalalatok[iter] = egyezoNevek[iter];
                        }

                        tempTalalatok[talalatok] = i;

                        delete[] egyezoNevek;
                        egyezoNevek = new int[talalatok + 1];
                        for(int iter = 0; iter<=talalatok; iter++){
                            egyezoNevek[iter] = tempTalalatok[iter];
                        }
                        delete[] tempTalalatok;
                        talalatok++;
                        std::cout<<"Talalat : " << i<<".indexen"<<std::endl;
                    }
                if(i == rekordokSzama - 1)
                    {
                        if(talalatok == 0)
                            {
                                 std::cout << "Nincs ilyen vezeteknev az adatbazisban.\n" << std::endl;
                                 delete[] temp;
                                 delete[] egyezoNevek;
                                 return;
                            }
                        // Itt van az igazi törlés
                        if(talalatok == 1) //amennyiben nincs egyezés vezetéknevekben
                            {
                            bool valtozott = true;
                            int index = egyezoNevek[0];
                            std::cout<<"Torlom:"<<rekordok[index]<<std::endl;
                            std::cout<<std::endl;

                                if(index == rekordokSzama-1)
                                {
                                    std::cout<<"Utolso elemet kell torolni"<<std::endl;
                                }
                                else
                                {
                                    for (int i = index; i < rekordokSzama-1; i++)
                                        {
                                            temp[i] = rekordok[i + 1]; //A találattól számítva átmásolunk egy elem különbséggel
                                        }
                                }
                                //A teszteset miatt kell, végigmegyünk újra a tömbön
                                for(int j = 0; j < rekordokSzama-1; j++)
                                {
                                        if(keresendo == temp[j].getVeznev()) //és ha van egyezés, akkor hibás a törlés
                                            {
                                            valtozott = false;
                                            }
                                }
                                TEST(KontaktTorles, NevEllenorzes)
                                EXPECT_TRUE(valtozott) << "Nem lett torolve az adatbázisunkbol a feljebb megadott vezeteknevu szemely"<<std::endl;
                                END

                            }

                        else
                            {
                                std::cout<<"Tobb ilyen vezeteknevu ember van az adatbazisban: "<<std::endl;
                                int szamlalo = 0;
                                //végigmegyünk az egyezonevek tömbön és az ott tárolt indexeket felhasználva kilistázzuk az azonos veznevű embereket
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    std::cout << rekordok[index]<<std::endl;
                                    //jelenleg ennyi azonos nevű van
                                    szamlalo++;
                                }
                                int ellenorzo = szamlalo;

                                //Telefonszám segítségével egyértelműsítjük a törlést
                                std::cout<<"Add meg a torlendo kontakt telefonszamat: "<<std::endl;
                                std::string telszam;
                                std::cin >> telszam;
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    if(rekordok[index].getTelszam() == telszam) //Ellenőrzünk a telefonszámra
                                        {
                                    std::cout << "Torlom a kovetkezot: " << rekordok[index]<<std::endl;
                                            for(;index < rekordokSzama -1; index++)
                                                {
                                                  temp[index] = rekordok[index+1];
                                                }
                                        }

                                }
                                szamlalo = 0;

                                //Végigmegyünk és ha a törlés előtti számláló, majd a törlés után létrejött számláló egyezik, akkor nem teljesül a teszteset
                                for(int j = 0;j<rekordokSzama-1; j++)
                                    {
                                       if(keresendo == temp[j].getVeznev())
                                        {
                                           szamlalo++;
                                        }
                                    }
                                TEST(KontaktTorles, EgyezoNevekEllenorzes)
                                EXPECT_NE(ellenorzo, szamlalo) << "Ugyanannyi azonos nevű ember maradt, magyarul nem tortent torles"<<std::endl;
                                END



                            }
                    }

                    //amíg nem értünk a végére a telkönyvnek, addig másolunk
                    if( i < rekordokSzama-1)
                        {
                    temp[i] = rekordok[i];

                        }

        }

        delete[] rekordok;
        rekordok = new Rekord[rekordokSzama-1];

        //az ideiglenes tömbünkből visszamásolunk
        for(int i = 0; i<rekordokSzama-1; i++)
            {
                rekordok[i] = temp[i];
            }

        delete[] temp;
        delete[] egyezoNevek;
        rekordokSzama--;
    }


//Egy kaptafa az összes modosit fv.
void Telkonyv::modositVeznev (const std::string keresendo)
    {
            int* egyezoNevek = NULL; //szintén egyező vezetékneveknél hasznos
            int talalatok = 0;
            for(int i = 0; i< rekordokSzama; i++){

                if(keresendo == rekordok[i].getVeznev())//Jól működik, csak sok az if-else, amikor kerestem a memoriaszivargast,a többi modosit fv-ben az eredeti formájában van
                    {
                        int* tempTalalatok;
                     //Amennyiben több egyezõ vezetéknevû ember van
                        if(talalatok == 0) tempTalalatok = new int;
                        else tempTalalatok = new int[talalatok+1];
                        for(int iter = 0; iter<talalatok; iter++)
                        {
                            tempTalalatok[iter] = egyezoNevek[iter];
                        }

                        tempTalalatok[talalatok] = i;

                        if (talalatok == 1) delete egyezoNevek;
                        else if(talalatok > 1)delete[] egyezoNevek;
                        if(talalatok == 0) egyezoNevek = new int;
                        else               egyezoNevek = new int[talalatok + 1];
                        for(int iter = 0; iter<=talalatok; iter++){
                            egyezoNevek[iter] = tempTalalatok[iter];
                        }
                        if(talalatok == 0)delete tempTalalatok;
                        else              delete[] tempTalalatok;
                        talalatok++;
                        std::cout<<"Talalat : " << i<<".indexen"<<std::endl;
                    }
                if(i == rekordokSzama - 1)
                    {
                        if (talalatok == 1) //Hasonló a törléshez, kiszedjük a módosítandó elem indexét az egyezonevek tömbből
                            {
                                int index = egyezoNevek[0];
                                std::cout<<"Ot kell modositani: "<<rekordok[index]<<std::endl << "Kerlek add meg az uj vezeteknevet: \n" << std::endl;
                                std::string ujveznev;
                                std::cin >> ujveznev;
                                std::string ellenorzo = rekordok[index].getVeznev();
                                rekordok[index].setVeznev(ujveznev);
                                std::cout<<"Uj vezetekneve: \n"<<rekordok[index].getVeznev()<<std::endl;

                                TEST(Modositas, VeznevValtozik)
                                EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getVeznev()[0]) << "Nem tortent modositas"<<std::endl;
                                END
                                delete egyezoNevek;
                                return;
                            }
                        else if(talalatok > 1)
                            {
                                std::cout<<"Tobb ilyen vezeteknevu ember van az adatbazisban: \n"<<std::endl;
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    std::cout << rekordok[index]<<std::endl;
                                }
                                std::cout<<"Add meg a modositando kontakt telefonszamat: "<<std::endl;
                                std::string telszam;
                                std::cin >> telszam;
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    if(rekordok[index].getTelszam()== telszam)
                                        {
                                            std::cout << "Modositom a kovetkezot: " << rekordok[index]<<std::endl << "Kerlek add meg az uj vezeteknevet: \n"<<std::endl;
                                            std::string ujveznev;
                                            std::cin >> ujveznev;
                                            std::string ellenorzo = rekordok[index].getVeznev();
                                            rekordok[index].setVeznev(&ujveznev[0]);
                                            std::cout<<"Uj vezetekneve: \n"<<rekordok[index].getVeznev()<<std::endl;
                                            TEST(Modositas, VeznevValtozik)
                                            EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getVeznev()[0]) << "Nem tortent modositas"<<std::endl;
                                            END
                                            delete[] egyezoNevek;
                                            return;
                                        }

                                }

                            }
                    }
            }

            std::cout<<"Nincs ilyen nev a listaban\n"<<std::endl;
    }



void Telkonyv::modositKernev (const std::string keresendo)
    {
            //egyező vezetékneveknél egy tömbbe gyűjtjük azok indexét
            int* egyezoNevek = new int[0];
            int talalatok = 0;
            for(int i = 0; i< rekordokSzama; i++){

                if(keresendo == rekordok[i].getVeznev())
                    {
                     //Amennyiben több egyezõ vezetéknevû ember van
                        int* tempTalalatok = new int[talalatok+1];
                        for(int iter = 0; iter<talalatok; iter++)
                            {
                                tempTalalatok[iter] = egyezoNevek[iter];
                            }

                        tempTalalatok[talalatok] = i;

                        delete[] egyezoNevek;
                        egyezoNevek = new int[talalatok + 1];
                        for(int iter = 0; iter<=talalatok; iter++)
                            {
                                egyezoNevek[iter] = tempTalalatok[iter];
                            }
                        delete[] tempTalalatok;
                        talalatok++;
                        std::cout<<"Talalat : " << i<<".indexen"<<std::endl;
                    }
                if(i == rekordokSzama - 1) //ha végigértünk a tömbön
                    {
                        if (talalatok == 1)
                            {
                                int index = egyezoNevek[0];
                                std::cout<<"Ot kell modositani: "<<rekordok[index]<<std::endl
                                << "Kerlek add meg az uj keresztnevet: \n" << std::endl;
                                std::string ujkernev;
                                std::cin >> ujkernev;
                                std::string ellenorzo = rekordok[index].getKernev();
                                rekordok[index].setKernev(&ujkernev[0]);
                                std::cout<<"Uj keresztneve: \n"<<rekordok[index].getKernev()<<std::endl;
                                TEST(Modositas, KernevValtozik)
                                EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getKernev()[0])
                                << "Nem tortent modositas"<<std::endl;
                                END
                                delete[] egyezoNevek;
                                return;
                            }
                        else if(talalatok > 1)
                            {
                                std::cout<<"Tobb ilyen vezeteknevu ember van az adatbazisban: "<<std::endl;
                                for(int iter = 0; iter < talalatok; iter++)
                                    {
                                        int index = egyezoNevek[iter];
                                        std::cout << rekordok[index]<<std::endl;
                                    }
                                std::cout<<"Add meg a modositando kontakt telefonszamat: "<<std::endl;
                                std::string telszam;
                                std::cin >> telszam;
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    if(rekordok[index].getTelszam() == telszam)
                                        {
                                            std::cout << "Modositom a kovetkezot: " << rekordok[index]<<std::endl
                                            << "Kerlek add meg az uj keresztnevet: \n"<<std::endl;
                                            std::string ujkernev;
                                            std::cin >> ujkernev;
                                            std::string ellenorzo = rekordok[index].getKernev();
                                            rekordok[index].setKernev(&ujkernev[0]);
                                            std::cout<<"Uj keresztneve: \n"<<rekordok[index].getKernev()<<std::endl;
                                            TEST(Modositas, KernevValtozik)
                                            EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getKernev()[0])
                                            << "Nem tortent modositas"<<std::endl;
                                            END
                                            delete[] egyezoNevek;
                                            return;
                                        }

                                }

                            }
                    }
            }

            std::cout<<"Nincs ilyen nev a listaban\n"<<std::endl;
    }



void Telkonyv::modositTelszam (const std::string keresendo)
    {
            int* egyezoNevek = new int[0];
            int talalatok = 0;
            for(int i = 0; i< rekordokSzama; i++){

                if(keresendo == rekordok[i].getVeznev())
                    {
                     //Amennyiben több egyezõ vezetéknevû ember van
                        int* tempTalalatok = new int[talalatok+1];
                        for(int iter = 0; iter<talalatok; iter++)
                            {
                                tempTalalatok[iter] = egyezoNevek[iter];
                            }

                        tempTalalatok[talalatok] = i;

                        delete[] egyezoNevek;
                        egyezoNevek = new int[talalatok + 1];
                        for(int iter = 0; iter<=talalatok; iter++)
                            {
                                egyezoNevek[iter] = tempTalalatok[iter];
                            }
                        delete[] tempTalalatok;
                        talalatok++;
                        std::cout<<"Talalat : " << i<<".indexen"<<std::endl;
                    }
                if(i == rekordokSzama - 1)
                    {
                        if (talalatok == 1)
                            {
                                int index = egyezoNevek[0];
                                std::cout<<"Ot kell modositani: "<<rekordok[index]<<std::endl << "Kerlek add meg az uj telefonszamot: \n" << std::endl;
                                std::string ujtelszam;
                                std::cin >> ujtelszam;
                                std::string ellenorzo = rekordok[index].getTelszam();
                                rekordok[index].setTelszam(&ujtelszam[0]);
                                std::cout<<"Uj telefonszama: \n"<<rekordok[index].getTelszam()<<std::endl;
                                TEST(Modositas, TelszamValtozik)
                                EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getTelszam()[0]) << "Nem tortent modositas"<<std::endl;
                                END
                                delete[] egyezoNevek;
                                return;
                            }
                        else if(talalatok > 1)
                            {
                                std::cout<<"Tobb ilyen vezeteknevu ember van az adatbazisban: "<<std::endl;
                                for(int iter = 0; iter < talalatok; iter++)
                                    {
                                        int index = egyezoNevek[iter];
                                        std::cout << rekordok[index]<<std::endl;
                                    }
                                std::cout<<"Add meg a modositando kontakt telefonszamat: "<<std::endl;
                                std::string telszam;
                                std::cin >> telszam;
                                for(int iter = 0; iter < talalatok; iter++)
                                    {
                                        int index = egyezoNevek[iter];
                                        if(rekordok[index].getTelszam() == telszam)
                                            {
                                                std::cout << "Modositom a kovetkezot: " << rekordok[index]<<std::endl << "Kerlek add meg az uj telefonszamot: \n"<<std::endl;
                                                std::string ujtelszam;
                                                std::cin >> ujtelszam;
                                                std::string ellenorzo = rekordok[index].getTelszam();
                                                rekordok[index].setTelszam(&ujtelszam[0]);
                                                std::cout<<"Uj telefonszama: \n"<<rekordok[index].getTelszam()<<std::endl;
                                                TEST(Modositas, TelszamValtozik)
                                                EXPECT_STRNE(&ellenorzo[0], &rekordok[index].getTelszam()[0]) << "Nem tortent modositas"<<std::endl;
                                                END
                                                delete[] egyezoNevek;
                                                return;
                                            }

                                    }

                            }
                    }
            }

            std::cout<<"Nincs ilyen nev a listaban\n"<<std::endl;
    }


void Telkonyv::modositCim (const std::string keresendo)
    {
            int* egyezoNevek = new int[0];
            int talalatok = 0;
            for(int i = 0; i< rekordokSzama; i++){

                if(keresendo == rekordok[i].getVeznev())
                    {
                     //Amennyiben több egyezõ vezetéknevû ember van
                        int* tempTalalatok = new int[talalatok+1];
                        for(int iter = 0; iter<talalatok; iter++)
                            {
                                tempTalalatok[iter] = egyezoNevek[iter];
                            }

                        tempTalalatok[talalatok] = i;

                        delete[] egyezoNevek;
                        egyezoNevek = new int[talalatok + 1];
                        for(int iter = 0; iter<=talalatok; iter++)
                            {
                                egyezoNevek[iter] = tempTalalatok[iter];
                            }
                        delete[] tempTalalatok;
                        talalatok++;
                        std::cout<<"Talalat : " << i<<".indexen"<<std::endl;
                    }
                if(i == rekordokSzama - 1)
                    {
                        if (talalatok == 1)
                            {
                                int index = egyezoNevek[0];
                                std::cout<<"Ot kell modositani: "<<rekordok[index]<<std::endl << "Kerlek add meg az uj cimet szokozokkel elvalasztva(pl.: 1333 Budapest Munkacsy 5): \n" << std::endl;
                                std::string ujtelep, ujutca;
                                int ujzip, ujhazszam;
                                std::cin >> ujzip >> ujtelep >> ujutca >> ujhazszam;
                                bool valtozott = true;
                                int ellenorzo1 = rekordok[index].getCimZipCode();
                                std::string ellenorzo2 = rekordok[index].getCimTelepules();
                                std::string ellenorzo3 = rekordok[index].getCimUtca();
                                int ellenorzo4 = rekordok[index].getCimHazszam();
                                rekordok[index].setCim(ujzip, ujtelep, ujutca, ujhazszam);
                                std::cout<<"Uj cime: \n"<<rekordok[index].getCimZipCode()<<" "<<rekordok[index].getCimTelepules()<<" "<<rekordok[index].getCimUtca()<<" "<< rekordok[index].getCimHazszam() << std::endl;
                                    //kicsit brute force módszer de működik a teszteléshez
                                        if (ellenorzo1 == rekordok[index].getCimZipCode() && ellenorzo2 == rekordok[index].getCimTelepules()
                                            && ellenorzo3 == rekordok[index].getCimUtca() && ellenorzo4 == rekordok[index].getCimHazszam()){valtozott = false;}

                                TEST(Modositas, CimValtozik)
                                EXPECT_TRUE(valtozott);
                                END
                                delete[] egyezoNevek;
                                return;
                            }
                        else if(talalatok > 1)
                            {
                                std::cout<<"Tobb ilyen vezeteknevu ember van az adatbazisban: \n"<<std::endl;
                                for(int iter = 0; iter < talalatok; iter++)
                                    {
                                        int index = egyezoNevek[iter];
                                        std::cout << rekordok[index]<<std::endl;
                                    }
                                std::cout<<"Add meg a modositando kontakt telefonszamat: "<<std::endl;
                                std::string telszam;
                                std::cin >> telszam;
                                for(int iter = 0; iter < talalatok; iter++)
                                {
                                    int index = egyezoNevek[iter];
                                    if(rekordok[index].getTelszam() == telszam)
                                        {
                                            std::cout<<"Ot kell modositani: "<<rekordok[index]<<std::endl << "Kerlek add meg az uj cimet szokozokkel elvalasztva(pl.: 1333 Budapest Munkacsy 5): \n" << std::endl;
                                            std::string ujtelep, ujutca;
                                            int ujzip, ujhazszam;
                                            std::cin >> ujzip >> ujtelep >> ujutca >> ujhazszam;
                                            bool valtozott = true;
                                            int ellenorzo1 = rekordok[index].getCimZipCode();
                                            std::string ellenorzo2 = rekordok[index].getCimTelepules();
                                            std::string ellenorzo3 = rekordok[index].getCimUtca();
                                            int ellenorzo4 = rekordok[index].getCimHazszam();
                                            rekordok[index].setCim(ujzip, ujtelep, ujutca, ujhazszam);
                                            std::cout<<"Uj cime: \n"<<rekordok[index].getCimZipCode()<<" "<<rekordok[index].getCimTelepules()<<" "<<rekordok[index].getCimUtca()<<" "<< rekordok[index].getCimHazszam() << std::endl;
                                                    //kicsit brute force módszer de működik a teszteléshez
                                                    if (ellenorzo1 == rekordok[index].getCimZipCode() && ellenorzo2 == rekordok[index].getCimTelepules()
                                                        && ellenorzo3 == rekordok[index].getCimUtca() && ellenorzo4 == rekordok[index].getCimHazszam()){valtozott = false;}

                                            TEST(Modositas, CimValtozik)
                                            EXPECT_TRUE(valtozott);
                                            END
                                            delete[] egyezoNevek;
                                            return;
                                        }

                                }

                            }
                    }
            }

            std::cout<<"Nincs ilyen nev a listaban\n"<<std::endl;
    }


//fájlba írjuk a telefönkömnyv tartalmát
void Telkonyv::saveToFile()
    {
        std::ofstream file;
        file.open("minta.txt", std::ios::trunc);
        for(int i = 0; i< rekordokSzama; i++)
        {
            file << rekordok[i].getVeznev() << " ";
            file << rekordok[i].getKernev() << " ";
            file << rekordok[i].getTelszam() << " ";
            file << rekordok[i].getCimZipCode() << " ";
            file << rekordok[i].getCimTelepules() << " ";
            file << rekordok[i].getCimUtca() << " ";
            file << rekordok[i].getCimHazszam() << '\n';
        }
        file.close();
    }



//fájlból olvassuk be a telefonkönyv tartalmát
void Telkonyv::readFromFile()
    {
        Rekord teszt;
        Lakcim ujcim;
        std::ifstream file;
        file.open("minta.txt");
        std::string word;

        int i = 0;

        while (file >> word){
            char* char_arr;

            char_arr = &word[0];

            if(i%7 == 0)
            {
            teszt.setVeznev(word);
            i++;
            }
            else if(i%7 == 1)
            {
            teszt.setKernev(word);
            i++;
            }
            else if(i%7 == 2)
            {
            teszt.setTelszam(word);
            i++;
            }
            else if(i%7 == 3)
            {
            teszt.setCimZip(atoi(char_arr));
            i++;
            }
            else if(i%7 == 4)
            {
            teszt.setCimTelep(word);
            i++;
            }
            else if(i%7 == 5)
            {
            teszt.setCimUtca(word);
            i++;
            }
            else if(i%7 == 6)
            {
            teszt.setCimHazszam(atoi(char_arr));
            this->addRekord(teszt); //itt történik a hozzáadás, miután minden értékét beállítottuk a rekordnak

            i++;
            }
        }
        file.close();
    }
