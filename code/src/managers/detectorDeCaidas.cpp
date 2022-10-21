#include "mediciones.h"
#include "filoArray.h"
#include "detectorDeCaidas.h"

String mapToTipo(int actividad) {
    switch (actividad) {
        case CAIDA_ADELANTE: return "Caida adelante"; break;
        case CAIDA_COSTADO: return "Caida costado"; break;
        case ACTIVIDAD_CHILL: return "Actividad chill"; break;
        case ACTIVIDAD_NO_CHILL: return "Actividad NO chill"; break;
        default: return "no se"; break;
    }
}

void inicializarDetectorDeCaidas() 
{
    Serial.println("Inicializando ADXL345");
    if (!accelerometro.begin())
    {
        Serial.println("No se encontro el ADXL345!! :(");
        delay(500);
    }

    accelerometro.setRange(ADXL345_RANGE_16G);

    for (int i = 0; i < 15; i++) modeloKnn.addExample(caidas_adelante[i], CAIDA_ADELANTE);
    for (int i = 0; i < 11; i++) modeloKnn.addExample(caidas_costado[i], CAIDA_COSTADO);
    for (int i = 0; i < 17; i++) modeloKnn.addExample(actividad_chill[i], ACTIVIDAD_CHILL);
    for (int i = 0; i < 15; i++) modeloKnn.addExample(actividad_notanchill[i], ACTIVIDAD_NO_CHILL);

    dataArr.initializeTo(10);

    inEstadoCaida = false;
}

bool dispositivoEnEstadoCaida() 
{
    Vector norm = accelerometro.readNormalize();

    float filtradoX = filtroX.updateEstimate(norm.XAxis);
    float filtradoY = filtroY.updateEstimate(norm.YAxis);
    float filtradoZ = filtroZ.updateEstimate(norm.ZAxis);

    float moduloSuma = sqrt(pow(filtradoX, 2) + pow(filtradoY, 2) + pow(filtradoZ, 2));

    dataArr.insertValue(moduloSuma);

    int clasificacion = modeloKnn.classify(dataArr.getDataPointer(), 5);

    if ((clasificacion == CAIDA_ADELANTE || clasificacion == CAIDA_COSTADO) && !inEstadoCaida) {
        inEstadoCaida = true;
    }

    if (clasificacion == ACTIVIDAD_CHILL || clasificacion == ACTIVIDAD_NO_CHILL) inEstadoCaida = false;

    return inEstadoCaida;
}
