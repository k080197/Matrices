#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <math.h>

int m = 0, n = 0, z = 0;
float **matrix, kst;
FILE *fo;
int filei, filej;


int number(void)
{
	int i = 0, len = 3;
	char a;
	char* str;
	if ( (str = ( char* ) calloc(3, sizeof(char))) == 0)
	{
		printf("couldn't allocate memory for string");
		return 0;
	}
	while (1)
	{
		a = _getch();

		if (( i == 0 )&&( a == 48 ))
		{
			
			printf(" \b");
			*(str + i) = '\0';
			continue;
		}

		if ( i + 1 == len && a != 13)
		{
			len += 3;
			if ((str = (char*) realloc( str, len)) == 0)
			{
				free( str );
				printf("couldn't allocate memory for string");
				return 0;
			}
		}
 		if ( (a == 13) && (i > 0) )
		{
			if ((str = (char*) realloc(str, i + 1)) == 0)
			{
				printf("couldn't allocate memory for string");
			}
			else
			{
				*(str + i) = '\0';
				puts("");
				break;
			}
		}

		if ( (a == 8) && (i > 0) )
		{
			printf("\b \b");
			*(str + i) = '\0';
			i -= 1;
			continue;
		}

		if( (a >= 48) && (a <= 57) )
		{
			
		printf("%c",a);
		*(str + i) = a;
		i += 1;			
			
		}
	}
	i = atoi( str );
	free( str );
	return i;
}

int create(void)
{
	int i, j;
	float x;
	system("cls");
	if (m!=0 && n!= 0)
	{
		printf ("Файл создан. \n");
		fo = fopen("inputing.txt", "wt");
		srand(time(NULL));
		for(i = 0; i < n; i+=1)
		{
			for(j = 0; j < m; j+=1)
			{
				x = rand() % 10;
				fprintf(fo, "%.0f	", x);
			}
			fprintf(fo, "\n");
		}
		fclose(fo); 
		z = 2;
		//fo=fopen ("D:\\inputing.txt", "r");
	}
	else 
	{
	   printf("Вы не выбрали первый пункт.");
	}
	filei=n;
	filej=m;
	return 0;
}

