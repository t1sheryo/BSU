import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class ChatClient extends UnicastRemoteObject implements ClientCallback {
    private String name;
    private ChatInterface chatService;

    protected ChatClient(String name, ChatInterface chatService) throws RemoteException {
        super();
        this.name = name;
        this.chatService = chatService;
    }

    @Override
    public void receiveMessage(String message) throws RemoteException {
        System.out.println(message);
    }

    public void start() {
        try {
            chatService.register(this);
            Scanner scanner = new Scanner(System.in);
            System.out.println("Connected to chat. Type messages below:");

            while (true) {
                String message = scanner.nextLine();
                if ("QUIT".equalsIgnoreCase(message)) {
                    System.out.println("Exiting chat...");
                    break;
                }
                chatService.sendMessage(name + ": " + message);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        try {
            System.out.println("Enter your name:");
            Scanner scanner = new Scanner(System.in);
            String name = scanner.nextLine();

            ChatInterface chatService = (ChatInterface) Naming.lookup("rmi://localhost/ChatService");
            ChatClient client = new ChatClient(name, chatService);
            client.start();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
