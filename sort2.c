#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 2147483648

int main(int argc, char* argv[]){

  FILE *inputfp;//入力ファイル
  FILE *outputfp;//出力ファイル

  if (argc != 3) { //引数のエラー処理
    printf("Usage: %s <入力ファイル名> <出力ファイル名>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char* inputname = argv[1];//入力ファイル名
  char* outputname = argv[2];//出力ファイル名
  long long int filesize;//ファイルサイズ

  /*ファイルサイズ計算*/
  inputfp = fopen(inputname, "rb");
  fseek(inputfp,0,SEEK_END);
  fgetpos(inputfp,&filesize);
  printf("filesize = %lld\n",filesize); //ファイルサイズ出力

    
  long long int intint = filesize/sizeof(int); //整数の個数
  int fornum=32;   
  int size = MAX / fornum; //配列のサイズ
  int current;
  int array_current;
  int write_current; 

 
  /*書き込み用ファイルを開く*/   
  outputfp = fopen(outputname,"wb");
  if(outputfp == NULL){
    printf("ファイルが開きません。\n");
    exit(EXIT_FAILURE);
  } 
  int* array = (int *)malloc(size*sizeof(int));
  
  for(int i = 0; i < fornum ; i++){

    /*読み込み用ファイルを開く*/   
    inputfp = fopen(inputname,"rb");
    if(inputfp == NULL){
      printf("ファイルが開けません。\n");
      exit(EXIT_FAILURE);
    }

    for(int i = 0; i < size; i++){//全部0に
      array[i] = 0;
    }
        
    /*ファイルの中の数字全てチェックして、数をカウント*/
    for(long long int j = 0; j < intint; j++){
      fread(&current, sizeof(int), 1, inputfp);
      if(current>= size*i && current<=size*(i+1)-1){
	array_current = current-size*i;
	array[array_current]++;
      }
    }
      

    /*書き込む*/  
    for(int j=0;j<size;j++){
      write_current=size*i+j;
      if(array[j] != 0){
	for(int k=0;k<array[j];k++){
	  fwrite(&write_current,sizeof(int),1,outputfp);
	}
      }
    }
      
     
    fclose(inputfp);
  }
    
  free(array);
  fclose(outputfp);

  FILE *outputfp2;

  /*読み込み用ファイルを開く*/   
  outputfp2 = fopen(outputname,"rb");
  if(outputfp2 == NULL){
    printf("ファイルが開けません。\n");
    exit(EXIT_FAILURE);
  }
  int x;
  for(int i=0;i<intint;i++){
  fread(&x, sizeof(int), 1, outputfp2);
  printf("%d = %d\n",i,x);
  }
  fclose(outputfp2);
      


  return 0;
}
