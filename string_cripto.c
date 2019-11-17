//
//  main.c
//  string_cripto
//
//  Created by Martina Astara on 13/11/2019.
//  Copyright © 2019 Marco Astara. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
char crittografiaCesareDec(int chiave,char valore){
    char decodificato;
    int min=0;
    //verifico se il caratte stringaCodificata[i] è minuscolo, maiuscolo o un carattere diverso
    //imposto il valore minimo che non deve essere raggiunto da valore-chiave (A=65,a=97)
    if (valore>64&&valore<91) {
        min=65;
           }else if (valore>96&&valore<123){
               min=97;
           }else{
               //nel caso in cui ci sia un valore diverso dal quelli dell'alfabeto lo invio senza modificarlo
               return valore;
           }
    if ((int)valore-chiave<min) {
        //se minore di min allora abbiamo superato a perciò aggiungo a 65 il numero di lettere +1 per ripartite dalla nostra z
        decodificato=(char)(valore-chiave+26);
        //printf("ciao\n");
    }else{
        //senno modifico tranquillamente
        decodificato=(char)(valore-chiave);
    }
    
    return decodificato;
}
char crittografiaCesareCod(int chiave,char valore){
    char codificato;
    int max=0;
    //verifico se il caratte stringaDecodificata[i] è minuscolo, maiuscolo o un carattere diverso
    //imposto il valore massimo che non deve essere raggiunto da valore+chiave (Z=90,z=90)
    
    if (valore>64&&valore<91) {
        max=90;
           }else if (valore>96&&valore<123){
               max=122;
           }else{
               //nel caso in cui ci sia un valore diverso dal quelli dell'alfabeto lo invio senza modificarlo
               return valore;
           }
    if ((int)valore+chiave>max) {
        //se maggiore di max allora abbiamo superato z perciò sottraggo a 90 il numero di lettere +1 per ripartite dalla nostra a
        codificato=(char)(valore+chiave-26);
        //printf("ciao\n");
    }else{
        //senno modifico tranquillamente
        codificato=(char)(valore+chiave);
    }
    
    return codificato;
}
int minuscoloANDconta(char *puntatore){
    int i=0;
    for (i=0; i<puntatore[i]; i++) {
        puntatore[i]=_tolower(puntatore[i]);
    }
    return i;
}
char alfabeto[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
void creaAlfabetoMescolato(char *chiave,int count){
    
    //-1 poichè un indice va da 0 a n-1
    //parto dall'ultimo indice per evitare di dover trascrivere
    for (int i=count-1;i>=0 ; i--) {
        //scorro per ogni elemento di chiave l'alfabeto, al fine di trovare il valore di chiave[i] nell'alfabeto
        for (int j=0; j<27; j++) {
            //ogni volta che troviamo il valore dobbiamo scorrere il precedente e i suo precedessori
            if (chiave[i]==alfabeto[j]) {
                //printf("chiave:%c alfabeto:%c\n",chiave[i],alfabeto[j]);
                //scorro l'alfabeto al contrario per modificare tutte le lettere precedenti
                while(j!=0){
                    alfabeto[j]=alfabeto[j-1];
                    j--;
                }
                //prendo il primo valore di alfabeto e ci inserisco la chiave
                //p.s. posso scriverlo qui poiche scorro la chiave al contrario perciò inserisco prima l'ultimo valore fino ad arrivare al primo
                alfabeto[0]=chiave[i];
                j=26;
            }
        }
    }
    
    //printf("%s",*alfabeto);
    
}
void Sostituzione(int NumText,char* testo){
    printf("testo funzione: %s",testo);
    int indice=0;
    //aggiungendo uno all'indice della condizione evitiamo di ripetere l'operazione per \n
      for (int i=0; i<NumText; i++) {
          //se il nostro testo[i] è un carattere gli tolgo 97 senno ritrascrivo il valore (ES. ? , : ! ecc...)
          //prendo il nostro carattere e gli sottraggo 'a' in modo tale da avere l'indice di collocazione nell'alfabeto originale (a,b,c,d,e,f,g,...,z)
          //inserisco la nostra posizione nell'alfabeto modificato con la chiave, per avere la corrispondenza in esso
          if (testo[i]<123&&testo[i]>96) {
              indice=testo[i]-97;
              testo[i]=alfabeto[indice];
          }
          //imposto che il valore successivo sia uguale \0 al fine di evitare che vengano stampate anche variabili non appartenenti a testoCodificato
                    //printf("testo: %c\nindice: %d\n",testo[i],indice);
      }
    
}
int main(int argc, const char * argv[]) {
    char k[28];
    int chiave=27;
    char testo[256];
    char scelta;
    char TestoCodificato[256];
    int count=0,NumText=0;
    printf("inserisci testo da codificare:\n");
    fgets(testo,sizeof(testo),stdin);
    NumText=minuscoloANDconta(testo);
   // printf("%s",testo);
    printf("inserisci come vuoi codificare il tuo testo:\n");
    printf("a) cifrario di cesare \n");
    printf("b) cifrario a sostituzione \n");
    printf("digita un valore qualunque per terminare il programma\n");
    scanf("%c",&scelta);
    switch (scelta) {
        case 'a':
            printf("inserisci chiave numerica:\n");
            do{
                fgets(k,sizeof(k),stdin);
                //se il valore di k sono più elementi interi (es 310) prende solamente il primo numero digitato
            } while(k[0]<='2'||k[0]>='9');
            //tolgo 48 al caratte (48=0)
            chiave=(int)k[0]-48;
            for (int i=0; i<NumText; i++) {
                TestoCodificato[i]=crittografiaCesareCod(chiave,testo[i]);
            }
            printf("%s",TestoCodificato);
            break;
        case 'b':
            printf("inserisci chiave o digita tutto l'alfabeto con grandezza minore di 27\n");
            fgets(k, sizeof(k), stdin);
            do{
                //se sbagli a scrivere e poi cancelli comunque sia prende prima i valori vecchi
            fgets(k, sizeof(k), stdin);
                //conto il numero di char in k per verificare che abbiano inserito un alfabeto oppure una parola
                count=minuscoloANDconta(k);
                //verifico che non sia maggiore di 26
                //se vero ripete
            }while(count>26);
            //conto il numero di lettere nel testo
            
            //sostituisco i valori dell'alfabeto originale in base alla nostra chiave
            creaAlfabetoMescolato(k,count);
            Sostituzione(NumText,testo);
            //printf("%s\n",alfabeto);
            printf("%s\n",testo);
            break;
            
        default:
            printf("hai scelto di terminare il programma.\n");
            break;
    }
    return 0;
}
