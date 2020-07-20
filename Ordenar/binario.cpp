 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <fstream>
 using namespace std;
 int combinacion(int[],char[],int,int,char[]);
 void universo(int);
 void menu();


 int main(){
 menu();
 return 0;
 }
 int combinacion(int i[], char r[],int l,int k,char b[]){
 	if(l == k){
 		r[l] = '\0';
 		ofstream archivo;
 		archivo.open("binario.txt",ios::app);
 		archivo<<r<<",";
 		return 0;
 	}
 	for(int j = 0; j<2;j++){
 		if(i[j] == 0)
 			continue;
 		r[l] = b[j];
 		i[j]--;
 		combinacion(i,r,l+1,k,b);

 		i[j]++;
 	}

 }
 void universo(int k){
 int r,p,nc,c,i,n,b,a,d = 0,n0= 0,n1= 0;
 char bin[2];
 bin[0] = '0';
 bin[1] = '1';
 ofstream fich("binario.txt");
 ofstream archivo;
 archivo.open("binario.txt",ios::app);
 if(k == -1){
 srand (time(NULL));
 r = rand()%1000+30;}
 if(k == 0)
 archivo <<"{e}";
 if(k == 1)
archivo <<"{e,0,1}";
 if(k == 2)
 archivo <<"{e,0,1,00,01,10,11}";
 if(k >2)
 r = k;
 archivo <<"{e,0,1,00,01,10,11,";
 archivo.close();
 for(p = 3; p<r ;p++){
 	char binario [p];
 	for( i = 0;i<=p;i++){
 		binario[i] = '0';
 		if (i == p)
 		binario[i] = '\0';
 	}
 	archivo.open("binario.txt",ios::app);
 	archivo << binario<< ",";
 	archivo.close();

 	for(nc = 1;nc<p; nc++){



 		for(a = 0; a<(p-nc);a++){
 			binario[a] = '0';
 			n0++;
 		}
 		for(a; a<p;a++){
 			binario[a] = '1';
 			n1++;

 		}
 		int cont[2];
 		cont[0] = n0;
 		cont[1] = n1;
 		char comb [k] ;
 		combinacion(cont,comb,0,p,bin);
 		n0 = 0;
 		n1 = 0;
 		}
 		for( i = 0;i<=p;i++){
 			binario[i] = '1';
 			if (i == p)
 			binario[i] = '\0';
 		}
 	archivo.open("binario.txt",ios::app);
 	archivo << binario<< ",";
 	archivo.close();
 	}
 	archivo<<"}";



 }
 void menu(){
 int opc = 0,k = 0;
 do{

 printf("1.-Introducir k manualmente\n");
 printf("2.-Automatico\n");
 printf("3.-Salir\n");
 scanf("%d",&opc);
 switch(opc){
 	case 1:
 		printf("Introdusca k");
 		scanf("%d",&k);
 		universo(k);
 		break;
 	case 2:
 		universo(-1);
 		break;
 	case 3:
 	exit(1);
 }
 }
 while(opc != 3);



 }




	
	

