#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

double** A;
double** B;
double** C;
int row1, col1, row2, col2;

//Funciones seriales
void carga_mat();
void print_result();

//Funcion paralela
void *matmul(void* data);

int main(int argc, char* argv[]){
  row1 = atoi(argv[1]);
  col1= atoi(argv[2]);
  row2 = atoi(argv[3]);
  col2 = atoi(argv[4]);
  int i,j;
  int num_hilos = row1 * col2;
  if (col1 ==row2){
	   pthread_t tid[num_hilos];
	  long rank;

	   A = malloc(row1*sizeof(double*)); 
      		for(i=0;i<row1;i++)
        		A[i]=malloc(col1*sizeof(double));
	   B = malloc(row2*sizeof(double*)); 
      		for(i=0;i<row2;i++)
        	B[i]=malloc(col2*sizeof(double)); 
  
  	   C =  malloc(row1*sizeof(double*)); 
      		for(i=0;i<row1;i++)
        	C[i]=malloc(col2*sizeof(double));

	  //carga de matices
	  carga_mat();
	  
	  //Creación de threads
	  //int i,j;
	  rank = 0;
	  int data[2];
	  for (i = 0; i < row1; i++){
	  data[0]=i;
        	for (j = 0; j < col2; j++){
        	data[1]=j;
	     	pthread_create(&tid[rank], NULL,matmul , (void*) data);
	     	rank++;
	     }}

	  //Unión de threads
	  rank=0;
	  for (i = 0; i < row1; i++){
	  data[0]=i;
        	for (j = 0; j < col2; j++){
	      pthread_join(tid[rank], NULL);
	      printf("resultado del hilo %ld :%.0lf\n",rank,C[i][j]);
	      	      rank++;
	      }

	      }

	  //Impresión de resultado
	  print_result();

	  //Liberación de memoria
	  free(A);
	  free(B);
	  free(C);

	  // Fin de proceso padre
	  pthread_exit(NULL);
  }
  
 
  return 0;
}

//-------------------------------------------
// Función que va ejecutarse en cada thread
void *matmul(void* arg){

  int i,j,k;
  int *data = (int *) arg;
  int col = data[1];
  int row = data[0];
    for (int i = 0; i < col2; i++) {
    // Dentro recorremos las filas de la primera (A)
    for (int j = 0; j < row1; j++) {
        int suma = 0;
        // Y cada columna de la primera (A)
        for (int k = 0; k < col1; k++) {
            // Multiplicamos y sumamos resultado
            suma += A[j][k] * B[k][i];
        }
        // Lo acomodamos dentro del producto
        C[j][i] = suma;
    }
}
    
}
//--------------------------------------------
//aqui se cargan aleatoriamiente las matrices
void carga_mat(){
  int i,j;
  
 printf(" Primera matriz: \n");
  for(i = 0; i < row1; i++){
      for(j = 0; j < col1; j++){
       A[i][j]= rand() % 30;
       printf("%.0lf ",A[i][j]);
      }
       printf("\n");
   }

  printf("\n Segunda matriz \n");

  for(i = 0; i < row2; i++){
      for(j = 0; j < col2; j++){
         B[i][j]= rand() % 30;
         printf("%.0lf ",B[i][j]); 
       }
      printf("\n");
   }
   for(i = 0; i < row1; i++){
      for(j = 0; j < col2; j++){
         C[i][j]= 0;
       }
   }
}

void print_result(){
  int i,j;
  printf("\n Matriz resultado: \n");
  for(i = 0; i < row1; i++){
      for(j = 0; j < col2; j++){ 
         printf("%.0lf ",C[i][j]); 
       }
      printf("\n");
   }

}
