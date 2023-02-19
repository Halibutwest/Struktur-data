#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nama[30], alamat[30], agama[10], pekerjaan[20], NIK[20], TTL[40];
} Data;

void save_to_file(Data* m, int n) {
    char filename[50];
    FILE *fp;

    printf("Masukkan nama file untuk disimpan (tanpa (.bin)): ");
    fgets(filename, 50, stdin);
    strtok(filename, "\n"); // membersihkan karakter newline di dalam buffer stdin
    strcat(filename, ".bin"); // menambahkan ekstensi .bin pada nama file

    fp = fopen(filename, "wb");
    if (fp != NULL) {
        fwrite(m, sizeof(Data), n, fp);
        fclose(fp);
        printf("Data berhasil disimpan di file %s.\n", filename);
    } else {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }
}

void read_from_file(char *filename, Data* m, int n) {
    FILE *fp;

    fp = fopen(filename, "rb");
    if (fp != NULL) {
        fread(m, sizeof(Data), n, fp);
        fclose(fp);
    } else {
        printf("Gagal membuka file %s.\n", filename);
        return;
    }
}

// Deklarasi variabel global
Data m[100];
int jumlahData = 0;

int Menu() {
    int IO;
    printf("--------------------\n");
    printf("-----Menu Utama-----\n");
    printf("--------------------\n");
    printf("1. Entri KTP\n");
    printf("2. Lihat KTP\n");
    printf("0. Keluar\n");
    printf("Silahkan Anda Memilih.. ");
    scanf("%d", &IO);
    getchar(); // membersihkan karakter newline di dalam buffer stdin
    printf("\n");
    return IO;
}

void EntriKTP() {
    int i;
    printf("Jumlah KTP yang akan diinput: ");
    scanf("%d", &jumlahData);
    getchar(); // membersihkan karakter newline di dalam buffer stdin

    for (i = 0; i < jumlahData; i++) {
        printf("Nama Lengkap: ");
        fgets(m[i].nama, 30, stdin);
        printf("Tempat & Tanggal Lahir(dd-mm-yy): ");
        fgets(m[i].TTL, 40, stdin);
        printf("Alamat: ");
        fgets(m[i].alamat, 30, stdin);
        printf("Agama: ");
        fgets(m[i].agama, 10, stdin);
        printf("Pekerjaan: ");
        fgets(m[i].pekerjaan, 20, stdin);
        printf("NIK: ");
        fgets(m[i].NIK, 20, stdin);
    }
    save_to_file(m, jumlahData);
}

void LihatKTP() {
    int i, j, k;
    char filename[50];
    Data temp;

    printf("Masukkan nama file untuk dibaca (tanpa (.bin)): ");
    fgets(filename, 50, stdin);
    strtok(filename, "\n"); // membersihkan karakter newline di dalam buffer stdin
    strcat(filename, ".bin"); // menambahkan ekstensi .bin pada nama file

    read_from_file(filename, m, 100);

    // Sorting data berdasarkan nama dengan insertion sort
    for (i = 1; i < jumlahData; i++) {
        temp = m[i];
        j = i - 1;
        while (j >= 0 && strcmp(m[j].nama, temp.nama) > 0) {
            m[j + 1] = m[j];
            j--;
        }
        m[j + 1] = temp;
    }

    printf("\n");

    char keyword[30];
    printf("Masukkan keyword nama: ");
    fgets(keyword, 30, stdin);
    strtok(keyword, "\n"); // membersihkan karakter newline di dalam buffer stdin

    printf("Berikut Data Yang Telah Tersimpan:\n\n");
    printf("Sorting data berdasarkan nama:\n");

    int count = 0;
    for (i = 0; i < jumlahData; i++) {
        if (strstr(m[i].nama, keyword) != NULL) {
            printf("Data KTP ke-%d:\n", ++count);
            printf("Nama Lengkap : %s", m[i].nama);
            printf("Tempat & Tanggal Lahir : %s", m[i].TTL);
            printf("Alamat : %s", m[i].alamat);
            printf("Agama : %s", m[i].agama);
            printf("Pekerjaan : %s", m[i].pekerjaan);
            printf("NIK : %s", m[i].NIK);
        }
    }
}
int main() {
    int IO;
    do{
    IO = Menu();
    switch(IO){
    case 1:
        EntriKTP();
        break;
    case 2:
        LihatKTP();
        break;
    case 0:
        printf("Program Selesai\n");
        exit(0);

    default:
        printf("Input Tidak Valid, Mohon Masukan Input lagi\n");
        break;
        }
    }while(IO != 0);
    return 0;
}
