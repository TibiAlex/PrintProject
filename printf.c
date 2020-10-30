//Buzera Tiberiu 323CA
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

//functia ce afisaza la stdout formatul introdus
static int write_stdout(const char *token, int length) {
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//functia in care se verifica fiecare caracter al sirului format
//functie cu numar necunoscut de parametrii
int iocla_printf(const char *format, ...) {
	/* TODO */
	//declaram args de tipul va_list in care vom memora pe rand parametrii functiei
    va_list args;
    //un sir de caractere a in care vom construi sirul de caractere ce trebuie afisat
    char a[10000];
    //numarul de caractere din sirul a
    int p = 0;

	va_start(args, format /* the first parameter */);

    //parcurgem sirul format si incercam sa gasim caracterul %
	for(int i = 0; i < strlen(format); i++) {
		   //o variabila pe care o folosesc sa verific daca 
		   //s-a adaugat ceva la acest pas in sirul a
           int k = 0;
           //verificam daca gasim grupul %d caz in care 
           //retinem intr-o variabila number parametrul uemator din va_args
		   if(format[i] == '%' && format[i + 1] == 'd' && k == 0) {
                    int number = va_arg(args,int);
                    //pentru numere foarte mari retinem valoarea intr-un unsigned int
                    unsigned int n;
                    if (number < 0) {
                        n = -number;
                        } else {
                        n = number;
                    }
                    int d = 0;
                    //afisam minusul daca numarul este negativ
                    if(number < 0) {
                        a[p++] = '-';
                    }
                    //construim un sir de caractere din unsigned int 
                    //pentru a fi mai usor de procesat caracter cu caracter
                    char inv[20];
                    while(n) { 
                        inv[d++] = n%10 + '0';
                        n = n/10;
                    }
                    //punem caracterele in sirul a
                    for(int j = 0; j < d; j++) {
                        a[p++] = inv[d-j-1];
                    }
                    //k devine 1 intrucat a s-a schimbat la pasul acesta
                    k = 1;
                    //incrementam i deoarece am prelucrat in acest if gruparea %d, nu doar un caracter
                    i++;
		    }
		    //verificam daca gasim grupul %c si adaugam urmatorul parametru in sir
		    if(format[i] == '%' && format[i + 1] == 'c' && k == 0) {
		      	    a[p++] = va_arg(args, int);
                    k = 1;
                    i++;
		    }
		    //verificam daca gasim grupul %s
		    if(format[i] == '%' && format[i + 1] == 's' && k == 0) {
		    	    //cream un nou sir in care copiem parametrul urmator
		    	    //si il punem caracter cu caracter in sirul a
		      	    char n[100];
		      	    strcpy(n, va_arg(args,char*));
		      	    for(int i = 0; i < strlen(n) ;i++) {
		      	        a[p++] = n[i];
		      	    }
                    k = 1;
                    i++;
		    }
		    //verificam daca gasim grupul %u
		    if(format[i] == '%' && format[i + 1] == 'u' && k == 0) {
		      	    unsigned int n = va_arg(args,unsigned int);
                    int d = 0;
                    char inv[20];
                    while(n) { 
                        inv[d++] = n%10 + '0';
                        n /= 10;
                    }
                    for(int j = 0; j < d; j++) {
                        a[p++] = inv[d-j-1];
                    }
                    k = 1;
                    i++;
		    }
		    //verificam daca gasim grupul %x
            if(format[i] == '%' && format[i + 1] == 'x' && k == 0) {
                    unsigned int n = va_arg(args,unsigned int);
                    int v[100];
                    int inv = 0;
                    //verificam daca numarul este negativ
                    if(n < 0) {
                        n += 4294967166;
                    }
                    //il impartim la 16 pana nu se mai poate
                    //si formam un vector cu toate resturile
                    while(n) {
                       	v[inv++] = n%16;
                       	n /=16;
                    }
                    //punem resturile in sirul a, verificand daca sunt 
                    //mai mai decat 10 pentru a pune litere unde este necesar
                    for(int j = 0; j < inv; j++) {
                        if(v[inv - j - 1] <= 9) {
                            a[p++] = v[inv - 1 -j] + '0';
                        }
                        if(v[inv -j -1] == 10) {
                            a[p++] = 'a';
                        }
                        if(v[inv - 1 -j] == 11) {
                            a[p++] = 'b';
                        }
                        if(v[inv - 1 -j] == 12) {
                            a[p++] = 'c';
                        }
                        if(v[inv - 1 -j] == 13) {
                            a[p++] = 'd';
                        }
                        if(v[inv - 1 -j] == 14) {
                            a[p++] = 'e';
                        }
                        if(v[inv - 1 -j] == 15) {
                            a[p++] = 'f';
                        }
                    }
                    k =1;
                    i++;
            }
            //verificam daca gasim grupul \n
            //si trecem pe randul urmator
            if(format[i] == '\n' && k == 0) {
                    a[p++] = '\n';
                    k = 1;
            }
            //verificam daca gasim grupul \t
            //si dam tab^^
            if(format[i] == '\t' && k == 0) {
                    a[p++] = '\t';
                    k = 1;
            }
            //verificam daca gasim grupul %%
            //caz in care ignoram primul %
            if (format[i] == '%' && format[i + 1] == '%' && k == 0) {
                    a[p++] = '%';
                    k = 1;
                    i++;
            }
            //in cazul in care s-a ajuns pana aici si k este inca 0
            //inseamna ca avem un caracter oarecare si il punem direct in sirul a
            if(k==0) {
                   a[p++] = format[i];
                   k = 1;
            }
	}      
	//apelam functia write_stdout cu parametrii sirul a si p numarul sau de caractere 
    return write_stdout((const char *)a, p);

	return -1;
}
