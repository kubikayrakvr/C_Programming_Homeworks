#define matris_l 25
#include <stdio.h>

int main(){
    int N;
    char oyun_matris[matris_l][matris_l];
    char oyuncu_renkleri[3][8]={{'K','i','r','m','i','z','i','\0'},{'S','a','r','i','\0'},{'M','a','v','i','\0'}};//kirmizi sari mavi
    int oyuncu_skorlar[3];
    int skor_siralama[3];
    int skor_temp;
    static char giris_koordinat[8];
    int yonler[8][2]={{-1,0},{-1, 1},{0, 1},{1, 1},{1, 0},{1,-1},{0,-1},{-1,-1}};//Olasi Yonler
    int cevirme_sutun;
    int cevirme_satir;
    int cevrilen_tas;
    int cevirme_kontrol;
    int yon_sira;
    int yon_kontrol;
    int giris_satir;
    int giris_sutun;
    int k;
    int sira;
    int satir_bas;
    int tas_sayi;
    int cikis_sinyal;
    char oyun_dongu;
    while(oyun_dongu!='E')
    {
        //Menu Tasarimi
        printf("+--------------------------------------------------------+\n");
        printf("|    TTTTT  RRRR   III  V   V  EEEEE  RRRR   SSSS  III   |\n");
        printf("|      T    R   R   I   V   V  E      R   R  S      I    |\n");
        printf("|      T    RRRR    I   V   V  EEEE   RRRR   SSSS   I    |\n");
        printf("|      T    R  R    I   V   V  E      R  R      S   I    |\n");
        printf("|      T    R   R  III   VVV   EEEEE  R   R  SSSS  III   |\n");
        printf("+--------------------------------------------------------+\n");
        printf("       +-------+      +--------+      +-----------+\n");
        printf("       |OYNA[Y]|      |CIKIS[E]|      |KURALLAR[K]|\n");
        printf("       +-------+      +--------+      +-----------+\n");
        printf("> Ne yapmak istiyorsunuz: ");
        scanf(" %c", &oyun_dongu);//harflere gore istenen donguye giriliyor
        if(oyun_dongu=='K')
        {
            printf("\nTemel Oyun Kurallari:\nOyun, 1. oyuncunun kirmizi tasini oyun tahtasinin ortasina en yakin koordinata koymasi ile baslar.\n");
            printf("Sirayla 2. oyuncu sari, 3.oyuncu mavi tasini tahtaya diger taslara yatay/dikey/capraz olarak koyar ve oyun bu sekilde devam eder.\n");
            printf("Renk degisimi icin, yatay/dikey/capraz siranin bir acik ucuna koyulan tas ile o siradaki ayni renkteki\ndiger en yakin tasin arasindaki diger renklerin tamami, koyulan tasin rengine doner.\n\n");
            printf("Amac:\nOyunun amaci, rakibin taslarini kendi taşlariniz arasina alarak onlari ters cevirmektir.\nOyun sonunda en fazla tas sahibi olan oyuncu kazanir.\n\n");
            printf("Oyun Alani Buyuklugu Sinirlari:\nOyunun maksimum buyuklugu 23x23, minimum buyuklugu ise 3x3'tur.\n\n");
            printf("Tas Yerlestirme:\nTas yerlestirirken koordinat satir_degeri,sutun_degeri seklinde girilmelidir. Ornek: 3,4\n\n");
        }
        while(oyun_dongu=='Y')
        {
            printf("\n> Oyun alani buyuklugunu giriniz: ");
            scanf("%d", &N);
            tas_sayi=0;
            sira=0;
            if(N<=23 && N>2)//Oyun Alani Buyuklugu Denetimi
            {
                //Sifirlama islemleri
                for(int i=0; i<3;i++)
                {
                    skor_siralama[i]=i;
                    oyuncu_skorlar[i]=0;
                }
                for(int i=0;i<N;i++)
                {
                    for(int j=0; j<N;j++)
                    {
                        oyun_matris[i][j]=' ';
                    }
                }
                cikis_sinyal=1;
                k=0;
                giris_satir=0;
                giris_sutun=0;
                //Tahta Yapisini Olusturma
                printf(" ");
                for(int i=0; i<N;i++)
                {
                    if (i<9)
                    {
                        printf("   %d", i+1);
                    }
                    else
                    {
                        printf("  %d", i+1);
                    }
                }
                printf("\n");
                for(int i=0; i<N; i++)
                {
                    printf("  ");
                    for(int j=0; j<N; j++)
                    {
                        printf("+---");
                    }
                    if (i<9)//solda satir sayilari icin
                    {
                        printf("+\n %d", i+1);
                    }
                    else
                    {
                        printf("+\n%d", i+1);
                    }
                    for(int j=0; j<N; j++)//Kutucuk Ici Degerleri
                    {
                        printf("| %c ", oyun_matris[i][j]);
                    }
                    printf("|\n");
                }
                printf("  ");
                for(int j=0; j<N; j++)
                {
                    printf("+---");
                }
                printf("+\n");
                if(N%2==0)//ilk tasin buyukluk cift ise manuel, tek ise otomatik konulma ayrimi
                {
                    while(cikis_sinyal)
                    {
                        printf("> %s oyuncu tasi merkeze en yakin koordinatlardan bir tanesi olacak sekilde istediginiz yeri girin: ", oyuncu_renkleri[sira]);
                        scanf("%s", giris_koordinat);
                        k=0;
                        //Stringden integer'a donusum
                        while(giris_koordinat[k]!=',') 
                        {
                            giris_satir=giris_satir*10 + (giris_koordinat[k]-'0');
                            k++;
                        }
                        k++;//stringde yer belirtici
                        while(giris_koordinat[k]!='\0') 
                        {
                            giris_sutun=giris_sutun*10 + (giris_koordinat[k]-'0');
                            k++;
                        }
                        giris_satir--;
                        giris_sutun--;//sutun,satir degerinin 1 azi(array ici kullanimini kolaylastiriyor)
                        if((N/2-1==giris_sutun || N/2==giris_sutun)  && (N/2-1==giris_satir || N/2==giris_satir))
                        {
                            oyun_matris[giris_satir][giris_sutun]=oyuncu_renkleri[sira][0];
                            oyuncu_skorlar[sira]++;
                            sira++;
                            tas_sayi++;
                            cikis_sinyal=0;
                        }
                        else
                        {
                            printf("!! Merkezi bir koordinat girin. %s oyuncu sira hala sende.\n", oyuncu_renkleri[sira]);
                            cikis_sinyal=1;
                        }
                        giris_satir=0;
                        giris_sutun=0;
                    }
                }
                else
                {
                    oyun_matris[N/2][N/2]=oyuncu_renkleri[sira][0];//N degerimiz integer oldugu icin 2'ye bolumu tam sayi kismini veriyor
                    oyuncu_skorlar[sira]++;
                    printf("! Buyukluk degeri tek oldugu icin %s oyuncunun sembolu en merkeze otomatik yerlestirilmistir.\n", oyuncu_renkleri[sira]);
                    sira++;
                    tas_sayi++;
                }
                //Tahta Yapisini Olusturma
                printf(" ");
                for(int i=0; i<N;i++)
                {
                    if (i<9)
                    {
                        printf("   %d", i+1);
                    }
                    else
                    {
                        printf("  %d", i+1);
                    }
                }
                printf("\n");
                for(int i=0; i<N; i++)
                {
                    printf("  ");
                    for(int j=0; j<N; j++)
                    {
                        printf("+---");
                    }
                    if (i<9){//solda satir sayilari icin
                        printf("+\n %d", i+1);
                    }
                    else
                    {
                        printf("+\n%d", i+1);
                    }
                    for(int j=0; j<N; j++)
                    {
                        printf("| %c ", oyun_matris[i][j]);
                    }
                    printf("|\n");
                }
                printf("  ");
                for(int j=0; j<N; j++)
                {
                    printf("+---");
                }
                printf("+\n");
                cikis_sinyal=1;
                while(cikis_sinyal)
                {
                    printf("> %s oyuncu tasi koymak istediginiz koordinati girin: ", oyuncu_renkleri[sira]);
                    scanf("%s", giris_koordinat);
                    k=0;//k stringde yer belirtici
                    //Stringden integer'a donusum
                    while(giris_koordinat[k]!=',') 
                    {
                        giris_satir=giris_satir*10 + (giris_koordinat[k]-'0');
                        k++;
                    }
                    k++;
                    while(giris_koordinat[k]!='\0') 
                    {
                        giris_sutun=giris_sutun*10 + (giris_koordinat[k]-'0');
                        k++;
                    }
                    giris_satir--;
                    giris_sutun--;//sutun,satir degerinin 1 azi(kullanimini kolaylastiriyor)
                    if(giris_sutun<N && giris_satir<N && giris_sutun>=0 && giris_satir>=0)//Girilen Koordinatin Oyun Sinirlarinin Icinde Olma
                    {
                        if(oyun_matris[giris_satir][giris_sutun]==' ')//Tasin Koyulacagi Yerin Bos Olmasi
                        {
                            yon_sira=0;
                            yon_kontrol=0;
                            while(yon_sira<8)//Koyulacak Tasin Tegetleri Var Mi, Varsa Ayni Yone Dogru Gidildiginde Kendisinin Aynisi Olan Bir Tas Var Mi
                            {
                                cevirme_satir=giris_satir+yonler[yon_sira][1];
                                cevirme_sutun=giris_sutun+yonler[yon_sira][0];//Bakilan yone gitmeye yarayan degiskenler
                                if((cevirme_satir>=0 && cevirme_satir<N) && (cevirme_sutun>=0 && cevirme_sutun<N))//Bakilan yonde sinirlar icinde kaliniyor mu
                                {
                                    if(oyun_matris[cevirme_satir][cevirme_sutun]!=' ')//Bakilan yonde tas var mi
                                    {
                                        yon_kontrol=1;
                                        cevirme_kontrol=1;
                                        cevrilen_tas=0;
                                        while(cevirme_kontrol)
                                        {
                                            if(oyun_matris[cevirme_satir][cevirme_sutun]==oyuncu_renkleri[sira][0])//Bakilan yonde ayni turde tas varsa
                                            {
                                                for(int i=0; i<cevrilen_tas; i++)//Bulunan ayni tur tasi uzakliga gore tas cevirme
                                                {
                                                    cevirme_satir-=yonler[yon_sira][1];
                                                    cevirme_sutun-=yonler[yon_sira][0];//Ayni tur tastan koyulan tasa dogru geri donme
                                                    if(oyun_matris[cevirme_satir][cevirme_sutun]=='K')//Skor tutma
                                                    {
                                                        oyuncu_skorlar[0]--;
                                                    }
                                                    else if(oyun_matris[cevirme_satir][cevirme_sutun]=='S')
                                                    {
                                                        oyuncu_skorlar[1]--;
                                                    }
                                                    else
                                                    {
                                                        oyuncu_skorlar[2]--;
                                                    }
                                                    oyun_matris[cevirme_satir][cevirme_sutun]=oyuncu_renkleri[sira][0];
                                                    oyuncu_skorlar[sira]++;
                                                }
                                                cevirme_kontrol=0;
                                            }
                                            cevirme_satir+=yonler[yon_sira][1];//Ayni tur tas arama icin ayni yonde devam
                                            cevirme_sutun+=yonler[yon_sira][0];
                                            if((cevirme_satir<0 || cevirme_satir>N) || (cevirme_sutun<0 || cevirme_sutun>N) || oyun_matris[cevirme_satir][cevirme_sutun]==' ')//Sinirlar asildiginda yada bos goze gelindiginde dur
                                            {
                                                cevirme_kontrol=0;
                                            }
                                            else
                                            {
                                                cevrilen_tas++;
                                            }
                                        }
                                    }
                                }
                                yon_sira++;
                            }
                            if(yon_kontrol==0)
                            {
                                printf("!! Onceki taslara teget olan bir koordinat girin. %s oyuncu sira hala sende..\n", oyuncu_renkleri[sira]);
                                sira--;
                            }
                            else//Teget bulunduysa girilen koordinata tas koy
                            {
                                oyun_matris[giris_satir][giris_sutun]=oyuncu_renkleri[sira][0];
                                oyuncu_skorlar[sira]++;
                                tas_sayi++;
                            }
                        }
                        else
                        {
                            printf("!! Girilen koordinatta tas mevcut, farkli bir koordinat girin. %s oyuncu sira hala sende..\n", oyuncu_renkleri[sira]);
                            sira--;
                        }
                    }
                    else
                    {
                        printf("!! Sinir disi koordinat, farkli bir koordinat girin. %s oyuncu sira hala sende..\n", oyuncu_renkleri[sira]);
                        sira--;
                    }
                    //Sira Yonetimi
                    if(sira<2)
                    {
                        sira++;
                    }
                    else
                    {
                        sira=0;
                    }
                    //Tahta Yapisinin Olusumu
                    printf(" ");
                    for(int i=0; i<N;i++)
                    {
                        if (i<9)
                        {
                            printf("   %d", i+1);
                        }
                        else
                        {
                            printf("  %d", i+1);
                        }
                    }
                    printf("\n");
                    for(int i=0; i<N; i++)
                    {
                        printf("  ");
                        for(int j=0; j<N; j++){
                            printf("+---");
                        }
                        if (i<9){
                            printf("+\n %d", i+1);
                        }
                        else{
                            printf("+\n%d", i+1);
                        }
                        for(int j=0; j<N; j++){
                            printf("| %c ", oyun_matris[i][j]);
                        }
                        printf("|\n");
                    }
                    printf("  ");
                    for(int j=0; j<N; j++)
                    {
                        printf("+---");
                    }
                    printf("+\n");
                    giris_satir=0;
                    giris_sutun=0;
                    if(tas_sayi==N*N)//bitim kontrolu ve skor tablosu sistemi
                    {
                        printf("\n| Oyun bitmistir. |\n");
                        printf("Skorlar:\n\n");
                        for(int i=0;i<2;i++)//siralama
                        {
                            for(int j=i+1;j<3;j++){
                                if(oyuncu_skorlar[i]>oyuncu_skorlar[j])
                                {
                                    skor_temp=oyuncu_skorlar[i];//Skorlari siraliyoruz
                                    oyuncu_skorlar[i]=oyuncu_skorlar[j];
                                    oyuncu_skorlar[j]=skor_temp;
                                    skor_temp=skor_siralama[i];//Yaptigimiz siralamada ve hangi rengin kacinci oldugunu tutuyoruz
                                    skor_siralama[i]=skor_siralama[j];
                                    skor_siralama[j]=skor_temp;
                                }
                            }
                        }
                        if(oyuncu_skorlar[0]==oyuncu_skorlar[1]){//Esitlik Durumlari
                            if(oyuncu_skorlar[0]==oyuncu_skorlar[2]){
                                printf("\n=Berabere=");
                            }
                            else{
                                printf("1. %s: %d 2. %s ve %s", oyuncu_renkleri[skor_siralama[2]], oyuncu_skorlar[2], oyuncu_renkleri[skor_siralama[1]], oyuncu_skorlar[1], oyuncu_renkleri[skor_siralama[0]], oyuncu_skorlar[0]);
                            }
                        }
                        else if(oyuncu_skorlar[1]==oyuncu_skorlar[2]){
                            printf("1. %s ve %s: %d\n2. %s: %d", oyuncu_renkleri[skor_siralama[2]], oyuncu_renkleri[skor_siralama[1]], oyuncu_skorlar[1],  oyuncu_renkleri[skor_siralama[0]], oyuncu_skorlar[0]);
                        }
                        else{
                            printf("1. %s: %d\n2. %s: %d\n3. %s: %d", oyuncu_renkleri[skor_siralama[2]], oyuncu_skorlar[2], oyuncu_renkleri[skor_siralama[1]],oyuncu_skorlar[1],  oyuncu_renkleri[skor_siralama[0]], oyuncu_skorlar[0]);
                        }
                        cikis_sinyal=0;
                    }
                }
            }
            else{
                printf("!!! Gecersiz Buyukluk");
            }
            printf("\n\n>Tekrar Oynamak Ister Misiniz?[Y/N]: ");
            scanf(" %c", &oyun_dongu);
        }
    }
    printf("\n> Oynadiginiz icin tesekkur ederim :D");
    return 0;
}
//Kodun Calisma Videosu -> https://www.youtube.com/watch?v=EQotomIWduY

//Functions Were Not Used On Purpose