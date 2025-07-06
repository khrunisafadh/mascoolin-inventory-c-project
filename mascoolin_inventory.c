#include <stdio.h>
#include <string.h>
#define MAX 500

struct Barang {
    char namabarang[MAX];
    int stockunit;
};

void tambah() {
    int pilihan;
    do {
        //Menu Tambah Barang
        printf("\nTambah Barang dan Stok\n");
        printf("===================================\n");
        printf("1> Buat daftar baru\n");
        printf("2> Tambah ke daftar yang sudah ada\n");
        printf("3> Kembali\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
        printf("\n");

        switch (pilihan) {
            //Menu 1: Buat daftar baru
            case 1: {
                //Pengguna meng-input jumlah jenis barang yang akan di-input
                int n;
                printf("\nBuat daftar baru\n");
                printf("===================================\n");
                printf("Masukkan jumlah jenis barang yang akan di-input: ");
                scanf("%d", &n);
                struct Barang info[n];

                getchar();

                //Pengguna meng-input nama barang & stok
                int i;
                for (i = 0; i < n; i++) {
                    printf("Masukkan nama barang %d: ", i + 1);
                    fgets(info[i].namabarang, sizeof(info[i].namabarang), stdin);
                    info[i].namabarang[strcspn(info[i].namabarang, "\n")] = 0;
                    printf("Masukkan stok barang %d: ", i + 1);
                    scanf("%d", &info[i].stockunit);
                    getchar();
                }

                //Menulis input dari console ke dalam berkas
                FILE *file;
                file = fopen("daftarbarang.txt", "w");
                if (file == NULL) {
                    printf("Gagal membuka berkas.");
                } else {
                    for (i = 0; i < n; i++) {
                        fprintf(file, "%s %d\n", info[i].namabarang, info[i].stockunit);
                    }
                    fclose(file);

                    //Indikator berhasil
                    printf("Data berhasil disimpan!\n\n");
                }
            }
            break;

            //Menu 2: Tambah ke daftar yang sudah ada
            case 2: {
            	struct Barang info[MAX];
                char data[MAX];
                FILE *file;
                
                printf("\nTambah ke daftar yang sudah ada\n");
                printf("===================================\n");
                
                //Menampilkan daftar yang sudah ada
                file = fopen("daftarbarang.txt", "r");
                if (file == NULL) {
        		printf("Gagal membuka berkas.");
    			} else {
        		int count = 0;
        		int a = 1;
        		printf("Daftar Penyimpanan Barang & Stok Mascoolin\n");
        		while (fgets(data, sizeof(data), file) != NULL && count < MAX) {
				printf("%d) ", a);
        		sscanf(data, "%s %d", info[count].namabarang, &info[count].stockunit);
        		printf("%s %d\n", info[count].namabarang, info[count].stockunit);
        		a++;
        		count++;
        		}
        		fclose(file);

                //Pengguna meng-input jumlah jenis barang yang akan di-input
                int n;
                printf("Masukkan jumlah jenis barang yang akan di-input: ");
                scanf("%d", &n);
                struct Barang newItem[n];
                getchar();

                //Pengguna meng-input nama barang & stok
                int i;
                for (i = 0; i < n; i++) {
                    printf("Masukkan nama barang %d: ", i + 1);
                    fgets(newItem[i].namabarang, sizeof(newItem[i].namabarang), stdin);
                    newItem[i].namabarang[strcspn(newItem[i].namabarang, "\n")] = 0;
                    printf("Masukkan stok barang %d: ", i + 1);
                    scanf("%d", &newItem[i].stockunit);
                    getchar();
                }

                ////Menulis input dari console ke dalam berkas (append)
                file = fopen("daftarbarang.txt", "a");
                if (file == NULL) {
                    printf("Gagal membuka berkas.");
                } else {
                    for (i = 0; i < n; i++) {
                        fprintf(file, "%s %d\n", newItem[i].namabarang, newItem[i].stockunit);
                    }
                    fclose(file);

                    //Indikator berhasil
                    printf("Data berhasil ditambahkan!\n\n");
                }
                return;
            }
            break;

            //Menu 3: Kembali ke menu
            case 3:
                printf("Kembali\n\n");
                break;

            //Pilihan lainnya
            default:
                printf("Pilihan tidak valid.\n");
                break;
        }
    } 
} while (pilihan != 3);
}

void masuk(){
		struct Barang info[MAX];
    char data[MAX];
    FILE *file;

	printf("\nStok Masuk\n");
	printf("===================================\n");
	//Menampilkan daftar yang sudah ada
    file = fopen("daftarbarang.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka berkas.");
    } else {
        int count = 0;
        int a = 1;
        printf("Daftar Penyimpanan Barang & Stok Mascoolin\n");
        while (fgets(data, sizeof(data), file) != NULL && count < MAX) {
				printf("%d) ", a);
        sscanf(data, "%s %d", info[count].namabarang, &info[count].stockunit);
        printf("%s %d\n", info[count].namabarang, info[count].stockunit);
        a++;
        count++;
        }
        fclose(file);

				//Pengguna meng-input nomor baris barang dengan stok yang ingin ditambahkan
        int lineNumber;
        printf("Masukkan nomor baris barang yang stoknya ingin ditambahkan: ");
        scanf("%d", &lineNumber);

				//Mengecek nomor baris
        if (lineNumber <= 0 || lineNumber > count) {
            printf("Nomor baris tidak valid.\n");
        }

				//Menampilkan barang yang dipilih untuk memastikan bahwa pilihan sudah benar
        printf("Barang yang dipilih: %s\n", info[lineNumber - 1].namabarang);

				//Pengguna meng-input jumlah stok yang ingin ditambahkan
        printf("Masukkan jumlah stok masuk: ");
        int addstock;
        scanf("%d", &addstock);

				//Program menambahkan stok masuk ke dalam stok yang sudah ada
        info[lineNumber - 1].stockunit += addstock;

				//Menuliskan hasil penjumlahan stok ke dalam berkas
        file = fopen("daftarbarang.txt", "w");
        if (file == NULL) {
            printf("Gagal membuka berkas.");
        }
				int i;
        for ( i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", info[i].namabarang, info[i].stockunit);
        }

        fclose(file);
				
				//Indikator berhasil
				printf("Data berhasil disimpan!\n\n");
    }
}

