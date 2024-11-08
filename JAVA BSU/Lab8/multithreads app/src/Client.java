import java.io.*;
import java.net.*;

public class Client extends Thread {
    private String SERVER_ADDRESS;
    private int SERVER_PORT;
    private Socket socket;
    private DataInputStream in;
    private DataOutputStream out;
    private volatile boolean IsRunning = true;


    public Client(String serverAddress, int serverPort) {
        this.SERVER_ADDRESS = serverAddress;
        this.SERVER_PORT = serverPort;
        //this.username = username;
    }

    @Override
    public void run(){
        //Socket socket = null;
        try {
            InetAddress IPAddress = InetAddress.getByName(SERVER_ADDRESS);
            socket = new Socket(IPAddress, SERVER_PORT);
            InputStream sin = socket.getInputStream();
            OutputStream sout = socket.getOutputStream();

            //DataInputStream in;
            //DataOutputStream out;
            in = new DataInputStream (sin);
            out = new DataOutputStream(sout);

//                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream())); // от сервера
//                PrintWriter out = new PrintWriter(socket.getOutputStream(), true); // на сервер
            BufferedReader consoleInput = new BufferedReader(new InputStreamReader(System.in));


            System.out.println("Print Username:");
            String line = consoleInput.readLine();
            String[] params = line.split(" ", 2);
            while(params.length < 2){
                System.out.println("Incorrect Username Protocol! Try again!");
                String Line = consoleInput.readLine();
                params = Line.split(" ", 2);
            }
            StringBuilder command = new StringBuilder(params[0]);
            StringBuilder username = new StringBuilder(params[1]);
            while(command.compareTo(new StringBuilder(ClientCommands.register)) != 0) {
                System.out.println("Incorrect Username Protocol! Try again!");
                String inputLine = consoleInput.readLine();
                String[] lineParams = inputLine.split(" ", 2);
                command.replace(0, command.length(), lineParams[0]);
                username.replace(0, username.length(), lineParams[1]);
            }
            out.writeUTF(String.valueOf(username));
            out.flush();

            new Thread(() -> {
                String serverMessage;
                try{
                    while(IsRunning){
                        if (in.available() > 0) {
                            serverMessage = in.readUTF();
                            System.out.println(serverMessage);
                        }
                    }
                } catch (IOException ex){
                    if (IsRunning) {
                        ex.printStackTrace();
                    }
                }
            }).start();

            String serverLine = consoleInput.readLine();
            String[] serverParams = serverLine.split(" ", 2);
            StringBuilder userCommand = new StringBuilder(serverParams[0]);
            StringBuilder userMessage = new StringBuilder();
            if(serverParams.length > 1) {
                userMessage.replace(0, userMessage.length(), serverParams[1]);
            }
            while(true){
                boolean incorrect = true;
                if(userCommand.compareTo(new StringBuilder(ClientCommands.send)) == 0) incorrect = false;
                if(userCommand.compareTo(new StringBuilder(ClientCommands.quit)) == 0) incorrect = false;
                while(incorrect){
                    System.out.println("Incorrect Message Protocol! Try again!");
                    String inputLine = consoleInput.readLine();
                    String[] lineParams = inputLine.split(" ", 2);
                    userCommand.replace(0, userCommand.length(), lineParams[0]);
                    if(lineParams.length > 1) {
                        userMessage.replace(0, userMessage.length(), lineParams[1]);
                    }
                    //incorrect = true;
                    if(userCommand.compareTo(new StringBuilder(ClientCommands.send)) == 0) incorrect = false;
                    if(userCommand.compareTo(new StringBuilder(ClientCommands.quit)) == 0) incorrect = false;
                }
                if(userCommand.compareTo(new StringBuilder(ClientCommands.send)) == 0){
                    out.writeUTF(String.valueOf(userMessage));
                    out.flush();
                }
                else if(userCommand.compareTo(new StringBuilder(ClientCommands.quit)) == 0){
                    out.writeUTF("QUIT");
                    out.flush();
                    IsRunning = false;
                    break;
                }
                String NewLine = consoleInput.readLine();
                String[] NewParams = NewLine.split(" ", 2);
                userCommand.replace(0, userCommand.length(), NewParams[0]);
                if(NewParams.length > 1) {
                    userMessage.replace(0, userMessage.length(), NewParams[1]);
                }
            }
        }
        catch (IOException ex){
            ex.printStackTrace();
        }
        finally {
            try{
                if (socket != null && !socket.isClosed()) {
                    socket.close();
                }
                if (in != null) {
                    in.close();
                }
                if (out != null) {
                    out.close();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }


}
