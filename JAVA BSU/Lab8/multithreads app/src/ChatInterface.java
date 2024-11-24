import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ChatInterface extends Remote {
    public void register(ClientCallback client) throws Exception;

    public void sendMessage(String message) throws RemoteException;

}