void keluar(){
		struct Barang info[MAX];
    char data[MAX];
    FILE *file;
    
    printf("\nStok Keluar\n");
	printf("===================================\n");
		//Menampilkan daftar yang sudah ada
    file = fopen("daftarbarang.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka berkas.");
    } else {
        int count = 0;
        int a = 1;
        printf("Daftar Penyimpanan Barang & Stok Mascoolin\n");
        while (fgets(data, sizeof(data), file) != NULL && count < MAX) {
						printf("%d) ", a);
            sscanf(data, "%s %d", info[count].namabarang, &info[count].stockunit);
            printf("%s %d\n", info[count].namabarang, info[count].stockunit);
            a++;
            count++;
        }
        fclose(file);

				//Pengguna meng-input nomor baris barang dengan stok yang ingin dikurangkan
        int lineNumber;
        printf("Masukkan nomor baris barang yang stoknya ingin dikurangkan: ");
        scanf("%d", &lineNumber);

				//Mengecek nomor baris
        if (lineNumber <= 0 || lineNumber > count) {
            printf("Nomor baris tidak valid.\n");
        }

				//Menampilkan barang yang dipilih untuk memastikan bahwa pilihan sudah benar
        printf("Barang yang dipilih: %s\n", info[lineNumber - 1].namabarang);

				//Pengguna meng-input jumlah stok yang ingin dikurangkan
        printf("Masukkan stok keluar: ");
        int stock_Out;
        scanf("%d", &stock_Out);

				//Program mengurangkan stok masuk ke dalam stok yang sudah ada
        info[lineNumber - 1].stockunit -= stock_Out;

				//Menuliskan hasil penjumlahan stok ke dalam berkas
        file = fopen("daftarbarang.txt", "w");
        if (file == NULL) {
            printf("Gagal membuka berkas.");
        }
		int i;
        for ( i = 0; i < count; i++) {
            fprintf(file, "%s %d\n", info[i].namabarang, info[i].stockunit);
        }

        fclose(file);

				//Indikator berhasil
				printf("Data berhasil disimpan!\n\n");
    }
}

