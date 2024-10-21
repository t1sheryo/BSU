package Lab6.stage1;

import java.io.Serial;
import java.io.Serializable;

public class Airplane extends CargoCarrier implements Serializable{

    @Serial
    private static final long serialVersionUID = 3L;

    public Airplane(String _model, int _speed){
        super(_model, CargoCarrierType.AIRPLANE, _speed);
    }

    public Airplane(String _model){
        super(_model, CargoCarrierType.AIRPLANE, 0);
    }

    public Airplane(){
        super("Unknown model", CargoCarrierType.AIRPLANE, -1);
    }
}
