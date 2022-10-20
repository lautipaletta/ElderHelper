#include <Wire.h>
#include <ADXL345.h>
#include <SimpleKalmanFilter.h>

SimpleKalmanFilter filtroX(2, 2, 0.01);
SimpleKalmanFilter filtroY(2, 2, 0.01);
SimpleKalmanFilter filtroZ(2, 2, 0.01);

ADXL345 accelerometer;
int contadorMediciones;

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

  contadorMediciones = 0;
}

void loop(void) 
{  
  // Output normalized m/s^2
  if (contadorMediciones == 0) {      
    Serial.print("Midiendo en ");
    for (int i = 3; i > 0; i--) {
      Serial.print(i);
      Serial.print("...");
      delay(1000); 
    }
    Serial.println("");
    Serial.print("{");
  }

  Vector norm = accelerometer.readNormalize();

  float filtradoX = filtroX.updateEstimate(norm.XAxis);
  float filtradoY = filtroY.updateEstimate(norm.YAxis);
  float filtradoZ = filtroZ.updateEstimate(norm.ZAxis);

  float moduloSuma = sqrt(pow(filtradoX, 2) + pow(filtradoY, 2) + pow(filtradoZ, 2));

  Serial.print(moduloSuma);
  Serial.print(",");

  contadorMediciones++;
  delay(15);
  
  if (contadorMediciones == 100) {
    Serial.println("}");
    contadorMediciones = 0;
  }
}