void hapus(){
	FILE *file, *tempFile;

	printf("\nHapus Barang dan Stok\n");
	printf("===================================\n");
	//Menampilkan daftar yang sudah ada
  	char data[MAX];
	file = fopen("daftarbarang.txt", "r");
    	if (file == NULL) {
        printf("Gagal membuka berkas.");
    	}else {
    	printf("Daftar Penyimpanan Barang dan Stok Toko Es Krim Mascoolin\n");
    	int a=1;
	while(fgets(data, sizeof(data), file) != NULL){
	printf("%d) ", a);
        printf("%s", data);
        a++;
	}
	}
	fclose(file);
			
  char filename[]="daftarbarang.txt";
  char tempFilename[]="temp.txt";
  char line[MAX];
  int lineNumber;

	//Pengguna meng-input nomor baris data yang ingin dihapus
  printf("Masukkan nomor baris data yang ingin dihapus: ");
  scanf("%d", &lineNumber);

	//Membuka file asli untuk mode baca
  file = fopen(filename, "r");
  if(file==NULL){
    printf("Gagal membuka berkas.\n");
    return;
  }

	//Membuka file sementara untuk mode tulis
  tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Gagal membuat berkas sementara.\n");
        fclose(file);
        return ;
    }

	//Menyalin semua baris record dari file asli ke file sementara kecuali nomor baris yang dipilih oleh pengguna
  int currentLine=1;
  while (fgets(line, sizeof(line), file)!=NULL){
    if(currentLine!=lineNumber){
        fputs(line, tempFile);
    }
    currentLine++;
  }

  fclose(file);
  fclose(tempFile);

	//Menghapus file asli dan mengganti nama file sementara menjadi file asli
  remove(filename);
  rename(tempFilename, filename);

	//Indikator berhasil
  printf("Data berhasil dihapus!\n\n");
}