int matoutp(float **matr)
{
	int i, j;
	for (i = 0; i < n; i+=1)
	{
		for (j = 0; j < m; j+=1)
		{
			printf("%2.0f	", matr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int matrix1(void)//day 1
{
	int i, j;
	system("cls");
    printf("Введите количество строк: ");
    n = number();
    printf("Введите количество столбцов: ");
    m = number();
	matrix = (float **)malloc(n * sizeof(float *));    //Выделение памяти двумерному массиву
	for (i = 0; i < n; i+=1)
		matrix[i] = (float *)malloc(m * sizeof(float));
	for (i = 0; i < n; i+=1)
	{
		for (j = 0; j < m; j+=1)
		{
			matrix[i][j] = 0;
			printf("%.0f ", matrix[i][j]);
		}
		printf("\n");
	} z = 1;
	return 0;
}

int open(void)
{
	int i, j, l = 0;
	//FILE *mf;
	if ((n<=filei)&&(m<=filej) && (filei!=0) && (filej!=0))
	{
	if (fo!=NULL)
	{
		
		printf ("Открытие файла: ");
		fo = fopen ("inputing.txt", "r");
		if (fo == NULL) 
		{
			printf ("ошибка\n"); return -1;
		}
		else 
		{
			printf ("выполнено.\n");
			printf ("Считаны строки:\n");
				for (i = 0; i < n; i+=1)
				{
					for (j = 0; j < m; j+=1)
					{
						if (!fscanf(fo,"%f	", &matrix[i][j]))
						{
							printf("\nФайл поврежден, выполните второй пункт. \n"); l = 1; break;
						}
						//fscanf(fo,"%f	", &matrix[i][j]);
						printf("%.0f	", matrix[i][j]);
					}
					if (l==1) break;
					fscanf(fo, "\n"); printf("\n");
				}
		
		}
		printf ("Закрытие файла: ");
	   if ( fclose (fo) == EOF) printf ("ошибка\n");
	   else printf ("выполнено\n");
		if (l==0) z = 3;
	}
	else
		printf("Вы не выполнили второй пункт.");
	}
	else printf("Вы не выполнили второй пункт.");
	return 0;
}

int matr(float **mas, float **p, int i, int j, int l) {
  int xi, xj, di, dj;
  di=0;
  for(xi=0; xi < l - 1; xi++) 
  {
    if (xi == i)  di = 1;

    xj = 0;

    for(xj = 0; xj < l - 1; xj++) 
	{
      if (xj == j)  dj = 1;
      p[xi][xj] = mas[xi+di][xj+dj];
    }
  }
  return 0;
}

long double determinant(float **mas, int l) 
{
	int i, j;
	long double d;
	float k, z;
	float **buf;
	buf = (float **)malloc(l * sizeof(float *));    //Выделение памяти двумерному массиву
	for (i = 0; i < l; i+=1)
		buf[i] = (float *)malloc(l * sizeof(float));
	j = 0; 
	d = 0;
	k = 1;
	z = l - 1;
	if (l < 1)  printf("Определитель вычислить невозможно, матрицы нет.");
	if (l == 1) 
	{
		d = mas[0][0];
		return(d);
	}
	if (l == 2) 
	{
		d = (mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]));
		return(d);
	}
	if (l > 2)
	{
		for (i = 0; i < l; i++) 
		{
			matr(mas, buf, i, 0, l);
			d = d + (k * mas[i][0] * determinant(buf,z));
			k=-k;
		}
	}
	free(buf);
	return d;
}

int obratn(void)
{
	int i, j;
	long double q, **mat;
	system("cls");
	if ((((z == 3)|| z == 4) || z == 5) || z == 6)
	{
		if ((n > m)||(m > n))
		{
			printf("Обратной матрицы для данной не существует, так как она не является квадратной.\n");
		}
		else
		{
			printf("Прямая матрица: \n");
			matoutp(matrix);
			q = determinant(matrix, m);
			//printf("Определитель: %f\n",q);

			if (q!=0)
			{
				mat = (long double **)malloc(m * sizeof(long double *));    //Выделение памяти двумерному массиву
					for (i = 0; i < n; i+=1)
						mat[i] = (long double *)malloc(n * sizeof(long double));
				printf("Обратная матрица: \n");
				for (i = 0; i < n; i+=1)
				{
					for (j = 0; j < m; j+=1)
					{
						mat[i][j]=matrix[j][i];
						mat[i][j]/=q;
						printf("%.5Lf	", mat[i][j]); //A^-1 = A^t/|A|
					}
					printf("\n");
				}
				free(mat);
			}
			else printf("\nОпределитель матрицы равен нулю, обратной матрицы не существует.\n");
		}
		z = 4;
	}
	else printf("Вы не выполнили третий пункт.");
	return 0;
}

void inputreversal(void) 
{
	float temp, **reva, **rev;
	int i, j, k;
	system("CLS");
	if (matrix == 0) 
	{
		printf("Ошибка в чтении матрицы. Выполните третий пункт меню.");
	}
	else 
	{
		if (determinant(matrix, n) == 0 || n != m)
		printf("Обратной матрицы не существует.");
		else 
		{
			printf("Прямая матрица: \n");
			matoutp(matrix);
			printf("Обратная матрица: \n");
			reva = (float**)calloc(n, sizeof(float*));
			for (i = 0; i < n; i++)
				reva[i] = (float*)calloc(n, sizeof(float));
			rev = (float**)calloc(n, sizeof(float*));
			for (i = 0; i < n; i++)
				rev[i] = (float*)calloc(n, sizeof(float));

			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					rev[i][j] = matrix[i][j];
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
				{
					reva[i][j] = 0;

					if (i == j)
						reva[i][j] = 1;
				}

			for (k = 0; k < n; k++)
			{
				temp = rev[k][k];

				for (j = 0; j < n; j++)
				{
					rev[k][j] /= temp;
					reva[k][j] /= temp;
				}

				for (i = k + 1; i < n; i++)
				{
					temp = rev[i][k];

					for (j = 0; j < n; j++)
					{
						rev[i][j] -= rev[k][j] * temp;
						reva[i][j] -= reva[k][j] * temp;
					}
				}
			}

			for (k = n - 1; k > 0; k--)
			{
				for (i = k - 1; i >= 0; i--)
				{
					temp = rev[i][k];

					for (j = 0; j < n; j++)
					{
						rev[i][j] -= rev[k][j] * temp;
						reva[i][j] -= reva[k][j] * temp;
					}
				}
			}

			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					rev[i][j] = reva[i][j];
			for (i = 0; i<n; i++)
			{
				for (j = 0; j<n; j++)
					printf("%.2f	", rev[i][j]);
				printf("\n");
			}
			for (i = 0; i < n; i++)
				free(reva[i]);
			free(reva);
			for (i = 0; i < n; i++)
				free(rev[i]);
			free(rev);
			printf("\n");
		}
	}
}

int transp(void)
{
	int i, j;
	float **a = NULL;
	a = (float **)malloc(m* sizeof(float *));    //Выделение памяти двумерному массиву
	for (i = 0; i < m; i+=1)
		a[i] = (float *)malloc(n* sizeof(float));
	system("cls");
	if ((((z == 3)|| z == 4) || z == 5) || z == 6)
	{
		printf("Прямая матрица: \n");
		matoutp(matrix);
		printf("Транспонированная матрица: \n");
			for (i = 0; i < m; i+=1)
				{
					for (j = 0; j < n; j+=1)
					{
						a[i][j] = matrix[j][i];
						printf("%.0f ", a[i][j]);
					}
					printf("\n\n");
				}
		z = 5;
	}
	else printf("Вы не выполнили третий пункт.");
	free(a);
	return 0;
}

int opred(void)
{
	int i;
	long double q, **mat;
	system("cls");
	if ((n > m)||(m > n))
	{
		printf("Определителя для данной матрицы не существует, так как она не является квадратной.\n");
	}
	else
	{
		if ((((z == 3)|| z == 4) || z == 5) || z == 6)
		{
			mat = (long double **)malloc(m * sizeof(long double *));    //Выделение памяти двумерному массиву
				for (i = 0; i < n; i+=1)
					mat[i] = (long double *)malloc(n * sizeof(long double));
			printf("Прямая матрица: \n");
			matoutp(matrix);
			q = determinant(matrix, m);
			printf("Определитель: %.3Lf\n",q);
			z = 6;
			free(mat);
		}
		else printf("Вы не выполнили третий пункт.");
	}
	return 0;
}

int choose(void)

{
	char r;
	while(1)
	{	
		do{
			system("cls");
			printf("		______________________________________________________________\n\
		|   Выбирете пункт меню:                                     |\n\
		| 1)	Создание матрицы.                                    |\n\
		| 2)	Заполнение файла inputdig.txt случайными числами.    |\n\
		| 3)	Заполнение матрицы.                                  |\n\
		| 4)	Нахождение обратной матрицы.                         |\n\
		| 5)	Нахождение транспонированной матрицы.                |\n\
		| 6)	Нахождение определителя матрицы.                     |\n\
		| 7)	Выход из программы.                                  |\n\
		______________________________________________________________\n\
		\n\
		Введите номер действия: ");
			r = _getch();
			switch(r)
			{
				case '1':system("cls"); matrix1();  break;
				case '2':system("cls"); create();  break;
				case '3':system("cls"); open();  break;
				case '4':system("cls"); inputreversal(); break;//obratn(); break;
				case '5':system("cls"); transp(); break;
				case '6':system("cls"); opred(); break;
				case '7':system("cls"); exit(0); break;
			}
		} while((_getch()!=' ')||_getch()!='\n');
	}
	return 0;
}

int main(void)
{
	setlocale(LC_ALL,"");
	system("color F9");
	choose();
	free(matrix);
}
