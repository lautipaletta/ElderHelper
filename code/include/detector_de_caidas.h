#ifndef detector_de_caidas
#define detector_de_caidas

#include <Arduino.h>

#include <Wire.h>
#include <ADXL345.h>
#include <SimpleKalmanFilter.h>
#include <Arduino_KNN.h>

#include "filoArray.h"

#define CAIDA_ADELANTE 2
#define CAIDA_COSTADO 3
#define ACTIVIDAD_CHILL 4
#define ACTIVIDAD_NO_CHILL 5

String mapToTipo(int actividad);
void inicializarDetectorDeCaidas();
bool dispositivoEnEstadoCaida();

#endif
