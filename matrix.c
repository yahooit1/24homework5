#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//행렬 구조체 정의
typedef struct{
    int **data; //2차원 행렬이므로 2차원 배열 포인터 사용
    int row;
    int col;
}Matrix;

//함수 선언
Matrix *create_matrix(int row, int col);
void free_matrix(Matrix *matrix);
void print_matrix(Matrix *matrix);
void fill_matrix(Matrix *matrix);
Matrix *addition_matrix(Matrix *matrix_a, Matrix *matrix_b);
Matrix *subtraction_matrix(Matrix *matrix_a, Matrix *matrix_b);
Matrix *transpose_matrix(Matrix *matrix);
Matrix *multiply_matrix(Matrix *matrix_a, Matrix *matrix_b);

int main(){

printf("[----- [Gahyun]  [2020045070] -----]\n");

int row,col;

//랜덤생성함수
srand(time(NULL));

//행, 열 입력받기
printf("Input row and col : ");
scanf("%d %d",&row,&col);

//matrix 생성
Matrix *matrix_a=create_matrix(row,col);
Matrix *matrix_b=create_matrix(row,col);

//matrix_a ,matrix_b 값 채우기
fill_matrix(matrix_a);
fill_matrix(matrix_b);

//출력
printf("Matrix A: \n");
print_matrix(matrix_a);
printf("Matirx B: \n");
print_matrix(matrix_b);

//matrix 연산
Matrix *matrix_sum=addition_matrix(matrix_a,matrix_b);
Matrix *matrix_sub=subtraction_matrix(matrix_a,matrix_b);
Matrix *matrix_transpose = transpose_matrix(matrix_a);
Matrix *matrix_product = multiply_matrix(matrix_a, matrix_b);

//출력
printf("Matrix A+B :\n");
print_matrix(matrix_sum);
printf("Matrix A - B:\n");
print_matrix(matrix_sub);
printf("Transpose of matrix A:\n");
print_matrix(matrix_transpose);
printf("Matrix A * B:\n");
print_matrix(matrix_product);

//할당된 메모리 해제
free_matrix(matrix_a);
free_matrix(matrix_b);
free_matrix(matrix_sum);
free_matrix(matrix_sub);
free_matrix(matrix_transpose);
free_matrix(matrix_product);

    return 0;
}

//matrix생성 함수 구현
Matrix *create_matrix(int row,int col){
    //Matrix 구조체에 대한 메모리 동적할당하기
   Matrix *matrix=(Matrix *)malloc(sizeof(Matrix)); //동적할당
   //행과 열의 크기 입력받은 걸로 설정하기
   matrix->row=row;
   matrix->col=col;

   //행렬 데이터를 저장할 2차원 배열에 대한 동적할당
   matrix->data=(int **)malloc(row*sizeof(int *));
   for(int i=0;i<row;i++){
    matrix->data[i]=(int *)malloc(col*sizeof(int));
   }
    
    return matrix;
}

//matrix 출력 함수 구현
void print_matrix(Matrix *matrix){
    //2차원 배열을 돌면서 출력하기
    for(int i = 0; i < matrix->row; i++){
        for(int j = 0; j < matrix->col; j++)
            printf("%d ", matrix->data[i][j]);
       printf("\n"); 
    }

    return;

}

//matrix 할당 해제 함수 구현
void free_matrix(Matrix *matrix){
    //각 행에 대한 메모리 할당 해제
    for(int i = 0; i < matrix->row; i++)
        free(matrix->data[i]);
    //배열의 메모리 할당 해제
    free(matrix->data);
    //행렬 구조체의 메모리 할당 해제
    free(matrix);
}

//matrix에 원소 채우는 함수 구현
void fill_matrix(Matrix *matrix){ //2차원 배열, 2중 for문 돌며 채우기
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            matrix->data[i][j] = rand() % 10; // 임의의 0에서 9 사이의 값
        }
    }

}

//matrix 더하는 함수 구현

Matrix *addition_matrix(Matrix *matrix_a, Matrix *matrix_b){
    Matrix *result = create_matrix(matrix_a->row, matrix_a->col); //더한 행렬 result로 저장
    //2중 for문을 돌며 각 원소 더하기
    for (int i = 0; i < matrix_a->row; i++) {
        for (int j = 0; j < matrix_a->col; j++) {
            result->data[i][j] = matrix_a->data[i][j] + matrix_b->data[i][j];
        }
    }
    //result 반환
    return result;
}

//matrix 빼는 함수 구현
Matrix *subtraction_matrix(Matrix *matrix_a, Matrix *matrix_b){
   Matrix *result = create_matrix(matrix_a->row, matrix_a->col); //뺀 행렬 result로 저장
    //2중 for문 돌며 각 원소 빼기
    for (int i = 0; i < matrix_a->row; i++) {
        for (int j = 0; j < matrix_a->col; j++) {
            result->data[i][j] = matrix_a->data[i][j] - matrix_b->data[i][j];
        }
    }
    //result 반환
    return result;
}
//전치행렬 구하는 함수 구현
Matrix *transpose_matrix(Matrix *matrix) {
    Matrix *result = create_matrix(matrix->col, matrix->row); // 전치 행렬은 열과 행이 바뀐다
    //2중 for문 돌며 각 원소 바꿔서 result에 채우기
    for (int i = 0; i < matrix->row; i++) {
        for (int j = 0; j < matrix->col; j++) {
            result->data[j][i] = matrix->data[i][j]; // 행과 열을 바꿔서 채워 넣음
        }
    }
    //result 반환
    return result;
}

//matrix 곱셈 함수 구현
Matrix *multiply_matrix(Matrix *matrix_a, Matrix *matrix_b)
{
    // 행렬 곱셈이 불가능한 경우 걸러내기
    if (matrix_a->col != matrix_b->row) {
        printf("Invalid\n");
        exit(1);
    }

    Matrix *result = create_matrix(matrix_a->row, matrix_b->col); //곱한 행렬 result에 저장
    for (int i = 0; i < matrix_a->row; i++) {
        for (int j = 0; j < matrix_b->col; j++) {
            result->data[i][j] = 0;
            //곱셈을 위한 내부 for
            for (int k = 0; k < matrix_a->col; k++) {
               //matrix a의 i번째 행과 matrix b의 j번째 열의 요소를 곱해서 더하기
                result->data[i][j] += matrix_a->data[i][k] * matrix_b->data[k][j];
            }
        }
    }
    return result;
}