void informasi(){
int pilihan;
    do {
        printf("\nInformasi Barang dan Stok\n");
        printf("1> Lihat informasi daftar barang dan stok\n");
        printf("2> Cari barang dan stok\n");
        printf("3> Kembali\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihan);
		printf("\n");
		
        switch (pilihan) {
            case 1: {
            struct Barang info[MAX];
			char data[MAX];
    			FILE *file;
    			
    			printf("\nInformasi daftar barang dan stok\n");
				printf("===================================\n");
    			file = fopen("daftarbarang.txt", "r");
    			if (file == NULL) {
        		printf("Gagal membuka berkas.");
    			} else {
        		int count = 0;
        		int a = 1;
        		printf("Daftar Penyimpanan Barang dan Stok Toko Es Krim Mascoolin\n");
        		while (fgets(data, sizeof(data), file) != NULL && count < MAX) {
				printf("%d) ", a);
            	sscanf(data, "%s %d", info[count].namabarang, &info[count].stockunit);
            	printf("%s %d\n", info[count].namabarang, info[count].stockunit);
            	a++;
            	count++;
        		}
        		printf("\n");
        	fclose(file);
			}
			} break;

				case 2: {
    			printf("\nCari barang dan stok\n");
    			printf("===================================\n");
    			char cari[MAX];
    			printf("Masukkan nama barang yang ingin dicari: ");
    			scanf("%s", cari);

    			FILE *file = fopen("daftarbarang.txt", "r");
    			if (file == NULL) {
        		printf("Gagal membuka berkas.");
    			} else {
        		int count = 0;
        		int hasil = 0;
        		struct Barang info;

        		while (fscanf(file, "%s %d", info.namabarang, &info.stockunit) != EOF) {
            	count++;
            	if (strcmp(info.namabarang, cari) == 0) {
                printf("Barang ditemukan pada nomor baris %d.\n", count);
                printf("%s %d\n", info.namabarang, info.stockunit);
                hasil = 1;
                break;
            }
        }

        if (!hasil) {
            printf("Barang tidak ditemukan.\n");
        }
        fclose(file);
    }
    break;
}
 break;
			
			case 3: printf("Kembali\n\n");; break;
			
			default: printf("Pilihan tidak valid.\n"); break;
		}
	} while (pilihan !=3);
}

int main() {	
    //Login akun
		char username[10] = "mascoolin";
    char password[8] = "123456";
    char inputusername[10], inputpassword[10];
    
    //Login interface
    printf("Masukkan username: ");
    scanf("%s", inputusername);
    printf("Masukkan password: ");
    scanf("%s", inputpassword);
    printf("\n");

	
    if (strcmp(inputusername, username) == 0 && strcmp(inputpassword, password) == 0){
	    int nav;
		do{
			printf("\nSelamat datang di Database MasCoolin'\n");
		    printf("===================================\n");
		    printf("1> Masuk\n");
		    printf("2> Keluar\n");
		    printf("Masukkan pilihan: ");
		    scanf("%d", &nav);
		    printf("\n");
			
			switch(nav){
				case 1: {
					int pilihan;
					do{
            //Main menu interface
						printf("\nMenu\n");
						printf("===================================\n");
		        		printf("1> Manajemen Barang dan Stok\n");
		        		printf("2> Informasi Barang dan Stok\n");
		        		printf("3> Kembali ke Menu Utama\n");
		        		printf("Masukkan pilihan: ");
		        		scanf("%d", &pilihan);
		        		printf("\n");
		
						switch(pilihan){
							case 1:{
								int pil_brg;
                //Menu manajemen barang dan stok
		                		printf("\nManajemen Barang dan Stok\n");
		                		printf("===================================\n");
								printf("1> Tambah Barang dan Stok\n");
								printf("2> Stok Masuk\n");
								printf("3> Stok Keluar\n");
								printf("4> Hapus Barang dan Stok\n");
								printf("5> Kembali\n");
		                		printf("Masukkan pilihan: ");
		                		scanf("%d", &pil_brg);
		                		printf("\n");
		                		
                //Masuk ke menu tambah barang dan stok
								if(pil_brg==1){
									tambah();
								}
                //Masuk ke fungsi stok masuk
                else if(pil_brg==2){
									masuk();
								}
                //Masuk ke fungsi stok keluar
								else if(pil_brg==3){
									keluar();
								}
                //Masuk ke fungsi hapus barang dan stok
								else if(pil_brg==4){
									hapus();
								}
                //Kembali ke menu
								else if(pil_brg==5){
									printf("Kembali\n\n");;
								}
								else printf("Pilihan tidak valid.");
							} break;

              //Masuk ke menu informasi barang dan stok
							case 2:{
								informasi(); 
							} break;

              //Kembali ke main menu
							case 3:{
                printf("Kembali\n\n");;
							} break;
							
							default:{
								printf("Pilihan tidak valid\n.");
							} break;
						}	
					} while (pilihan!=3); 
					break;

        //Keluar dari program
				case 2:{
					printf("Anda telah keluar.\n");
				} break;
				
				default:{
					printf("Pilihan tidak valid.");
				} break;
		    }
		}
	} while (nav!=2);
	}
  //Pengguna salah input username dan/atau password
	else {
        printf("Akun salah!\n");
    }


return 0;
}

