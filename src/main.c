/* TUGAS BESAR: MEMBUAT QUIZ GAME TERKAIT SYNTAX DI BAHASA C */
/* 
 * Tasks:
 * 1) Membuat Interface Bagian Input Nama.
 * 2) Membuat Interface Menu.
 * 3) Menampilkan Manpage (basically help center) untuk panduan mengerjakan soal.
 * 4) Membuat Kumpulan Soal Terkait Syntax Dasar Bahasa C.
 * 5) Membuat Sistem Penilaian.
 * 6) Membuat Sistem Penginputan Jawaban.
 * 7) Membuat Tampilan UI Ketika Peserta Mendapatkan Nilai di Atas dan di Bawah KKM.
 */

// Preprocessor
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

#define NAME_LEN 256
#define QUESTION_LEN 1024

// Struct Declarations
typedef struct player {
  char nama[NAME_LEN];
  int skor;
} PlayerInfo;

typedef struct node {
  unsigned nomor;
  char teks[QUESTION_LEN];
} Question;

typedef struct linked_list {
  Question node;
  Question next;
} QuestionList;

// Functions Declaration
void start_program();
void show_menu();
void show_result();
unsigned randomize();
void start_quiz();
void open_help_book();
void show_question();
void insert_questions_into_list();

// LINKED LIST FOR QUESTIONS
QuestionList ENTRIES[10][sizeof(QuestionList)];

// Main Entry Point
int main(int argc, char** argv)
{
  start_program();
  return EXIT_SUCCESS;
}

// Functions Definition
void start_program()
{
  show_menu();
  insert_questions_into_list();
}

void show_menu()
{
  unsigned choice;
  int num_opt = 1;
  while (true)
  {
    printf("Selamat Datang Di Kuis Syntax Bahasa C!\n");
    printf("%d) Mulai Kuis\n", num_opt++);
    printf("%d) Buka Buku Panduan\n", num_opt++);
    printf("%d) Keluar\n", num_opt++);
    printf("Masukkan Pilihan: ");
    scanf("%u", &choice);
    fflush(stdin);

    switch (choice)
    {
      case 1:
        start_quiz();
        break;
      case 2:
        open_help_book();
        break;
      case 3:
        printf("Terimakasih Sudah Mengerjakan Kuis ini, Kami berharap Kuis yang kami berikan dapat bermanfaat bagi banyak orang");
        break;
      default:
        fprintf(stderr, "Input Tidak Dimengerti. Silahkan Coba Kembali!\n");
    }
  }
}

void show_result()
{

}

unsigned randomize()
{

}

void start_quiz()
{

}

void open_help_book()
{

}

void show_question()
{

}

void insert_questions_into_list()
{

}
