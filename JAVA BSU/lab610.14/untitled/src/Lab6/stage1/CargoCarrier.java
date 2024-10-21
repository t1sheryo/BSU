package Lab6.stage1;

import java.io.Serial;
import java.io.Serializable;

public class CargoCarrier implements Serializable {

    @Serial
    private static final long serialVersionUID = 0L;
    private String model = "";
    private CargoCarrierType type;
    private int speed;

    protected CargoCarrier(String _model, CargoCarrierType _type, int _speed){
        this.model = _model;
        this.type = _type;
        this.speed = _speed;
    }

    public String getModel() { return this.model; }

    public CargoCarrierType getType() { return this.type; }

    public int getSpeed() { return this.speed; }

    public String toString() {
        return "Type: " + this.type.toString() + "; Model: " + this.model + "; Speed: " + this.speed;
    }

    public void setSpeed(int _speed){
        this.speed = _speed;
    }

}
