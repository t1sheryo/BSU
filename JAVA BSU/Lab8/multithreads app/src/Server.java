import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.HashSet;
import java.util.Set;

public class Server extends UnicastRemoteObject implements ChatInterface {
    private Set<ClientCallback> clients = new HashSet<>();

    protected Server() throws RemoteException {
        super();
    }

    @Override
    public synchronized void register(ClientCallback client) throws RemoteException {
        clients.add(client);
        System.out.println("New client registered.");
    }

    @Override
    public synchronized void sendMessage(String message) throws RemoteException {
        System.out.println("Broadcasting: " + message);
        for (ClientCallback client : clients) {
            client.receiveMessage(message);
        }
    }

    public static void main(String[] args) {
        try {
            Server server = new Server();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("ChatService", server);
            System.out.println("Chat server started...");
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }
}
