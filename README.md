# SoalShiftSISOP20_modul2_D10

## Soal1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:

    i. Detik: 0-59 atau * (any value)
    ii. Menit: 0-59 atau * (any value)
    iii. Jam: 0-23 atau * (any value)
    iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

## Soal2 (Belum Selesai)
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk
menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.

e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
     Catatan:
    - Tidak boleh memakai system().
    - Program utama harus ter-detach dari terminal
    Hint:
    - Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
      tertentu
    - Epoch Unix bisa didapatkan dari time()

### Permasalahan
Belum dapat menyelesaikan bagian (d) dan (e).

## Soal3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).

a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.

c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.

d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.

(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

### SOLUSI
Untuk source code dapat diihat dibawah ini:
```c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {
  pid_t child_id1, child_id2, child_id3, child_id4, child_id5, child_id6, child_id7, child_id8;
  int status;
  char ch[100];
  FILE *destination;
  struct stat check;

  child_id1 = fork();

  if (child_id1 == 0) {
    child_id2 = fork();
    if (child_id2 == 0) {
      child_id3 = fork();
      if (child_id3 == 0) {
        child_id4 = fork();
        if (child_id4 == 0) {
            char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/indomie", NULL};
            execv("/bin/mkdir", argv);
          }else {
            while ((wait(&status)) > 0);
            sleep(5);
            char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/sedaap", NULL};
            execv("/bin/mkdir", argv);
          }
        }else {
          while ((wait(&status)) > 0);
          char *argv[] = {"unzip", "jpg.zip", NULL};
          execv("/usr/bin/unzip", argv);
        }
      }else {
        while ((wait(&status)) > 0);
        sprintf(ch, "/home/dicki/Praktikum/Praktikum2/jpg");
        char *argv[] = {"mv", ch, "/home/dicki/modul2", NULL};
        execv("/bin/mv", argv);
      }  
    }else {
      while ((wait(&status)) > 0);
      chdir("/home/dicki/modul2/jpg/");
      struct dirent *de;
      DIR *dr = opendir(".");
      while ((de = readdir(dr)) != NULL){
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
          continue;
        child_id6 = fork();
        if (child_id6 == 0) {
          child_id7 = fork();
          if (child_id7 == 0) {
            child_id8 = fork();
            if (child_id8 == 0) {
              if (stat(de->d_name,&check) == 0){
                if (check.st_mode & S_IFDIR) {
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/indomie", NULL};
                  execv("/bin/mv", argv);
                }else {
                  while ((wait(&status)) > 0);
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/sedaap" , NULL};
                  execv("/bin/mv", argv);
                } 
              }
            }else {
                while ((wait(&status)) > 0);
                sprintf(ch, "/home/dicki/modul2/indomie/%s/coba1.txt", de->d_name);
                destination = fopen(ch, "w+");
                fclose(destination);
            }
          }else {
            while ((wait(&status)) > 0);
            sleep(3);
            sprintf(ch, "/home/dicki/modul2/indomie/%s/coba2.txt", de->d_name);
            destination = fopen(ch, "w+");
            fclose(destination);
          }
        }else {
          while ((wait(&status)) > 0);    
        }
      }
      close(dr);
    }
}
```

Pada bagian (a) diminta untuk membuat dua direktori di `/home/[USER]/modul2/` dengan 
nama `indomie` dan `sedaap`. Pertama dilakukan fork sebanyak empat kali untuk nantinya
digunakan pada proses selanjutnya. Pada child process ke-4, diproses pembuatan direktori
dengan nama direktori `indomie`, dan pada parent process ke-4, diproses pembuatan direktori
dengan nama direktori `sedaap` selang lima detik setekah pembuatan direktori `indomie`.
```c
child_id1 = fork();
  if (child_id1 == 0) {
    child_id2 = fork();
    if (child_id2 == 0) {
      child_id3 = fork();
      if (child_id3 == 0) {
        child_id4 = fork();
        if (child_id4 == 0) {
          // child_id5 = fork();
          // if (child_id5 == 0) {
            char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/indomie", NULL};
            execv("/bin/mkdir", argv);
          }else {
            while ((wait(&status)) > 0);
            sleep(5);
            char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/sedaap", NULL};
            execv("/bin/mkdir", argv);
          }
```

Pada bagian (b) diminta untuk meng-ekstrak file `jpg.zip` di direktori `/home/[USER]/modul2/`.
Pada parent proccess ke-3, dilakukan proses unzip terhadap file `jpg.zip`. Kemudian hasil
ekstrak akan dipindahkan ke direktori `/home/dicki/modul2/` pada parent process ke-2.
```c
}else {
          while ((wait(&status)) > 0);
          char *argv[] = {"unzip", "jpg.zip", NULL};
          execv("/usr/bin/unzip", argv);
        }
      }else {
        while ((wait(&status)) > 0);
        sprintf(ch, "/home/dicki/Praktikum/Praktikum2/jpg");
        char *argv[] = {"mv", ch, "/home/dicki/modul2", NULL};
        execv("/bin/mv", argv);
      }
```

Pada bagaian (c) diminta untuk memindahakn isi dari direktori `jpg` ke direktori `indomie`
dan `sedaap`, dimana semua file harus dipindahkan ke direktori `/home/[USER]/modul2/sedaap/`
dan semua direktori harus dipindahkan ke direktori `/home/[USER]/modul2/indomie/`. Pada parent
process pertama, akan dilakukan proses fork kembali untuk memproses direktori `jpg`.
Direktori `jpg` akan diakses dengan `opendir`, dan prosesnya akan terus berjalan selama
direktori tidak `NULL`. Karena direktori `.` dan `..` tidak termasuk, maka kita cek terlebih
dahulu. Pada child process `child_id8` dilakukan pengecekan untuk ekstensi dari file tersebut.
Jika itu direktori, maka nantinya akan dipindah ke direktori `indomie`. Jika bukan direktori,
maka akan dipindah ke direktori `sedaap`.
```c
}else {
      while ((wait(&status)) > 0);
      chdir("/home/dicki/modul2/jpg/");
      struct dirent *de;
      DIR *dr = opendir(".");
      while ((de = readdir(dr)) != NULL){
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
          continue;
        child_id6 = fork();
        if (child_id6 == 0) {
          child_id7 = fork();
          if (child_id7 == 0) {
            child_id8 = fork();
            if (child_id8 == 0) {
              if (stat(de->d_name,&check) == 0){
                if (check.st_mode & S_IFDIR) {
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/indomie", NULL};
                  execv("/bin/mv", argv);
                }else {
                  while ((wait(&status)) > 0);
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/sedaap" , NULL};
                  execv("/bin/mv", argv);
                } 
              }
```

Pada bagian (d), diminta untuk mengisi setiap direktori yang dipindahkan ke direktori
`indomie` dengan file kosong, yaitu `coba1.txt` dan `coba2.txt`. Dimana syaratnya `coba2.txt`
akan dibuat setelah tiga detik berselang setelah dibuatnya `coba1.txt`.
```c
            }else {
                while ((wait(&status)) > 0);
                sprintf(ch, "/home/dicki/modul2/indomie/%s/coba1.txt", de->d_name);
                destination = fopen(ch, "w+");
                fclose(destination);
            }
          }else {
            while ((wait(&status)) > 0);
            sleep(3);
            sprintf(ch, "/home/dicki/modul2/indomie/%s/coba2.txt", de->d_name);
            destination = fopen(ch, "w+");
            fclose(destination);
          }
        }else {
          while ((wait(&status)) > 0);    
        }
      }
      close(dr);
    }
}
```
