package Lab6.stage2;

import java.io.Serial;
import java.io.Serializable;

public class Car extends CargoCarrier implements Serializable{

    @Serial
    private static final long serialVersionUID = 1L;

    public Car(String _model, int _speed){
        super(_model, CargoCarrierType.CAR, _speed);
    }

    public Car(String _model){
        super(_model, CargoCarrierType.CAR, 0);
    }

    public Car(){
        super("Unknown model", CargoCarrierType.CAR, -1);
    }
}
