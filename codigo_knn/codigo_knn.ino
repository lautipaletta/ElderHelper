#include <Wire.h>
#include <ADXL345.h>
#include <SimpleKalmanFilter.h>
#include <Arduino_KNN.h>

#include "mediciones.h"
#include "filoArray.h"

SimpleKalmanFilter filtroX(2, 2, 0.01);
SimpleKalmanFilter filtroY(2, 2, 0.01);
SimpleKalmanFilter filtroZ(2, 2, 0.01);

ADXL345 accelerometer;

KNNClassifier modeloKnn(100);
#define CAIDA_ADELANTE 2
#define CAIDA_COSTADO 3
#define ACTIVIDAD_CHILL 4
#define ACTIVIDAD_NO_CHILL 5

filoArray dataArr;

String mapToTipo(int actividad) {
  switch (actividad) {
    case CAIDA_ADELANTE: return "Caida adelante"; break;
    case CAIDA_COSTADO: return "Caida costado"; break;
    case ACTIVIDAD_CHILL: return "Actividad chill"; break;
    case ACTIVIDAD_NO_CHILL: return "Actividad NO chill"; break;
    default: return "no se"; break;
  }
}

bool inEstadoCaida;

void setup(void) 
{
  Serial.begin(115200);

  Serial.println("Inicializando ADXL345");
  if (!accelerometer.begin())
  {
    Serial.println("No se encontro el ADXL345!! :(");
    delay(500);
  }

  accelerometer.setRange(ADXL345_RANGE_16G);

  for (int i = 0; i < 15; i++) modeloKnn.addExample(caidas_adelante[i], CAIDA_ADELANTE);
  for (int i = 0; i < 11; i++) modeloKnn.addExample(caidas_costado[i], CAIDA_COSTADO);
  for (int i = 0; i < 17; i++) modeloKnn.addExample(actividad_chill[i], ACTIVIDAD_CHILL);
  for (int i = 0; i < 15; i++) modeloKnn.addExample(actividad_notanchill[i], ACTIVIDAD_NO_CHILL);

  dataArr.initializeTo(10);

  inEstadoCaida = false;
}

void loop(void) 
{
  Vector norm = accelerometer.readNormalize();

  float filtradoX = filtroX.updateEstimate(norm.XAxis);
  float filtradoY = filtroY.updateEstimate(norm.YAxis);
  float filtradoZ = filtroZ.updateEstimate(norm.ZAxis);

  float moduloSuma = sqrt(pow(filtradoX, 2) + pow(filtradoY, 2) + pow(filtradoZ, 2));

  dataArr.insertValue(moduloSuma);

  int clasificacion = modeloKnn.classify(dataArr.getDataPointer(), 5);
  
  if ((clasificacion == CAIDA_ADELANTE || clasificacion == CAIDA_COSTADO) && !inEstadoCaida) {
    Serial.println("Se cayo el Paletta");
    inEstadoCaida = true;
  }

  if (clasificacion == ACTIVIDAD_CHILL || clasificacion == ACTIVIDAD_NO_CHILL) inEstadoCaida = false;

  delay(15);
}
