// Marco Rondón, 1794984. Mario Roda, 1792216

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nom[20];
  char estacio[35];
  int alt;
  float tmtj, tmxm, tmnm, tmx, tmn;
} MetCom;

void maxmin(MetCom llista[], unsigned num_elements, float *t_max, float *t_min, unsigned *p_max, unsigned *p_min);
void mitj_temperatures(MetCom llista[], unsigned num_elements, float *tm_max, float *tm_min);

int main() {
  FILE *meteo;
  MetCom *comarca;
  unsigned i = 0, numcom = 0, *p_min, *p_max;
  int ll;
  float *t_max, *t_min, *tm_max, *tm_min;

  if ((meteo = fopen("MeteoCat2024.txt", "r")) == NULL) {
    printf("No es pot obrir el fitxer\n");
    return 1;
  }

  while ((ll = fgetc(meteo)) != EOF) {
    if (ll == '\n') {
      numcom++;
    }
  }
  printf("\nDades de %d comarques\n", numcom);

  rewind(meteo);

  if ((comarca = (MetCom *)malloc(numcom * sizeof(MetCom))) == NULL) {
    printf("\nNo es possible assignar la memoria necessaria...\n\n");
    return 1;
  }

  for (i = 0; i < numcom; i++) {
    fscanf(meteo, "%19[a-zA-Z'. -];", comarca[i].nom);
    fscanf(meteo, "%34[a-zA-Z'. -];", comarca[i].estacio);
    fscanf(meteo, "%d;", &comarca[i].alt);
    fscanf(meteo, "%f;", &(comarca[i].tmtj));
    fscanf(meteo, "%f;", &(comarca[i].tmxm));
    fscanf(meteo, "%f;", &(comarca[i].tmnm));
    fscanf(meteo, "%f;", &(comarca[i].tmx));
    fscanf(meteo, "%f\n", &(comarca[i].tmn));
  }
  printf("Fi de la lectura.....\n\n");

  fclose(meteo);

  printf("   Comarca              Estacio                             Max         Min\n");
  printf("============================================================================\n");
  for (i = 0; i < numcom; i++) {
    printf("%2u ", i + 1);
    printf("%-20s ", comarca[i].nom);
    printf("%-35s ", comarca[i].estacio);
    printf("%-.1f", comarca[i].tmx);
    printf("\t%-.1f", comarca[i].tmn); // afegim les temperatures mínimes
    printf("\n");
  }

  // codi propi
  // reserva de memòria
  t_max = (float *)malloc(sizeof(float));
  t_min = (float *)malloc(sizeof(float));
  tm_max = (float *)malloc(sizeof(float));
  tm_min = (float *)malloc(sizeof(float));
  
  p_max = (unsigned *)malloc(sizeof(unsigned));
  p_min = (unsigned *)malloc(sizeof(unsigned));

  // anunciem les funcions que utilitzarem
  maxmin(comarca, numcom, t_max, t_min, p_max, p_min);
  mitj_temperatures(comarca, numcom, tm_max, tm_min);

  printf("\nLa mitjana de temperatures màximes (tm_max) és: %.2f °C\n", *tm_max);
  printf("La mitjana de temperatures mínimes (tm_min) és: %.2f °C\n\n", *tm_min);
  // alliberem els espais de memòria
  free(t_max);
  free(t_min);
  free(tm_max);
  free(tm_min);
  free(p_max);
  free(p_min);
  free(comarca);
  return 0;
}
// definim la funció per calcular la mitjana de temperatures màximes i mínimes
void mitj_temperatures(MetCom llista[], unsigned num_elements, float *tm_max, float *tm_min){
  unsigned j;
  float suma_max = 0.;
  float suma_min = 0.;
  for (j = 0; j < num_elements; j++){ // amb un bulce acumulem la suma de les temperatures
    suma_max += llista[j].tmx;
    suma_min += llista[j].tmn;
  }
  // fem la mitjana de les màximes i mínimes
  *tm_max = (suma_max / num_elements);
  *tm_min = (suma_min / num_elements);
}

// definim la funció per calcular la temperatura màxima
void maxmin(MetCom llista[], unsigned num_elements, float *t_max, float *t_min, unsigned *p_max, unsigned *p_min){
  unsigned j;
  *t_min = llista[0].tmn;
  *t_max = llista[0].tmx;
  *p_min = *p_max = 0;
  
  for (j=0; j < num_elements; j++){
    if (llista[j].tmn < *t_min){ // si la temperatura actual és menor que la mínima guardem aquesta com la nova mínima
      *t_min = llista[j].tmn;
      *p_min = j;
    }
    if (llista[j].tmx > *t_max){ // el mateix raonament amb les temperatures màximes
      *t_max = llista[j].tmx;
      *p_max = j;
    }
  }
}
