#define row_len 100

#include <stdio.h>

int main(int argc, char* argv[])
{
    int N;
    int M;
    int i, j;
    int matrix1[2][row_len];
    int matrix2[2][row_len];
    printf("Ilk matris uzunlugunu girin: ");
    scanf("%d", &N);
    for(i = 0; i < N; i++)
    {
        scanf("%d", *(matrix1)+i);
        for(j = 0; j < i; j++)
        {
            if(*(*(matrix1)+j) == *(*(matrix1)+i)){
                printf("Benzersizlik olmasi lazim, uygun deger gir. \n");
                i--;
            }
        }
    }
    for(i = 0; i < N; i++)
    {
        scanf("%d", *(matrix1+1)+i);
    }
    printf("Ikinci matris uzunlugunu girin: ");
    scanf("%d", &M);
    for(i = 0; i < M; i++)
    {
        scanf("%d", *(matrix2)+i);
        for(j = 0; j < i; j++)
        {
            if(*(*matrix2+j) == *(*matrix2+i)){
                printf("Benzersizlik olmasi lazim, uygun deger gir. \n");
                i--;
            }
        }
    }
    for(i = 0; i < M; i++)
    {
        scanf("%d", *(matrix2+1)+i);
    }
    printf("Ortak sayilar ve toplamlari:\n");
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
        {
            if (*(*matrix1 + i) == *(*matrix2 + j))
            {
                printf("%d -> %d + %d = %d\n", *(*matrix1 + i), *(*(matrix1+1) + i), *(*(matrix2+1)+j), *(*(matrix1 + 1) + i) + *(*(matrix2+1)+j));
            }
        }
    }
    return 0;
}