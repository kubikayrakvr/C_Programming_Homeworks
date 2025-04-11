#include <stdio.h>
#define dizi_len 50

int main()
{
    int N, M;
    int giris_matris[dizi_len][dizi_len];
    int yol_deger[dizi_len];
    int konumX[dizi_len];
    int konumY[dizi_len];
    int yol_len[dizi_len];
    int yol_say=0;
    int var_yok;
    int yon_num;
    int hareket_yonleri[8][2]={{1,0},{-1,0},{0,-1},{0,1},{1,-1},{-1,-1},{1,1},{-1,1}};//teker teker else if ifadeleri kullanmak yerine olasi yonleri kullanabilmek icin yaziyoruz
    printf("Matris satir sayisini girin: ");
    scanf("%d",&N);
    printf("Matris sutun sayisini girin: ");
    scanf("%d",&M);
    printf("Matrisi girin:\n");
    for(int i=0; i<N ;i++)
    {
        for(int j=0; j<M ; j++)
        {
            /*printf("%d. satirin %d. elemanini girin: ", i+1, j+1); //alternatif girdi modeli*/
            scanf("%d", &giris_matris[i][j]);
        }
    }

    for (int i = 0; i < N; i++) {
        if (giris_matris[i][0] != 0) {//sifir olmayan degerleri yol olarak atiyoruz ve konumlarini aliyoruz
            konumY[yol_say] = i;
            konumX[yol_say] = 0;
            yol_deger[yol_say] = giris_matris[i][0];
            yol_len[yol_say] = 1; 
            yol_say++;
        }
    }
    /*
    printf("Girilen 2 boyutlu matris:\n");//sonraki ifadelerde matrisin uzerinde oynama yapacagimiz icin ilk basta ciktisini aliyoruz
    for(int i=0; i<N ;i++)
    {
        for(int j=0; j<M ;j++) //(alternatif girdi modeli kullanilmak istenirse)
        {
            printf("%d ", giris_matris[i][j]);
        }
        printf("\n");
    }
    */
    for(int i=0; i<yol_say ;i++)
    {
        var_yok=1;
        while(var_yok)
        {
            var_yok=0;//eger yol bulunmazsa bu deger en sona kadar degismeyecegi icin while loopundan cikmayi saglayacak
            for(yon_num=0; yon_num<8; yon_num++)//for dongusuyle olasi hareketleri dizide siraladigimiz oncelikle kontrol ediyoruz
            {
                if(konumX[i]+hareket_yonleri[yon_num][0] < M && konumX[i]+hareket_yonleri[yon_num][0] >= 0 && konumY[i]+hareket_yonleri[yon_num][1] >=0 && konumY[i]+hareket_yonleri[yon_num][1] < N)
                //bu kondisyonlar hareket gerceklestiginde eger sinirlari asilacak mi onu kontrol ediyor
                {
                    if(yol_deger[i]==giris_matris[konumY[i]+hareket_yonleri[yon_num][1]][konumX[i]+hareket_yonleri[yon_num][0]])
                    //burada gidilebilecek yerlerin yolla ayni degerde olup olmadigina bakiliyor
                    {
                        giris_matris[konumY[i]][konumX[i]]=0; //gecmiste gidilen noktalara bir daha gitmemek icin 0'liyoruz matrisi onceden yazdirdigimizdan sikinti olmuyor ayrica yeni bir matris yaratmamiz gerekmiyor
                        konumX[i]+=hareket_yonleri[yon_num][0];//konumunuzu guncelliyoruz
                        konumY[i]+=hareket_yonleri[yon_num][1];
                        yol_len[i]++;//yol uzunlugunu yukseltiyoruz
                        var_yok=1;//while dongusune devam edilmesi icin
                        break;//break kullanilmasina izin veriliyor muydu bilmiyorum ama olmasa da oluyor sadece ekstra bir kondisyon daha eklememiz ve daha fazla iteration yapmak gerekiyor
                    }
                }
            }
        }
    }

    for(int i=0;i<yol_say; i++)
    {
        printf("Yol %d-> Uzunluk %d\n", yol_deger[i], yol_len[i]);//cikti (sira sayilarin degerine degil ustten asagiya gore)
    }
    return 0;
}