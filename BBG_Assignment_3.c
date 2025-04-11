#include <stdio.h>

int main()
{
    int N, k;
    int ucus_nu[100], ucus_saat[100], pist_1_saat[100], pist_2_saat[100], pist_1_nu[100], pist_2_nu[100];/*Burada C'nin kisitlamalari nedeniyle dizilerin uzunlugunu belirtiyoruz, 100 dedigimiz icin maks 100 ucus yapabiliyoruz*/
    printf("Ucus sayisini girin.\n");
    scanf("%d", &N);
    printf("Ucuslar arasi sureyi girin.\n");
    scanf("%d", &k);
    printf("Ucus numaralarini girin.\n");
    for(int i = 0; i<N; i++)/*ucus numaralarini alan for loop*/
    {
        scanf("%d", &ucus_nu[i]);
    }
    printf("Ucus saatlerini girin.\n");
    for(int i = 0; i<N; i++)/*ucus saatlerini alan for loop*/
    {
        scanf("%d", &ucus_saat[i]);
    }
    pist_1_saat[0] = ucus_saat[0];/*kolaylik olsun diye ilk ucuslarin zamanlarini atiyoruz*/
    pist_2_saat[0] = ucus_saat[1];
    pist_1_nu[0] = ucus_nu[0];
    pist_2_nu[0] = ucus_nu[1];
    int pist_1_say=1, pist_2_say=1;/*Pistlere inen ucak sayisini belirten degiskenler*/
    float pist_1_gec = 0, pist_2_gec = 0; /*ortalama gec kalma degiskeni*/
    if(N%2==0){/*cift olup olmadigina gore farkli sayida tekrar yapacagimizdan if statementiyla ayiriyoruz*/
        for(int i = 2; i<N; i+=2)/*bir dongude iki piste de ucak koydugumuzda incrementimiz 2li artiyor*/
        {
            pist_1_nu[pist_1_say]=ucus_nu[i];
            pist_2_nu[pist_2_say]=ucus_nu[i+1];
            if((pist_1_saat[pist_1_say-1]+k)>ucus_saat[i])/*eger onceki ucus saati arti aralik planlanan saatten daha gecse gecikme olucak*/
            {
                pist_1_saat[pist_1_say]=pist_1_saat[pist_1_say-1]+k;
                pist_1_gec+=(pist_1_saat[pist_1_say-1]+k)-ucus_saat[i];/*toplam gecikme degerini artiriyoruz*/
            }
            else
                pist_1_saat[pist_1_say]=ucus_saat[i];
            if((pist_2_saat[pist_2_say-1]+k)>ucus_saat[i])/*eger onceki ucus saati arti aralik planlanan saatten daha gecse gecikme olucak*/
            {
                pist_2_saat[pist_2_say]=pist_2_saat[pist_2_say-1]+k;
                pist_2_gec+=(pist_2_saat[pist_2_say-1]+k)-ucus_saat[i];/*toplam gecikme degerini artiriyoruz*/
            }
            else
                pist_2_saat[pist_2_say]=ucus_saat[i+1];
            pist_1_say++;/*pistlerde ucan ucak sayisini tutuyoruz*/
            pist_2_say++;
        }
    }
    else/*tek oldugunda ekstra bir ucusu pist 1'e eklememiz gerekiyor o yuzden ifle farkli fonksiyonlar gerceklestiriyoruz*/
    {
        for(int i = 2; i<N-1; i+=2)
        {
            pist_1_nu[pist_1_say]=ucus_nu[i];
            pist_2_nu[pist_2_say]=ucus_nu[i+1];
            if((pist_1_saat[pist_1_say-1]+k)>ucus_saat[i])/*eger onceki ucus saati arti aralik planlanan saatten daha gecse gecikme olucak*/
            {
                pist_1_saat[pist_1_say]=pist_1_saat[pist_1_say-1]+k;
                pist_1_gec+=(pist_1_saat[pist_1_say-1]+k)-ucus_saat[i];/*toplam gecikme degerini artiriyoruz*/
            }
            else
                pist_1_saat[pist_1_say]=ucus_saat[i];
            if((pist_2_saat[pist_2_say-1]+k)>ucus_saat[i])/*eger onceki ucus saati arti aralik planlanan saatten daha gecse gecikme olucak*/
            {
                pist_2_saat[pist_2_say]=pist_2_saat[pist_2_say-1]+k;
                pist_2_gec+=(pist_2_saat[pist_2_say-1]+k)-ucus_saat[i];/*toplam gecikme degerini artiriyoruz*/
            }
            else
                pist_2_saat[pist_2_say]=ucus_saat[i+1];
            pist_1_say++;
            pist_2_say++;
        }
        pist_1_nu[(N-1)/2]=ucus_nu[N-1];
        if((pist_1_saat[pist_1_say-1]+k)>ucus_saat[N-1])/*eger onceki ucus saati arti aralik planlanan saatten daha gecse gecikme olucak*/
        {
            pist_1_saat[pist_1_say]=pist_1_saat[pist_1_say-1]+k;
            pist_1_gec+=(pist_1_saat[pist_1_say-1]+k)-ucus_saat[N-1];/*toplam gecikme degerini artiriyoruz*/
        }
        else
            pist_1_saat[pist_1_say]=ucus_saat[N-1];
        pist_1_say++;
    }
    float pist_1_ort = pist_1_gec/pist_1_say;/*toplam gecikmeyi pistteki ucus sayisina boluyoruz*/
    float pist_2_ort = pist_2_gec/pist_2_say;
    printf("\nPist 1 ucus numaralari: ");
    for(int l = 0; l<pist_1_say; l++)/*for looplari ile buldugumuz degerlerin ucak sayisina gore ciktisini aliyoruz*/
    {
    printf("%d ", pist_1_nu[l]);
    }

    printf("Pist 1 saatleri: ");
    for(int l = 0; l<pist_1_say; l++)
    {
    printf("%d ", pist_1_saat[l]);
    }
    printf("\n1. Pist Ortalama gecikme degeri: %f\n", pist_1_ort);

    printf("Pist 2 ucus numaralari: ");
    for(int l = 0; l<pist_2_say; l++)
    {
    printf("%d ", pist_2_nu[l]);
    }
    printf("Pist 2 saatleri: ");
    for(int l = 0; l<pist_2_say; l++)
    {
    printf("%d ", pist_2_saat[l]);
    }
    printf("\n2. Pist Ortalama gecikme degeri: %f\n", pist_2_ort);
}/*Kod su an girdilerin dogru ve 100 ucagi asmadigini farz ediyor ancak odevde herhalde bunlari onemsememiz gerektigini dusunerek hazirladim*/