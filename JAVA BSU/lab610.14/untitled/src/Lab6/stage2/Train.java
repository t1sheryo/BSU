package Lab6.stage2;

import java.io.Serial;
import java.io.Serializable;

public class Train extends CargoCarrier implements Serializable{

    @Serial
    private static final long serialVersionUID = 2L;

    public Train(String _model, int _speed){
        super(_model, CargoCarrierType.TRAIN, _speed);
    }

    public Train(String _model){
        super(_model, CargoCarrierType.TRAIN, 0);
    }

    public Train(){
        super("Unknown model", CargoCarrierType.TRAIN, -1);
    }
}
