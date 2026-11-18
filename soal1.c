// Nama: Faiz Azmi Irwan
// NIM: 13224040
// Kode: Pesta Besar (BFS) --> dipilih BFS karena kita harus mencari jumlah minimum langkah
// Program memperoleh nilai target dengan mengosongkan gelas, mengisi penuh gelas, dan menuangkan isi gelas dari satu ke lainnya

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define N 3

int hasilMin(int x, int y, int z) {
    //dalam memastikan bahwa operasi memungkinkan, harus x < z < y atau y < z < x, maka
    if (x > y) {
        if (z > x) {
            return -1;
        }
    } else {
        if (z > y) {
            return -1;
        }
    }


    //queue u/ BFS
    int q[10000][3], depan = 0, belakang = 0;

    //kondisi ketika melalui kemungkinan yang sudah pernah
    bool pernah[x + 1][y + 1];
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            pernah[i][j] = false;
        }
    } 

    //kondisi awal BFS
    q[belakang][0] = 0;
    q[belakang][1] = 0;
    q[belakang][2] = 0;
    belakang++;
    pernah[0][0] = true;

    while (depan != belakang) { //apabila seluruh kemungkinan belum dipenuhi

        //mengambil nilai paling depan (FIFO)
        int gelas1 = q[depan][0];
        int gelas2 = q[depan][1];
        int langkah = q[depan][2];
        depan++;

        if (gelas1 == z || gelas2 == z){ //jika salah satu nilai gelas memenuhi, akan dikembalikan langkah minimum
            return langkah;
        }

        //Kemungkinan 1: Mengisi gelas 1 hingga penuh
        if(!pernah[x][gelas2]) {
            pernah[x][gelas2] = true;
            q[belakang][0] = x;
            q[belakang][1] = gelas2;
            q[belakang][2] = langkah + 1;
            belakang++;
        }

        //Kemungkinan 2: Mengisi gelas 2 hingga penuh
        if(!pernah[gelas1][y]) {
            pernah[gelas1][y] = true;
            q[belakang][0] = gelas1;
            q[belakang][1] = y;
            q[belakang][2] = langkah + 1;
            belakang++;
        }

        //Kemungkinan 3: Mengosongkan gelas 1
        if(!pernah[0][gelas2]) {
            pernah[0][gelas2] = true;
            q[belakang][0] = 0;
            q[belakang][1] = gelas2;
            q[belakang][2] = langkah + 1;
            belakang++;
        }

        //Kemungkinan 4: Mengosongkan gelas 2
        if(!pernah[gelas1][0]) {
            pernah[gelas1][0] = true;
            q[belakang][0] = gelas1;
            q[belakang][1] = 0;
            q[belakang][2] = langkah + 1;
            belakang++;
        }
        
        int selisih1ke2, selisih2ke1;
        //Kemungkinan 5: Menuangkan gelas 1 ke gelas 2
        if (gelas1 < (y - gelas2)) {
            selisih1ke2 = gelas1;
        } else {
            selisih1ke2 = y - gelas2;
        }
        if(!pernah[gelas1 - selisih1ke2][gelas2 + selisih1ke2]) {
            pernah[gelas1 - selisih1ke2][gelas2 + selisih1ke2] = true;
            q[belakang][0] = gelas1 - selisih1ke2;
            q[belakang][1] = gelas2 + selisih1ke2;
            q[belakang][2] = langkah + 1;
            belakang++;

        }

        //Kemungkinan 6: Menuangkan gelas 2 ke gelas 1
        if (gelas2 < (x - gelas1)) {
            selisih2ke1 = gelas2;
        } else {
            selisih2ke1 = x - gelas1;
        }
        if(!pernah[gelas1 + selisih2ke1][gelas2 - selisih2ke1]) {
            pernah[gelas1 + selisih2ke1][gelas2 - selisih2ke1] = true;
            q[belakang][0] = gelas1 + selisih2ke1;
            q[belakang][1] = gelas2 - selisih2ke1;
            q[belakang][2] = langkah + 1;
            belakang++;

        }
    }
    return -1;
}


int main() {
    int i, gelas[N];

    for (i = 0; i < N; i++) {
        if (scanf("%d", &gelas[i]) != 1) {
            printf("Input tidak valid\n");
            return 1;
        }
    }

    int a = gelas[0];
    int b = gelas[1];
    int c = gelas[2];

    int hasil = hasilMin(a, b, c);
    printf("%d\n", hasil);
    return 0;
}
