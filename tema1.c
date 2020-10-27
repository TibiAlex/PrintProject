//Buzera Tiberiu 323CA
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

static int write_stdout(const char *token, int length)
{
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

int iocla_printf(const char *format, ...)
{
	/* TODO */
    va_list args;
    char a[10000];
    int p = 0;

	va_start(args, format /* the first parameter */);

	for(int i = 0; i < strlen(format); i++) {
           int k = 0;
		       if(format[i] == '%' && format[i + 1] == 'd' && k == 0) {
                          int number = va_arg(args,int);
                          unsigned int n;

                          if (number < 0) {
                            n = -number;
                          } else {
                            n = number;
                          }
                          int d = 0;
                          if(number < 0) {
                              a[p++] = '-';
                            }
                          char inv[20];
                          while(n) { 
                             inv[d++] = n%10 + '0';
                             n = n/10;
                          }
                          for(int j = 0; j < d; j++) {
                               a[p++] = inv[d-j-1];
                          }
                          k = 1;
                          i++;
		      }
		      if(format[i] == '%' && format[i + 1] == 'c' && k == 0) {
		      	    a[p++] = va_arg(args, int);
                k = 1;
                i++;
		      }
		      if(format[i] == '%' && format[i + 1] == 's' && k == 0) {
		      	          char n[100];
		      	          strcpy(n, va_arg(args,char*));
		      	          for(int i = 0; i < strlen(n) ;i++) {
		      	          	    a[p++] = n[i];
		      	          }
                      k = 1;
                      i++;
		      }
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
              if(format[i] == '%' && format[i + 1] == 'x' && k == 0) {
                       unsigned int n = va_arg(args,unsigned int);
                       int v[100];
                       int inv = 0;
                       if(n < 0) {
                            n += 4294967166;
                       }
                       while(n) {
                       	   v[inv++] = n%16;
                       	   n /=16;
                       }
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
              if(format[i] == '\n' && k == 0) {
                      a[p++] = '\n';
                      k = 1;
              }
              if(format[i] == '\t' && k == 0) {
                      a[p++] = '\t';
                      k = 1;
              }

              if (format[i] == '%' && format[i + 1] == '%' && k == 0) {
                a[p++] = '%';
                k = 1;
                i++;
              }

              if(k==0) {
                   a[p++] = format[i];
                   k = 1;
              }
	}       
    return write_stdout((const char *)a, p);

	return -1;
}

// int main() {
// 	iocla_printf("%d\n\t%d\n\t\t%u\n", 2147483647, -2147483648, 4294967295);
// }
