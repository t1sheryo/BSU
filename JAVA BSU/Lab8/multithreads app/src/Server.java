import java.io.*;
import java.net.*;
import java.util.*;

public class Server extends Thread {
    private static final int server_port = 1488;
    private static List<ClientHandler> clients = new ArrayList<>();
    private Socket socket;
    private int num;

    public Server(int num, Socket socket) {
        this.num = num;
        this.socket = socket;
        setDaemon(true);
        setPriority(NORM_PRIORITY);
    }

    @Override
    public void run() {
        try {
            InputStream sin = socket.getInputStream();
            OutputStream sout = socket.getOutputStream();
            DataInputStream dis = new DataInputStream(sin);
            DataOutputStream dos = new DataOutputStream(sout);

            String clientName = dis.readUTF();
            ClientHandler clientHandler = new ClientHandler(clientName, dis, dos);
            clients.add(clientHandler);
            for (ClientHandler client : clients) {
                try {
                    client.getOutputStream().writeUTF("Welcome to chat, " + clientName);
                    client.getOutputStream().flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            System.out.println("The client '" + clientName + "' has connected");

            while (true) {
                try {
                    String message = dis.readUTF();
                    if ("QUIT".equalsIgnoreCase(message)) {
                        clients.remove(clientHandler);
                        for (ClientHandler client : clients) {
                            try {
                                client.getOutputStream().writeUTF("The client '" + clientName + "' has quit");
                                client.getOutputStream().flush();
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        }
                        System.out.println("The client '" + clientName + "' has quit");
                        break;
                    }
                    broadcastMessage(clientName + ": " + message);
                    System.out.println(clientName + ": " + message);
                } catch (SocketException e) {
                    System.out.println("The client '" + clientName + "' has disconnected");
                    clients.remove(clientHandler);
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                socket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void broadcastMessage(String message) {

        for (ClientHandler client : clients) {
            try {
                client.getOutputStream().writeUTF(message);
                client.getOutputStream().flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ServerSocket srvSocket = null;
        try {
            InetAddress ia = InetAddress.getByName("127.0.0.1");
            srvSocket = new ServerSocket(server_port, 0, ia);
            System.out.println("Server started\n");

            int i = 0;
            while (true) {
                Socket socket = srvSocket.accept();
                System.out.println("Client accepted");
                new Server(i++, socket).start();
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (srvSocket != null)
                    srvSocket.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

class ClientHandler {
    private String name;
    private DataInputStream inputStream;
    private DataOutputStream outputStream;

    public ClientHandler(String name, DataInputStream inputStream, DataOutputStream outputStream) {
        this.name = name;
        this.inputStream = inputStream;
        this.outputStream = outputStream;
    }

    public String getName() {
        return name;
    }

    public DataInputStream getInputStream() {
        return inputStream;
    }

    public DataOutputStream getOutputStream() {
        return outputStream;
    }
}